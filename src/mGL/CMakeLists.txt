# Get all .h and .cpp files
file(GLOB mGL_src CONFIGURE_DEPENDS "*.h" "*.cpp" "Lights/*.cpp" "Lights/*.h" "Material/*.h" "Material/*.cpp" "Renderable/*.h" "Renderable/*.cpp" "Texture/*.h" "Texture/*.cpp")

# Create the library
add_library(mGL ${mGL_src})

target_include_directories(mGL
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mGL PUBLIC 
  mBase
  engine_compiler_flags
  m
  "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/lib/Release/x64/glew32.lib"
  "${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022/glfw3.lib"
  "opengl32.lib"
)

target_include_directories(mGL PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.8.bin.WIN64/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glm"
                           )