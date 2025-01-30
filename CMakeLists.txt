cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(RaylibGame)

option(USE_STATIC "Use static library" ON)

message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")

# Додаємо вихідні файли
set(SOURCE_FILES
    ./src/Background/Background.cpp
    ./src/Food/Food.cpp
    ./src/Snake/Snake.cpp
)

set(HEADER_FILES
    ./lib/Background.h
    ./lib/Food.h
    ./lib/Snake.h
)

add_executable(start src/main.cpp ${SOURCE_FILES})

target_compile_options(start PRIVATE -Wall -fPIC)

target_include_directories(start PRIVATE ./lib)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(raylib REQUIRED)
    target_link_libraries(start PRIVATE raylib m)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(start PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(start PRIVATE ${CMAKE_SOURCE_DIR}/lib/libraylib-mingw.a -lopengl32 -lgdi32 -lwinmm)
endif()
