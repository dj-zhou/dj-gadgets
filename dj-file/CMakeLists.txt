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

find_package(CLI11 CONFIG)

# ------------------------------
add_executable(
  djfile
  "main.cpp"
  "file-create.cpp"
  "prompt-msg.cpp"
  "time-fetch.cpp"
)

install(TARGETS djfile RUNTIME DESTINATION bin)
