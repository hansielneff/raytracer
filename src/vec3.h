#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
public:
    Vec3() : elem { 0, 0, 0 } {}
    Vec3(float x, float y, float z) : elem { x, y, z } {}

    float x() const { return elem[0]; }
    float y() const { return elem[1]; }
    float z() const { return elem[2]; }
    float r() const { return elem[0]; }
    float g() const { return elem[1]; }
    float b() const { return elem[2]; }

    void x(float x) { elem[0] = x; }
    void y(float y) { elem[1] = y; }
    void z(float z) { elem[2] = z; }
    void r(float r) { elem[0] = r; }
    void g(float g) { elem[1] = g; }
    void b(float b) { elem[2] = b; }

private:
    float elem[3];
};

Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2);
Vec3& operator+=(Vec3 &vec1, const Vec3 &vec2);

Vec3 operator-(const Vec3 &vec1, const Vec3 &vec2);
Vec3& operator-=(Vec3 &vec1, const Vec3 &vec2);

Vec3 operator*(const Vec3 &vec, const float scalar);
Vec3& operator*=(Vec3 &vec, const float scalar);

Vec3 operator*(const float scalar, const Vec3 &vec);
Vec3& operator*=(const float scalar, const Vec3 &vec);

Vec3 operator/(const Vec3 &vec, const float scalar);
Vec3& operator/=(Vec3 &vec, const float scalar);

Vec3 operator-(const Vec3 &vec);

float dot(const Vec3 &vec1, const Vec3 &vec2);
Vec3 cross(const Vec3 &vec1, const Vec3 &vec2);
float magnitude(const Vec3 &vec);
Vec3 normalized(const Vec3 &vec);
Vec3 clamp(const Vec3 &vec, float min, float max);

std::ostream& operator<<(std::ostream &os, const Vec3 &vec);

#endif