cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLHeaderGen)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS core REQUIRED)

find_package(TinyXML2 REQUIRED)
include_directories(${TINYXML2_INCLUDE_DIRS})
set(LIBS ${LIBS} ${TINYXML2_LIBRARIES} Qt5::Core)

MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${TINYXML2_INCLUDE_DIRS} )
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${LIBS} )

add_executable(GLHeaderGen WIN32 main.cpp glheadergen.cpp)
target_link_libraries(GLHeaderGen ${LIBS})
