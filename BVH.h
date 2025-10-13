//
// Created by eluvian on 12/10/25.
//

#ifndef BVH_H
#define BVH_H
#include <algorithm>
#include <filesystem>

#include "objects.h"

class BVHNode final : public hittable {
public:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    AABB bound;
    BVHNode(hittableList list) : BVHNode(list.objects,0, list.objects.size() ) {}
    BVHNode(std::vector<shared_ptr<hittable>>& objects,size_t start, size_t end) {
        int axis = static_cast<int> (random_double(0,3)); //random int
        auto comp = axis == 0 ? comparator_x : axis == 1 ? comparator_y : comparator_z;
        int span = end - start;
        if (span == 1)
            left = right = objects[start];
        else if (span == 2) {
            left = objects[start];
            right = objects[start + 1];
        }else {
            std::sort(std::begin(objects)+start,std::begin(objects)+end,comp);
            auto mid = start + span/2;
            left = make_shared<BVHNode>(objects, start,mid);
            right = make_shared<BVHNode>(objects,mid, end);
        }
        bound = AABB(left->getAABB(),right->getAABB());

    }
    AABB buildAABB() const override{return bound;}
    AABB getAABB() const override {
        return bound;
    }
    bool hit(ray& r, const interval& deltaT, hitRecord& record) const override {
        if (!bound.hit(r,deltaT))
            return false;
        bool hitLeft = left->hit(r,deltaT,record);
        bool hitRight = right->hit(r, interval(deltaT.min, hitLeft ? record.t : deltaT.max), record);
        return hitLeft || hitRight;
    }
    bool static comparator(const shared_ptr<hittable> obj1, const shared_ptr<hittable> obj2, int axis) {
        interval a = obj1->getAABB().axis_interval(axis);
        interval b = obj2->getAABB().axis_interval(axis);

        return a.min < b.min;
    }
    bool static comparator_x(const shared_ptr<hittable> obj1, const shared_ptr<hittable> obj2) {
        return comparator(obj1,obj2,0);
    }
    bool static comparator_y(const shared_ptr<hittable> obj1, const shared_ptr<hittable> obj2) {
        return comparator(obj1,obj2,1);
    }
    bool static comparator_z(const shared_ptr<hittable> obj1, const shared_ptr<hittable> obj2) {
        return comparator(obj1,obj2,2);
    }




};


#endif //BVH_H
