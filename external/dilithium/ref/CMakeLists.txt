cmake_minimum_required(VERSION 3.11)

project(dilithium LANGUAGES C)

find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
  message(STATUS "Found OpenSSL: ${OPENSSL_VERSION}")
  include_directories(${OPENSSL_INCLUDE_DIR})
  link_directories(/opt/homebrew/opt/openssl@3/lib)
else()
  message(FATAL_ERROR "OpenSSL not found. Please install OpenSSL and set the appropriate paths.")
endif()



if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/output/$<CONFIG>/lib")
endif()

# Define the installation directory variables
include(GNUInstallDirs)

# Define source files
set(DILITHIUM_SRCS sign.c packing.c polyvec.c poly.c ntt.c reduce.c rounding.c)
set(DILITHIUM_FIPS202_SRCS ${DILITHIUM_SRCS} symmetric-shake.c)
set(DILITHIUM_AES_SRCS ${DILITHIUM_SRCS} symmetric-aes.c)
set(FIPS202_SRCS fips202.c)
set(AES256CTR_SRCS aes256ctr.c)
set(TEST_DILITHIUM_SRCS test/test_dilithium.c randombytes.c)
set(TEST_VECTORS_SRCS test/test_vectors.c)
set(TEST_SPEED_SRCS test/test_speed.c test/speed_print.c test/cpucycles.c randombytes.c)

# Set default Dilithium version
set(DILITHIUM_VERSION 2)

# Compiler-specific options
if(MSVC)
  add_compile_options(/nologo /O2 /W4 /wd4146 /wd4244)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
  add_compile_options(-Wmissing-prototypes -Wredundant-decls -Wshadow -Wpointer-arith)
  add_compile_options(-O3 -fomit-frame-pointer)
endif()

# Add common libraries
add_library(fips202_ref ${FIPS202_SRCS})
add_library(aes256ctr_ref ${AES256CTR_SRCS})

# Add Dilithium libraries and executables based on the version
if(DILITHIUM_VERSION MATCHES "2")
  set(DILITHIUM_TARGET dilithium2_ref)
  set(DILITHIUM_ALIAS dilithium::dilithium2)
  set(TEST_TARGET test_dilithium2_ref)
  set(VECTORS_TARGET test_vectors2_ref)
  add_library(dilithium2_ref STATIC 
  ${DILITHIUM_FIPS202_SRCS}
  sign.c
  randombytes.c
  packing.c
  poly.c
  polyvec.c
  fips202.c
  symmetric-shake.c
  ntt.c
  reduce.c)
  add_library(dilithium::dilithium2 ALIAS dilithium2_ref)
  target_compile_definitions(dilithium2_ref PUBLIC DILITHIUM_MODE=2)
  target_link_libraries(dilithium2_ref INTERFACE fips202_ref)
  add_executable(${TEST_TARGET} ${TEST_DILITHIUM_SRCS})
  add_executable(${VECTORS_TARGET} ${TEST_VECTORS_SRCS})
  target_link_libraries(${TEST_TARGET} dilithium2_ref)
  target_link_libraries(${VECTORS_TARGET} dilithium2_ref)
  
  add_test(NAME ${DILITHIUM_TARGET} COMMAND ${TEST_TARGET})

elseif(DILITHIUM_VERSION MATCHES "2_aes")
  set(DILITHIUM_TARGET dilithium2aes_ref)
  set(DILITHIUM_ALIAS dilithium::dilithium2_aes)
  set(TEST_TARGET test_dilithium2aes_ref)
  set(VECTORS_TARGET test_vectors2aes_ref)
  add_library(dilithium2aes_ref STATIC ${DILITHIUM_AES_SRCS})
  add_library(dilithium::dilithium2_aes ALIAS dilithium2aes_ref)
  target_compile_definitions(dilithium2aes_ref PUBLIC DILITHIUM_MODE=2 DILITHIUM_USE_AES)
  target_link_libraries(dilithium2aes_ref INTERFACE fips202_ref aes256ctr_ref)
  add_executable(${TEST_TARGET} ${TEST_DILITHIUM_SRCS})
  add_executable(${VECTORS_TARGET} ${TEST_VECTORS_SRCS})
  target_link_libraries(${TEST_TARGET} dilithium2aes_ref)
  target_link_libraries(${VECTORS_TARGET} dilithium2aes_ref)
  add_test(NAME ${DILITHIUM_TARGET} COMMAND ${TEST_TARGET})

elseif(DILITHIUM_VERSION MATCHES "3")
  set(DILITHIUM_TARGET dilithium3_ref)
  set(DILITHIUM_ALIAS dilithium::dilithium3)
  set(TEST_TARGET test_dilithium3_ref)
  set(VECTORS_TARGET test_vectors3_ref)
  add_library(dilithium3_ref STATIC ${DILITHIUM_FIPS202_SRCS})
  add_library(dilithium::dilithium3 ALIAS dilithium3_ref)
  target_compile_definitions(dilithium3_ref PUBLIC DILITHIUM_MODE=3)
  target_link_libraries(dilithium3_ref INTERFACE fips202_ref)
  add_executable(${TEST_TARGET} ${TEST_DILITHIUM_SRCS})
  add_executable(${VECTORS_TARGET} ${TEST_VECTORS_SRCS})
  target_link_libraries(${TEST_TARGET} dilithium3_ref)
  target_link_libraries(${VECTORS_TARGET} dilithium3_ref)
  add_test(NAME ${DILITHIUM_TARGET} COMMAND ${TEST_TARGET})

elseif(DILITHIUM_VERSION MATCHES "3_aes")
  set(DILITHIUM_TARGET dilithium3aes_ref)
  set(DILITHIUM_ALIAS dilithium::dilithium3_aes)
  set(TEST_TARGET test_dilithium3aes_ref)
  set(VECTORS_TARGET test_vectors3aes_ref)
  add_library(dilithium3aes_ref STATIC ${DILITHIUM_AES_SRCS})
  add_library(dilithium::dilithium3_aes ALIAS dilithium3aes_ref)
  target_compile_definitions(dilithium3aes_ref PUBLIC DILITHIUM_MODE=3 DILITHIUM_USE_AES)
  target_link_libraries(dilithium3aes_ref INTERFACE fips202_ref aes256ctr_ref)
  add_executable(${TEST_TARGET} ${TEST_DILITHIUM_SRCS})
  add_executable(${VECTORS_TARGET} ${TEST_VECTORS_SRCS})
  target_link_libraries(${TEST_TARGET} dilithium3aes_ref)
  target_link_libraries(${VECTORS_TARGET} dilithium3aes_ref)
  add_test(NAME ${DILITHIUM_TARGET} COMMAND ${TEST_TARGET})

elseif(DILITHIUM_VERSION MATCHES "5")
  set(DILITHIUM_TARGET dilithium5_ref)
  set(DILITHIUM_ALIAS dilithium::dilithium5)
  set(TEST_TARGET test_dilithium5_ref)
  set(VECTORS_TARGET test_vectors5_ref)
  add_library(dilithium5_ref STATIC ${DILITHIUM_FIPS202_SRCS})
  add_library(dilithium::dilithium5 ALIAS dilithium5_ref)
  target_compile_definitions(dilithium5_ref PUBLIC DILITHIUM_MODE=5)
  target_link_libraries(dilithium5_ref INTERFACE fips202_ref)
  add_executable(${TEST_TARGET} ${TEST_DILITHIUM_SRCS})
  add_executable(${VECTORS_TARGET} ${TEST_VECTORS_SRCS})
  target_link_libraries(${TEST_TARGET} dilithium5_ref)
  target_link_libraries(${VECTORS_TARGET} dilithium5_ref)
  add_test(NAME ${DILITHIUM_TARGET} COMMAND ${TEST_TARGET})

elseif(DILITHIUM_VERSION MATCHES "5_aes")
  set(DILITHIUM_TARGET dilithium5aes_ref)
  set(DILITHIUM_ALIAS dilithium::dilithium5_aes)
  set(TEST_TARGET test_dilithium5aes_ref)
  set(VECTORS_TARGET test_vectors5aes_ref)
  add_library(dilithium5aes_ref STATIC ${DILITHIUM_AES_SRCS})
  add_library(dilithium::dilithium5_aes ALIAS dilithium5aes_ref)
  target_compile_definitions(dilithium5aes_ref PUBLIC DILITHIUM_MODE=5 DILITHIUM_USE_AES)
  target_link_libraries(dilithium5aes_ref INTERFACE fips202_ref aes256ctr_ref)
  add_executable(${TEST_TARGET} ${TEST_DILITHIUM_SRCS})
  add_executable(${VECTORS_TARGET} ${TEST_VECTORS_SRCS})
  target_link_libraries(${TEST_TARGET} dilithium5aes_ref)
  target_link_libraries(${VECTORS_TARGET} dilithium5aes_ref)
  add_test(NAME ${DILITHIUM_TARGET} COMMAND ${TEST_TARGET})
endif()

# Conditionally add vector tests
if(DEFINED VECTORS_TARGET)
  if(WIN32)
    add_test(NAME vectors_${VECTORS_TARGET} COMMAND PowerShell -Command "$<TARGET_FILE:${VECTORS_TARGET}> | dos2unix > tvecs")
  else()
    add_test(NAME vectors_${VECTORS_TARGET} COMMAND sh -c "\"$<TARGET_FILE:${VECTORS_TARGET}>\" > tvecs")
  endif()
endif()

add_test(NAME hashes COMMAND sha256sum -c ../../SHA256SUMS)

# Include directories
target_include_directories(${DILITHIUM_TARGET} PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Installation rules
install(
  TARGETS ${DILITHIUM_TARGET} fips202_ref
  EXPORT ${PROJECT_NAME}-exports
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
install(
  EXPORT ${PROJECT_NAME}-exports
  NAMESPACE dilithium::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  FILE ${PROJECT_NAME}-targets.cmake
)
install(
  FILES sign.h
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Summary messages
message("\n")
message("Dilithium configure summary")
message("===========================")
message("Dilithium Version: ${DILITHIUM_VERSION}")

# Messages for the selected library and test executables
if(DEFINED DILITHIUM_TARGET)
  message("Building Libraries:")
  message("  - Dilithium cryptographic library: ${DILITHIUM_TARGET}")
  message(STATUS "DILITHIUM_TARGET: ${DILITHIUM_TARGET}")

  get_target_property(DILITHIUM_MODE_DEFINITIONS ${DILITHIUM_TARGET} COMPILE_DEFINITIONS)
  message("  - ${DILITHIUM_TARGET} compile definitions: ${DILITHIUM_MODE_DEFINITIONS}")
  
  message("Building Test Executables:")
  message("  - Test executable for ${DILITHIUM_TARGET} functionality: ${TEST_TARGET}")
  message("  - Test executable for ${DILITHIUM_TARGET} vector tests: ${VECTORS_TARGET}")
  
  message("Library Linkage:")
  message("  - Test executable linked against ${DILITHIUM_TARGET}")
  message("  - Vector test executable linked against ${DILITHIUM_TARGET}")
endif()

# If using INTERFACE to link libraries
message("Using INTERFACE to link the fips202_ref library, ensuring dependencies propagate correctly.")

# Optional, providing information about how to proceed or more details
message("Run 'make' to compile all targets")
message("Use 'ctest' to run all configured tests (after building)")

message("\n")
