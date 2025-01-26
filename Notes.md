# RayTracer Project Notes

## Overview
This document contains notes and ideas for the RayTracer project.

## vec_class.h
- I have implemented all utility functions inside the vector class itself. Lets see what happens.


## color.h
- In color.h file, for the fill_color function, i have taken an ofstream object reference as one of the parameters. This helped me to pass the original ppm file that i had opened in the main function

- I also noticed that writing the rgb values for each pixel to the console was making the render process very slow. So i commented it. Will uncomment it if required.

-While converting in range of 0-255, i have multiplied with 255 instead of 255.999, since i dont understand yet why 255.999 is used.


## Things to add.
-My sphere is currently placed at z=-1 which is infront of the camera. Now if i place it at z=1, this means it is at back of camera. So ideally, the object shouldnt be visible. So need to handle that.
- Add const keyword wherever required.
- Add pass by reference wherever required.
- Need to implement hit ellipsoid correctly. It is not rendering.

## Resources
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

