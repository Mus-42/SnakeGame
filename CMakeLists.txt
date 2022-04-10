cmake_minimum_required(VERSION 3.8)
project(SnakeGame)
find_package(GLFW3 REQUIRED)
add_executable(Snake src/main.cpp src/impl.cpp)
set_target_properties(Snake PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(Snake glfw)
target_include_directories(Snake PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb")