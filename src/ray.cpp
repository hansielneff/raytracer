#include "ray.h"

#include <iostream>
#include <cmath>

float intersectsSphere(const Ray &r, const Sphere &sphere) {
    float a = dot(r.direction(), r.direction());
    float b = dot(2 * r.direction(), r.origin() - sphere.center);
    float c = dot(r.origin() - sphere.center, r.origin() - sphere.center) - 
        sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        float t1 = (-b + sqrt(discriminant)) / (2 * a);
        float t2 = (-b - sqrt(discriminant)) / (2 * a);
        return fmin(t1, t2);
    } else if (discriminant == 0) {
        return -b / 2 * a;
    } else {
        return 0;
    }
}

std::ostream& operator<<(std::ostream &os, const Ray &r) {
    os << "Origin: " << r.origin() << '\n' <<
        "Direction: " << r.direction() << '\n';
    return os;
}