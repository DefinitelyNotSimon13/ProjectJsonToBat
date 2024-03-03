# Trying to find some packages
# This is currently just for testing. My plan is to add
# more automation in order to be compatible with different
# systems/compilers.
find_package(Catch2)
find_package(PkgConfig)
pkg_check_modules(JSONCPP jsoncpp)

# Linking necessary libraries



if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/lib/libjsoncpp.a
  ${PROJECT_SOURCE_DIR}/lib/libLoggingWrapper.a
  xgetopt)
else ()
target_link_libraries(${PROJECT_NAME} PRIVATE
  jsoncpp
  ${PROJECT_SOURCE_DIR}/lib/libLoggingWrapper.a)
endif ()

