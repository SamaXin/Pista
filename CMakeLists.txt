cmake_minimum_required(VERSION 3.16)

# ===============================
# Project Info
# ===============================
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ===============================
# Paths
# ===============================
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")
set(IMGUI_DIR "${EXTERNAL_DIR}/imgui")

# ===============================
# Source Files
# ===============================
file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/srcFiles/*.cpp"
    "${SRC_DIR}/headerFiles/*.h"
)

file(GLOB IMGUI_SRC
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

file(GLOB_RECURSE SHADER_FILES
    "${SRC_DIR}/shaders/*"
)

# ===============================
# Add Executable
# ===============================
add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${SHADER_FILES} # tracked, not compiled
 "src/mesh/sphere.cpp" "src/mesh/sphere.h")

# Copy shaders to output folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SRC_DIR}/shaders"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
)

# ===============================
# External Libraries
# ===============================
add_subdirectory(${EXTERNAL_DIR}/glfw)
add_subdirectory(${EXTERNAL_DIR}/glm)

# ===============================
# GLAD
# ===============================
set(GLAD_DIR "${EXTERNAL_DIR}/glad")
add_library(glad STATIC ${GLAD_DIR}/src/glad.c "src/mesh/sphere.cpp" "src/mesh/sphere.h")
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

# ===============================
# ImGui Setup
# ===============================
add_library(imgui STATIC ${IMGUI_SRC} "src/mesh/sphere.cpp" "src/mesh/sphere.h")

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${EXTERNAL_DIR}/glfw/include
    ${GLAD_DIR}/include
)

target_link_libraries(imgui PRIVATE glfw glad)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# ===============================
# Include Directories for Project
# ===============================
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SRC_DIR}
    ${GLAD_DIR}/include
    ${EXTERNAL_DIR}/glfw/include
    ${EXTERNAL_DIR}/glm
    ${EXTERNAL_DIR}/imgui
)

# ===============================
# Link Libraries
# ===============================
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
    imgui
)

# ===============================
# Platform-specific OpenGL linking
# ===============================
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif (APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenGL_LIBRARY})
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
endif()
