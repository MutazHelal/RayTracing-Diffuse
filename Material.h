#ifndef MATERIAL_H
#define MATERIAL_H

class HitResult;

class ReflectResult
{
public:
    Ray m_ray;
    Vector3D m_color;
};

class Material
{
public:
    Vector3D m_color;
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) = 0;
};


class Diffuse : public Material
{
public:
    Diffuse(const Vector3D& color)
    {
        m_color = color;
    };
    
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) override
    {
        //ReflectResult res;
        ////TODO: 4. generate one scattered ray and assign it to res.m_ray
        //
        //res.m_color = m_color;
        //return res;
            //Vector3D reflection = ray.m_direction - 2 * dot(ray.m_direction, hit.m_hitNormal) * hit.m_hitNormal;

            //// Generate a random direction on the hemisphere
            //float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            //float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            //float theta = 2 * M_PI * r1;
            //float phi = acos(2 * r2 - 1);
            //Vector3D random_dir = Vector3D(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
            //Vector3D v = reflection + random_dir;
            //Ray scattered_ray(hit.m_hitPos, v);
            //// Return the result
            //ReflectResult result;
            //result.m_ray = scattered_ray;
            //result.m_color = m_color;
            //return result;
        ReflectResult res;
        Vector3D target = hit.m_hitPos + hit.m_hitNormal + m_color.random();
        Vector3D vector = target - hit.m_hitPos;
        Ray scattered_ray(hit.m_hitPos, vector);

        res.m_ray = scattered_ray;
        res.m_color = m_color;

        // Check if the scattered ray is within the hemisphere.
        // If not, reverse its direction to keep it within the hemisphere.
        if (dot(res.m_ray.direction(), hit.m_hitNormal) < 0)
        {
            Vector3D v = -scattered_ray.direction();
            Ray ray(hit.m_hitPos, v);
            res.m_ray = ray;
        }

        return res;
    }
};


class Specular : public Material
{
public:
    Specular(const Vector3D& color)
    {
        m_color = color;
    }
    
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) override
    {
        //ReflectResult res;
        ////TODO: 5. generate one mirrored ray and assign it to res.m_ray
        //
        //res.m_color = m_color;
        //return res;

        // Calculate the reflection vector
        Vector3D reflection = ray.m_direction - 2 * dot(ray.m_direction, hit.m_hitNormal) * hit.m_hitNormal;

        // Create the scattered ray
        Ray scattered_ray( hit.m_hitPos,reflection);

        // Return the result
        ReflectResult result;
        result.m_ray = scattered_ray;
        result.m_color = m_color;
        return result;

    }
};

#endif
