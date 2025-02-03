cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(RaylibGame)

option(USE_STATIC "Use static library" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")

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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(EXECUTABLE start-win)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(EXECUTABLE start-linux)
endif()

# Вказуємо шлях до бібліотеки
link_directories("C:/Users/Administrator/vcpkg/installed/x64-windows/lib")  # Якщо використовуєте vcpkg

# Вказуємо шлях до бібліотеки raylib, якщо використовуєте її вручну
set(RAYLIB_DIR "C:/raylib")
include_directories(${RAYLIB_DIR}/src)
link_directories(${RAYLIB_DIR}/lib)  # Вказуємо правильну директорію з бібліотеками

add_executable(${EXECUTABLE} src/main.cpp ${SOURCE_FILES})

# Лінкуємо raylib
target_link_libraries(${EXECUTABLE} PRIVATE raylib)

# Для Windows: встановлюємо компіляційні флаг для обробки виключень
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()
