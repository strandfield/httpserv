
add_executable(httpserv "main.cpp")

target_include_directories(httpserv PRIVATE "${HTTPSERV_PROJECT_DIR}/lib")

target_link_libraries(httpserv httpserv-lib)

set_target_properties(httpserv PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(httpserv PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (WIN32)
  set_target_properties(httpserv PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${Poco_RUNTIME_LIBRARY_DIRS};%PATH%")
endif()
