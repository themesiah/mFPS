# Get all .h and .cpp files
file(GLOB mFPS_src CONFIGURE_DEPENDS "*.cpp" "Cameras/*.cpp" "Input/*.cpp" "Game.h")

# Create the library
add_executable(mFPS ${mFPS_src})

target_link_libraries(mFPS PUBLIC 
  mBase
  mGL
  engine_compiler_flags
  "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/lib/Release/x64/glew32.lib"
  "${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022/glfw3.lib"
  "opengl32.lib"
)

target_include_directories(mFPS PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.8.bin.WIN64/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glm"
                           )