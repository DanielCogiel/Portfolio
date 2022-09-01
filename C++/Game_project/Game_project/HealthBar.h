#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar
{
	sf::Vector2f initialSize;
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBackground;
public:
	HealthBar(float X, float Y);
	void move(float X, float Y);
	void render(sf::RenderTarget& target);
	void setHp(int percent);
	void setPosition(float X, float Y);
	sf::Vector2f getInitialSize();
};

#endif