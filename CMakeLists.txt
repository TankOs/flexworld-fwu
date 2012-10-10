cmake_minimum_required( VERSION 2.8 )
project( FWU )

find_package( SFML 2.0 REQUIRED SYSTEM )

set( FWU_BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries." )
set( FWU_BUILD_TEST TRUE CACHE BOOL "Build test suite." )
set( FWU_BUILD_DOCS FALSE CACHE BOOL "Build Doxygen API documentation." )
set( FWU_SKIP_INSTALL FALSE CACHE BOOL "Do not run install target (useful when including lib in projects)." )

if( CMAKE_COMPILER_IS_GNUCXX )
	if( NOT CMAKE_CXX_FLAGS )
		set( CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Wshadow -Wconversion -pedantic" CACHE STRING "C++ compiler flags." FORCE )
	endif()
endif()

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type." FORCE )
endif()

set( SRC_DIR "src" )
set( INC_DIR "include" )

set(
	SOURCES
	${INC_DIR}/FWU/Config.hpp
	${INC_DIR}/FWU/Cuboid.hpp
	${INC_DIR}/FWU/Cuboid.inl
	${INC_DIR}/FWU/Log.hpp
	${INC_DIR}/FWU/LooseOctree.hpp
	${INC_DIR}/FWU/LooseOctree.inl
	${INC_DIR}/FWU/Math.hpp
	${INC_DIR}/FWU/Math.inl
	${INC_DIR}/FWU/Matrix.hpp
	${INC_DIR}/FWU/Matrix.inl
	${INC_DIR}/FWU/Quaternion.hpp
	${INC_DIR}/FWU/Quaternion.inl
	${SRC_DIR}/FWU/Log.cpp
	${SRC_DIR}/FWU/Math.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${SFML_INCLUDE_DIRS} )

add_library( fwu ${LIB_TYPE} ${SOURCES} )

if( FWU_BUILD_SHARED_LIBS )
	set( LIB_TYPE SHARED )

	set_target_properties( fwu PROPERTIES DEBUG_POSTFIX -d )
else()
	set( LIB_TYPE STATIC )
	add_definitions( -DFWU_STATIC )

	set_target_properties( fwu PROPERTIES DEBUG_POSTFIX -s-d )
	set_target_properties( fwu PROPERTIES RELEASE_POSTFIX -s )
	set_target_properties( fwu PROPERTIES MINSIZEREL_POSTFIX -s )
endif()

if( NOT FWU_SKIP_INSTALL )
	install(
		TARGETS fwu
		RUNTIME DESTINATION bin COMPONENT bin
		LIBRARY DESTINATION lib COMPONENT bin
		ARCHIVE DESTINATION lib COMPONENT dev
	)

	install(
		DIRECTORY include
		DESTINATION .
	)
endif()

if( FWU_BUILD_TEST )
	add_subdirectory( test )
endif()

if( FWU_BUILD_DOCS )
	add_subdirectory( "doc/doxygen" )
endif()
