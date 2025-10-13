cmake_minimum_required(VERSION 3.31)
project(raytracingGLM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find SDL2 manually
# (This matches your -I and -L flags in g++)
include_directories(/usr/include/)
link_directories(/usr/lib64)

# Add executable
add_executable(MGR
        main.cpp
        vec3.h
        color.h
        settings.h
        ray.h
        objects.h
        utilities.h
        interval.h
        camera.h
        material.h
        aabb.h
        BVH.h
        rayUtilities.h

)

# Link SDL2
target_link_libraries(MGR SDL2)
