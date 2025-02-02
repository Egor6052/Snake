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
# ... (ваш код для ресурсного файлу)

# Додаємо об'єктний файл іконки для Linux
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Перевіряємо, чи існує файл іконки
    if(EXISTS "${CMAKE_SOURCE_DIR}/assets/logo.png")
        # Конвертуємо зображення в об'єктний файл
        execute_process(
            COMMAND ld -r -b binary -o "${CMAKE_BINARY_DIR}/icon.o" "${CMAKE_SOURCE_DIR}/assets/logo.png"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

        # Додаємо об'єктний файл до списку джерел
        set(SOURCE_FILES ${SOURCE_FILES} "${CMAKE_BINARY_DIR}/icon.o")
    endif()
endif()

add_executable(${EXECUTABLE} src/main.cpp ${SOURCE_FILES})

target_compile_options(${EXECUTABLE} PRIVATE -Wall -fPIC)

target_include_directories(${EXECUTABLE} PRIVATE ./lib)


# Додаємо бібліотеки raylib
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(raylib CONFIG REQUIRED HINTS C:/Program Files/raylib)
    target_link_libraries(${EXECUTABLE} PRIVATE raylib)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED raylib)
    target_link_libraries(${EXECUTABLE} PRIVATE ${RAYLIB_LIBRARIES})
endif()


# Додаємо бібліотеки raylib
find_package(raylib CONFIG REQUIRED HINTS /путь/до/каталогу/з/raylib)
target_link_libraries(${EXECUTABLE} PRIVATE raylib)

# Конфігурація для Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Для Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")  # Обробка виключень
endif()
