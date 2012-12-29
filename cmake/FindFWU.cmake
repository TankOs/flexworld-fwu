#
# Find's FWU library.
#
# Input variables:
#   FWU_ROOT              Additional library search directory.
#   FWU_STATIC_LIBRARIES  Look for static libraries.
#
# Output variables:
#   FWU_INCLUDE_DIR   Include directory.
#   FWU_LIBRARY       Library.

cmake_minimum_required( VERSION 2.8 )

set( FWU_FOUND FALSE )

if( FWU_STATIC_LIBRARIES )
	set( FWU_SUFFIX "-s" )
	add_definitions( -DFWU_STATIC )
else()
	set( FWU_SUFFIX "" )
endif()

find_path(
	FWU_INCLUDE_DIR
	FWU/Config.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${FWU_ROOT}
)

find_library(
	FWU_LIBRARY_RELEASE
	fwu${FWU_SUFFIX}
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWU_ROOT}
)

find_library(
	FWU_LIBRARY_DEBUG
	fwu${FWU_SUFFIX}-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWU_ROOT}
)

if( FWU_LIBRARY_RELEASE AND FWU_LIBRARY_DEBUG )
	set( FWU_LIBRARY debug ${FWU_LIBRARY_DEBUG} optimized ${FWU_LIBRARY_RELEASE} )
endif()

if( FWU_LIBRARY_RELEASE AND NOT FWU_LIBRARY_DEBUG )
	set( FWU_LIBRARY_DEBUG ${FWU_LIBRARY_RELEASE} )
	set( FWU_LIBRARY ${FWU_LIBRARY_RELEASE} )
endif()

if( FWU_LIBRARY_DEBUG AND NOT FWU_LIBRARY_RELEASE )
	set( FWU_LIBRARY_RELEASE ${FWU_LIBRARY_DEBUG} )
	set( FWU_LIBRARY ${FWU_LIBRARY_DEBUG} )
endif()

if( NOT FWU_INCLUDE_DIR OR NOT FWU_LIBRARY )
	message( FATAL_ERROR "FWU not found." )
else()
	message( "FWU found: ${FWU_INCLUDE_DIR}" )
endif()
