#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>
class interval_class
{
    public:

    double min;
    double max;

    interval_class()
    {
        min = std::numeric_limits<double>::infinity();
        max = -std::numeric_limits<double>::infinity();
    }
    interval_class(double min,double max)
    {
        this->min = min;
        this->max = max;
    }
    double size()
    {
        return max-min;
    }
    bool contains(double x)
    {
        return x>=min && x<=max;
    }
    bool surrounds(double x)
    {
        return x>min && x< max;
    }
    double clamp(double x)
    {
        return x<min?min:(x>max?max:x);
    }
    static interval_class empty, universe;
};

interval_class interval_class::empty = interval_class(std::numeric_limits<double>::infinity(),-std::numeric_limits<double>::infinity());
interval_class interval_class::universe = interval_class(-std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity());

#endif
