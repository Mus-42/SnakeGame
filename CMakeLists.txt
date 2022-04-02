cmake_minimum_required(VERSION 3.8)
project(SnakeGame)
find_package(GLFW3 REQUIRED)
add_executable(Snake src/main.cpp src/gladimpl.cpp)
set_target_properties(Snake PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(Snake glfw)