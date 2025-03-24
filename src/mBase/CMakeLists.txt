# Get all .h and .cpp files
file(GLOB mBase_src CONFIGURE_DEPENDS "*.h" "*.cpp" "XML/*.cpp" "XML/*.h" "ImGui/*.h" "ImGui/*.cpp")

# Create the library
add_library(mBase ${mBase_src})

target_include_directories(mBase
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mBase PUBLIC engine_compiler_flags)