#include <FWU/Axis.hpp>

#include <boost/test/unit_test.hpp>

using namespace util;

BOOST_AUTO_TEST_CASE( TestAxis ) {
	// Initial state.
	{
		BOOST_CHECK( axis_vector<Axis::X>() == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( axis_vector<Axis::Y>() == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
		BOOST_CHECK( axis_vector<Axis::Z>() == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
	}
}
