#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_writer.h"

#include <cmath>
#include <vector>

#include "vec3.h"
#include "ray.h"
#include "coordinate_frame.h"
#include "point_light.h"

Vec3 color(CoordinateFrame cam, const Ray &ray, std::vector<Sphere> objs, std::vector<PointLight> lights) {
    float shortestDist = 10000;
    Sphere *closestSphere = nullptr;
    for (std::vector<Sphere>::size_type i = 0; i < objs.size(); i++) {
        float t = intersectsSphere(ray, objs[i]);
        if (t > 0 && t < shortestDist) {
            shortestDist = t;
            closestSphere = &objs[i];
        }
    }

    if (closestSphere != nullptr) {
        Vec3 intersectPoint = ray.point(shortestDist);
        Vec3 n = normalized(intersectPoint - closestSphere->center);
        Vec3 v = normalized(cam.origin() - intersectPoint);
        
        Vec3 color(closestSphere->color.r() * 0.2f, closestSphere->color.g() * 0.2f, closestSphere->color.b() * 0.2f);
        
        for (std::vector<PointLight>::size_type i = 0; i < lights.size(); i++) {
            Vec3 l = normalized(lights[i].position() - intersectPoint);
            Vec3 h = normalized(v + l);

            color += Vec3(
                closestSphere->color.r() * (lights[i].color().r() * lights[i].intensity()) * fmax(0, dot(n, l)) +
                    0.5f * (lights[i].color().r() * lights[i].intensity()) * pow(fmax(0, dot(n, h)), 25),
                closestSphere->color.g() * (lights[i].color().g() * lights[i].intensity()) * fmax(0, dot(n, l)) +
                    0.5f * (lights[i].color().g() * lights[i].intensity()) * pow(fmax(0, dot(n, h)), 25),
                closestSphere->color.b() * (lights[i].color().b() * lights[i].intensity()) * fmax(0, dot(n, l)) +
                    0.5f * (lights[i].color().b() * lights[i].intensity()) * pow(fmax(0, dot(n, h)), 25)
            );
        }

        color = clamp(color, 0, 1);

        return color;
    }

    Vec3 unitDir = normalized(ray.direction());
    float t = 0.5f * (unitDir.y() + 1);
    return t * Vec3(0, 0, 0) +
        (1.0f - t) * Vec3(0.2f, 0.2f, 0.6f);
}

int main() {
    CoordinateFrame camFrame(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0));

    constexpr int width = 1920;
    constexpr int height = 1080;
    constexpr int comps = 3;
    constexpr int quality = 100;
    unsigned char *imgData = new unsigned char[width * height * comps];

    std::vector<Sphere> objects {
        Sphere { 1, Vec3(2, 0, 4), Vec3(0.6f, 0.2f, 0.2f) },
        Sphere { 1, Vec3(-2, 0, 3), Vec3(0.2f, 0.6f, 0.2f) },
        Sphere { 1, Vec3(0, 0, 5), Vec3(0.2f, 0.2f, 0.6f) }
    };

    std::vector<PointLight> lights {
        PointLight(Vec3(0, 1, 3)),
        PointLight(Vec3(4, -2, 3))
    };

    unsigned char *comp = imgData;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float planeDistance = 1;
            float top = 1, right = top * (float(width) / float(height));
            float bottom = -top, left = -right;

            float u = left + (right - left) * (x + 0.5f) / width;
            float v = bottom + (top - bottom) * (y + 0.5f) / height;

            Ray ray(camFrame.origin(), u * camFrame.u() + 
                v * camFrame.v() + -planeDistance * camFrame.w());

            Vec3 col = color(camFrame, ray, objects, lights);

            col *= 255;
            *(comp++) = col.r();
            *(comp++) = col.g();
            *(comp++) = col.b();
        }
    }

    stbi_write_jpg("image.jpg", width, height, comps, imgData, quality);
    delete[] imgData;
}