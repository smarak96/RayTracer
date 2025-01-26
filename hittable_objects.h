#ifndef HITTABLE_OBJECTS_H
#define HITTABLE_OBJECTS_H

#include "ray_class.h"
#include "interval.h"

class material_class;
class hit_record
{
    public:
    point p;
    vector_class normal;
    shared_ptr<material_class> mat_ptr;
    double t;
    bool front_face; // if true then we are talking about the outer face of the object. if false then we are talking about the interior face of the object.
    void set_face_normal(ray& r,vector_class& normal)
    {
        vector_class ray_direction = r.get_direction();
        front_face = ray_direction.dot(normal) < 0;
        normal = front_face  ? normal : -normal;
    }
};

class hittable
{
    public:
    virtual ~hittable() = default;
    virtual bool hit(ray& r, interval_class ray_t, hit_record& rec) = 0;
    bool front_face;
};


#endif