#include "WorldToScreen.h"

template<class Comparable>
Comparable min(Comparable c1, Comparable c2) {
	return c1 >= c2 ? c2 : c1;
}

sf::Vector2<float> specialDivide(sf::Vector2<float> v1, sf::Vector2<float> v2) {
	return sf::Vector2<float>(v1.x / v2.x, v1.y / v2.y);
}

sf::Vector2<float> abs(sf::Vector2<float> v) {

	float x = v.x >= 0 ? v.x : -v.x;
	float y = v.y >= 0 ? v.y : -v.y;

	return sf::Vector2<float>(x, y);
}

Matrix22 inverse(Matrix22 m) {
	Matrix22 m1;

	float f = m.m00 * m.m11 - m.m01 * m.m10;

	m1.m00 = m.m11 / f;
	m1.m01 = -m.m01 / f;
	m1.m10 = -m.m10 / f;
	m1.m11 = m.m00 / f;

	return m1;
}

sf::Vector2<float> mult(Matrix22 m, sf::Vector2<float> v) {
	sf::Vector2<float> res;

	res.x = m.m00 * v.x + m.m10 * v.y;
	res.y = m.m10 * v.x + m.m11 * v.y;

	return res;
}

WorldToScreen::WorldToScreen(
	const sf::Vector2<float> DownLeftCornerWorld,
	const sf::Vector2<float> UpRightCornerWorld,
	const sf::Vector2<float> DownLeftCornerScreen,
	const sf::Vector2<float> UpRightCornerScreen) {

	sf::Vector2<float> v1 = UpRightCornerWorld - DownLeftCornerWorld;
	sf::Vector2<float> v2 = UpRightCornerScreen - DownLeftCornerScreen;

	//Figuring the zoom ratio	
	sf::Vector2<float> q = specialDivide(v2, v1);
	sf::Vector2<float> q1 = abs(q);
	float lambda = min<float>(q1.x, q1.y);

	float eps1 = q.x > 0 ? 1 : -1;
	float eps2 = q.y > 0 ? 1 : -1;

	_M.m00 = eps1 *lambda;
	_M.m10 = 0;
	_M.m01 = 0;
	_M.m11 = eps2 *lambda;

	//figuring offset
	sf::Vector2<float> c1 = 0.5f*(DownLeftCornerWorld + UpRightCornerWorld);
	sf::Vector2<float> c2 = 0.5f*(UpRightCornerScreen + DownLeftCornerScreen);

	zoom = lambda;

	_B = c2 - mult(_M, c1);
}

sf::Vector2<float> WorldToScreen::operator()(const sf::Vector2<float> worldCoordinate){
	return mult(_M, worldCoordinate) + _B;
}

