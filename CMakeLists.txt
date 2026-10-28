cmake_minimum_required(VERSION 3.10)
project(vclient CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CRYPTOPP REQUIRED libcrypto++)

include_directories(include ${CRYPTOPP_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp)

add_executable(client ${SOURCES})
target_link_libraries(client ${CRYPTOPP_LIBRARIES})