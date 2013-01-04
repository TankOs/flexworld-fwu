#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace util {

static const float PI = 3.14159265f; ///< PI.

/** Calculate a vector's length.
 * @param v Vector.
 * @return Length.
 */
float length( const sf::Vector3f& v );

/** Calculate a vector's length.
 * @param v Vector.
 * @return Length.
 */
float length( const sf::Vector2f& v );

/** Normalize vector.
 * @param v Vector.
 */
void normalize( sf::Vector3f& v );

/** Normalize vector.
 * @param v Vector.
 */
void normalize( sf::Vector2f& v );

/** Calculate dot product.
 * @param v0 Vector 0.
 * @param v1 Vector 1.
 * @return Dot product.
 */
float dot_product( const sf::Vector3f& v0, const sf::Vector3f& v1 );

/** Calculate signum.
 * @param value Value.
 * @tparam T Value type.
 * @return -1 if negative, 0 if zero, 1 if positive.
 */
template <class T>
T signum( T value );

/** Determine sign of value.
 * @param value Value.
 * @return -1 if value < 0, otherwise +1.
 */
template <class T>
T sign( T value );

/** Calculate area of triangle.
 * The points must be ordered counter-clockwise.
 * @param p0 Point 0.
 * @param p1 Point 1.
 * @param p2 Point 2.
 * @return Area.
 */
float triangle_area( const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2 );

/** Calculate area of rect.
 * @param a Length of side A.
 * @param b Length of side B.
 * @return Area.
 */
float rect_area( float a, float b );

/** Convert polar coordinates to vector.
 * The resulting vector is adjusted to match OpenGL's coordinate system. When
 * Phi and Theta are 0°, the vector is pointing up (x=0, y=1, z=0). Angles are
 * counter-clockwise.
 * @param theta Theta (polar angle/altitude, OGL x axis) in radians.
 * @param phi Phi (azimuth, OGL y axis) in radians.
 * @param r Radius.
 * @return Vector.
 */
sf::Vector3f polar_to_vector( float theta, float phi, float r = 1.f );

/** Convert degrees to radians.
 * @param deg Degrees.
 * @return Radians.
 */
float deg_to_rad( float deg );

/** Convert radians to degrees.
 * @param rad Radians.
 * @return Degrees.
 */
float rad_to_deg( float rad );

/** Cross product.
 * @param a Vector.
 * @param b Vector.
 * @return Cross product a x b.
 */
sf::Vector3f cross_product( const sf::Vector3f& a, const sf::Vector3f& b );

/** Inverse of vector.
 * @param v Vector.
 * @return Inverse of v.
 */
sf::Vector3f inverse( const sf::Vector3f& v );

/** Convert angle-axis to Euler angles.
 * @param angle Angle, in radians.
 * @param axis Rotation axis.
 * @return Euler angles.
 */
sf::Vector3f angle_axis_to_euler( float angle, const sf::Vector3f& axis );

}

#include "Math.inl"
