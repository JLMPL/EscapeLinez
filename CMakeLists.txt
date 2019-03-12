cmake_minimum_required(VERSION 3.0.0)
project(ESCAPELINEZ)

set(PROJECT_LINK_LIBS -lm -lsfml-network -lsfml-system -lSDL2 -lSDL2_ttf -lSDL2_image)

set(CMAKE_CXX_FLAGS "-no-pie")

add_definitions(-g -std=c++17 -Wfatal-errors -Wall)

include_directories(src)

file(GLOB src0 "src/*.cpp")

add_executable(EscapeLinez
    ${src0}
)
target_link_libraries(EscapeLinez ${PROJECT_LINK_LIBS})
