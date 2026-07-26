#pragma once
#include "Vector3.h"


Vector3 operator+(const Vector3 &, const Vector3 &);
Vector3 operator-(const Vector3 &, const Vector3 &);
Vector3 operator*(const Vector3 &, const double);
Vector3 operator*(const double, const Vector3 &);
Vector3 operator/(const Vector3 &, const double);
