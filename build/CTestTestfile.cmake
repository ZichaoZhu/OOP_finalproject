# CMake generated Testfile for 
# Source directory: /Users/zzc/Desktop/OOP homework/Finalproject
# Build directory: /Users/zzc/Desktop/OOP homework/Finalproject/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BinaryTest "/Users/zzc/Desktop/OOP homework/Finalproject/build/bin/binary_test")
set_tests_properties(BinaryTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/zzc/Desktop/OOP homework/Finalproject/CMakeLists.txt;35;add_test;/Users/zzc/Desktop/OOP homework/Finalproject/CMakeLists.txt;0;")
add_test(XmlTest "/Users/zzc/Desktop/OOP homework/Finalproject/build/bin/xml_test")
set_tests_properties(XmlTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/zzc/Desktop/OOP homework/Finalproject/CMakeLists.txt;36;add_test;/Users/zzc/Desktop/OOP homework/Finalproject/CMakeLists.txt;0;")
subdirs("external/googletest")
subdirs("external/tinyxml2")
