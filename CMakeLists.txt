cmake_minimum_required(VERSION 3.25)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp Vec3.h Ray.h Hittable.h Sphere.h Sphere.cpp HittableList.h Utils.h Interval.h Camera.h Camera.cpp Renderer.h Renderer.cpp HittableList.cpp Material.h AABB.h BVH.h BVH.cpp Scene.h)
