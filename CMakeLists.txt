cmake_minimum_required(VERSION 3.24.2)

project(Bacteria LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB files
     "src/*.hpp"
     "src/*.cpp"
)

file(GLOB tests
     "test/*.cpp"
)

set(testfiles ${files})

file(COPY_FILE conanfile.txt ${CMAKE_BINARY_DIR}/conanfile.txt)
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR};${CMAKE_PREFIX_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_MODULE_PATH}")

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(Application ${files})
target_include_directories(Application PRIVATE src)
target_link_libraries(Application sfml::sfml Eigen3::Eigen)

if(ENABLE_TESTING)

enable_testing()
find_package(Catch2 3 REQUIRED)

list(REMOVE_ITEM testfiles ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(ApplicationTests ${testfiles} ${tests})
target_include_directories(ApplicationTests PRIVATE src)
target_link_libraries(ApplicationTests Eigen3::Eigen sfml::sfml Catch2::Catch2WithMain)

add_test(NAME ApplicationTests COMMAND ApplicationTests)
install(TARGETS ApplicationTests RUNTIME)
endif()

install(TARGETS Application RUNTIME)



