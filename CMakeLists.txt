cmake_minimum_required(VERSION 3.23)
project(Artificial_Life)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)

add_executable(Artificial_Life main.cpp)

include_directories("C:/include/SFML-2.5.1/include")

set(SFML_DIR C:/includes/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML 2.5 REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(Artificial_Life sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
