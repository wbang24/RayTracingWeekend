//
//  hitable.h
//  RayTracing
//
//  Created by Wayland Bang on 2019-08-19.
//  Copyright © 2019 Wayland Bang. All rights reserved.
//

#ifndef hitable_h
#define hitable_h

#include "ray.h"

class material;

struct hit_record{
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    
};
#endif /* hitable_h */
