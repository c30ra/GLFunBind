#path to TinyXML2 lib directory
TinyXML2_lib_path_release = $$PWD/../../../../../../Development/libs/tinyxml2/tinyxml2_x86/lib
TinyXML2_lib_path_debug = $$PWD/../../../../../../Development/libs/tinyxml2/tinyxml2_x86/lib

#name without extension
TinyXML_lib_name_debug = tinyxml2d
TinyXML_lib_name_release = tinyxml2

#path to TinyXML2 include directory
TinyXML_include_path = $$PWD/../../../../../../Development/libs/tinyxml2/tinyxml2_x86/include

#!exists($$TinyXML2) {
#    error( "Path to TinyXML doesn't exist...." )
#}

