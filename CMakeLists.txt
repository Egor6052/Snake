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

# Визначаємо ім'я виконуваного файлу залежно від ОС
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(EXECUTABLE start-win)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(EXECUTABLE start-linux)
endif()

# Додаємо ресурсний файл для Windows (якщо потрібно)
# if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#     execute_process(COMMAND magick ${CMAKE_SOURCE_DIR}/assets/logo.png ${CMAKE_BINARY_DIR}/logo.ico)
# endif()

# Додаємо об'єктний файл іконки для Linux (якщо потрібно)
# if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     execute_process(COMMAND ld -r -b binary -o ${CMAKE_BINARY_DIR}/icon.o ${CMAKE_SOURCE_DIR}/assets/logo.png)
#     set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_BINARY_DIR}/icon.o)
# endif()

add_executable(${EXECUTABLE} src/main.cpp ${SOURCE_FILES})

target_compile_options(${EXECUTABLE} PRIVATE -Wall -fPIC)

target_include_directories(${EXECUTABLE} PRIVATE ./lib)

# Додаємо бібліотеки raylib
find_package(raylib CONFIG REQUIRED) 
target_link_libraries(${EXECUTABLE} PRIVATE raylib) 

# Якщо вам потрібні додаткові опції для Windows:
# if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#     # ... (наприклад, опції для MinGW)
# endif()