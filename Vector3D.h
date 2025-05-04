//
// Created by mwizzard on 5/2/25.
//


#ifndef INC_3DVECTOR_H
#define INC_3DVECTOR_H
#include "Utils.h"
class Vector3D {
  public:
    double val[3];
    //Default constructor
    Vector3D() {val[0] = val[1] = val[2] = 0.0;}
    //Constructor with defined values
    Vector3D(double x, double y, double z) {val[0] = x, val[1] = y, val[2] = z;}

    //getters
    double getX() const {return val[0];}
    double getY() const {return val[1];}
    double getZ() const {return val[2];}
    double operator[](int i) const { return val[i]; }

    ///Simple arithmetic methods

    //invert vector
    void operator-(){
      val[0] = -val[0];
      val[1] = -val[1];
      val[2] = -val[2];
    }
    //Substraction this - vector in parameter
    Vector3D& operator-=(const Vector3D &v){
      val[0] -= v.val[0];
      val[1] -= v.val[1];
      val[2] -= v.val[2];
      return *this;
    }

    Vector3D& operator+=(const Vector3D &v) {
      this->val[0] += v.val[0];
      this->val[1] += v.val[1];
      this->val[2] += v.val[2];
      return *this;
    }

    Vector3D& operator*=(double d) {
      this->val[0] *= d;
      this->val[1] *= d;
      this->val[2] *= d;
      return *this;
    }
    Vector3D& operator/=(double d) {
      this->val[0] /= d;
      return *this;
    }
    double length() const {
      return std::sqrt((this->val[0]*this->val[0]) + (this->val[1]*this->val[1]) + (this->val[2]*this->val[2]));
    }
    double lengthSquared() const{
      return pow(val[0],2) + pow(val[1],2) +  pow(val[2],2);
    }
    static Vector3D random() {
      return Vector3D(randomDouble(), randomDouble(), randomDouble());
    }

    static Vector3D random(double min, double max) {
      return Vector3D(randomDouble(min,max), randomDouble(min,max), randomDouble(min,max));
    }

    bool near_zero() const {
        //returns true if the vector is close to zero.
        auto epsilon = 1e-8;
        return (std::fabs(val[0]) < epsilon) && (std::fabs(val[1]) < epsilon) && (std::fabs(val[2]) < epsilon);
      }
};
using point3 = Vector3D;
//Print
std::ostream& operator<<(std::ostream &os, const Vector3D &v) {
  os << "x: "<< v.val[0] << " y: " << v.val[1] << " z: " << v.val[2];
  return os;
}
//Arithmetic operation with 2 vectors in parameters
inline Vector3D operator+(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.val[0] + v.val[0], u.val[1] + v.val[1], u.val[2] + v.val[2]);
}

inline Vector3D operator-(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.val[0] - v.val[0], u.val[1] - v.val[1], u.val[2] - v.val[2]);
}

inline Vector3D operator*(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.val[0] * v.val[0], u.val[1] * v.val[1], u.val[2] * v.val[2]);
}

inline Vector3D operator*(double t, const Vector3D& v) {
  return Vector3D(t*v.val[0], t*v.val[1], t*v.val[2]);
}

inline Vector3D operator*(const Vector3D& v, double t) {
  return t * v;
}

inline Vector3D operator/(const Vector3D& v, double t) {
  return (1/t) * v;
}

//More Advanced utility methods
inline double dotProduct(const Vector3D& u, const Vector3D& v) {
  return u.val[0] * v.val[0]
       + u.val[1] * v.val[1]
       + u.val[2] * v.val[2];
}

inline Vector3D cross(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.val[1] * v.val[2] - u.val[2] * v.val[1],
                  u.val[2] * v.val[0] - u.val[0] * v.val[2],
                  u.val[0] * v.val[1] - u.val[1] * v.val[0]);
}

inline Vector3D unit_vector(const Vector3D& v) {
  return v / v.length();
}
inline Vector3D random_unit_vector()
{
  while (true) {
    auto p = Vector3D::random(-1,1);
    auto lensquared = p.lengthSquared();
    if (1e-160 < lensquared && lensquared <= 1) //floating point abstraction leak
      return p / sqrt(lensquared);
  }
}
inline Vector3D reflect(const Vector3D& v, const Vector3D& u) {
  return v - 2 * dotProduct(v,u) * u;
}
inline Vector3D random_on_hemisphere(const Vector3D& normal) {
  Vector3D on_unit_sphere = random_unit_vector();
  if (dotProduct(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return on_unit_sphere *-1;
}
#endif //INC_3DVECTOR_H
