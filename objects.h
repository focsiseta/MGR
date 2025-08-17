//
// Created by focsiseta on 8/7/25.
//

#ifndef OBJECTS_H
#define OBJECTS_H
#include <memory>
#include <vector>

#include "interval.h"
#include "ray.h"

using std::shared_ptr;
using std::vector;

//So the idea behind hitSphere is to check if our ray will EVER hit our sphere.
//I've added the actual resolution of the equation for t as to give at which t
//our ray WILL hit the sphere.

// double  hitSphere(vec3 spherePosition, double radius, ray& r) {
//     auto C_Q = (spherePosition - r.Origin());
//     auto a = r.Direction().length_squared();
//     auto h =dot(r.Direction(),C_Q);
//     auto c = C_Q.length_squared() - radius   * radius;
//     //b² - 4ac
//     auto discriminant = (h*h - a*c);
//     if (discriminant < 0) return -1;
//     return (h - std::sqrt(discriminant))/a;
// }
class material;

class hitRecord {
public:
    vec3 hitPosition;
    vec3 normal;
    shared_ptr<material> mat;
    bool frontFace;
    double t;
    void setFaceNormal(const ray& r, vec3& outwardNormal) {
        //!!!!!!: !outwardNormal needs to be unit length!

        frontFace = dot(outwardNormal,r.direction) < 0.0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
class hittable {
public:
    virtual ~hittable() = default; //default ci dice che ricade sulla implementazione di default generata dal compilatore
    //=0 sta per che non esiste nessuna implementazione di default ed è completamente virtuale
    //const è una promessa verso il fatto che non modifichiamo l'oggetto
    virtual bool hit(ray& r, const interval& deltaT, hitRecord& record) const = 0;

};

class hittableList : public hittable {
private:
    vector<shared_ptr<hittable>> objects;
    public:
    hittableList(vector<shared_ptr<hittable>> objects) : objects(objects) {}
    hittableList() {}
    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }
    void clear() {
        objects.clear();
    }
    // bool hit(ray& r, double ray_tmin,double ray_tmax, hitRecord& record) const override {
    //     hitRecord tempRecord;
    //     bool hitAnything = false;
    //     auto closestSoFar = ray_tmax;
    //     for (std::shared_ptr<hittable> object : objects) {
    //         if (object->hit(r,ray_tmin,ray_tmax,tempRecord)) {
    //             hitAnything = true;
    //             if (closestSoFar < tempRecord.t) {
    //                 closestSoFar = tempRecord.t;
    //             }
    //             record = tempRecord;
    //         }
    //     }
    //     return hitAnything;
    // }
    bool hit(ray& r, const interval& deltaT, hitRecord& record) const override {
        hitRecord tempRecord;
        bool hitAnything = false;
        auto closestSoFar = deltaT.max;
        for (std::shared_ptr<hittable> object : objects) {
            if (object->hit(r,deltaT,tempRecord)) {
                hitAnything = true;
                if (closestSoFar < tempRecord.t) {
                    closestSoFar = tempRecord.t;
                }
                record = tempRecord;
            }
        }
        return hitAnything;
    }



};

class sphere : public hittable {
    public:
    vec3 center;
    double radius;
    //sphere(vec3 center, double radius) : center(center), radius(radius) {}
    sphere(vec3 center, double radius,shared_ptr<material> matt) : center(center) ,radius(radius), mat(matt) {}
    bool hit(ray &r, const interval& deltaT, hitRecord &record) const override {
        const auto C_Q = (center - r.Origin());
        auto a = r.Direction().length_squared();
        auto h = dot(r.Direction(),C_Q);
        auto c = C_Q.length_squared() - radius   * radius;
        //b² - 4ac
        auto discriminant = (h*h - a*c);
        if (discriminant < 0) return false;
        auto t = (h - std::sqrt(discriminant))/a;
        auto tt =  (h + std::sqrt(discriminant))/a;
        t = t < tt ? t : tt;
        if (!deltaT.contains(t)) {
            return false;
        }
        record.t = t;
        record.hitPosition = r.at(t);
        vec3 n = (record.hitPosition - center) / radius;
        record.mat = mat;
        record.setFaceNormal(r,n);
        return true;
    }
    void addMaterial(const shared_ptr<material>& matt) {
        mat = matt;
    }
    shared_ptr<material> getMaterial() const {
        return mat;
    }
    ~sphere() override = default;
private:
    shared_ptr<material> mat;
};

#endif //OBJECTS_H
