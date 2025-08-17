//
// Created by focsiseta on 8/9/25.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#include "utilities.h"

class interval {
    public:
    double max,min;
    interval() : max{-infinity}, min{infinity} {}
    interval(double min, double max) : min{min}, max{max} {}
    bool surrounds(const double x) const{
        return min < x && max > x;
    }
    bool contains(const double x) const{
        return min <= x && max >= x;
    }
    double clamp(const double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};

static const interval empty{+infinity, -infinity};
static const interval universe{-infinity, infinity};

#endif //INTERVAL_H
