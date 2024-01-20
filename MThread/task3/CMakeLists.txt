cmake_minimum_required(VERSION 3.5.0)
project (main)

# prevent for in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(CMAKE_CXX_COMPILER g++-13)
set(CMAKE_BUILD_TYPE Debug) #Debug #Release
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -pthread)  
target_compile_options(${PROJECT_NAME} INTERFACE -pthread)  
target_link_libraries(${PROJECT_NAME} -pthread -lm)
