cmake_minimum_required(VERSION 3.25.1)

project(Bacteria LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB files
     "src/*.hpp"
     "src/*.cpp"
)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES catch2/3.4.0 sfml/2.5.1
                BASIC_SETUP)

add_executable(Application ${files})
target_include_directories(Application PRIVATE src)
target_link_libraries(Application ${CONAN_LIBS})





