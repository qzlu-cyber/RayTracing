//
// Created by 94164 on 2023/10/6.
//
#include "Camera.h"
#include "Utils.h"

Camera::Camera(int width, int height, double fov, double defocusAngle, double focusDistance) : m_Width(width),
                                                                                               m_Height(height),
                                                                                               m_FOV(fov),
                                                                                               m_DefocusAngle(defocusAngle),
                                                                                               m_FocusDistance(focusDistance) {
    // Camera
    Point3 lookFrom = {13, 2, 3}; // 相机的位置
    Point3 lookAt = {0, 0, 0}; // 相机的朝向
    Vec3 vUp = {0, 1, 0}; // 相机的上方向
    m_Origin = lookFrom;

    // Camera coordinate system
    Vec3 z = Normalize(lookFrom - lookAt); // +z 轴方向
    Vec3 x = Normalize(Cross(vUp, z)); // +x 轴方向
    Vec3 y = Cross(z, x); // +y 轴方向

    // Viewport
    double theta = DegreesToRadians(m_FOV);
    double viewportHeight = 2.0 * m_FocusDistance * std::tan(theta / 2.0); // 视口高度
    double viewportWidth = viewportHeight * (static_cast<double>(m_Width) / m_Height);

    // Viewport coordinate system, the origin is in the upper left corner
    Vec3 viewport_X = viewportWidth * x; // 视口坐标系的 X 轴
    Vec3 viewport_Y = viewportHeight * -y; // 视口坐标系的 -Y 轴

    m_PixelDelta_X = viewport_X / m_Width; // 每个像素的宽度
    m_PixelDelta_Y = viewport_Y / m_Height; // 每个像素的高度

    // Calculate the location of the upper left pixel
    m_ViewportUpperLeft = m_Origin - (m_FocusDistance * z) - viewport_X / 2 - viewport_Y / 2; // 视口左上角坐标
    m_PixelOrigin = m_ViewportUpperLeft + 0.5 * (m_PixelDelta_X + m_PixelDelta_Y);

    // Calculate the camera defocus disk basis vectors
    double defocusRadius = m_FocusDistance * std::tan(DegreesToRadians(m_DefocusAngle / 2)); // 相机的模糊半径
    m_DefocusDiskX = defocusRadius * x; // 相机的模糊半径在 X 轴上的投影
    m_DefocusDiskY = defocusRadius * y; // 相机的模糊半径在 Y 轴上的投影
}

Ray Camera::GetRay(int i, int j) const {
    Point3 pixelCenter = m_ViewportUpperLeft + i * m_PixelDelta_X + j * m_PixelDelta_Y;
    Point3 pixelSample = pixelCenter + PixelSampleSquare(); // 像素采样点

    Point3 rayOrigin = (m_DefocusAngle > 0) ? DefocusDiskSample() : m_Origin; // 光线的原点
    double rayTime = RandomDouble(); // 发出光线的时间

    return {rayOrigin, Normalize(pixelSample - rayOrigin), rayTime};
}

Vec3 Camera::PixelSampleSquare() const {
    double px = -0.5 + RandomDouble(); // [-0.5, 0.5)
    double py = -0.5 + RandomDouble(); // [-0.5, 0.5)

    return px * m_PixelDelta_X + py * m_PixelDelta_Y;
}

Point3 Camera::DefocusDiskSample() const {
    Vec3 v = RandomInUnitDisk();
    return m_Origin + m_DefocusDiskX * v.x() + m_DefocusDiskY * v.y();
}
