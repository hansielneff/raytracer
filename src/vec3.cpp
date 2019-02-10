#include "vec3.h"

#include <cmath>

Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2) {
    return Vec3(
        vec1.x() + vec2.x(), 
        vec1.y() + vec2.y(), 
        vec1.z() + vec2.z()
    );
}

Vec3& operator+=(Vec3 &vec1, const Vec3 &vec2) {
    vec1 = vec1 + vec2;
    return vec1;
}

Vec3 operator-(const Vec3 &vec1, const Vec3 &vec2) {
    return Vec3(
        vec1.x() - vec2.x(), 
        vec1.y() - vec2.y(), 
        vec1.z() - vec2.z()
    );
}

Vec3& operator-=(Vec3 &vec1, const Vec3 &vec2) {
    vec1 = vec1 - vec2;
    return vec1;
}

Vec3 operator*(const Vec3 &vec, const float scalar) {
    return Vec3 {
        vec.x() * scalar,
        vec.y() * scalar,
        vec.z() * scalar
    };
}

Vec3& operator*=(Vec3 &vec, const float scalar) {
    vec = vec * scalar;
    return vec;
}

Vec3 operator*(const float scalar, const Vec3 &vec) {
    return Vec3 {
        scalar * vec.x(),
        scalar * vec.y(),
        scalar * vec.z()
    };
}

Vec3& operator*=(const float scalar, Vec3 &vec) {
    vec = scalar * vec;
    return vec;
}

Vec3 operator/(const Vec3 &vec, const float scalar) {
    return Vec3 {
        vec.x() / scalar,
        vec.y() / scalar,
        vec.z() / scalar
    };
}

Vec3& operator/=(Vec3 &vec, const float scalar) {
    vec = vec / scalar;
    return vec;
}

Vec3 operator-(const Vec3 &vec) {
    return Vec3(-vec.x(), -vec.y(), -vec.z());
}

float dot(const Vec3 &vec1, const Vec3 &vec2) {
    return vec1.x() * vec2.x() + 
           vec1.y() * vec2.y() + 
           vec1.z() * vec2.z();
}

Vec3 cross(const Vec3 &vec1, const Vec3 &vec2) {
    return Vec3(
        vec1.y() * vec2.z() - vec1.z() * vec2.y(),
        vec1.z() * vec2.x() - vec1.x() * vec2.z(),
        vec1.x() * vec2.y() - vec1.y() * vec2.x()
    );
}

float magnitude(const Vec3 &vec) {
    return sqrt(
        vec.x() * vec.x() + 
        vec.y() * vec.y() + 
        vec.z() * vec.z()
    );
}

Vec3 normalized(const Vec3 &vec) {
    return vec / magnitude(vec);
}

Vec3 clamp(const Vec3 &vec, float min, float max) {
    return Vec3(
        fmin(max, fmax(vec.x(), min)),
        fmin(max, fmax(vec.y(), min)),
        fmin(max, fmax(vec.z(), min))
    );
}

std::ostream& operator<<(std::ostream &os, const Vec3 &vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return os;
}