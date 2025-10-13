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
    interval(const interval& box1, const interval& box2) {
        min = box1.min < box2.min ? box1.min : box2.min;
        max = box1.max > box2.max ? box1.max : box2.max;
    }
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
    interval expand(int delta) {
        int pad = delta * 0.5;
        return interval(min - pad, max + pad);
    }
};

static const interval empty{+infinity, -infinity};
static const interval universe{-infinity, infinity};

#endif //INTERVAL_H
