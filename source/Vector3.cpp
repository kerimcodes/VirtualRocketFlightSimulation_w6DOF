#include "Vector3.h"
#include <iostream>
Vector3::Vector3(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {};

void Vector3::print() const
{
    std::cout << "[ " << x << " " << y << " " << z << " ]\n";
}


