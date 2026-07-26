#pragma once
#include "Vector3.h"
#include "VectorOperation.h"


double length(const Vector3&);
double dotproduct(const Vector3 &, const Vector3 &);
Vector3 crossproduct(const Vector3 &, const Vector3 &);
Vector3 unitvector(const Vector3&);