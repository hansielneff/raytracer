#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_writer.h"

#include <vector>

#include "vec3.h"
#include "ray.h"
#include "coordinate_frame.h"
#include "point_light.h"

Vec3 color(CoordinateFrame cam, const Ray &ray, std::vector<Sphere> objs, PointLight light) {
    float shortestDist = 1000;
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
        Vec3 l = normalized(light.position() - intersectPoint);
        Vec3 v = normalized(cam.origin() - intersectPoint);

        Vec3 color(
            closestSphere->color.r() * (light.color().r() * light.intensity()) * fmax(0, dot(n, l)), 
            closestSphere->color.g() * (light.color().g() * light.intensity()) * fmax(0, dot(n, l)), 
            closestSphere->color.b() * (light.color().b() * light.intensity()) * fmax(0, dot(n, l))
        );

        return color;
    }

    Vec3 unitDir = normalized(ray.direction());
    float t = 0.5f * (unitDir.y() + 1);
    return t * Vec3(0, 0, 0) +
        (1.0f - t) * Vec3(0.2f, 0.2f, 0.6f);
}

int main() {
    CoordinateFrame camFrame(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0));
    PointLight light(Vec3(0, 1, 3));

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

            Vec3 col = color(camFrame, ray, objects, light);

            col *= 255;
            *(comp++) = col.r();
            *(comp++) = col.g();
            *(comp++) = col.b();
        }
    }

    stbi_write_jpg("image.jpg", width, height, comps, imgData, quality);
    delete[] imgData;
}