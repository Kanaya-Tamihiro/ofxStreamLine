#ifndef Stream_hpp
#define Stream_hpp

#include <stdio.h>
#include "LookupGrid.hpp"
#include "Option.hpp"
#include "Vector.hpp"

class Stream {
public:
    const int FORWARD = 1;
    const int BACKWARD = 2;
    const int DONE = 3;
    
    static const Vector ZERO_VECTOR;
    
    Option* option = NULL;
    std::vector<Vector> points;
    Vector head;
    Vector start;
    int state;
    double ownGridSeparation;
    LookupGrid* ownGrid = NULL;
    LookupGrid* grid = NULL;
    int lastCheckedSeed = -1;
    
    std::function<bool(double)> isShorterThanStreamWideSeparation;
    std::function<bool(double)> isShorterThanStreamNarrowSeparation;
    std::function<bool(double)> hasCollisionToOwnStream;

    Stream(Vector start, LookupGrid* grid, Option* option);
    ~Stream();
    bool isSame(double a, double b);
    bool getNextValidSeed(Vector* seed);
    bool next();
    bool growForward(Vector* result);
    bool growBackward(Vector* result);
    bool growByVelocity(Vector pos, Vector velocity, Vector* result);
    bool notifyPointAdded(Vector point);
    Vector getVelocity (Vector point);
    Vector rk4(Vector point, double dt);
};

#endif /* Stream_hpp */
