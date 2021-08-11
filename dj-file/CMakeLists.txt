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

# --------------------------------------------------------------------------
execute_process(COMMAND git describe --abbrev=7 --dirty --always --tags
    OUTPUT_VARIABLE GIT_TAG
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions(-D_GIT_TAG=\"${GIT_TAG}\")
message(STATUS "     Git Repo Tag : " ${GIT_TAG})

# --------------------------------------------------------------------------
add_executable(
  djfile
  "main.cpp"
  "cli-arguments.cpp"
  "file-create.cpp"
  "time-fetch.cpp"
)

install(TARGETS djfile RUNTIME DESTINATION bin)
