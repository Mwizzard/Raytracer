//
// Created by mwizzard on 5/2/25.
//

#ifndef RAY_H
#define RAY_H
#include "Vector3D.h"
class Ray {
private:
    point3 origin;
    Vector3D direction;
  public:
    //default constructor
    Ray(){};
    //Specific constructors
    Ray(const Vector3D& orig, const Vector3D& direct){origin = orig; direction = direct;}

    //getters
    const point3& getOrigin() const {return origin;}
    const Vector3D& getDirection() const {return direction;}
    point3 at(double t) const {return origin + t * direction;}
};
#endif //RAY_H
