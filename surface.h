//
// Created by mwizzard on 5/2/25.
//

#ifndef SURFACE_H
#define SURFACE_H
#include "Utils.h"


class hitSurfaceRecord {
  public:
    point3 p;
    Vector3D normal;
    double t{};

    bool front_face{};

    void setFaceNormal(const Ray& r, const Vector3D& outward_normal) {

        front_face = dotProduct(r.getDirection(), outward_normal) < 0;
		//If the normal vector points in the same direction as the ray, then we are in the sphere
        //Else, we are outside the sphere
        if (dotProduct(r.getDirection(), outward_normal) > 0.0) {
    		// ray is inside the sphere
    		normal = outward_normal * -1;
    		front_face = false;
		} else {
    		// ray is outside the sphere
    		normal = outward_normal;
    		front_face = true;
		}
    }
};
//"Abstract class" made to define properties of any object the rays can intersect
class hittable {
public:
    //Default destructor
    virtual ~hittable() = default;
    //Abstract constructor
    virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, hitSurfaceRecord& rec) const = 0;
};

#endif //SURFACE_H
