//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include <iostream>

#include "Vec3.h"
#include "Ray.h"

class Camera {
public:
    Camera(int width, int height, double fov, double defocusAngle, double focusDistance);

    Point3 Origin() const { return m_Origin; }
    Point3 PixelOrigin() const { return m_PixelOrigin; }
    Vec3 PixelDelta_X() const { return m_PixelDelta_X; }
    Vec3 PixelDelta_Y() const { return m_PixelDelta_Y; }

    Ray GetRay(int i, int j) const;
    Vec3 PixelSampleSquare() const;
    Point3 DefocusDiskSample() const;

private:
    int m_Width; // 图像宽度
    int m_Height; // 图像高度

    Point3 m_Origin; // 相机原点

    double m_FOV; // 视野

    Vec3 m_PixelDelta_X; // 水平方向像素间距
    Vec3 m_PixelDelta_Y; // 垂直方向像素间距

    Point3 m_ViewportUpperLeft; // 视口左上角坐标
    Point3 m_PixelOrigin; // 像素原点

    double m_DefocusAngle; // 通过每个像素的光线变化角度
    double m_FocusDistance; // 焦距
    Vec3 m_DefocusDiskX; // 相机的模糊半径在 X 轴上的投影
    Vec3 m_DefocusDiskY; // 相机的模糊半径在 Y 轴上的投影
};

#endif //RAYTRACING_CAMERA_H
