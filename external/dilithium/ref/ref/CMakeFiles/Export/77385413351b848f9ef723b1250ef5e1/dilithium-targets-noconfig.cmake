#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dilithium::dilithium2_ref" for configuration ""
set_property(TARGET dilithium::dilithium2_ref APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(dilithium::dilithium2_ref PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libdilithium2_ref.a"
  )

list(APPEND _cmake_import_check_targets dilithium::dilithium2_ref )
list(APPEND _cmake_import_check_files_for_dilithium::dilithium2_ref "${_IMPORT_PREFIX}/lib/libdilithium2_ref.a" )

# Import target "dilithium::fips202_ref" for configuration ""
set_property(TARGET dilithium::fips202_ref APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(dilithium::fips202_ref PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfips202_ref.a"
  )

list(APPEND _cmake_import_check_targets dilithium::fips202_ref )
list(APPEND _cmake_import_check_files_for_dilithium::fips202_ref "${_IMPORT_PREFIX}/lib/libfips202_ref.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
