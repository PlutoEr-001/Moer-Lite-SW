#include "Parallelogram.h"
#include <ResourceLayer/Factory.h>
Parallelogram::Parallelogram(const Json &json) : Shape(json) {
  base = fetchRequired<Point3f>(json, "base");
  edge0 = fetchRequired<Vector3f>(json, "edge0");
  edge1 = fetchRequired<Vector3f>(json, "edge1");

  base = transform.toWorld(base);
  edge0 = transform.toWorld(edge0);
  edge1 = transform.toWorld(edge1);

  //* 计算AABB包围盒
  Point3f vertices[4];
  vertices[0] = base;
  vertices[1] = vertices[0] + edge0;
  vertices[2] = vertices[1] + edge1;
  vertices[3] = vertices[0] + edge1;
  pMin = pMax = vertices[0]; // 初始化
  for (int dim = 0; dim < 3; ++dim) {
    for (int i = 1; i < 4; ++i) {
      pMin[dim] = std::min(pMin[dim], vertices[i][dim]);
      pMax[dim] = std::max(pMax[dim], vertices[i][dim]);
    }
  }
}

bool Parallelogram::rayIntersectShape(const Ray &ray, float *distance,
                                      int *primID, float *u, float *v) const {
  Point3f origin = ray.origin;
  Vector3f direction = ray.direction;
  Vector3f paralNormal = normalize(cross(edge0, edge1));
  float d = -dot(paralNormal, Vector3f{base[0], base[1], base[2]});
  float a = dot(paralNormal, Vector3f{origin[0], origin[1], origin[2]}) + d;
  float b = dot(paralNormal, direction);
  if (b == .0f)
    return false; // miss
  float t = -a / b;

  if (t < ray.tNear || t > ray.tFar)
    return false;

  Point3f hitpoint = origin + t * direction;
  // hitpoint = base + u * e0 + v * e1, 0 <= u, v <= 1
  Vector3f v1 = cross(hitpoint - base, edge1), v2 = cross(edge0, edge1);
  float u_ = v1.length() / v2.length();
  if (dot(v1, v2) < 0)
    u_ *= -1;

  v1 = cross(hitpoint - base, edge0);
  v2 = cross(edge1, edge0);
  float v_ = v1.length() / v2.length();
  if (dot(v1, v2) < 0)
    v_ *= -1;

  if (0.f <= u_ && u_ <= 1.f && 0.f <= v_ && v_ <= 1.f) {
    *distance = t;
    *primID = 0;
    *u = u_;
    *v = v_;
    return true;
  }

  return false;
}

void Parallelogram::fillIntersection(float distance, int primID, float u,
                                     float v,
                                     Intersection *intersection) const {
  intersection->shape = this;
  intersection->distance = distance;
  intersection->normal = normalize(cross(edge0, edge1));
  intersection->texCoord = Vector2f{u, v};
  intersection->position = base + u * edge0 + v * edge1;
  // TODO 计算交点的切线和副切线
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

REGISTER_CLASS(Parallelogram, "parallelogram")