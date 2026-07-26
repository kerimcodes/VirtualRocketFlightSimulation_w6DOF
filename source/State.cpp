#include "State.h"

State::State(const Vector3& p,const Vector3& v,const Vector3& a,const Vector3& angular_p,const Vector3& angular_v,const Vector3& angular_a) 
: position(p),velocity(v),acceleration(a), theta(angular_p),angularVelocity(angular_v),angularAcceleration(angular_a) {}