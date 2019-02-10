#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "vec3.h"

class PointLight {
public:
    PointLight(Vec3 position = Vec3(0, 0, 0), 
        float intensity = 1, Vec3 color = Vec3(1, 1, 1)) : 
        pos { position },
        intens { intensity },
        col { color } {}
    
    Vec3 position() const { return pos; }
    void position(Vec3 position) { pos = position; }

    Vec3 color() const { return col; }
    void color(Vec3 color) { col = color; }

    float intensity() const { return intens; }
    void position(float intensity) { intens = intensity; }

private:
    Vec3 pos;
    Vec3 col;
    float intens;
};

#endif