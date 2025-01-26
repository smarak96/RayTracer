#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <iostream>
#include<cmath>
#include "raytrace_main.h"
class vector_class{
    public:
    double e[3];

    vector_class()
    {
        e[0] = 0;
        e[1] = 0;
        e[2] = 0;
    }
    vector_class(double e0, double e1, double e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    double x(){return e[0];}
    double y(){return e[1];}
    double z(){return e[2];}

    vector_class operator-() const {return vector_class(-e[0], -e[1], -e[2]);}
    double operator[](int i) const {return e[i];}
    double& operator[](int i){return e[i];}

    vector_class& operator+=(const vector_class& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    vector_class& operator *=(double t)
    {
        e[0] = t*e[0];
        e[1] = t*e[1];
        e[2] = t* e[2];
        return *this;
    }
    vector_class& operator /=(double t)
    {
        e[0] = e[0]/t;
        e[1] = e[1]/t;
        e[2] = e[2]/t;
        return *this;
    }
    vector_class operator/(double t)
    {
        return vector_class(e[0]/t, e[1]/t, e[2]/t);
    }
    double squared_length()
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    double length()
    {
        return sqrt(squared_length());
    }
    vector_class operator+(vector_class v2)
    {
        return vector_class(this->e[0] + v2.e[0], this->e[1] + v2.e[1], this->e[2] + v2.e[2]);
    }
    vector_class operator-(vector_class v2)
    {
        return vector_class(this->e[0] - v2.e[0], this->e[1] - v2.e[1], this->e[2] - v2.e[2]);
    }
    vector_class operator*(double t)
    {
        return vector_class(this->e[0]*t, this->e[1]*t, this->e[2]*t);
    }
    double dot(vector_class v2)
    {
        return this->e[0]*v2.e[0] + this->e[1]*v2.e[1] + this->e[2]*v2.e[2];
    }
    vector_class cross(const vector_class & v) 
    {
        return vector_class(e[1] * v.e[2] - e[2] * v.e[1],e[2] * v.e[0] - e[0] * v.e[2],e[0] * v.e[1] - e[1] * v.e[0]);
    }
    void normalize()
    {
        double l = length();
        e[0] = e[0]/l;
        e[1] = e[1]/l;
        e[2] = e[2]/l;
    }
    vector_class operator*(vector_class v2)
    {
        return vector_class(this->e[0]*v2.e[0], this->e[1]*v2.e[1], this->e[2]*v2.e[2]);
    }
    static vector_class random() {
        return vector_class(random_double(), random_double(), random_double());
    }
    static vector_class random(double min, double max) {
        return vector_class(random_double(min,max), random_double(min,max), random_double(min,max));
    }
    static vector_class randomUnitVector()
    {
        while(true)
        {
            auto p = vector_class::random(-1,1);
            auto lengthOfRandomVector = p.squared_length();
            if(1e-160 < lengthOfRandomVector && lengthOfRandomVector < 1)
            {
                return p/lengthOfRandomVector;
            }
        }
    }
    static vector_class randomVectorOnHemisphere(vector_class normal)
    {
        vector_class unitVectorInSphere = randomUnitVector();
        if(unitVectorInSphere.dot(normal) > 0.0)
        {
            return unitVectorInSphere;
        }
        else
        {
            return -unitVectorInSphere;
        }
    }
    bool near_zero()
    {
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
    static vector_class reflect(vector_class& v, vector_class& n)
    {
        return v - (n * (2 * v.dot(n)));
    }
    static vector_class refract(vector_class& u,vector_class& n, double refractive_index)
    {
        auto cos_theta = fmin((-u).dot(n),1.0);
        vector_class r_perpendicular = (u + n * cos_theta) * refractive_index;
        vector_class r_parallel = n * (-sqrt(fabs(1.0 - r_perpendicular.squared_length())));
        return r_perpendicular + r_parallel;
    }
};

using point = vector_class;


#endif