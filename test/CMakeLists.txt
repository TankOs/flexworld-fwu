cmake_minimum_required( VERSION 2.8 )
project( FWU-test )

find_package( Boost 1.46 REQUIRED unit_test_framework )

if( NOT Boost_USE_STATIC_LIBS )
	add_definitions( -DBOOST_TEST_DYN_LINK )
endif()

set( SRC_DIR "src" )
set( INC_DIR "src" )

set(
	SOURCES
	${SRC_DIR}/Test.cpp
	${SRC_DIR}/TestCuboid.cpp
	${SRC_DIR}/TestLooseOctree.cpp
	${SRC_DIR}/TestMath.cpp
	${SRC_DIR}/TestMatrix.cpp
)

include_directories( ${PROJECT_SOURCE_DIR}/../include )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable( test ${SOURCES} )

target_link_libraries( test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries( test fwu )

add_custom_command(
	TARGET test
	COMMAND test
	ARGUMENTS "--log_level=message"
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
