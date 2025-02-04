# CMake generated Testfile for 
# Source directory: /Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref
# Build directory: /Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/ref
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(dilithium2_ref "/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/ref/test_dilithium2_ref")
set_tests_properties(dilithium2_ref PROPERTIES  _BACKTRACE_TRIPLES "/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/CMakeLists.txt;75;add_test;/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/CMakeLists.txt;0;")
add_test(vectors_test_vectors2_ref "sh" "-c" "\"/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/ref/test_vectors2_ref\" > tvecs")
set_tests_properties(vectors_test_vectors2_ref PROPERTIES  _BACKTRACE_TRIPLES "/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/CMakeLists.txt;158;add_test;/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/CMakeLists.txt;0;")
add_test(hashes "sha256sum" "-c" "../../SHA256SUMS")
set_tests_properties(hashes PROPERTIES  _BACKTRACE_TRIPLES "/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/CMakeLists.txt;162;add_test;/Users/atharvalele/Desktop/Work/rippled_dilithium/rippled-upstream/external/dilithium/ref/CMakeLists.txt;0;")
