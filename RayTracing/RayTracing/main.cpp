//
//  main.cpp
//  RayTracing
//
//  Created by Wayland Bang on 2019-08-15.
//  Copyright © 2019 Wayland Bang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "float.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

using namespace std;


/*
 colour is a function that will decide what colours need to be scattered
 This will depend on the material the sphere has
 */
vec3 colour(const ray& r, hitable *world, int depth){
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation*colour(scattered, world, depth+1);
        }
        else{
            return vec3(0,0,0);
        }
    }
    else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y()+1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
    }
}

/*
 This function creates the scene seen on the cover of the minibook
 It will create man spheres of varying materials: Diffuse, Metal, Deilectric
 */
hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                //DIFFUSE MATERIAL
                if (choose_mat < 0.8) {
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                //METAL MATERIAL
                else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center, 0.2,
                                           new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
                }
                //REFLECTIVE GLASS MATERIAL
                else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    
    return new hitable_list(list,i);
}

int main(){
    
    ofstream img ("image.ppm");
    
    int nx = 600;
    int ny = 400;
    int ns = 10;
    
    img<<"P3\n" << nx << " " << ny << " \n255\n";
    
    hitable *list[5];
  
    //  float R = cos(M_PI/4);
    
    /*
     Creating spheres of different materials
     */
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1,0.2,0.5)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2), 0.2));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));
   // list[0] = new sphere(vec3(-R,0,-1), R, new lambertian(vec3(0,0,1)));
    //list[1] = new sphere(vec3(R,0,-1), R, new lambertian(vec3(1,0,0)));

    hitable *world = new hitable_list(list, 5);
    world = random_scene();
    
    /*
     Camera Position and Focus
     */
    vec3 lookfrom(13,2,15);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);

    /*
     Drawing each pixel of our rendered image
     Outputting to a ppm file
     Set computer default program that supports ppm files
        Like Peter, I used ToyViewer
     */
    for(int j = ny-1; j >= 0; j-- ){
        for(int i = 0; i <nx; i++){
            vec3 col(0,0,0);
            for(int s=0; s < ns; s++){
            float u = float(i + drand48()) / float(nx);
            float v = float(j + drand48()) / float(ny);
            ray r = cam.get_ray(u,v);
            vec3 p = r.point_at_parameter(2.0);
            col += colour(r,world,0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            
            img<< ir << " " << ig << " " << ib << "\n";
        }
    }
    
    system("open image.ppm");
    return 0;
}

