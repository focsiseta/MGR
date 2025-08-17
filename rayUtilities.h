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
vec3 reflect(const vec3& rayDirection,const vec3& normal ) {
    return rayDirection -2 * dot(rayDirection,normal) * normal;
}
vec3 refract(const ray &r,const hitRecord& rec,double etaRatio) {
    vec3 unitDirection = unit_vector(r.direction);
    double cosEta  = dot(-unitDirection,rec.normal);
    double sinEta = sqrt(1.0 - cosEta*cosEta);
    if (sinEta * etaRatio > 1) return reflect(r,rec);
    vec3 perp = etaRatio * (unitDirection + dot(-unitDirection, rec.normal)*rec.normal);
    vec3 par = - sqrt(1 - perp.length_squared()) * rec.normal;
    return perp + par;

}
//fromToRatio referes to the ratio of the media exiting and the one entering
vec3 refract(const vec3& direction,const vec3& normal, double fromToRatio) {
    vec3 perp = fromToRatio * (direction + dot(-direction, normal)*normal);
    vec3 par = - sqrt(1 - perp.length_squared()) * normal;
    return perp + par;
}

#endif //RAYUTILITIES_H
