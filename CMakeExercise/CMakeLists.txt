cmake_minimum_required(VERSION 3.15)

project(CMakeExe LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# glad
set(GLAD_DIR ./external/glad)
list(APPEND INCLUDE_DIR ${GLAD_DIR}/include)

# GLFW
set(GLFW_DIR ./external/glfw)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} glfw_binary EXCLUDE_FROM_ALL)

list(APPEND INCLUDE_DIR ${GLFW_DIR}/include)
list(APPEND IMGUI_INCLUDE_DIR ${GLFW_DIR}/include)
list(APPEND INCLUDE_DIR ${GLFW_DIR}/deps)
list(APPEND IMGUI_INCLUDE_DIR ${GLFW_DIR}/deps)

list(APPEND LINK_LIBS glfw)

list(APPEND OPENGL_SOURCE ${GLAD_DIR}/src/glad.c src/OpenGLDemo.cpp)
add_executable(OpenGLDemo ${OPENGL_SOURCE})
target_include_directories(OpenGLDemo PUBLIC ${INCLUDE_DIR})
target_link_libraries(OpenGLDemo PUBLIC ${LINK_LIBS})

# imgui
set(IMGUI_DIR ./external/imgui)
list(APPEND IMGUI_INCLUDE_DIR ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# vulkan
find_package(Vulkan REQUIRED)
list(APPEND LINK_LIBS "Vulkan::Vulkan")

# SOURCE
list(
  APPEND
  IMGUI_SOURCE
  src/main.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp)

add_executable(IMGUI_DEMO ${IMGUI_SOURCE})
target_include_directories(IMGUI_DEMO PUBLIC ${IMGUI_INCLUDE_DIR})
target_link_libraries(IMGUI_DEMO PUBLIC ${LINK_LIBS})
