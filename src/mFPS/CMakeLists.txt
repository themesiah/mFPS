# Get all .h and .cpp files
file(GLOB mFPS_src CONFIGURE_DEPENDS "*.cpp" "Cameras/*.cpp" "Input/*.cpp")

# Create the library
add_executable(mFPS ${mFPS_src})

target_link_libraries(mFPS PUBLIC 
  mBase
  mGL
  engine_compiler_flags
)

# Copy files after building
add_custom_command(
  TARGET mFPS POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${PROJECT_SOURCE_DIR}/Data"
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data"
  COMMENT "Copying data folder from ${PROJECT_SOURCE_DIR} TO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)
add_custom_command(
  TARGET mFPS POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  "${PROJECT_SOURCE_DIR}/Dependencies/glew-2.2.0/bin/Release/x64/glew32.dll"
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glew32.dll"
  COMMENT "Copying glew32.dll (TEMP)"
)