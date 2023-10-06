//
// Created by 94164 on 2023/10/6.
//
#include "Camera.h"
#include "Utils.h"

Camera::Camera(int width, int height) {
    // Image
    m_Width = width;
    m_Height = height;

    // Camera
    double focalLength = 1.0;
    m_Origin = Point3(0.0, 0.0, 0.0);

    // Viewport
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (static_cast<double>(m_Width) / m_Height);

    // Viewport coordinate system, the origin is in the upper left corner
    Vec3 viewport_X = {viewportWidth, 0, 0}; // 视口坐标系的 X 轴
    Vec3 viewport_Y = {0, -viewportHeight, 0}; // 视口坐标系的 -Y 轴

    m_PixelDelta_X = viewport_X / m_Width; // 每个像素的宽度
    m_PixelDelta_Y = viewport_Y / m_Height; // 每个像素的高度

    // Calculate the location of the upper left pixel
    m_ViewportUpperLeft = m_Origin - Vec3(0, 0, focalLength) - viewport_X / 2 - viewport_Y / 2; // 视口左上角坐标
    m_PixelOrigin = m_ViewportUpperLeft + 0.5 * (m_PixelDelta_X + m_PixelDelta_Y);
}

Ray Camera::GetRay(int i, int j) const {
    Point3 pixelCenter = m_ViewportUpperLeft + i * m_PixelDelta_X + j * m_PixelDelta_Y;
    Point3 pixelSample = pixelCenter + PixelSampleSquare(); // 像素采样点

    return {m_Origin, Normalize(pixelSample - m_Origin)};
}

Vec3 Camera::PixelSampleSquare() const {
    double px = -0.5 + RandomDouble(); // [-0.5, 0.5)
    double py = -0.5 + RandomDouble(); // [-0.5, 0.5)

    return px * m_PixelDelta_X + py * m_PixelDelta_Y;
}
