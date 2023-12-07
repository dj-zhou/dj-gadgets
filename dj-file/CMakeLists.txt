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
find_package(CLI11 REQUIRED)
include_directories(${CLI11_INCLUDE_DIRS})
include_directories(/usr/local/include)

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
  dj-file
  "main.cpp"
  "cli-arguments.cpp"
  "file-create.cpp"
  "time-fetch.cpp"
)
target_include_directories(dj-file PRIVATE ${CLI11_INCLUDE_DIRS})

install(TARGETS dj-file RUNTIME DESTINATION bin)
