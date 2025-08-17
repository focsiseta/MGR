//
// Created by focsiseta on 8/6/25.
//

#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray {
    public:
    vec3 origin;
    vec3 direction;
    ray() = default;
    ray(const vec3& origin, const vec3& direction) : origin(origin), direction(direction) {}
    ray(vec3&& origin, vec3&& direction) : origin(origin), direction(direction) {}
    vec3 at(double t) const {
        return origin + direction * t;
    }
    const vec3& Origin(){return (this->origin);}
    const vec3& Direction(){return (this->direction);}
};


// vec3 reflect(const vec3& v, const vec3& n) {
//     return v - 2*dot(-v, n) * n;
// }
// vec3 refract(const vec3& v, const vec3& n, double etai_over_etat,bool frontFace) {
//     //lets say that if ratio of indices is 0 or less, we reflect
//     if (etai_over_etat <= 0) return reflect(v,n);
//     double refractiveIndex = frontFace ? etai_over_etat : 1.0/etai_over_etat;
//     vec3 unitDirection = unit_vector(r.direction);
//     vec3 perp = etaRatio * (unitDirection + dot(-unitDirection, rec.normal)*rec.normal);
//     vec3 par = - sqrt(1 - perp.length_squared()) * rec.normal;
//
//
// }




#endif //RAY_H
