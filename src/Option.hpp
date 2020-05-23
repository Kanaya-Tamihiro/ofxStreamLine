#ifndef Option_hpp
#define Option_hpp

#include <stdio.h>
#include "Vector.hpp"

struct Option {
    double xrange[2] = {0, 1};
    double yrange[2] = {0, 1};
    Vector seed;
    double scale = 1;
    std::function<Vector(Vector)> vectorFunc;
    std::function<void(std::vector<Vector>*)> onStreamAdded;
    std::function<bool(Vector, Vector)> onPointAdded;
    bool forwardOnly = false;
    double wideSeparation = 0;
    double narrowSeparation = 0;
    double dt = 0.05;
    int stepsPerIteration = 10;
};

#endif /* Option_hpp */
