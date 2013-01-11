#include <FWU/Math.hpp>

#include <utility>
#include <cassert>
#include <cmath>

namespace util {

template <typename T>
Quaternion<T> Quaternion<T>::from_angle_axis( T angle, const Vector& axis ) {
	assert( length( axis ) <= 1 );

	const float SIN_ANGLE_OVER_2 = std::sin( angle / 2 );

	return std::move(
		Quaternion<T>(
			std::cos( angle / 2 ),
			Vector(
				axis.x * SIN_ANGLE_OVER_2,
				axis.y * SIN_ANGLE_OVER_2,
				axis.z * SIN_ANGLE_OVER_2
			)
		)
	);
}

template <typename T>
Quaternion<T> Quaternion<T>::from_euler( const Vector& angles ) {
	float c1 = std::cos( angles.y / 2.0f );
	float c2 = std::cos( angles.x / 2.0f );
	float c3 = std::cos( angles.z / 2.0f );
	float s1 = std::sin( angles.y / 2.0f );
	float s2 = std::sin( angles.x / 2.0f );
	float s3 = std::sin( angles.z / 2.0f );

	return std::move(
		Quaternion<T>(
			c1 * c2 * c3 - s1 * s2 * s3,
			Vector(
				s1 * s2 * c3 + c1 * c2 * s3,
				s1 * c2 * c3 + c1 * s2 * s3,
				c1 * s2 * c3 - s1 * c2 * s3
			)
		)
	);
}

template <typename T>
Quaternion<T>::Quaternion( T w, const Vector& v ) :
	m_vector{ v },
	m_w{ w }
{
}

template <typename T>
const typename Quaternion<T>::Vector& Quaternion<T>::get_vector() const {
	return m_vector;
}

template <typename T>
void Quaternion<T>::set_vector( const Vector& v ) {
	m_vector = v;
}

template <typename T>
void Quaternion<T>::set_w( T w ) {
	m_w = w;
}

template <typename T>
void Quaternion<T>::set_x( T x ) {
	m_vector.x = x;
}

template <typename T>
void Quaternion<T>::set_y( T y ) {
	m_vector.y = y;
}

template <typename T>
void Quaternion<T>::set_z( T z ) {
	m_vector.z = z;
}

template <typename T>
T Quaternion<T>::get_w() const {
	return m_w;
}

template <typename T>
T Quaternion<T>::get_x() const {
	return m_vector.x;
}

template <typename T>
T Quaternion<T>::get_y() const {
	return m_vector.y;
}

template <typename T>
T Quaternion<T>::get_z() const {
	return m_vector.z;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator*=( const Quaternion<T>& q ) {
	float w{ m_w * q.m_w - m_vector.x * q.m_vector.x - m_vector.y * q.m_vector.y - m_vector.z * q.m_vector.z};
	Vector vector{
		m_w * q.m_vector.x + m_vector.x * q.m_w        + m_vector.y * q.m_vector.z - m_vector.z * q.m_vector.y,
		m_w * q.m_vector.y - m_vector.x * q.m_vector.z + m_vector.y * q.m_w        + m_vector.z * q.m_vector.x,
		m_w * q.m_vector.z + m_vector.x * q.m_vector.y - m_vector.y * q.m_vector.x + m_vector.z * q.m_w
	};

	std::swap( w, m_w );
	std::swap( vector, m_vector );

	return *this;
}

template <typename T>
Quaternion<T> Quaternion<T>::make_conjugate() const {
	return Quaternion<T>(
		m_w,
		Vector(
			-m_vector.x,
			-m_vector.y,
			-m_vector.z
		)
	);
}

template <typename T>
void Quaternion<T>::normalize() {
	T length = std::sqrt( m_w * m_w + m_vector.x * m_vector.x + m_vector.y * m_vector.y + m_vector.z * m_vector.z );

	m_w /= length;
	m_vector.x /= length;
	m_vector.y /= length;
	m_vector.z /= length;
}

/// Free.

template <typename T>
bool operator==( const util::Quaternion<T>& first, const util::Quaternion<T>& second ) {
	return
		first.m_w == second.m_w &&
		first.m_vector == second.m_vector
	;
}

template <typename T>
bool operator!=( const util::Quaternion<T>& first, const util::Quaternion<T>& second ) {
	return
		first.m_w != second.m_w ||
		first.m_vector != second.m_vector
	;
}

template <typename T>
util::Quaternion<T> operator*( const util::Quaternion<T>& quaternion, T scalar ) {
	return util::Quaternion<T>(
		quaternion.m_w * scalar,
		typename Quaternion<T>::Vector(
			quaternion.m_vector.x * scalar,
			quaternion.m_vector.y * scalar,
			quaternion.m_vector.z * scalar
		)
	);
}

template <typename T>
Quaternion<T> operator*( const Quaternion<T>& first, const Quaternion<T>& second ) {
	return Quaternion<T>{
		first.m_w * second.m_w - first.m_vector.x * second.m_vector.x - first.m_vector.y * second.m_vector.y - first.m_vector.z * second.m_vector.z,
		typename Quaternion<T>::Vector{
			first.m_w * second.m_vector.x + first.m_vector.x * second.m_w        + first.m_vector.y * second.m_vector.z - first.m_vector.z * second.m_vector.y,
			first.m_w * second.m_vector.y - first.m_vector.x * second.m_vector.z + first.m_vector.y * second.m_w        + first.m_vector.z * second.m_vector.x,
			first.m_w * second.m_vector.z + first.m_vector.x * second.m_vector.y - first.m_vector.y * second.m_vector.x + first.m_vector.z * second.m_w
		}
	};
}

template <typename T>
typename Quaternion<T>::Vector operator*( const Quaternion<T>& quaternion, const typename Quaternion<T>::Vector& vector ) {
	return
		(
			quaternion *
			Quaternion<T>{ 0, vector } *
			quaternion.make_conjugate()
		).get_vector();
	;
}

template <typename T>
sf::Vector3f Quaternion<T>::to_euler() const {
	return sf::Vector3f{
		std::atan2(
			2.0f * (m_w * m_vector.x + m_vector.y * m_vector.z),
			1.0f - 2.0f * (m_vector.x * m_vector.x + m_vector.y * m_vector.y)
		),
		std::asin( 2.0f * (m_w * m_vector.y - m_vector.z * m_vector.x) ),
		std::atan2(
			2.0f * (m_w * m_vector.z + m_vector.x * m_vector.y ),
			1.0f - 2.0f * (m_vector.y * m_vector.y + m_vector.z * m_vector.z)
		)
	};
}

template <typename T>
void Quaternion<T>::to_angle_axis( float& angle, sf::Vector3f& axis ) const {
	const float W_SQRT{ std::sqrt( 1.0f - m_w * m_w ) };

	angle = 2.0f * std::acos( m_w );
	axis.x = m_vector.x / W_SQRT;
	axis.y = m_vector.y / W_SQRT;
	axis.z = m_vector.z / W_SQRT;
}

}
