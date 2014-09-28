# - Try to find the GENGINE library
# Once done this will define
#
#  GENGINE_FOUND - system has GENGINE
#  GENGINE_INCLUDE_DIR - the GENGINE include directory
#  GENGINE_LIBRARIES - The libraries needed to use GENGINE

if(NOT GENGINE_INCLUDE_DIR OR NOT GENGINE_LIBRARIES)
	set (LIB_SEARCH_PATHS
	   /usr/lib
	   /usr/lib64
	   /usr/local/lib
	   /usr/local/lib64
	   $ENV{GENGINEROOT}/lib
	   $ENV{GENGINEROOT}/bin
	   $ENV{GENGINE_ROOT}/lib
	   $ENV{GENGINE_ROOT}/bin
	   $ENV{GENGINE_DIR}/lib
	   $ENV{GENGINE_DIR}/bin
	   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Lib
	)
	FIND_PATH(GENGINE_INCLUDE_DIR GEngine/GEngine.hpp
	   /usr/include
	   /usr/local/include
	   $ENV{GENGINEROOT}/include
	   $ENV{GENGINE_ROOT}/include
	   $ENV{GENGINE_DIR}/include
	   $ENV{GENGINE_DIR}/inc
	   [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VC]/PlatformSDK/Include
	   DOC "Include path for GEngine"
	)

	FIND_LIBRARY(GENGINE_LIBRARY_STATIC NAMES gengine_static
	   PATHS ${LIB_SEARCH_PATHS}
	   DOC "GEngine static library name"
	)
	FIND_LIBRARY(GENGINE_LIBRARY_DYN NAMES gengine
	   PATHS ${LIB_SEARCH_PATHS}
	   DOC "GEngine dynamic library name"
	)
	if (GENGINE_FIND_DYNAMIC)
		set(GENGINE_LIBRARIES ${GENGINE_LIBRARY_DYN})
	else(GENGINE_FIND_DYNAMIC)
		set(GENGINE_LIBRARIES ${GENGINE_LIBRARY_STATIC})
	endif(GENGINE_FIND_DYNAMIC)
	MARK_AS_ADVANCED(GENGINE_INCLUDE_DIR GENGINE_LIBRARIES)
endif(NOT GENGINE_INCLUDE_DIR OR NOT GENGINE_LIBRARIES)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GEngine DEFAULT_MSG GENGINE_INCLUDE_DIR GENGINE_LIBRARIES)
