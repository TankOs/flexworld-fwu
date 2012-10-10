#include <FWU/Quaternion.hpp>
#include <FWU/Math.hpp>

#include <SFML/System/Vector3.hpp>
#include <boost/test/unit_test.hpp>

using namespace util;

static const float TOLERANCE = 0.0001f;

BOOST_AUTO_TEST_CASE( TestQuaternion ) {
	BOOST_MESSAGE( "Testing quaternion..." );

	// Initial state.
	{
		FloatQuaternion q;

		BOOST_CHECK( q.get_w() == 1.0f );
		BOOST_CHECK( q.get_vector() == FloatQuaternion::Vector( 0.0f, 0.0f, 0.0f ) );
	}

	// Ctor.
	{
		FloatQuaternion q( 10.0f, FloatQuaternion::Vector( 2.0f, 3.0f, 4.0f ) );

		BOOST_CHECK( q.get_w() == 10.0f );
		BOOST_CHECK( q.get_vector() == sf::Vector3f( 2.0f, 3.0f, 4.0f ) );
	}

	// Basic properties.
	{
		FloatQuaternion q;

		q.set_w( 1.0f );
		q.set_x( 2.0f );
		q.set_y( 3.0f );
		q.set_z( 4.0f );

		BOOST_CHECK( q.get_w() == 1.0f );
		BOOST_CHECK( q.get_x() == 2.0f );
		BOOST_CHECK( q.get_y() == 3.0f );
		BOOST_CHECK( q.get_z() == 4.0f );
		BOOST_CHECK( q.get_vector() == FloatQuaternion::Vector( 2.0f, 3.0f, 4.0f ) );

		q.set_vector( FloatQuaternion::Vector( 10.0f, 20.0f, 30.0f ) );
		BOOST_CHECK( q.get_w() == 1.0f );
		BOOST_CHECK( q.get_x() == 10.0f );
		BOOST_CHECK( q.get_y() == 20.0f );
		BOOST_CHECK( q.get_z() == 30.0f );
		BOOST_CHECK( q.get_vector() == FloatQuaternion::Vector( 10.0f, 20.0f, 30.0f ) );
	}

	// Equality.
	{
		FloatQuaternion a;
		FloatQuaternion b;

		BOOST_CHECK( a == b );

		a.set_w( 999.9f );
		BOOST_CHECK( (a == b) == false );
		a.set_w( 1.0f );
		BOOST_CHECK( (a == b) == true );

		a.set_x( 999.9f );
		BOOST_CHECK( (a == b) == false );
		a.set_x( 0.0f );
		BOOST_CHECK( (a == b) == true );

		a.set_y( 999.9f );
		BOOST_CHECK( (a == b) == false );
		a.set_y( 0.0f );
		BOOST_CHECK( (a == b) == true );

		a.set_z( 999.9f );
		BOOST_CHECK( (a == b) == false );
		a.set_z( 0.0f );
		BOOST_CHECK( (a == b) == true );
	}

	// Unequality.
	{
		FloatQuaternion a;
		FloatQuaternion b;

		BOOST_CHECK( (a != b) == false );

		a.set_w( 999.9f );
		BOOST_CHECK( (a != b) == true );
		a.set_w( 1.0f );
		BOOST_CHECK( (a != b) == false );

		a.set_x( 999.9f );
		BOOST_CHECK( (a != b) == true );
		a.set_x( 0.0f );
		BOOST_CHECK( (a != b) == false );

		a.set_y( 999.9f );
		BOOST_CHECK( (a != b) == true );
		a.set_y( 0.0f );
		BOOST_CHECK( (a != b) == false );

		a.set_z( 999.9f );
		BOOST_CHECK( (a != b) == true );
		a.set_z( 0.0f );
		BOOST_CHECK( (a != b) == false );
	}

	// Scalar product.
	{
		FloatQuaternion q( 1.0f, FloatQuaternion::Vector( 2.0f, 3.0f, 4.0f ) );

		BOOST_CHECK( q * 10.0f == FloatQuaternion( 10.0f, FloatQuaternion::Vector( 20.0f, 30.0f, 40.0f ) ) );
	}

	// Construct from angle-axis notation.
	{
		FloatQuaternion q;
		
		q = FloatQuaternion::from_angle_axis( deg_to_rad( 0.0f ), FloatQuaternion::Vector( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( q == FloatQuaternion( 1.0f, FloatQuaternion::Vector( 0.0f, 0.0f, 0.0f ) ) );

		q = FloatQuaternion::from_angle_axis( deg_to_rad( 45.0f ), FloatQuaternion::Vector( 1.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( std::abs( q.get_w() - 0.92388f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.382683f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.0f ) <= TOLERANCE );

		q = FloatQuaternion::from_angle_axis( deg_to_rad( 88.3f ), FloatQuaternion::Vector( 0.0f, 1.0f, 0.0f ) );
		BOOST_CHECK( std::abs( q.get_w() - 0.717519f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.696539f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.0f ) <= TOLERANCE );

		q = FloatQuaternion::from_angle_axis( deg_to_rad( 273.9f ), FloatQuaternion::Vector( 0.0f, 0.0f, 1.0f ) );
		BOOST_CHECK( std::abs( q.get_w() - -0.730758f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.682636f ) <= TOLERANCE );

		FloatQuaternion::Vector insane_vector( 435.3f, 491.9f, 2945.1f );
		normalize( insane_vector );

		q = FloatQuaternion::from_angle_axis( deg_to_rad( 343.5f ), insane_vector );
		BOOST_CHECK( std::abs( q.get_w() - -0.989651f) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.0207003f) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.0233919f) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.140052f) <= TOLERANCE );
	}

	// Multiply (combine).
	{
		// Multiplying identities doesn't change anything.
		{
			FloatQuaternion a;
			FloatQuaternion b;
			FloatQuaternion result;

			result = a * b;
			a *= result;

			BOOST_CHECK( a == FloatQuaternion() );
			BOOST_CHECK( b == FloatQuaternion() );
			BOOST_CHECK( result == FloatQuaternion() );
		}

		// Random combinations.
		{
			FloatQuaternion result =
				FloatQuaternion( 33.2f, sf::Vector3f( 1.0f, 0.0f, 0.0f ) ) *
				FloatQuaternion( 93.1f, sf::Vector3f( 0.0f, 1.0f, 0.0f ) ) *
				FloatQuaternion( 253.9f, sf::Vector3f( 0.0f, 0.0f, 1.0f ) )
			;

			BOOST_CHECK( std::abs( result.get_w() - 784783.5625f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( result.get_x() - 23671.2890625f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( result.get_y() - 8336.380859375f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( result.get_z() - 3344.81982421875f ) <= TOLERANCE );

			result = FloatQuaternion();
			result *= FloatQuaternion( 33.2f, sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
			result *= FloatQuaternion( 93.1f, sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
			result *= FloatQuaternion( 253.9f, sf::Vector3f( 0.0f, 0.0f, 1.0f ) );

			BOOST_CHECK( std::abs( result.get_w() - 784783.5625f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( result.get_x() - 23671.2890625f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( result.get_y() - 8336.380859375f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( result.get_z() - 3344.81982421875f ) <= TOLERANCE );
		}
	}

	// Conjugate.
	{
		FloatQuaternion q( 1.0f, sf::Vector3f( 2.0f, 3.0f, 4.0f ) );

		BOOST_CHECK( q.make_conjugate() == FloatQuaternion( 1.0f, sf::Vector3f( -2.0f, -3.0f, -4.0f ) ) );
	}

	// Rotate vector.
	{
		sf::Vector3f vector =
			FloatQuaternion( 100.0f, sf::Vector3f( 20.0f, 10.0f, 5.0f ) ) *
			sf::Vector3f( 1.0f, 2.0f, 3.0f )
		;

		BOOST_CHECK( std::abs( vector.x - 15675.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( vector.y - 9050.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( vector.z - 34975.0f ) <= TOLERANCE );
	}
}
