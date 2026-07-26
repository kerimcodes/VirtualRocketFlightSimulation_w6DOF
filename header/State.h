#pragma once 

#include "Vector3.h"

class State
{
private:
    Vector3 position, velocity, acceleration;
    Vector3 theta,angularVelocity, angularAcceleration;

public:
    State() : position(0,0,0),velocity(0,0,0),acceleration(0,0,0), angularVelocity(0,0,0),angularAcceleration(0,0,0) {}
    State(const Vector3 &,const Vector3 &,const Vector3 &, const Vector3&,const Vector3&,const Vector3&);

    Vector3 get_P() const { return position; }
    Vector3 get_V() const { return velocity; }
    Vector3 get_A() const { return acceleration; }
    Vector3 get_theta() const { return theta; }
    Vector3 get_AngularV() const { return angularVelocity; }
    Vector3 get_AngularA() const { return angularAcceleration; }

    void set_P(const Vector3& p) { position = p; }
    void set_V(const Vector3& v) { velocity = v; }
    void set_A(const Vector3 &a) { acceleration = a; }
    void set_theta(const Vector3 &t) { theta = t; }
    void set_AngularV(const Vector3 &a_v) { angularVelocity = a_v; }
    void set_AngularA(const Vector3 &a_a) { angularAcceleration = a_a; }
};