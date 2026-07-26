#include "VectorOperation.h"
#include <stdexcept>
#include <iostream>

Vector3 operator+(const Vector3& v1,const Vector3& v2)
{
    double x = v1.getX() + v2.getX();
    double y = v1.getY() + v2.getY();
    double z = v1.getZ() + v2.getZ();
    Vector3 result(x, y, z);
    return result;
}

Vector3 operator-(const Vector3& v1,const Vector3& v2)
{
    double x = v1.getX() - v2.getX();
    double y = v1.getY() - v2.getY();
    double z = v1.getZ() - v2.getZ();
    Vector3 result(x, y, z);
    return result;
}

Vector3 operator*(const Vector3& vector, const double number)
{
    double x = vector.getX() * number;
    double y = vector.getY() * number;
    double z = vector.getZ() * number;
    Vector3 result(x, y, z);
    return result;
}

Vector3 operator*(const double number, const Vector3& vector)
{
    return vector * number;
}

Vector3 operator/(const Vector3& vector, const double number)
{   
    if (std::abs(number) < 1e-15) // Zero control
		throw std::invalid_argument("Error: Division by zero or near-zero scalar!\n");
   
    double x = vector.getX() / number;
    double y = vector.getY() / number;
    double z = vector.getZ() / number;
    Vector3 result(x, y, z);
    return result;
}

