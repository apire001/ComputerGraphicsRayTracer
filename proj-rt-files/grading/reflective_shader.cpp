#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 l;
    vec3 r;
    Ray tempRay;
    //TODO; // determine the color
    //printf("Called reflective shader shade_surface\n");
    //r = -l + 2(dot(l,n)*n)
    l = -1.0 * ray.direction.normalized();
    r = (-1.0 * l + 2.0 * (dot(l, normal) * normal)).normalized();
    tempRay.endpoint = intersection_point;
    tempRay.direction = r;
    color = (1.0 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth + 1);
    if(recursion_depth < world.recursion_depth_limit){
	color = color + reflectivity * world.Cast_Ray(tempRay, recursion_depth + 1);
    }
    return color;
}
