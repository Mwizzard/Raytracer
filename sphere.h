//
// Created by mwizzard on 5/2/25.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "surface.h"
#include "Utils.h"

class sphere : public hittable {
    private:
      point3 center;
      double radius;
    public:
      sphere(const point3& c, const double& r) : center(c), radius(std::fmax(0,r)) {}
      virtual bool hit(const Ray& r, Interval ray_t, hitSurfaceRecord& rec) const override {
		Vector3D oc = center - r.getOrigin();
        auto a = r.getDirection().lengthSquared();
        auto half_b = dotProduct(r.getDirection(), oc);
        auto c = oc.lengthSquared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) {
          return false;
        }
        auto sqrtd = std::sqrt(discriminant);

        auto root = (half_b - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (half_b + sqrtd) / a;

            if (!ray_t.surrounds(root))
                return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        Vector3D outward_normal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outward_normal);
        return true;
      }

};
#endif //SPHERE_H
