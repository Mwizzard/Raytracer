//
// Created by mwizzard on 5/2/25.
//

#ifndef COLOR_H
#define COLOR_H
#include "Utils.h"
#include "Vector3D.h"
#include "Interval.h"


using color = Vector3D;
inline double linearToGamma(double linearComponent)
{
  if (linearComponent > 0)
    return std::sqrt(linearComponent);

  return 0;
}
void writeColor(std::ostream& os, const color& pixelColor) {
  auto r = pixelColor.getX();
  auto g = pixelColor.getY();
  auto b = pixelColor.getZ();
  // Apply a linear to gamma transform for gamma 2
  r = linearToGamma(r);
  g = linearToGamma(g);
  b = linearToGamma(b);
  //Translate the [0,1] component values to the color range [0,255]
  static const Interval intensity(0.000, 0.999);
  int pixr = int(256 * intensity.clamp(r));
  int pixg = int(256 * intensity.clamp(g));
  int pixb = int(256 * intensity.clamp(b));
  
  os << pixr << ' ' << pixg << ' ' << pixb << '\n';
}

#endif //COLOR_H
