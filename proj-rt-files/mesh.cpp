#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    //TODO;
    double tempDist;
    if(part < 0){
        for(unsigned i = 0; i < triangles.size(); ++i){
	    if(Intersect_Triangle(ray, i, tempDist)){
	        return {this, tempDist, static_cast<int>(i)};
	    }
        }
    }
    else{
	if(Intersect_Triangle(ray, part, tempDist)){
	    return {this, tempDist, part};
	}
    }
    return {NULL, 0, 0};
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    //TODO;
    return cross(vertices[triangles[part][2]] - vertices[triangles[part][1]], vertices[triangles[part][0]] - vertices[triangles[part][1]]).normalized();
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.

bool plane_intersection(vec3 p0, vec3 v, vec3 n, vec3 d, Ray ray, vec3& point){
    if(dot(n, v) == 0){
        return false;
    }
    double t = (dot(d - p0, n))/(dot(n, v));
    if(t > 0){
        point = ray.Point(t);
	return true;
    }
    return false;
}

bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    //TODO;
    vec3 point;
    vec3 A = vertices[triangles[tri][0]];
    vec3 B = vertices[triangles[tri][1]];
    vec3 C = vertices[triangles[tri][2]];
    vec3 n = (cross(C - B, A - B)).normalized();
    vec3 p0 = ray.endpoint;
    vec3 v = ray.direction.normalized();
    bool plane_intersect = plane_intersection(p0, v, n, A, ray, point);
    if(plane_intersect){
        double areaABC = dot(n, cross((B - A), (C - A)));
        double areaPBC = dot(n, cross((B - point), (C - point)));
        double areaPCA = dot(n, cross((C - point), (A - point)));
        double alpha = areaPBC / areaABC ;
        double beta = areaPCA / areaABC ;
        double gamma = 1.0 - alpha - beta;
	if((alpha >= (-1.0 * weight_tol)) && (beta >= (-1.0 * weight_tol)) && (gamma >= (-1.0 * weight_tol))){
	    dist = (point - ray.endpoint).magnitude();
	    return true;
	}
    }
    //printf("Point is not in triangle\n");
    return false;
}



// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
