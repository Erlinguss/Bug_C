cmake_minimum_required(VERSION 3.24)
project(Bug_C)

set(CMAKE_CXX_STANDARD 11)

add_executable(Bug_C main.cpp Bug.cpp Bug.h Crawler.cpp Crawler.h Hopper.cpp Hopper.h Bugboard.cpp Bugboard.h Scorpion.cpp Scorpion.h SuperBug.cpp)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/User/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/User/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include)
target_link_libraries(Bug_C sfml-system sfml-window sfml-graphics sfml-audio)