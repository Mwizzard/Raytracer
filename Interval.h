//
// Created by mwizzard on 5/3/25.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#include "Utils.h"
//Class used to manage real valued interval easily
class Interval {
    private:
      double min, max;
    public:

    //Constructors
    Interval(){min = -infinity; max = infinity;}
    Interval(double min, double max){this->min = min; this->max = max;}

    double clamp(double x ) const{
        if (x < min)
          return min;
        if (x > max)
          return max;
      return x;
    }

    //Size of the interval
    double size(){return max - min;}

    // x is in the interval
    bool contains(double x){
      return min <= x && x <= max;
    }

    bool surrounds(double x){
      return x > min && x < max;
    }

    //getters
    double getMax(){return max;}
    double getMin(){return min;}

    //specific types of interval
    static const Interval empty, universe;
};

const Interval Interval::empty    = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
#endif //INTERVAL_H
