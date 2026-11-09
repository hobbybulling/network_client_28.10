cmake_minimum_required(VERSION 3.10)
project(vclient CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CRYPTOPP REQUIRED libcrypto++)
pkg_check_modules(UNITTESTPP REQUIRED UnitTest++)

# Библиотека с основной логикой (все .cpp кроме main.cpp)
file(GLOB LIB_SOURCES src/*.cpp)
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(client_lib STATIC ${LIB_SOURCES})
target_include_directories(client_lib PUBLIC include ${CRYPTOPP_INCLUDE_DIRS})
target_link_libraries(client_lib ${CRYPTOPP_LIBRARIES})

# Основной исполняемый файл
add_executable(client src/main.cpp)
target_link_libraries(client client_lib)

# Тесты
enable_testing()
add_executable(run_tests
    tests/main_test.cpp
    tests/test_authenticator.cpp
    tests/test_cli_handler.cpp
    tests/test_config_reader.cpp
    tests/test_data_reader_writer.cpp
)
target_include_directories(run_tests PRIVATE include ${UNITTESTPP_INCLUDE_DIRS})
target_link_libraries(run_tests client_lib ${UNITTESTPP_LIBRARIES})

add_test(NAME AllTests COMMAND run_tests)
