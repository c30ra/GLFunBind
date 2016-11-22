cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLHeaderGen)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

find_package(TinyXML2 REQUIRED)
include_directories(${TINYXML2_INCLUDE_DIRS})
set(LIBS ${LIBS} ${TINYXML2_LIBRARIES} Qt5::Core)

add_executable(GLHeaderGen main.cpp glheadergen.cpp)
target_link_libraries(GLHeaderGen ${LIBS})

install(TARGETS GLHeaderGen
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin) 
