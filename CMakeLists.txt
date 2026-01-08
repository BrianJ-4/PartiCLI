cmake_minimum_required(VERSION 4.1)
project(PartiCLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(PartiCLI src/main.cpp
        src/engine.cpp
        include/engine.h
        src/renderer.cpp
        include/renderer.h
        include/constants.h
)

if(WIN32)
    target_link_options(PartiCLI PRIVATE "-static-libgcc" "-static-libstdc++" "-static")
endif()