#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include "vec_class.h"
#include "hittable_objects.h"

class material_class{
    public:
    virtual ~material_class() = default;
    
    virtual bool scatter(ray &r_in,hit_record& rec,color& attenuation, ray& scattered)
    {
        return false;
    }
};

class lambertian_class : public material_class
{
    public:
    lambertian_class(const color& albedo){ this->albedo = albedo;}
    bool scatter(ray& r_in,hit_record& rec, color& attenuation,ray& scattered)override
    {
        auto scatter_direction = rec.normal + vector_class::randomUnitVector();
        if(scatter_direction.near_zero())
        {
            scatter_direction = rec.normal;
        }
        scattered =ray(rec.p,scatter_direction);
        attenuation = albedo;
        return true;
    }

    private:
    color albedo;
};

class metal_class : public material_class
{
    public:
    metal_class(const color& albedo,double fuzz)
    {
        this->albedo = albedo;
        this->fuzz = fuzz < 1 ? fuzz : 1;
    }
    bool scatter(ray& r_in,hit_record& rec, color& attenuation,ray& scattered)override
    {
        vector_class incidentRay = r_in.get_direction();
        incidentRay.normalize();
        vector_class reflected = vector_class::reflect(incidentRay,rec.normal);
        reflected.normalize();
        reflected= reflected + vector_class::randomUnitVector() * fuzz;
        scattered = ray(rec.p,reflected);
        attenuation = albedo;
        return scattered.get_direction().dot(rec.normal) > 0;
    }
    private:
    color albedo;
    double fuzz;
};
class dielectric_class : public material_class{
    public:
    dielectric_class(double refraction_index)
    {
        this->refraction_index = refraction_index;
    }
    bool scatter(ray& r_in,hit_record& rec, color& attenuation,ray& scattered)override
    {
        attenuation = color(1.0,1.0,1.0);
        double refraction_ratio = rec.front_face ? (1.0/refraction_index) : refraction_index;
        vector_class unit_direction = r_in.get_direction();
        unit_direction.normalize();
        double cos_theta = std :: fmin((-unit_direction).dot(rec.normal),1.0);
        double sin_theta =  sqrt(1.0 - cos_theta*cos_theta);
        bool cannotRefract = refraction_ratio * sin_theta > 1.0;
        vector_class direction;
        if(cannotRefract || reflectance(cos_theta,refraction_ratio)> random_double()) direction = vector_class::reflect(unit_direction,rec.normal);
        else direction = vector_class::refract(unit_direction,rec.normal,refraction_ratio);

        scattered = ray(rec.p,direction);
        return true;
    }

    private:
    double refraction_index;

    static double reflectance(double cosine,double ref_idx)
    {
        double r0 = (1-ref_idx)/(1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1-cosine),5);
    }
};
#endif