#pragma once

#include <SFML/System/Vector3.hpp>

namespace util {

/** Axis.
 */
enum Axis : int {
	X = 0, ///< X axis.
	Y = 1, ///< Y axis.
	Z = 2 ///< Z axis.
};

/** Construct axis vector.
 * @tparam axis Axis.
 * @return Axis vector.
 */
template <int axis>
const sf::Vector3f& axis_vector();

/** Construct x axis vector.
 * @return X axis vector.
 */
template <>
const sf::Vector3f& axis_vector<Axis::X>();

/** Construct y axis vector.
 * @return Y axis vector.
 */
template <>
const sf::Vector3f& axis_vector<Axis::Y>();

/** Construct z axis vector.
 * @return Z axis vector.
 */
template <>
const sf::Vector3f& axis_vector<Axis::Z>();

}

#include "Axis.inl"
