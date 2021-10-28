cmake_minimum_required(VERSION 3.5)
project(cmake-project)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(
  -Wall
  -Wextra
  -pedantic
  -Werror
  -Wformat=2
  -Wduplicated-cond
  -Wfloat-equal
  -Wshadow
  -Wconversion
  -Wlogical-not-parentheses
)

# ------------------------------
add_executable(ascii-code ascii-code.cpp)
install(TARGETS ascii-code RUNTIME DESTINATION bin)

add_executable(double-to-time double-to-time.cpp)
install(TARGETS double-to-time RUNTIME DESTINATION bin)

add_executable(double-to-u8 double-to-u8.cpp)
install(TARGETS double-to-u8 RUNTIME DESTINATION bin)

add_executable(float-to-u8 float-to-u8.cpp)
install(TARGETS float-to-u8 RUNTIME DESTINATION bin)

add_executable(rad-to-deg rad-to-deg.cpp)
install(TARGETS rad-to-deg RUNTIME DESTINATION bin)
add_executable(deg-to-rad deg-to-rad.cpp)
install(TARGETS deg-to-rad RUNTIME DESTINATION bin)

add_executable(u8-to-double u8-to-double.cpp)
install(TARGETS u8-to-double RUNTIME DESTINATION bin)

add_executable(u8-to-float u8-to-float.cpp)
install(TARGETS u8-to-float RUNTIME DESTINATION bin)