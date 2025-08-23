//
// Created by focsiseta on 8/11/25.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "objects.h"
#include "rayUtilities.h"
#define INDEX_AIR 1.00047
#define INDEX_VACUUM  1.000
#define INDEX_WATER  1.3333333
#define INDEX_ICE  1.31
#define INDEX_GLASS  1.5
#define INDEX_DIAMOND  2.417

class material {
    public:
    virtual ~material() = default;
    material() = default;
    virtual bool scatter(const ray& r, const hitRecord& rec, color& attenuation, ray& scattered) const {
        return false;
    }
    virtual double getRefractionIndex() const {
        return 0.0;
    }

};
class lambert: public material {
    public:
    color albedo;
    lambert(color & albedo) : albedo(albedo) {}
    lambert(color &&albedo) : albedo(albedo) {}
    bool scatter(const ray& r, const hitRecord& rec, color& attenuation, ray& scattered) const override{
        vec3 scatterDirection = rec.normal + randomUnitDir();
        if (scatterDirection.near_zero()) scatterDirection = rec.normal;
        scattered = ray{rec.hitPosition, scatterDirection};
        attenuation = albedo;
        return true;
    }
};
class metallic: public material {
public:
    color albedo;
    double fuzzy = 0.0;
    metallic(color& albedo) : albedo(albedo) {}
    metallic(color&& albedo) : albedo(albedo) {}

    bool scatter(const ray &r, const hitRecord &rec, color &attenuation, ray &scattered) const override {
        vec3 unitV = unit_vector(r.direction);
        vec3 reflected = reflect(unitV, rec.normal);
        vec3 fuzzyReflected = unit_vector(reflected) + (vectorInsideEmisphere(rec.normal) * fuzzy);
        fuzzyReflected = unit_vector(fuzzyReflected);
        scattered = ray{rec.hitPosition, fuzzyReflected};
        attenuation = albedo;
        return (dot( rec.normal,(fuzzyReflected)) > 0.0);
    }
    void setFuzzy(double fuz) {
        fuzzy = fuz;
    }

};
class dielectric : public material {
    public:
    color albedo;
    double refractIndex;
    dielectric(color&& albedo,double refIndex) : albedo(albedo), refractIndex(refIndex) {
    }
    dielectric(double refIndex) : albedo(color{1,1,1}), refractIndex(refIndex) {
    }
    dielectric(color& albedo,double refIndex) : albedo(albedo), refractIndex(refIndex) {
    }

    bool scatter(const ray &r, const hitRecord &rec, color &attenuation, ray &scattered) const override {
        double etaRatio = refractIndex;
        etaRatio = rec.frontFace ? 1.0/etaRatio : refractIndex;
        vec3 unitDirection = unit_vector(r.direction);
        double cosEta  =std::fmin( dot(-unitDirection,rec.normal),1.0);
        double sinEta = sqrt(1.0 - cosEta*cosEta);
        bool isReflect = etaRatio * sinEta > 1.0;
        vec3 scatterDirection;
        //|| reflectance(cosEta,etaRatio) > random_double()
        auto reflct = reflectance(cosEta,etaRatio);
        auto rrr = random_double();
        if (isReflect ||  reflct > rrr) {
            scatterDirection = reflect(unitDirection, rec.normal);
        }else {
            scatterDirection = refract(unitDirection,rec.normal,etaRatio);
        }
        scattered = ray{rec.hitPosition, scatterDirection};
        attenuation = albedo;
        return true;
    }
    double getRefractionIndex() const override {
        return refractIndex;
    }

};


#endif //MATERIAL_H
