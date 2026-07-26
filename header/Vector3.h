#pragma once

class Vector3 
{
private:
    double x, y, z;

public:
    Vector3() : x(0),y(0),z(0) {};                                          
    Vector3(double , double , double );     

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    void setX(double xVal) { x = xVal; }
    void setY(double yVal) { y = yVal; }
    void setZ(double zVal) { z = zVal; }

    void print() const;
};