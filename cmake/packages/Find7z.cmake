# Try to find the 7Z library
#
# If successful, the following variables will be defined:
# 7Z_INCLUDE_DIR
# 7Z_LIBRARIES
# 7Z_FOUND
#
# Additionally, one of the following import targets will be defined:
# z

find_package(PkgConfig QUIET)
pkg_check_modules(PC_7Z QUIET 7Z)

set(CMAKE_FIND_DEBUG_MODE TRUE)

find_path(7Z_INCLUDE_DIRS NAMES 7zVersion.h HINTS ${PC_7Z_INCLUDE_DIRS})
find_library(7Z_LIBRARIES NAMES 7z HINTS ${PC_7Z_LIBRARY_DIRS})

set(CMAKE_FIND_DEBUG_MODE FALSE)

message(STATUS "CMAKE_SYSTEM_PREFIX_PATH = ${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "7Z_INCLUDE_DIRS = ${7Z_INCLUDE_DIRS}")
message(STATUS "7Z_LIBRARIES = ${7Z_LIBRARIES}")
message(STATUS "PC_7Z_INCLUDE_DIRS = ${PC_7Z_INCLUDE_DIRS}")
message(STATUS "PC_7Z_LIBRARY_DIRS = ${PC_7Z_LIBRARY_DIRS}")

include(CheckIncludeFile)
if(7Z_INCLUDE_DIRS AND EXISTS "${7Z_INCLUDE_DIRS}/7zVersion.h")
  include(CMakePushCheckState)
  cmake_push_check_state()
  set(CMAKE_REQUIRED_QUIET ${7Z_FIND_QUIETLY})
  set(CMAKE_REQUIRED_INCLUDES ${7Z_INCLUDE_DIRS})
  set(CMAKE_REQUIRED_LIBRARIES ${7Z_LIBRARIES})
  check_include_file(7zVersion.h HAVE_7Z_H)
  cmake_pop_check_state()
  if (HAVE_7Z_H)
    file(STRINGS "${7Z_INCLUDE_DIRS}/7zVersion.h" _7z_version_lines REGEX "#define[ \t]+MY_VERSION_NUMBERS")
    string(REGEX REPLACE ".*MY_VERSION_NUMBERS \"\([0-9]*\)\..*\"" "\\1" _7z_version_major "${_7z_version_lines}")
    string(REGEX REPLACE ".*MY_VERSION_NUMBERS \"[0-9]*\.\([0-9]*\)\"" "\\1" _7z_version_minor "${_7z_version_lines}")
    set(7Z_VERSION_STRING "${_7z_version_major}.${_7z_version_minor}")
  else()
    set(7Z_INCLUDE_DIRS "")
    set(7Z_LIBRARIES "")
  endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(7z
                                  FOUND_VAR
                                    7Z_FOUND
                                  REQUIRED_VARS
                                    7Z_INCLUDE_DIRS
                                    7Z_LIBRARIES
                                  VERSION_VAR
                                    7Z_VERSION_STRING)
mark_as_advanced(7Z_INCLUDE_DIRS 7Z_LIBRARIES)

if (7Z_FOUND AND NOT TARGET LLVM_STATIC_7z)
  add_library(LLVM_STATIC_7z UNKNOWN IMPORTED)
  set_target_properties(LLVM_STATIC_7z PROPERTIES
                        IMPORTED_LOCATION ${7Z_LIBRARIES}
                        INTERFACE_INCLUDE_DIRECTORIES ${7Z_INCLUDE_DIRS})
  set(7Z_TARGET LLVM_STATIC_7z)
endif()
