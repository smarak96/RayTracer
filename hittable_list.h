#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable_objects.h"
#include<vector>
#include<memory>
using namespace std; //if i use this command, i will bring all names into current scope
// so i will use the below only

// using std::make_shared;
// using std::shared_ptr;


class hittable_list : public hittable{
    public:
    vector<shared_ptr<hittable>> objects;
    hittable_list(){}
    hittable_list(shared_ptr<hittable> object)
    {
        addToListOfObjects(object);
    }
    void clear(){objects.clear();}
    void addToListOfObjects(shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }   
    bool hit(ray& r,interval_class ray_t,hit_record& rec)
    {
        hit_record temp_record;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;
        for(int i =0;i<objects.size();i++)
        {
            if(objects[i]->hit(r,interval_class(ray_t.min,closest_so_far),temp_record))
            {
                hit_anything = true;
                closest_so_far = temp_record.t;
                rec = temp_record;
            }
        }
        return hit_anything;
    }
    
};
#endif