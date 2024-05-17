#ifndef Vector_hpp
#define Vector_hpp

#include <functional>
#include <stdio.h>
#include <iostream>

struct Vector {
    double x = 0;
    double y = 0;
    
    Vector();
    Vector(double x, double y);
    
    double& operator[](int i);
    bool operator==(Vector vector);
    bool operator!=(Vector vector);
    Vector operator+(Vector vector);
    Vector operator-(Vector vector);
    Vector operator*(double scala);
    double length();
    void normalize();
};

#endif /* Vector_hpp */
