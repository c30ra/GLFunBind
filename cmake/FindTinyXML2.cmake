# - Try to find TinyXML2
# Once done this will define
#  TINYXML2_FOUND - System has TinyXML2
#  TINYXML2_INCLUDE_DIRS - The TinyXML2 include directories
#  TINYXML2_LIBRARIES - The libraries needed to use TinyXML2
#  TINYXML2_DEFINITIONS - Compiler switches required for using TinyXML2

if(NOT WIN32)
  find_package(PkgConfig)
  pkg_check_modules(PC_TINYXML2 QUIET tinyxml2)
  set(TINYXML2_DEFINITIONS ${PC_TINYXML2_CFLAGS_OTHER})
endif(NOT WIN32)

find_path(TINYXML2_INCLUDE include/tinyxml2.h
          HINTS ${TINYXML2_INCLUDEDIR})
find_library(TINYXML2_LIB tinyxml2
              HINTS ${PC_TINYXML2_LIBDIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(TinyXML2  DEFAULT_MSG
                                  TINYXML2_LIB TINYXML2_INCLUDE)

mark_as_advanced(CLEAR TINYXML2_INCLUDE TINYXML2_LIB )

set(TINYXML2_LIBRARIES ${TINYXML2_LIB} )
set(TINYXML2_INCLUDE_DIRS ${TINYXML2_INCLUDE} )
