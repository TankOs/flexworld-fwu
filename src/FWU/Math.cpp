#include <FWU/Math.hpp>
#include <cassert>
#include <cmath>

namespace util {

float calc_length( const sf::Vector3f& v ) {
	return std::sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

void normalize( sf::Vector3f& v ) {
	float length = calc_length( v );
	assert( length > 0.0f );

	v.x /= length;
	v.y /= length;
	v.z /= length;
}

float calc_scalar_product( const sf::Vector3f& v0, const sf::Vector3f& v1 ) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

float calc_triangle_area( const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2 ) {
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

float calc_rect_area( float a, float b ) {
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

sf::Vector3f dot_product( const sf::Vector3f& a, const sf::Vector3f& b ) {
	return sf::Vector3f(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float rad_to_deg( float rad ) {
	return rad * 180.0f / PI;
}

}
