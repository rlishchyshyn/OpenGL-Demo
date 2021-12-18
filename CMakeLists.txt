project(it-step-viewer)
cmake_minimum_required(VERSION 3.20)

set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/lib/glfw3.lib)
include_directories(include)
include_directories(src)

aux_source_directory(src SOURCE)
file(GLOB HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
