cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(GLFunBind)

add_subdirectory(src)

install(DIRECTORY include 
		DESTINATION ${CMAKE_INSTALL_PREFIX})
