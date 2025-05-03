//
// Created by mwizzard on 5/3/25.
//

#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double randomDouble(){
  // [0, 1[
  return std::rand() / (RAND_MAX + 1.0);
}
inline double randomDouble(double min, double max){
  return min + (max - min) * randomDouble();
}

// Common Headers

#include "Color.h"
#include "Ray.h"
#include "Vector3D.h"
#include "Interval.h"

#endif //UTILS_H
