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
)