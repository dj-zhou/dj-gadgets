cmake_minimum_required(VERSION 3.5)
project(cmake-project)
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
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
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
add_compile_options(
  -Wall
  -Wextra
  -pedantic
  -Wformat=2
  -Wfloat-equal
  -Wshadow
  -Wconversion
  -Wlogical-not-parentheses
)
else()
    # Code for other operating systems here
    message("This is a different operating system")
endif()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

macro(add_exec_and_install example_name)
    add_executable("dj-${example_name}" "${example_name}.cpp")
    install(TARGETS "dj-${example_name}" RUNTIME DESTINATION bin)
endmacro()

add_exec_and_install(ascii-code)
add_exec_and_install(date-time-to-epoch)
add_exec_and_install(deg-to-rad)
add_exec_and_install(double-to-u8)
add_exec_and_install(epoch-to-date-time)
add_exec_and_install(euler-to-quat)
add_exec_and_install(float-to-u8)
add_exec_and_install(quat-to-euler)
add_exec_and_install(quat-to-rot)
add_exec_and_install(rad-to-deg)
add_exec_and_install(rot-to-quat)
add_exec_and_install(u8-to-double)
add_exec_and_install(u8-to-float)
