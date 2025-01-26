#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include "hittable_objects.h"
#include "vec_class.h"

class sphere : public hittable
{
    public:
    sphere(point center ,double radius,shared_ptr<material_class> mat)
    {
        this->center = center;
        this->radius = radius;
        this->material_ptr = mat;
    }

    bool hit(ray& r,interval_class ray_t, hit_record& rec)
    {
        vector_class oc = center - r.get_origin();
        auto a = r.get_direction().dot(r.get_direction());
        auto b = -2.0 * oc.dot(r.get_direction());
        auto c = oc.dot(oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        
        if(discriminant <0) return false;
        auto sqrt_discriminant = sqrt(discriminant);
        auto root = (- b - sqrt_discriminant)/(2.0*a);
        if(! ray_t.surrounds(root))
        {
            root = (- b + sqrt_discriminant)/(2.0*a);
            if(! ray_t.surrounds(root))
            {
                return false;
            }
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center);
        rec.normal.normalize();
        rec.set_face_normal(r,rec.normal);
        rec.mat_ptr = material_ptr;
        return true;
    }   
    private:
    point center;
    double radius;
    shared_ptr<material_class> material_ptr;
};

#endif