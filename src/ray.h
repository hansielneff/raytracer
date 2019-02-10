#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Sphere {
    float radius;
    Vec3 center;
    Vec3 color;
};

class Ray {
public:
    Ray() : a { Vec3() }, b { Vec3() } {}
    Ray(Vec3 origin, Vec3 direction) : a { origin }, b { direction } {}

    Vec3 origin() const { return a; }
    void origin(Vec3 origin) { a = origin; }

    Vec3 direction() const { return b; }
    void direction(Vec3 direction) { b = direction; }

    Vec3 point(float t) const { return a + t * b; }

private:
    Vec3 a, b;
};

float intersectsSphere(const Ray &r, const Sphere &sphere);

std::ostream& operator<<(std::ostream &os, const Ray &r);

#endif