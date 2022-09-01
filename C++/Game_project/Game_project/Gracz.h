#ifndef GRACZ_H
#define GRACZ_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "HealthBar.h"

class Gracz
{
    //obiekt z tekstur� do wyrenderowania
	sf::Sprite ship;

	std::shared_ptr<HealthBar> hpBar;
	double hp, hpMax;
	
	//szybko�� statku
	float movementSpeed;

	sf::Clock ShootingCooldown;

	float MaxShootingCooldown;

	void initAttributes();
	
	//ustawia i skaluje tekstur� statku
	void initShip(std::shared_ptr<sf::Texture> texture);
	

public:
	//ustawia szybko�� i dodaje tekstur� do statku 
	Gracz(std::shared_ptr<sf::Texture> texture);
	~Gracz(); 

	bool isAllowedToAttack(); 

	//renderuje gracza do okna
	void render(sf::RenderTarget& target); 

	void addHp(double value);
	double getHp();
	void setHp(double new_hp);

	//pozwala zmienia� pozycj� gracza
	void move(const float direction_X, const float direction_Y);

	void setPosition(sf::Vector2f vec);
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	sf::FloatRect getLocalBounds();

	void setPosition(float X, float Y);
};

#endif