//
// Created by eluvian on 11/10/25.
//

#ifndef AABB_H
#define AABB_H
#include "interval.h"
#include "ray.h"


class ray;
typedef vec3 point3;
class AABB {
    public:
    //can be also expressed with 2 vectors
    interval x,y,z;
    AABB(){}
    AABB(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {}
    AABB(const interval& x, const interval& y) : x(x), y(y) {}
    AABB(const point3& pointA, const point3& pointB) {
        x = interval(pointA.x() <= pointB.x() ? pointA.x() : pointB.x(), pointA.x() >= pointB.x() ? pointA.x() : pointB.x());
        y = interval(pointA.y() <= pointB.y() ? pointA.y() : pointB.y(), pointA.y() >= pointB.y() ? pointA.y() : pointB.y());
        z = interval(pointA.z() <= pointB.z() ? pointA.z() : pointB.z(), pointA.z() >= pointB.z() ? pointA.z() : pointB.z());
    }
    AABB(const AABB& box1, const AABB& box2) {
        x = interval(box1.x,box2.x);
        y = interval(box1.y,box2.y);
        z = interval(box1.z,box2.z);
    }
    const interval& axis_interval(int n) const{
        if (n == 0) return x;
        if (n == 1) return y;
        return z;
    }
    bool hit(const ray& r, interval rayInterval) const{
        const vec3& origin = r.origin;
        const vec3& direction = r.direction;
        for (int i = 0; i < 3; i++) {
            const interval& intervalOnAxis = axis_interval(i);
            double invDistance = 1/direction[i];
            double t0 = (intervalOnAxis.min - origin[i])*invDistance;
            double t1 = (intervalOnAxis.max - origin[i])*invDistance;
            bool isFront = t0 < t1;
            if (isFront) {
                if (rayInterval.min < t0) rayInterval.min = t0;
                if (rayInterval.max > t1) rayInterval.max = t1;
            }else {
                if (rayInterval.min > t1) rayInterval.min = t1;
                if (rayInterval.max < t0) rayInterval.max = t0;
            }
            if (rayInterval.min > rayInterval.max) return false;

        }
        return true;
    }
};

#endif //AABB_H
