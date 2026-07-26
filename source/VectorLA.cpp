#include "VectorLA.h"
#include "VectorOperation.h"
#include <iostream>
#include <cmath>

double dotproduct(const Vector3& v1,const Vector3& v2)
{
    double result = v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
    return result;
}

double length(const Vector3& vector)
{
    return std::sqrt(dotproduct(vector, vector));
}

Vector3 crossproduct(const Vector3& v1,const Vector3& v2)
{
    double x = v1.getY() * v2.getZ() - v1.getZ() * v2.getY();
    double y = v1.getZ() * v2.getX() - v1.getX() * v2.getZ();
    double z = v1.getX() * v2.getY() - v1.getY() * v2.getX();
    Vector3 result(x, y, z);
    return result;
}

Vector3 unitvector(const Vector3& vector)
{
    double len = length(vector);
    if (len != 0)
    {
        return vector / len;
    }
    return vector;
}