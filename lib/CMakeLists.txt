
########################################################################

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/**.cpp)
file(GLOB_RECURSE HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/**.h)

add_library(httpserv-lib STATIC ${HDR_FILES} ${SRC_FILES})

if(UNIX)
  target_link_libraries(httpserv-lib pthread)
endif(UNIX)

target_include_directories(httpserv-lib PUBLIC "${Poco_INCLUDE_DIRS}")
target_link_libraries(httpserv-lib ${Poco_LIBRARIES})

foreach(_source IN ITEMS ${SRC_FILES} ${HDR_FILES} ${HTML_FILES} ${XML_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
