# Get all .h and .cpp files
file(GLOB mBase_src CONFIGURE_DEPENDS "*.h" "*.cpp" "XML/*.cpp" "XML/*.h" "ImGui/*.h" "ImGui/*.cpp")

# Create the library
add_library(mBase ${mBase_src})

target_include_directories(mBase
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mBase PUBLIC engine_compiler_flags)

target_include_directories(mBase PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.8.bin.WIN64/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glm"
                           )