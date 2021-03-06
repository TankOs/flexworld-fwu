#include <FWU/Quaternion.hpp>
#include <FWU/Math.hpp>
#include <FWU/Axis.hpp>

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

	// Convert to angle-axis notation.
	{
		sf::Vector3f axis{ 1.0f, 2.0f, 3.0f };
		const float ANGLE{ deg_to_rad( 67.123f ) };

		normalize( axis );

		FloatQuaternion q = FloatQuaternion::from_angle_axis( ANGLE, axis );
		float converted_angle{ 0.0f };
		sf::Vector3f converted_axis{ 0.0f, 0.0f, 0.0f };

		q.to_angle_axis( converted_angle, converted_axis );

		BOOST_CHECK( std::abs( converted_angle - ANGLE ) <= TOLERANCE );
		BOOST_CHECK( std::abs( converted_axis.x - axis.x ) <= TOLERANCE );
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

	// Rotate vector (y rotation).
	{
		sf::Vector3f vector =
			FloatQuaternion::from_angle_axis( util::deg_to_rad( 180.0f ), sf::Vector3f( 0.0f, 1.0f, 0.0f ) ) *
			sf::Vector3f( 0.0f, 0.0f, -1.0f )
		;

		BOOST_CHECK( std::abs( vector.x - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( vector.y - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( vector.z - 1.0f ) <= TOLERANCE );
	}

	// Normalize.
	{
		FloatQuaternion q{ 1234.56f, sf::Vector3f{ 6543.21f, 9874.59f, 4982.35f } };
		q.normalize();

		BOOST_CHECK( std::abs( q.get_w() - 0.095627911388874053955078125f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.50683116912841796875f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.764876842498779296875f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.3859283626079559326171875f ) <= TOLERANCE );
	}

	// Convert to Euler angles.
	{
		FloatQuaternion q;

		q = FloatQuaternion::from_angle_axis( deg_to_rad( 5.0f ), axis::x ) * q;
		q = FloatQuaternion::from_angle_axis( deg_to_rad( 10.0f ), axis::y ) * q;
		q = FloatQuaternion::from_angle_axis( deg_to_rad( 15.0f ), axis::z ) * q;

		sf::Vector3f euler_angles = q.to_euler();

		BOOST_CHECK( std::abs( euler_angles.x - deg_to_rad( 5.0f ) ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler_angles.y - deg_to_rad( 10.0f ) ) <= TOLERANCE );
		BOOST_CHECK( std::abs( euler_angles.z - deg_to_rad( 15.0f ) ) <= TOLERANCE );
	}

	// Construct from Euler angles.
	{
		FloatQuaternion q;
		
		q = FloatQuaternion::from_euler( sf::Vector3f{ 0.0f, 0.0f, 0.0f } );
		BOOST_CHECK( std::abs( q.get_w() - 1.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.0f ) <= TOLERANCE );

		q = FloatQuaternion::from_euler( sf::Vector3f{ util::deg_to_rad( 93.5f ), 0.0f, 0.0f } );
		BOOST_CHECK( std::abs( q.get_w() - 0.6851829f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.7283709f ) <= TOLERANCE );

		q = FloatQuaternion::from_euler( sf::Vector3f{ 0.0f, util::deg_to_rad( 233.0f ), 0.0f } );
		BOOST_CHECK( std::abs( q.get_w() - -0.446197f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.8949343f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.0f ) <= TOLERANCE );

		q = FloatQuaternion::from_euler( sf::Vector3f{ 0.0f, 0.0f, util::deg_to_rad( 341.2f ) } );
		BOOST_CHECK( std::abs( q.get_w() - -0.986572f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - 0.163325f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - 0.0f ) <= TOLERANCE );

		q = FloatQuaternion::from_euler( sf::Vector3f{ util::deg_to_rad( 143.4f ), util::deg_to_rad( 32.9f ), util::deg_to_rad( 294.6f ) } );
		BOOST_CHECK( std::abs( q.get_w() - -0.398659f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - -0.063558f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - 0.417099f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - -0.814284f ) <= TOLERANCE );
		/*
		q = FloatQuaternion::from_euler( sf::Vector3f{ 0.0f, util::deg_to_rad( 233.0f ), 0.0f, 0.0f } );
		BOOST_CHECK( std::abs( q.get_w() - f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_x() - f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_y() - f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( q.get_z() - f ) <= TOLERANCE );
		*/
	}
}
