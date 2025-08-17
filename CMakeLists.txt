cmake_minimum_required(VERSION 3.31)
project(raytracingGLM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find SDL2 manually
# (This matches your -I and -L flags in g++)
include_directories(/usr/local/include/SDL2 /usr/X11R6/include)
link_directories(/usr/local/lib)

# Add executable
add_executable(raytracingGLM
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
        realtimeRender.h
        rayUtilities.h
)

# Link SDL2
target_link_libraries(raytracingGLM SDL2)
