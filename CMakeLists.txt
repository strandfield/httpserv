cmake_minimum_required(VERSION 3.13)
project(httpserv VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # disables warning about DLL export 
  # this is annoying when using C++ STL
  add_compile_options(/wd4251)  
endif()

set(HTTPSERV_PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

##################################################################
###### dependencies
##################################################################

find_package(Poco COMPONENTS Foundation Net)

##################################################################
###### lib & app
##################################################################

add_subdirectory(lib)
add_subdirectory(app)

##################################################################
###### tests
##################################################################

#add_subdirectory(tests)

##################################################################
###### virtual env
##################################################################

if(WIN32)
  file(WRITE "${CMAKE_BINARY_DIR}/activate.bat" "set PATH=${Poco_RUNTIME_LIBRARY_DIRS};%PATH%")
endif()



