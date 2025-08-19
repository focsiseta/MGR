//
// Created by focsiseta on 8/16/25.
//

#ifndef RAYUTILITIES_H
#define RAYUTILITIES_H


vec3 reflect(const vec3& rayDirection,const vec3& normal ) {
    return rayDirection +2 * dot(-rayDirection,normal) * normal;
}
//fromToRatio referes to the ratio of the media exiting and the one entering
vec3 refract(const vec3& direction,const vec3& normal, double fromToRatio) {
    auto cosTheta = std::fmin(dot(-direction, normal),1.0);
    vec3 perp = fromToRatio * (direction + cosTheta*normal);
    vec3 par = - sqrt(std::fabs(1 - perp.length_squared())) * normal;
    return perp + par;
}

#endif //RAYUTILITIES_H
