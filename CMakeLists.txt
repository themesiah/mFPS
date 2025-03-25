cmake_minimum_required(VERSION 3.15)

# Set the project name and version
project(mEngine VERSION 0.1)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

# Specify the C++ standard
add_library(engine_compiler_flags INTERFACE)
target_compile_features(engine_compiler_flags INTERFACE cxx_std_23)

# Set some precompiling definitions depending on target
target_compile_definitions(engine_compiler_flags INTERFACE "DEBUG")
target_compile_definitions(engine_compiler_flags INTERFACE "EDITOR_MODE")
target_compile_definitions(engine_compiler_flags INTERFACE "GLM_ENABLE_EXPERIMENTAL")

# Link common use libraries
target_link_libraries(engine_compiler_flags
                      INTERFACE
                      glfw
                      glm
                      "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/lib/Release/x64/glew32.lib"
                      opengl32
)

include_directories(
  "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/include"
  )

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(engine_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-Wno-unused-variable;-Wno-unused-parameter>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# Add all subdirectories
add_subdirectory("src/mBase")
add_subdirectory("src/mGL")
add_subdirectory("src/mFPS")
add_subdirectory("Dependencies/glfw")
add_subdirectory("Dependencies/glm")