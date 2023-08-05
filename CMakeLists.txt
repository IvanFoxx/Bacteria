cmake_minimum_required(VERSION 3.24.2)

project(Bacteria LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB files
     "src/*.hpp"
     "src/*.cpp"
)

file(COPY_FILE conanfile.txt ${CMAKE_BINARY_DIR}/conanfile.txt)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Application ${files})
target_include_directories(Application PRIVATE src)
target_link_libraries(Application ${CONAN_LIBS})





