cmake_minimum_required(VERSION 3.22)

# Currently not supported on Windows
if (WIN32)
  message(FATAL_ERROR "This project is not supported on Windows yet.")
endif()

set(PROJECT_NAME jsonToBatch)

# Set basic CMAKE flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting information for the generated files
set(AUTOGENERATED_WARNING "This file is autogenerated. Changes will be overwritten")
set(AUTHORS "Elena Schwarzbach, Max Rodler, Simon Blum, Sonia Sinaci")

# Initialize the project
# This information is also used to generate files
project(${PROJECT_NAME} 
  VERSION 0.1.3
  DESCRIPTION "A simple tool to convert json to batch"
  HOMEPAGE_URL "https://definitelynotsimon13.github.io/ProjectJsonToBat"
)

# Generating files
configure_file(${PROJECT_SOURCE_DIR}/conf/config.hpp.in ${PROJECT_SOURCE_DIR}/src/include/config.hpp)
configure_file(${PROJECT_SOURCE_DIR}/conf/README.in.md ${PROJECT_SOURCE_DIR}/README.md)

# Astyle will autoformat when building
find_program(ASTYLE_EXECUTABLE NAMES astyle)
if(ASTYLE_EXECUTABLE)
  add_custom_target(astyle
    COMMAND 
      astyle --project=${PROJECT_SOURCE_DIR}/.astylerc -r ${PROJECT_SOURCE_DIR}/src/*.cpp,*.hpp 
    VERBATIM
  )
  set_target_properties(astyle PROPERTIES EXCLUDE_FROM_ALL FALSE)
endif()

# If doxygen is found, documentation can be generated by building the target doxygen_build
find_package(Doxygen)
if (DOXYGEN_FOUND)
 set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/conf/Doxyfile.in) 
 set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/Doxyfile)
 configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
 add_custom_target(doxygen_build
  COMMENT "Generating documentation with Doxygen..."
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
 )
else (DOXYGEN_FOUND)
  message(WARNING "Doxygen not found, unable to build documentation")
endif(DOXYGEN_FOUND)


# Add sources for the main executable
set(SOURCES
  src/main.cpp
)
# Add main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add subdirectories
add_subdirectory(lib)

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src/include
)

