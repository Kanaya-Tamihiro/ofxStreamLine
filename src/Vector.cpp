#include "Vector.hpp"
#include <cmath>

Vector::Vector() {}

Vector::Vector(double _x, double _y) {
    x = _x;
    y = _y;
}

double& Vector::operator[](int i) {
    return i == 0 ? x : y;
}

bool Vector::operator==(Vector vector) {
    return x == vector.x && y == vector.y;
}

bool Vector::operator!=(Vector vector) {
    return x != vector.x || y != vector.y;
}

Vector Vector::operator+(Vector vector) {
    return Vector(x+vector.x, y+vector.y);
}

Vector Vector::operator-(Vector vector) {
    return Vector(x-vector.x, y-vector.y);
}

Vector Vector::operator*(double scala) {
    return Vector(x*scala, y*scala);
}

double Vector::length() {
    return std::sqrt(x*x + y*y);
}

bool Vector::normalize() {
    double l = std::sqrt(x*x + y*y);
    x = x / l;
    y = y / l;
}
