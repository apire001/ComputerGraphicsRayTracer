#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; //determine the color
    vec3 Ra;
    vec3 La;
    vec3 Rd;
    vec3 Ld;
    vec3 Rs;
    vec3 Ls;
    vec3 r;
    vec3 tempvec;
    vec3 neg1 = {-1, -1, -1};
    double temp;
    double alpha;
    Hit tempHit;
    Ray tempRay;
    bool tempBool;
    Ra = this->color_ambient;
    Rd = this->color_diffuse;
    Rs = this->color_specular;
    La = world.ambient_intensity * world.ambient_color;
    color = Ra * La;
    Light* curr;
    for(unsigned i = 0; i < world.lights.size(); ++i){
	curr = world.lights.at(i);
	//compute shadow ray
	//check if shadow ray intersects an object
	//if no intersection add diffuse and specular components
	tempRay.endpoint = intersection_point;
	tempRay.direction = (curr->position - intersection_point).normalized();
	tempHit = world.Closest_Intersection(tempRay);
	if(tempHit.object){
	    temp = (intersection_point - curr->position).magnitude();
	    if(tempHit.dist > temp){
		tempBool = true;
	    }
	    else{
	        tempBool = false;
	    }
	}
	else{
	    tempBool = true;
	}
	if(!(world.enable_shadows)){
	    tempBool = true;
	}
	if(tempBool){
	    //diffuse calculation
	    tempvec = curr->position - intersection_point;
	    Ld = curr->Emitted_Light(tempvec);
	    temp = dot(normal, tempvec.normalized());
	    if(temp < 0){ //check max(n.l, 0)
	        temp = 0;
	    }
	    color = color + Rd * Ld * temp;
	    //specular calculation
	    //r = -l + 2(dot(l,n)*n)
	    r = neg1 * tempvec.normalized() + 2.0 * (dot(tempvec.normalized(), normal) * normal);
	    Ls = Ld;
	    temp = dot(neg1 * ray.direction.normalized(), r.normalized());
	    alpha = this->specular_power;
	    if(temp < 0){ //check max(cos(phi), 0)
	        temp = 0;
	    }
	    color = color + Rs * Ls * pow(temp, alpha);
	}
    }
    return color;
}
