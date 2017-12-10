cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(otuscpp VERSION 1.0.$ENV{TRAVIS_BUILD_NUMBER} LANGUAGES CXX)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
endif()

include_directories(${CMAKE_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/src/version.h.in ${CMAKE_BINARY_DIR}/version.h)

add_executable(helloworld_cli
    src/main.cpp
    )

add_executable(test_version
    tests/test_version.cpp)

set_target_properties(helloworld_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    )

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dima@doty.ru)

include(CPack)

enable_testing()

add_test(test_version test_version)

