cmake_minimum_required(VERSION 3.16)
project(CatchMe)

set(CMAKE_CXX_STANDARD 14)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
file(GLOB SOURCE_FILES ${SRC_DIR}/*.cpp)
add_executable(CatchMe ${SOURCE_FILES})
# TODO: Remove this
add_definitions(-DDEBUG)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")


# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# stb_image
set(STB_DIR "${LIB_DIR}/stb_image")
add_library("stb_image" "${STB_DIR}/src/stb_image.cpp")
target_include_directories("stb_image" PRIVATE "${STB_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_DIR}/include")
target_link_libraries(${PROJECT_NAME} "stb_image")

include(FindPkgConfig)

pkg_check_modules(GL REQUIRED gl)
pkg_check_modules(GLM REQUIRED glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${GL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GL_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${GLM_LIBRARIES})









