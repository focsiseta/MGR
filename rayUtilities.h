//
// Created by focsiseta on 8/16/25.
//

#ifndef RAYUTILITIES_H
#define RAYUTILITIES_H

vec3 reflect(const ray& r, const hitRecord& rec) {
    vec3 unitV = unit_vector(r.direction);
    auto scale = dot(unitV,rec.normal);
    return unitV -2 * scale * rec.normal;

}
vec3 refract(const ray &r,const hitRecord& rec,double etaRatio) {
    if (etaRatio == 0) return reflect(r,rec);
    etaRatio = rec.frontFace ? etaRatio : 1.0/etaRatio;
    vec3 unitDirection = unit_vector(r.direction);
    vec3 perp = etaRatio * (unitDirection + dot(-unitDirection, rec.normal)*rec.normal);
    vec3 par = - sqrt(1 - perp.length_squared()) * rec.normal;
    return perp + par;

}

#endif //RAYUTILITIES_H
