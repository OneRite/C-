cmake_minimum_required(VERSION 3.15) # Проверка версии CMake
set(PROJECT_NAME laba_1) # Задаем значение PROJECT NAME
project("${PROJECT_NAME}") # Устанавливаем имя проекта

set(CMAKE_CXX_STANDARD 17) # Устанавливаем стандарт C++
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Подключаем header-файлы. В данном случае указываем текущий каталог ".",
# чтобы CMake мог найти файлы func.hpp и func.cpp, находящиеся в том же каталоге, что и CMakeLists.txt.
include_directories(".")

# Указываем, что должен быть исполняемый файл с именем проекта
add_executable("${PROJECT_NAME}" main.cpp func.cpp func.hpp)

# Исправляем установку цели для копирования исполняемого файла
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)

# Исправляем копирование файла input.txt в директорию сборки
file(COPY "input.txt" DESTINATION "${CMAKE_BINARY_DIR}")
