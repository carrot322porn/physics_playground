cmake_minimum_required(VERSION 4.0)
project(physics_playground)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_DIR "C:/raylib")

include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

file(GLOB SRC_FILES src/*.cpp)

add_executable(physics_playground ${SRC_FILES})

target_include_directories(physics_playground PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(physics_playground
        raylib
        opengl32
        gdi32
        winmm
)
