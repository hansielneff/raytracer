#ifndef COORDINATE_FRAME_H
#define COORDINATE_FRAME_H

#include "vec3.h"

class CoordinateFrame {
public:
    CoordinateFrame(Vec3 origin, Vec3 forward, Vec3 up) { construct(origin, forward, up); }

    Vec3 origin() const { return o; }
    Vec3 u() const { return x; }
    Vec3 v() const { return y; }
    Vec3 w() const { return z; }

private:
    void construct(Vec3 origin, Vec3 forward, Vec3 up);
    Vec3 o, x, y, z;
};

std::ostream& operator<<(std::ostream &os, const CoordinateFrame &cf);

#endif