#ifndef POCISK_H
#define POCISK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>


class Pocisk
{
	//obiekt pocisku z tekstur¹
	sf::Sprite bullet;

	//kierunek poruszania pocisku
	sf::Vector2f direction;
	
	//szybkoœæ pocisku
	float movementSpeed;

public:
	//ustawia prêdkoœæ, pozycjê, teksturê i kierunek poruszania siê pocisku
	Pocisk(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, float direction_X, float direction_Y);
	~Pocisk(); //puste

	const sf::FloatRect getBounds() const;

	//porusza pocisk w odpowiednim kierunku
	void update();

	//renderuje pocisk do okna
	void render(std::shared_ptr<sf::RenderTarget> target);

	sf::Sprite getSprite();
};

#endif 