// #include <iostream>
#include "raytrace_main.h"
#include "hittable_objects.h"
#include "hittable_list.h"
#include "sphere_class.h"
#include <fstream> // Added for file operations
#include "camera_class.h"
#include "material_class.h"
#include <chrono>

// #include <cmath>

// #include "color.h"
// #include "vec_class.h"
// #include "ray_class.h"
using namespace std;


int main() 
{
    auto start = chrono::high_resolution_clock::now();
    hittable_list world;

    auto material_ground = make_shared<lambertian_class>(color(0.5, 0.5, 0.5));
    world.addToListOfObjects(make_shared<sphere>(point( 0.0, -1000, 0), 1000, material_ground));

    for(int a = -7;a<7;++a)
    {
        for(int b = -7;b<7;++b)
        {
            auto chooseMaterial = random_double();
            point center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if( (center - point(4,0.2,0)).length() > 0.9 )
            {
                shared_ptr<material_class> sphere_material;
                if(chooseMaterial < 0.8)
                {
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian_class>(albedo);
                    world.addToListOfObjects(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (chooseMaterial<0.95)
                {
                    auto albedo =  color :: random(0.5,1);
                    auto fuzz = random_double(0,0.5);
                    sphere_material = make_shared<metal_class>(albedo,fuzz);
                    world.addToListOfObjects(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    sphere_material = make_shared<dielectric_class>(1.5);
                    world.addToListOfObjects(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric_class>(1.5);
    world.addToListOfObjects(make_shared<sphere>(point(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian_class>(color(0.4, 0.2, 0.1));
    world.addToListOfObjects(make_shared<sphere>(point(-4, 1, 0), 1.0, material2));
    
    auto material3 = make_shared<metal_class>(color(0.7, 0.6, 0.5), 0.0);
    world.addToListOfObjects(make_shared<sphere>(point(4, 1, 0), 1.0, material3));

    // auto material_center = make_shared<lambertian_class>(color(0.1, 0.6, 0.3));
    // auto material_left   = make_shared<metal_class>(color(0.3, 0.6, 0.2), 0.1);
    // // auto material_bubble = make_shared<dielectric_class>(1.00 / 1.50);
    // auto material_right  = make_shared<metal_class>(color(0.8, 0.6, 0.2), 0.1);

    // world.addToListOfObjects(make_shared<sphere>(point( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.addToListOfObjects(make_shared<sphere>(point( 0.0,    0.0, -1.2),   0.5, material_center));
    // world.addToListOfObjects(make_shared<sphere>(point(-1.0,    0.0, -1.0),   0.5, material_left));
    // // world.addToListOfObjects(make_shared<sphere>(point(-1.0,    0.0, -1.0),   0.4, material_bubble));
    // world.addToListOfObjects(make_shared<sphere>(point( 1.0,    0.0, -1.0),   0.5, material_right));
  
   

    camera_class camera;

    camera.aspect_ratio = 2.0;
    camera.image_width=400;
    camera.samples_per_pixel = 100;
    camera.max_depth_recursion = 50;
    
    
    camera.vfov = 20;
    camera.lookfrom  = point(13,2,3);
    camera.lookat = point(0,0,0);
    camera.vup = vector_class(0,1,0);

    camera.render(world);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout<<"Time taken to render the image: "<<elapsed.count()<<" seconds"<<endl;
    return 0;
}