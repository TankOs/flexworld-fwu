#include <FWU/Axis.hpp>

#include <boost/test/unit_test.hpp>

using namespace util;

BOOST_AUTO_TEST_CASE( TestAxis ) {
	// Initial state.
	{
		BOOST_CHECK( axis::x == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( axis::y == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
		BOOST_CHECK( axis::z == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
	}
}
