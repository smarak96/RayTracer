#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "hittable_objects.h"
#include "color.h"
#include "raytrace_main.h"
#include "material_class.h"

#include <thread>
#include <future>
#include <sstream>
class camera_class
{
    public:
    double aspect_ratio = 1;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth_recursion = 10;

    double vfov = 90;
    point lookfrom = point(0,0,0);
    point lookat = point(0,0,-1);
    vector_class vup = vector_class(0,1,0);
   void render(hittable& world) {
        initialize_camera();
        std::ofstream image("output.ppm");
        if (!image) {
            std::cerr << "Error: Could not open the file for writing." << std::endl;
            exit(1);
        }

        image << "P3\n" << image_width << " " << image_height << "\n255\n";

        // Vector to store the final color data for all pixels
        std::vector<std::string> pixel_data(image_width * image_height);

        // Vector to store futures
        std::vector<std::future<void>> futures;

        // Launch tasks asynchronously
        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                futures.emplace_back(std::async(std::launch::async, 
                    [&, i, j]() {
                        // Compute the color for the pixel
                        color pixel_color(0, 0, 0);
                        for (int sample = 0; sample < samples_per_pixel; ++sample) {
                            ray r = get_ray(i, j);
                            pixel_color += ray_color(r, max_depth_recursion, world);
                        }
                        color final_color = pixel_color * pixel_samples_scale;

                        // Store the computed color as a string
                        std::ostringstream oss;
                        oss << static_cast<int>(255.999 * final_color.x()) << " "
                            << static_cast<int>(255.999 * final_color.y()) << " "
                            << static_cast<int>(255.999 * final_color.z()) << "\n";
                        pixel_data[j * image_width + i] = oss.str();
                    }
                ));
            }
        }

        // Wait for all tasks to complete
        for (auto& fut : futures) {
            fut.get();
        }

        // Write the collected data to the file
        for (const auto& row : pixel_data) {
            image << row;
        }

        image.close();
        std::cout << "Image generated successfully in output.ppm" << std::endl;
}
    private:
    int image_height;
    point camera_center;
    point pixel00_pos;
    vector_class pixel_delta_u;
    vector_class pixel_delta_v;
    double pixel_samples_scale;
    vector_class u,v,w; //declaring local coordinates system for camera

    void initialize_camera()
    {
        image_height = int(image_width/aspect_ratio); //since width/height = aspect_ratio
        image_height = image_height<1?1:image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        camera_center = lookfrom;

        //defining camera parameters
        auto focal_length = (lookfrom-lookat).length();
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focal_length;
        auto viewport_width = aspect_ratio * viewport_height;

        //calculate the local coordinate system for camera
        w = lookfrom - lookat;
        w.normalize();
        u = vup.cross(w);
        v= w.cross(u);
        //calculate the viewport vectors;
        // auto viewport_u = vector_class(viewport_width,0,0);
        // auto viewport_v = vector_class(0,-viewport_height,0);

        vector_class viewport_u = u * viewport_width;
        vector_class viewport_v = -v * viewport_height;

        //calculate the horizontal and vertical distance vectors between pixel centers
        pixel_delta_u = viewport_u/image_width;
        pixel_delta_v = viewport_v/image_height;

        //first calculate the corner of the viewport . Then use it to calculate position of upper left pixel
        // auto viewport_corner = camera_center - viewport_u/2 - viewport_v/2 - vector_class(0,0,focal_length);
        auto viewport_corner = camera_center - viewport_u/2 - viewport_v/2 - (w * focal_length);
        pixel00_pos = viewport_corner +  (pixel_delta_u + pixel_delta_v)* 0.5;

    }
    ray get_ray(int i,int j)
    {
        auto offset = sample_square();
        auto pixel_sample = pixel00_pos + (pixel_delta_u * (i+ offset.x())) + (pixel_delta_v * (j + offset.y()));
        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - camera_center;
        return ray(ray_origin,ray_direction);
    }
    vector_class sample_square()
    {
        return vector_class(random_double(),random_double(),0);
    }
    color ray_color(ray& r,int depth, hittable& world)
    {
        if(depth<=0) return color(0,0,0);

        hit_record rec;

        if(world.hit(r,interval_class(0,std::numeric_limits<double>::infinity()),rec))
        {
            ray scattered;
            color attenuation;

            if(rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            {
                return attenuation * ray_color(scattered,depth-1,world);
            }
            return color(0,0,0);
        }
        vector_class unit_direction = r.get_direction();
        unit_direction.normalize();
        auto t = 0.5*(unit_direction.y() + 1.0);
        return color(1.0,1.0,1.0)* (1.0-t) + color(0.5,0.7,1.0)*t;
    }

};

#endif