#include "Cylinder.h"

#include <cmath>
#include "ResourceLayer/Factory.h"
bool Cylinder::rayIntersectShape(Ray &ray, int *primID, float *u, float *v) const {
    //* todo 完成光线与圆柱的相交 填充primId,u,v.如果相交，更新光线的tFar
    //* 1.光线变换到局部空间
    //* 2.联立方程求解
    //* 3.检验交点是否在圆柱范围内
    //* 4.更新ray的tFar,减少光线和其他物体的相交计算次数
    //* Write your code here.
    Ray local_ray=this->transform.inverseRay(ray);
    float t0,t1;
    float a=local_ray.direction[0]*local_ray.direction[0]+local_ray.direction[1]*local_ray.direction[1];
    float b=2*(local_ray.origin[0]*local_ray.direction[0]+local_ray.origin[1]*local_ray.direction[1]);
    float c=local_ray.origin[0]*local_ray.origin[0]+local_ray.origin[1]*local_ray.origin[1]-this->radius*this->radius;
    bool legal=Quadratic(a,b,c,&t0,&t1);
    if(!legal) return false;
    Point3f p_near=local_ray.at(t0),p_far=local_ray.at(t1);
    double res;
    //t0<t1
    if(t0<local_ray.tNear||t0>local_ray.tFar) goto T1;
    if(p_near[2]<0||p_near[2]>this->height) goto T1;
    res= std::atan2(p_near[1],p_near[0]);
    if(res<0) res+=2*PI;
    if(res>this->phiMax) goto T1;
    ray.tFar=t0;
    *u=res/this->phiMax;
    *v=p_near[2]/this->height;
    return true;
    T1:
    if(t1<local_ray.tNear||t1>local_ray.tFar) return false;
    if(p_far[2]<0||p_far[2]>this->height) return false;
    res= std::atan2(p_far[1],p_far[0]);
    if(res<0) res+=2*PI;
    if(res>this->phiMax) return false;
    ray.tFar=t1;
    *u=res/this->phiMax;
    *v=p_far[2]/this->height;
    return true;
}

void Cylinder::fillIntersection(float distance, int primID, float u, float v, Intersection *intersection) const {
    /// ----------------------------------------------------
    //* todo 填充圆柱相交信息中的法线以及相交位置信息
    //* 1.法线可以先计算出局部空间的法线，然后变换到世界空间
    //* 2.位置信息可以根据uv计算出，同样需要变换
    //* Write your code here.
    /// ----------------------------------------------------
    float angle =u*this->phiMax;
    Point3f p(this->radius* cosf(angle), this->radius* sinf(angle),v*this->height);
    intersection->position=this->transform.toWorld(p);
    Vector3f local_normal(cosf(angle), sinf(angle), 0.0);
    intersection->normal=this->transform.toWorld(local_normal);
    intersection->shape = this;
    intersection->distance = distance;
    intersection->texCoord = Vector2f{u, v};
    Vector3f tangent{1.f, 0.f, .0f};
    Vector3f bitangent;
    if (std::abs(dot(tangent, intersection->normal)) > .9f) {
        tangent = Vector3f(.0f, 1.f, .0f);
    }
    bitangent = normalize(cross(tangent, intersection->normal));
    tangent = normalize(cross(intersection->normal, bitangent));
    intersection->tangent = tangent;
    intersection->bitangent = bitangent;
}

void Cylinder::uniformSampleOnSurface(Vector2f sample, Intersection *result, float *pdf) const {

}

Cylinder::Cylinder(const Json &json) : Shape(json) {
    radius = fetchOptional(json,"radius",1.f);
    height = fetchOptional(json,"height",1.f);
    phiMax = fetchOptional(json,"phi_max",2 * PI);
    AABB localAABB = AABB(Point3f(-radius,-radius,0),Point3f(radius,radius,height));
    boundingBox = transform.toWorld(localAABB);
}

REGISTER_CLASS(Cylinder,"cylinder")
