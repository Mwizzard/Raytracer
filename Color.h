//
// Created by mwizzard on 5/2/25.
//

#ifndef COLOR_H
#define COLOR_H
#include "Utils.h"
#include "Vector3D.h"

using color = Vector3D;

void writeColor(std::ostream& os, const color& pixelColor) {
  auto r = pixelColor.getX();
  auto g = pixelColor.getY();
  auto b = pixelColor.getZ();

  //Translate the [0,1] component values to the color range [0,255]

  int pixr = int(255.999*r);
  int pixg = int(255.999*g);
  int pixb = int(255.999*b);
  
  os << pixr << ' ' << pixg << ' ' << pixb << '\n';
}
#endif //COLOR_H
