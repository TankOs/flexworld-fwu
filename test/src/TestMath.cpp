#include <FWU/Math.hpp>

#include <boost/test/unit_test.hpp>
#include <cmath>

static const float TOLERANCE = 0.000001f;

BOOST_AUTO_TEST_CASE( TestMath ) {
	BOOST_MESSAGE( "Testing math..." );

	using namespace util;

	// Vector length (3 components).
	{
		sf::Vector3f v;

		v = sf::Vector3f( 2.0f, 0.0f, 0.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector3f( -2.0f, 0.0f, 0.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, 2.0f, 0.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, -2.0f, 0.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, 0.0f, 2.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, 0.0f, -2.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector3f( 1.0f, 2.0f, 3.0f );
		BOOST_CHECK( length( v ) == std::sqrt( 14.0f ) );

		v = sf::Vector3f( 0.0f, 0.0f, 0.0f );
		BOOST_CHECK( length( v ) == std::sqrt( 0.0f ) );
	}

	// Vector length (2 components).
	{
		sf::Vector2f v;

		v = sf::Vector2f( 2.0f, 0.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector2f( -2.0f, 0.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector2f( 0.0f, 2.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector2f( 0.0f, -2.0f );
		BOOST_CHECK( length( v ) == 2.0f );

		v = sf::Vector2f( 1.0f, 2.0f );
		BOOST_CHECK( length( v ) == std::sqrt( 5.0f ) );

		v = sf::Vector2f( 0.0f, 0.0f );
		BOOST_CHECK( length( v ) == std::sqrt( 0.0f ) );
	}

	// Normalize vector (3 components).
	{
		sf::Vector3f v;

		v = sf::Vector3f( 10.0f, 0.0f, 0.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );

		v = sf::Vector3f( 0.0f, 10.0f, 0.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );

		v = sf::Vector3f( 0.0f, 0.0f, 10.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
	}

	// Normalize vector (2 components).
	{
		sf::Vector2f v;

		v = sf::Vector2f( 10.0f, 0.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector2f( 1.0f, 0.0f ) );

		v = sf::Vector2f( 0.0f, 10.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector2f( 0.0f, 1.0f ) );
	}

	// Scalar product.
	{
		sf::Vector3f v0( 10.0f, 5.0f, 5.0f );
		sf::Vector3f v1( 0.5f, 0.5f, 0.0f );

		float result = dot_product( v0, v1 );
		BOOST_CHECK( result == 7.5f );
	}

	// Signum.
	{
		BOOST_CHECK( signum( -10 ) == -1 );
		BOOST_CHECK( signum( 10 ) == 1 );
		BOOST_CHECK( signum( 0 ) == 0 );
	}

	// Sign.
	{
		BOOST_CHECK( sign( -1 ) == -1 );
		BOOST_CHECK( sign( 0 ) == 1 );
		BOOST_CHECK( sign( 1 ) == 1 );
	}

	// Calc area of 2D triangle.
	{
		sf::Vector2f points[3] = {
			sf::Vector2f( 5, 5 ),
			sf::Vector2f( 10, 5 ),
			sf::Vector2f( 10, 10 )
		};

		BOOST_CHECK( std::abs( triangle_area( points[0], points[1], points[2] ) - 12.5f ) <= TOLERANCE );
	}

	// Calc area of 2D rect.
	{
		float a = 10.0f;
		float b = 30.0f;

		BOOST_CHECK( rect_area( a, b ) == a * b );
	}

	// Degrees to radians.
	{
		BOOST_CHECK( deg_to_rad( 0 ) == 0 );
		BOOST_CHECK( std::abs( deg_to_rad( 90 ) - 1.57079633f ) < TOLERANCE);
		BOOST_CHECK( std::abs( deg_to_rad( 180 ) - 3.14159265f ) < TOLERANCE);
		BOOST_CHECK( std::abs( deg_to_rad( 270 ) - 4.71238898f ) < TOLERANCE);
		BOOST_CHECK( std::abs( deg_to_rad( 360 ) - 6.28318531f ) < TOLERANCE);
	}

	// Radians to degrees.
	{
		BOOST_CHECK( rad_to_deg( 0 ) == 0.0f );
		BOOST_CHECK( std::abs( rad_to_deg( 90.0f ) - (90.0f * 180.0f / util::PI) <= TOLERANCE ) );
	}

	// Convert polar coordinate to vector.
	{
		static const float FAULT_TOLERANCE = 0.0001f;

		sf::Vector3f result;

		result = polar_to_vector( deg_to_rad( 0.0f ), deg_to_rad( 0.0f ), 1.0f );
		BOOST_CHECK( std::abs( 0.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 1.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.z ) <= FAULT_TOLERANCE );

		result = polar_to_vector( deg_to_rad( 90.0f ), deg_to_rad( 0.0f ), 1.0f );
		BOOST_CHECK( std::abs( 0.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( -1.0f - result.z ) <= FAULT_TOLERANCE );

		result = polar_to_vector( deg_to_rad( 180.0f ), deg_to_rad( 0.0f ), 1.0f );
		BOOST_CHECK( std::abs( 0.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( -1.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.z ) <= FAULT_TOLERANCE );

		result = polar_to_vector( deg_to_rad( 270.0f ), deg_to_rad( 0.0f ), 1.0f );
		BOOST_CHECK( std::abs( 0.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 1.0f - result.z ) <= FAULT_TOLERANCE );

		result = polar_to_vector( deg_to_rad( 90.0f ), deg_to_rad( 90.0f ), 1.0f );
		BOOST_CHECK( std::abs( -1.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.z ) <= FAULT_TOLERANCE );

		result = polar_to_vector( deg_to_rad( 90.0f ), deg_to_rad( 180.0f ), 1.0f );
		BOOST_CHECK( std::abs( 0.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 1.0f - result.z ) <= FAULT_TOLERANCE );

		result = polar_to_vector( deg_to_rad( 90.0f ), deg_to_rad( 270.0f ), 1.0f );
		BOOST_CHECK( std::abs( 1.0f - result.x ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.y ) <= FAULT_TOLERANCE );
		BOOST_CHECK( std::abs( 0.0f - result.z ) <= FAULT_TOLERANCE );
	}

	// Dot product.
	{
		sf::Vector3f result = cross_product(
			sf::Vector3f( 1, 2, 3 ),
			sf::Vector3f( 3, 2, 1 )
		);

		BOOST_CHECK(
			result.x == -4 &&
			result.y == 8 &&
			result.z == -4
		);
	}

	// Inverse.
	{
		static const sf::Vector3f VECTOR{ 1.0f, -2.0f, 3.0f };
		static const sf::Vector3f INVERSE_VECTOR{ -1.0f, 2.0f, -3.0f };

		BOOST_CHECK( INVERSE_VECTOR == inverse( VECTOR ) );
	}

	// Angle-axis to Euler.
	{
		sf::Vector3f euler;

		euler = angle_axis_to_euler( deg_to_rad( 22.2f ), sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( std::abs( euler.x - deg_to_rad( 22.2f ) ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler.y ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler.z ) <= TOLERANCE );

		euler = angle_axis_to_euler( deg_to_rad( 44.4f ), sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
		BOOST_CHECK( std::abs( euler.x ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler.y - deg_to_rad( 44.4f ) ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler.z ) <= TOLERANCE );

		euler = angle_axis_to_euler( deg_to_rad( 66.6f ), sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
		BOOST_CHECK( std::abs( euler.x ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler.y ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler.z - deg_to_rad( 66.6f ) ) <= TOLERANCE );
	}
}
