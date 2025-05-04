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
private:
  color col;
  double fuzz;

public:
  metal(const color& c, double fuz) : col(c), fuzz(fuz) {}

  bool scatter(const Ray& r_in, const hitSurfaceRecord& rec, color& attenuation, Ray& scattered)
  const override {
    Vector3D reflected = reflect(r_in.getDirection(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = col;
    return (dotProduct(scattered.getDirection(), rec.normal) > 0);
  }
};
class refractive : public material {
private:

  double refraction_index;
public:
  refractive(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const Ray& r_in, const hitSurfaceRecord& rec, color& attenuation, Ray& scattered)
  const override {
    attenuation = color(1.0, 1.0, 1.0);

    double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;
    Vector3D unit_direction = unit_vector(r_in.getDirection());

    double cos_theta = std::fmin(dotProduct((unit_direction)*-1, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vector3D direction;

    if (cannot_refract)
      direction = reflect(unit_direction, rec.normal);
    else
      direction = refract(unit_direction, rec.normal, ri);
    scattered = Ray(rec.p, direction);

    Vector3D refracted = refract(unit_direction, rec.normal, ri);

    scattered = Ray(rec.p, refracted);
    return true;
  }
};
#endif //MATERIAL_H
