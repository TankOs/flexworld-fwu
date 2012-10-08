#pragma once

#include <SFML/System/Vector3.hpp>

namespace util {

/** Quaternion.
 * @tparam T Number type.
 */
template <typename T>
class Quaternion {
	public:
		typedef sf::Vector3<T> Vector; ///< Vector type.

		/** Construct quaternion from angle-axis notation.
		 * @param angle Angle in radians.
		 * @param axis Rotation axis (must be normalized).
		 * @return Quaternion.
		 */
		static Quaternion<T> from_angle_axis( T angle, const Vector& axis );

		/** Ctor.
		 * Default values represent the multiply identity quaternion.
		 * @param w w.
		 * @param v Vector (x, y, z).
		 */
		Quaternion( T w = T( 1 ), const Vector& v = Vector( 0, 0, 0 ) );

		/** Set vector.
		 * @param v Vector (x, y, z).
		 */
		void set_vector( const Vector& v );

		/** Get vector.
		 * @return Vector (x, y, z).
		 */
		const Vector& get_vector() const;

		/** Set w.
		 * @param w w.
		 */
		void set_w( T w );

		/** Set x.
		 * @param x x.
		 */
		void set_x( T x );

		/** Set y.
		 * @param y y.
		 */
		void set_y( T y );

		/** Set z.
		 * @param z z.
		 */
		void set_z( T z );

		/** Get w.
		 * @return w.
		 */
		T get_w() const;

		/** Get x.
		 * @return x.
		 */
		T get_x() const;

		/** Get y.
		 * @return y.
		 */
		T get_y() const;

		/** Get z.
		 * @return z.
		 */
		T get_z() const;

		/** Equality.
		 * @param other Other quaternion.
		 */
		bool operator==( const Quaternion<T>& other ) const;

		/** Unequality.
		 * @param other Other quaternion.
		 */
		bool operator!=( const Quaternion<T>& other ) const;

		/** Scalar product.
		 * @param scalar Scalar.
		 * @return Quaternion multiplied by scalar.
		 */
		Quaternion<T> operator*( T scalar ) const;

	private:
		Vector m_vector;
		T m_w;
};

typedef Quaternion<float> FloatQuaternion; ///< Float quaternion.

}


#include "Quaternion.inl"
