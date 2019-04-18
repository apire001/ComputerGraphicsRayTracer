#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    //printf("Entered Sphere Intersection Function\n");
    Hit intersectionHit;
    vec3 q = ray.endpoint - center;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(ray.direction, q);
    double c = dot(q, q) - (radius * radius);
    
    double t0;
    double t1;
    bool is_hit = false;
    double q0 = b*b - 4*a*c;
    if(q0 > 0){
	is_hit = true;
	t0 = ((-1*b - sqrt(q0))/(2*a));
	t1 = ((-1*b + sqrt(q0))/(2*a));
    }
    if(!is_hit){
        return {0,0,0};
    }
    double t;
    if(t0 > small_t){
        t = t0;
    }
    else if(t1 > small_t){
        t = t1;
    }
    else{
        return intersectionHit;
    }
    return {this, t ,part};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = (point - center);
    return normal.normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
