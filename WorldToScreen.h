#ifndef WORLDTOSCREEN_H
#define WORLDTOSCREEN_H
#include <SFML\Graphics.hpp>

typedef struct Matrix22 {
	float m00, m01, m10, m11;
} Matrix22;

class WorldToScreen {
private:
	Matrix22 _M;
	sf::Vector2<float>_B;

public:
	float zoom;

	WorldToScreen() = delete;
	WorldToScreen(
		const sf::Vector2<float> DownLeftCornerWorld,
		const sf::Vector2<float> UpRightCornerWorld,
		const sf::Vector2<float> DownLeftCornerScreen,
		const sf::Vector2<float> UpRightCornerScreen);

	sf::Vector2<float> operator()(const sf::Vector2<float> worldCoordinate);
	
};

#endif
