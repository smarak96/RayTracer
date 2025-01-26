#ifndef COLOR_H
#define COLOR_H
#include<fstream>
#include "vec_class.h"
#include "interval.h"
#include<iostream>
using namespace std;
using color = vector_class;

inline double convert_linear_to_gamma(double linear_compoenent)
{
    if(linear_compoenent>0) return sqrt(linear_compoenent);
    else return 0;
}

void fill_color(color& pixel_color, ofstream& image)
{
    auto red = pixel_color.x();
    auto green = pixel_color.y();
    auto blue = pixel_color.z();

    red = convert_linear_to_gamma(red);
    green = convert_linear_to_gamma(green);
    blue = convert_linear_to_gamma(blue);
    
    //converting in terms of range 0-255
    static interval_class intensity(0.000,0.999);
    int rbyte = int(255 * intensity.clamp(red));
    int gbyte = int(255 * intensity.clamp(green));
    int bbyte = int(255 * intensity.clamp(blue));
    // cout<<rbyte<<" "<<gbyte<<" "<<bbyte<<"\n";
    image<<rbyte<<" "<<gbyte<<" "<<bbyte<<"\n";
}
#endif