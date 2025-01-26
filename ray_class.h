#ifndef RAY_CLASS_H
#define RAY_CLASS_H

#include "vec_class.h"

class ray_class{
    public:
    ray_class() {}

    ray_class(point origin, vector_class direction)
    {
        orig = origin;
        dir = direction;
    }
    
    //getter methods

    point& get_origin(){return orig;}
    vector_class& get_direction(){return dir;}

    //setter methods
    void set_origin(point& origin){orig = origin;}
    void set_direction(vector_class& direction){dir = direction;}
    
    point at(double t){ return orig + dir * t;}
    private:
    point orig;
    vector_class dir;
};
using ray = ray_class;
#endif