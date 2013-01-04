#include <FWU/Math.hpp>
#include <cassert>
#include <cmath>

namespace util {

float length( const sf::Vector3f& v ) {
	return std::sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

float length( const sf::Vector2f& v ) {
	return std::sqrt( v.x * v.x + v.y * v.y );
}

void normalize( sf::Vector3f& v ) {
	float len = length( v );
	assert( len > 0.0f );

	v.x /= len;
	v.y /= len;
	v.z /= len;
}

void normalize( sf::Vector2f& v ) {
	float len = length( v );
	assert( len > 0.0f );

	v.x /= len;
	v.y /= len;
}

float dot_product( const sf::Vector3f& v0, const sf::Vector3f& v1 ) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

float triangle_area( const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2 ) {
	float lengths[3] = {
		std::sqrt(
			+ (p1.x - p0.x) * (p1.x - p0.x)
			+ (p1.y - p0.y) * (p1.y - p0.y)
		),
		std::sqrt(
			+ (p2.x - p1.x) * (p2.x - p1.x)
			+ (p2.y - p1.y) * (p2.y - p1.y)
		),
		std::sqrt(
			+ (p0.x - p2.x) * (p0.x - p2.x)
			+ (p0.y - p2.y) * (p0.y - p2.y)
		)
	};

	float h_perimeter = (lengths[0] + lengths[1] + lengths[2]) / 2.0f;

	return std::sqrt( h_perimeter * (h_perimeter - lengths[0]) * (h_perimeter - lengths[1]) * (h_perimeter - lengths[2]) );
}

float rect_area( float a, float b ) {
	return a * b;
}

sf::Vector3f polar_to_vector( float theta, float phi, float r ) {
	return sf::Vector3f(
		-r * std::sin( theta ) * std::sin( phi ),
		r * std::cos( theta ),
		-r * std::sin( theta ) * std::cos( phi )
	);
}

float deg_to_rad( float deg ) {
	return deg / 180.0f * PI;
}

sf::Vector3f cross_product( const sf::Vector3f& a, const sf::Vector3f& b ) {
	return sf::Vector3f(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float rad_to_deg( float rad ) {
	return rad * 180.0f / PI;
}

sf::Vector3f inverse( const sf::Vector3f& v ) {
	return sf::Vector3f{
		-v.x,
		-v.y,
		-v.z
	};
}

sf::Vector3f angle_axis_to_euler( float angle, const sf::Vector3f& axis ) {
	return sf::Vector3f{
		std::atan2(
			axis.x * std::sin( angle ) - axis.y * axis.z * (1.0f - std::cos( angle )),
			1.0f - (axis.x * axis.x + axis.z * axis.z) * (1.0f - std::cos( angle ))
		),
		std::atan2(
			axis.y * std::sin( angle ) - axis.x * axis.z * (1.0f - std::cos( angle )),
			1.0f - (axis.y * axis.y + axis.z * axis.z) * (1.0f - std::cos( angle ))
		),
		std::asin( axis.x * axis.y * (1.0f - std::cos( angle )) + axis.z * std::sin( angle ) )
	};
}

}
