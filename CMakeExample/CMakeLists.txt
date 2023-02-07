cmake_minimum_required(VERSION 3.15)

project(
  CMakeExample
  LANGUAGES CXX
  VERSION 0.1.9.0 # Major.Minor.Patch.Tweak
)

# set(CMAKE_CXX_STANDARD 17) set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(compiler_flags INTERFACE)
target_compile_definitions(compiler_flags INTERFACE cxx_std_17)

# 生成器表达式 $<A:B>
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(
  compiler_flags
  INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_like_cxx}:$<BUILD_INTERFACE:-W3>>")

list(APPEND EXTRA_LIBS compiler_flags)

message("CMAKE SOURCE DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE BINARY DIR: ${CMAKE_BINARY_DIR}")
# ${CMAKE_SOURCE_DIR} CMakeLists.txt所在的文件间 ${CMAKE_BINARY_DIR} BUILD
configure_file(Configure.h.in "${CMAKE_SOURCE_DIR}/src/Configure.h")

option(USEXADD "Use external Add." ON)

if(USEXADD)
  # 引入外部的library
  set(ExternalADD_PATH "./external/ExternalAdd")
  add_subdirectory(${ExternalADD_PATH})

  list(APPEND EXTRA_LIBS ExternalAdd)
  list(APPEND EXTRA_INCLUDES ${ExternalADD_PATH})

endif()

list(APPEND EXTRA_INCLUDES ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCE src/*.cpp src/*.h)

add_executable(MyAdd ${SOURCE})
target_include_directories(MyAdd PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(MyAdd PUBLIC ${EXTRA_LIBS})

install(TARGETS compiler_flags DESTINATION lib)
install(TARGETS MyAdd DESTINATION bin)
install(FILES src/Configure.h src/MyAdd/MyAdd.h DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_GENERATOR "TXZ")
include(CPack)
