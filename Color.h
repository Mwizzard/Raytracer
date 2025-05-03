//
// Created by mwizzard on 5/2/25.
//

#ifndef COLOR_H
#define COLOR_H
#include "Utils.h"
#include "Vector3D.h"
#include "Interval.h"

using color = Vector3D;

void writeColor(std::ostream& os, const color& pixelColor) {
  auto r = pixelColor.getX();
  auto g = pixelColor.getY();
  auto b = pixelColor.getZ();

  //Translate the [0,1] component values to the color range [0,255]
  static const Interval intensity(0.000, 0.999);
  int pixr = int(256 * intensity.clamp(r));
  int pixg = int(256 * intensity.clamp(g));
  int pixb = int(256 * intensity.clamp(b));
  
  os << pixr << ' ' << pixg << ' ' << pixb << '\n';
}
#endif //COLOR_H
