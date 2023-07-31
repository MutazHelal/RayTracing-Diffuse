#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include "Ray.h"
using namespace std;
class Material;

class HitResult {
public:
    HitResult() { m_isHit = false; };
    bool m_isHit;
    Vector3D m_hitPos;
    Vector3D m_hitNormal;
    shared_ptr<Material> m_hitMaterial;
    float m_t;
};


class Sphere {
    
public:
    Sphere() {}
    Sphere(Vector3D center, float r, shared_ptr<Material> m)
    {
        m_center = center;
        m_radius = r;
        m_pMaterial = m;
    }
    HitResult hit(Ray& r, float min_t, float max_t);

    public:
    Vector3D m_center;
    float m_radius;
    shared_ptr<Material> m_pMaterial;
};


//test if ray hits this sphere within range min_t and max_t
HitResult Sphere::hit(Ray& ray, float min_t, float max_t)
{
    HitResult hit_result;
    // compute the coefficients of the quadratic equation
    // to determine if the ray intersects the sphere
    Vector3D oc = ray.origin() - m_center;
    float a = ray.direction().length_squared();
    float b = 2.0f * dot(oc, ray.direction());
    float c = oc.length_squared() - m_radius * m_radius;
    float discriminant = b * b - 4 * a * c;
    // check if the ray intersects the sphere
    if (discriminant > 0.0f)
    {
        // find the two solutions to the quadratic equation
        float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        // check if the solutions are within the specified range
        if (t1 >= min_t && t1 <= max_t)
        {
            hit_result.m_isHit = true;
            hit_result.m_t = t1;
            hit_result.m_hitPos = ray.at(t1);
            hit_result.m_hitNormal = (hit_result.m_hitPos - m_center) / m_radius;
            hit_result.m_hitMaterial = m_pMaterial;
            return hit_result;
        }
        else if (t2 >= min_t && t2 <= max_t)
        {
            hit_result.m_isHit = true;
            hit_result.m_t = t2;
            hit_result.m_hitPos = ray.at(t2);
            hit_result.m_hitNormal = (hit_result.m_hitPos - m_center) / m_radius;
            hit_result.m_hitMaterial = m_pMaterial;
            return hit_result;
        }
    }
    hit_result.m_isHit = false;
    return hit_result;
}

#endif
