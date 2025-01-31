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

set(EXECUTABLE start)

# Додаємо ресурсний файл для Windows

if(WIN32)
    execute_process(COMMAND magick convert ${CMAKE_SOURCE_DIR}/assets/logo.png ${CMAKE_BINARY_DIR}/logo.ico)
endif()

if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} icon.rc)
endif()

# Додаємо об'єктний файл іконки для Linux
if(UNIX)
    execute_process(COMMAND ld -r -b binary -o ${CMAKE_BINARY_DIR}/icon.o ${CMAKE_SOURCE_DIR}/assets/logo.png)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_BINARY_DIR}/icon.o)
endif()

add_executable(${EXECUTABLE} src/main.cpp ${SOURCE_FILES})

target_compile_options(${EXECUTABLE} PRIVATE -Wall -fPIC)

target_include_directories(${EXECUTABLE} PRIVATE ./lib)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(raylib REQUIRED)
    target_link_libraries(${EXECUTABLE} PRIVATE raylib m)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/lib/libraylib-mingw.a -lopengl32 -lgdi32 -lwinmm)
endif()
