//
// Created by mwizzard on 5/3/25.
//


#ifndef HITABLELIST_H
#define HITABLELIST_H
#include "surface.h"
#include <memory>
#include <vector>
//This class is used to store the different items, the rays can interact with (intersect, bounce refract,etc)

class HitableList : public hittable{
    public:
      //This is where the object list is kept (stored inside a vector of shared pointers, that point to a
      //reference of each object in the world
      std::vector<std::shared_ptr<hittable>> objects;

      //Constructors
      HitableList() {} //default
      HitableList(std::shared_ptr<hittable> object) {    //Only one object at constuction
          objects.push_back(object);
      }
      HitableList(std::vector<std::shared_ptr<hittable>> list){    //Constructor with all the object given in param
        //add each object to the list
        for(const std::shared_ptr<hittable> object : list){
          objects.push_back(object);
        }
      }

      void clear(){
        objects.clear();
      }
      void add(std::shared_ptr<hittable> object)
      {
          objects.push_back(object);
      }


      virtual bool hit(const Ray& r, Interval ray_t, hitSurfaceRecord& rec) const override {
          hitSurfaceRecord tempRec;
          bool hitAnything = false;
          auto closestSoFar = ray_t.getMax();

          //For each object in the list, we call it's own hit method, and update the hitAnything accordingly
          for (const auto& object : objects) {
              if (object->hit(r, Interval(ray_t.getMin(), closestSoFar), tempRec)) {
                  hitAnything = true;
                  closestSoFar = tempRec.t;
                  rec = tempRec;
              }
          }

          return hitAnything;
      }
};
#endif //HITABLELIST_H
