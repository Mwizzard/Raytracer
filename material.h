//
// Created by mwizzard on 5/3/25.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "surface.h"
#include "Utils.h"


//Abstract class used to represent different materials like metal, glass, smoke, etc
class material {
  public:
    //Destructor
    virtual ~material() =default;

    virtual bool scatter(const Ray& in, const hitSurfaceRecord& rec, color& attenuation, Ray& scattered) const = 0;

};

class lambertian : public material {
  private:
    color col;
  public:
    lambertian(const color& c) : col(c) {}

    bool scatter(const Ray& in, const hitSurfaceRecord& rec, color& attenuation, Ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero())
          scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);
        attenuation = col;
        return true;
      }
};

class metal : public material {
public:
  metal(const color& c) : col(c) {}

  bool scatter(const Ray& r_in, const hitSurfaceRecord& rec, color& attenuation, Ray& scattered)
  const override {
    Vector3D reflected = reflect(r_in.getDirection(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = col;
    return true;
  }

private:
  color col;
};
#endif //MATERIAL_H
