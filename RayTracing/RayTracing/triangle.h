//
//  triangle.h
//  RayTracing
//
//  Created by Wayland Bang on 2019-08-21.
//  Copyright © 2019 Wayland Bang. All rights reserved.
//

#ifndef triangle_h
#define triangle_h

#include "hitable.h"

class triangle: public hitable{
public:
    triangle(){}
    triangle(vec3 tri_a, vec3 tri_b, vec3 tri_c, float h, float b, material *m) : triangle_point_a(tri_a),
    triangle_point_b(tri_b), triangle_point_c(tri_c), height(h), base(b), mat_ptr(m) {};
    
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    vec3 triangle_point_a;
    vec3 triangle_point_b;
    vec3 triangle_point_c;
    float height;
    float base;
    material *mat_ptr;
};

bool triangle::hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
    
/*
 Calculations for the area of the triangle
 My thought process so far...
 I need the base and height
 I need to use cross product
 */
            return true;
        }
    }
    return false;
}


#endif /* triangle_h */
