namespace util {

template <>
const sf::Vector3f& axis_vector<Axis::X>() {
	static const sf::Vector3f v{ 1.0f, 0.0f, 0.0f };
	return v;
}

template <>
const sf::Vector3f& axis_vector<Axis::Y>() {
	static const sf::Vector3f v{ 0.0f, 1.0f, 0.0f };
	return v;
}

template <>
const sf::Vector3f& axis_vector<Axis::Z>() {
	static const sf::Vector3f v{ 0.0f, 0.0f, 1.0f };
	return v;
}

}
