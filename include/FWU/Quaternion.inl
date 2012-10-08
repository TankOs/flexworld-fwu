#include <FWU/Math.hpp>

#include <utility>
#include <cassert>
#include <cmath>

namespace util {

template <typename T>
Quaternion<T> Quaternion<T>::from_angle_axis( T angle, const Vector& axis ) {
	assert( calc_length( axis ) <= 1 );

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
bool Quaternion<T>::operator==( const Quaternion<T>& other ) const {
	return
		other.m_w == m_w &&
		other.m_vector == m_vector
	;
}

template <typename T>
bool Quaternion<T>::operator!=( const Quaternion<T>& other ) const {
	return
		other.m_w != m_w ||
		other.m_vector != m_vector
	;
}

template <typename T>
Quaternion<T> Quaternion<T>::operator*( T scalar ) const {
	return Quaternion<T>(
		m_w * scalar,
		typename Quaternion<T>::Vector(
			m_vector.x * scalar,
			m_vector.y * scalar,
			m_vector.z * scalar
		)
	);
}

}
