cmake_minimum_required(VERSION 3.0.0)
project(network-chat VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/1/CLionProjects/libs/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

add_executable(network-chat main.cpp)

target_link_libraries(network-chat sfml-network sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
