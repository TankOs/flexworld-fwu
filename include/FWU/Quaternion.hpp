#pragma once

#include <SFML/System/Vector3.hpp>

namespace util {

/** Quaternion.
 * This quaternion implementation does NOT normalize the quaternion. Before you
 * create a matrix or rotate vectors, make sure that the quaternion is
 * normalized.
 *
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

		/** Construct quaternion from Euler angles.
		 * @param angles Angles in radians.
		 * @return Quaternion.
		 */
		static Quaternion<T> from_euler( const Vector& angles );

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

		/** Make conjugate.
		 * @return Conjugate.
		 */
		Quaternion<T> make_conjugate() const;

		/** Normalize.
		 */
		void normalize();

		/** Equality.
		 * @param first First quaternion.
		 * @param second Second quaternion.
		 * @return true if equal.
		 */
		template <typename TT>
		friend bool operator==( const Quaternion<TT>& first, const Quaternion<TT>& second );

		/** Unequality.
		 * @param first First quaternion.
		 * @param second Second quaternion.
		 * @return true if not equal.
		 */
		template <typename TT>
		friend bool operator!=( const Quaternion<TT>& first, const Quaternion<TT>& second );

		/** Scalar product.
		 * @param quaternion Quaternion.
		 * @param scalar Scalar.
		 * @return Quaternion multiplied by scalar.
		 */
		template <typename TT>
		friend Quaternion<TT> operator*( const Quaternion<TT>& quaternion, TT scalar );

		/** Combine two quaternions.
		 * Note: Multiplying quaternions is not commutative!
		 * @param first First quaternion.
		 * @param second Second quaternion.
		 * @return first and second combined.
		 */
		template <typename TT>
		friend Quaternion<TT> operator*( const Quaternion<TT>& first, const Quaternion<TT>& second );

		/** Rotate vector.
		 * @param quaternion Quaternion.
		 * @param vector Vector.
		 * @return Rotated vector.
		 */
		template <typename TT>
		friend typename Quaternion<TT>::Vector operator*( const Quaternion<TT>& quaternion, const typename Quaternion<TT>::Vector& vector );

		/** Combine this quaternion with another one.
		 * Note: Multiplying quaternions is not commutative!
		 * @param q Other quaternion.
		 * @return *this.
		 */
		Quaternion<T>& operator*=( const Quaternion<T>& q );

		/** Convert to Euler angles.
		 * @return Euler angles.
		 */
		sf::Vector3f to_euler() const;

		/** Convert to angle-axis notation.
		 * @param angle Filled with converted angle.
		 * @param axis Filled with converted axis.
		 */
		void to_angle_axis( float& angle, sf::Vector3f& axis ) const;

	private:
		Vector m_vector;
		T m_w;
};

typedef Quaternion<float> FloatQuaternion; ///< Float quaternion.

}


#include "Quaternion.inl"
