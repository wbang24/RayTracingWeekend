//
//  sphere.h
//  RayTracing
//
//  Created by Wayland Bang on 2019-08-19.
//  Copyright © 2019 Wayland Bang. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "hitable.h"

class sphere: public hitable{
    public:
        sphere(){}
        sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
        material *mat_ptr;
};

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
    
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if(discriminant > 0){
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < tmax && temp > tmin){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center)/ radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }//note to self: not sure why it does it twice...
        temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < tmax && temp > tmin){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center)/ radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
        return false;
}

    
#endif /* sphere_h */
