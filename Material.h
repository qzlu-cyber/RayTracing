//
// Created by 94164 on 2023/10/7.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "Ray.h"
#include "Hittable.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material {
public:
    explicit Lambertian(const Color &albedo) : m_Albedo(albedo) {}

    bool Scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        Vec3 scatterDirection = record.normal + RandomUnitVector(); // 生成随机漫反射方向
        if (scatterDirection.NearZero()) // 防止生成的随机单位向量与法线向量正好相反
            scatterDirection = record.normal; // 如果随机漫反射方向为 0 向量，则将其设置为法向量
        scattered = Ray(record.point, scatterDirection); // 生成漫反射光线

        attenuation = m_Albedo; // 漫反射光线衰减率

        return true;
    }

private:
    Color m_Albedo; // 反射率
};

class Specular : public Material {
public:
    explicit Specular(const Color &albedo, double fuzz) : m_Albedo(albedo), m_Fuzz(fuzz) {}

    bool Scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        Vec3 reflected = Reflect(ray.Direction(), record.normal); // 计算反射光线的方向
        scattered = Ray(record.point, reflected + m_Fuzz * RandomUnitVector()); // 生成反射光线，并将反射光线方向进行微调，从而实现模糊效果

        attenuation = m_Albedo; // 反射光线衰减率

        return (Dot(scattered.Direction(), record.normal) > 0.0); // 如果反射光线与法线方向相同，则说明光线从物体外部射入，需要继续处理
    }

private:
    Color m_Albedo; // 反射率
    double m_Fuzz = 0.0; // 模糊系数
};

#endif //RAYTRACING_MATERIAL_H
