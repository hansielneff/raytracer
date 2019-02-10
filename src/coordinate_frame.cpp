#include "coordinate_frame.h"

void CoordinateFrame::construct(Vec3 origin, Vec3 forward, Vec3 up) {
    o = origin;
    z = normalized(forward);
    x = normalized(cross(up, z));
    y = cross(x, z);
}

std::ostream& operator<<(std::ostream &os, const CoordinateFrame &cf) {
    os << "Origin: " << cf.origin() << '\n' <<
        "U: " << cf.u() << ", V: " << cf.v() << 
        ", W: " << cf.w();
    return os;
}