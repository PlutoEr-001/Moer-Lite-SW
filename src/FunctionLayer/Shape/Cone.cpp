#include "Cone.h"
#include "ResourceLayer/Factory.h"

bool Cone::rayIntersectShape(Ray &ray, int *primID, float *u, float *v) const {
    //* todo 完成光线与圆柱的相交 填充primId,u,v.如果相交，更新光线的tFar
    //* 1.光线变换到局部空间
    //* 2.联立方程求解
    //* 3.检验交点是否在圆锥范围内
    //* 4.更新ray的tFar,减少光线和其他物体的相交计算次数
    //* Write your code here.
    /*
     * let cc = Point3::new(0.0, 0.0, self.height);
        let co: V3f = o - cc;
        let pw2_cos = self.cos_theta * self.cos_theta;
        let a = -d.z * -d.z - pw2_cos; // (d . v)^2 - cos^2 theta.
        let b = 2.0 * (-d.z * -co.z - d.dot(co) * pw2_cos);
        let c = -co.z * -co.z - co.dot(co) * pw2_cos;
     */
    Ray local_ray=this->transform.inverseRay(ray);
    Vector3f V(0.0,0.0,-1.0);
    Vector3f CO(local_ray.origin[0],local_ray.origin[1],local_ray.origin[2]-this->height);
    float t0,t1;
    float square_Theta=this->cosTheta*this->cosTheta;
    float a= dot(local_ray.direction,V)*dot(local_ray.direction,V)-square_Theta;
    float b=2*(dot(local_ray.direction,V)* dot(CO,V)- dot(local_ray.direction,CO)*square_Theta);
    float c=dot(CO,V)*dot(CO,V)-dot(CO,CO)*square_Theta;
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
void Cone::fillIntersection(float distance, int primID, float u, float v, Intersection *intersection) const {
    /// ----------------------------------------------------
    //* todo 填充圆锥相交信息中的法线以及相交位置信息
    //* 1.法线可以先计算出局部空间的法线，然后变换到世界空间
    //* 2.位置信息可以根据uv计算出，同样需要变换
    //* Write your code here.
    /// ----------------------------------------------------
    float angle =u*this->phiMax;
    Point3f m(this->radius*(1.0-v)* cosf(angle),this->radius*(1.0-v)* sinf(angle),v*this->height);
    intersection->position=this->transform.toWorld(m);
    Vector3f cm(m[0],m[1],m[2]-this->height);
    Point3f k(0.0,0.0,this->height-cm.length()/this->cosTheta);
    Vector3f km(m[0],m[1],m[2]-k[2]);
    km=normalize(km);
    intersection->normal=this->transform.toWorld(km);
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

void Cone::uniformSampleOnSurface(Vector2f sample, Intersection *result, float *pdf) const {

}

Cone::Cone(const Json &json) : Shape(json) {
    radius = fetchOptional(json, "radius", 1.f);
    height = fetchOptional(json, "height", 1.f);
    phiMax = fetchOptional(json, "phi_max", 2 * PI);
    float tanTheta = radius / height;
    cosTheta = sqrt(1/(1+tanTheta * tanTheta));
    //theta = fetchOptional(json,)
    AABB localAABB = AABB(Point3f(-radius,-radius,0),Point3f(radius,radius,height));
    boundingBox = transform.toWorld(localAABB);
    boundingBox = AABB(Point3f(-100,-100,-100),Point3f(100,100,100));
}

REGISTER_CLASS(Cone, "cone")
