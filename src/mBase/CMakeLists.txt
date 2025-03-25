# Get all .h and .cpp files
file(GLOB mBase_src CONFIGURE_DEPENDS "*.cpp" "XML/*.cpp" "ImGui/*.cpp")

# Create the library
add_library(mBase ${mBase_src})

target_include_directories(mBase
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mBase PUBLIC engine_compiler_flags)