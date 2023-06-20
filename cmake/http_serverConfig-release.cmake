#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WebCpp::http_server" for configuration "Release"
set_property(TARGET WebCpp::http_server APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(WebCpp::http_server PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/http_server.lib"
  )

list(APPEND _cmake_import_check_targets WebCpp::http_server )
list(APPEND _cmake_import_check_files_for_WebCpp::http_server "${_IMPORT_PREFIX}/lib/http_server.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
