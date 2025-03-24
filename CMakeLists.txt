cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(mEngine VERSION 0.1)

# specify the C++ standard
add_library(engine_compiler_flags INTERFACE)
target_compile_features(engine_compiler_flags INTERFACE cxx_std_23)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(engine_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_subdirectory("src/mBase")
add_subdirectory("src/mGL")
add_subdirectory("src/mFPS")