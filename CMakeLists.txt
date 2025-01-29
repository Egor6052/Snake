
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(RaylibGame)

# Опція для використання статичних бібліотек
option(USE_STATIC "Use static library" ON)

# Вивід повідомлення про систему
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")


# Знаходимо бібліотеку raylib
find_package(raylib REQUIRED)

# Шлях до вихідних файлів
set(SOURCE_FILES
    ./src/Background/Background.cpp
    ./src/Food/Food.cpp
    ./src/Snake/Snake.cpp
)

# Заголовкові файли
set(HEADER_FILES
    ./lib/Background.h
    ./lib/Food.h
    ./lib/Snake.h
)

# Додавання виконуваного файлу
add_executable(start
    src/main.cpp
    ${SOURCE_FILES}
)

# Компіляторні опції
target_compile_options(start
    PRIVATE
        -Wall -fPIC
)

# Додавання шляхів до заголовкових файлів
target_include_directories(start
    PRIVATE
        ./lib
)

# Лінкуємо бібліотеку raylib
target_link_libraries(start PRIVATE raylib)

# Додаткові параметри для Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(start PRIVATE m)
endif()


# # find_package(PostgreSQL REQUIRED)
# # target_link_libraries(start PRIVATE pqxx)
