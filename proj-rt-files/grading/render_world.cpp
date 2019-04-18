#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include "float.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    //TODO;
    //printf("Entered Render World Closest Intersection Function\n");
    double min_t = DBL_MAX;
    Hit tempHit;
    Hit minHit;
    minHit.dist = 0;
    minHit.object = 0;
    minHit.part = 0;
    for(unsigned i = 0; i < this->objects.size(); i = i + 1){
	//printf("min_t is %f, number of objects is %d, i is %d\n", min_t, this->objects.size(), i);
        tempHit = this->objects.at(i)->Intersection(ray, -1);
	//printf("tempHit dist is %f\n", tempHit.dist);
        if((tempHit.dist > small_t) && (tempHit.dist < min_t)){
	    //printf("Entered if statement\n");
	    min_t = tempHit.dist;
	    minHit = tempHit;
	    //printf("min_t is %f\n", min_t);
	}
	//printf("Exited if statement\n");
    }
    //printf("Returning from Closest_Intersection");
    return minHit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    // set up the initial view ray here
    //printf("Entered Render World Render Pixel Function\n");
    Ray ray(camera.position, (camera.World_Position(pixel_index) - camera.position).normalized());
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    //printf("Entered Render World Cast Ray Function\n");    
    vec3 color;
    //TODO; // determine the color here
    Hit closestHit = Closest_Intersection(ray);
    if(closestHit.dist){
	vec3 point = ray.endpoint + ray.direction * closestHit.dist;
	color = closestHit.object->material_shader->Shade_Surface(ray, point, closestHit.object->Normal(point, closestHit.part), recursion_depth);
    }
    else{
	vec3 temp;
	color = this->background_shader->Shade_Surface(ray, temp, temp, recursion_depth);
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
