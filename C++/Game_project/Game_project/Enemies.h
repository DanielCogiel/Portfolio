#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "HealthBar.h"

class Enemy
{
protected:
	sf::Sprite shape;
	sf::Text name;
	sf::Font font;

	std::shared_ptr<HealthBar> hpBar;

	std::string type;
	int damage;
	int health;
	int healthMax;
	int score;
	float speedX, speedY;

	sf::Clock clock;

	virtual void initAttributes() = 0;

public:
	Enemy(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	virtual ~Enemy();

	std::string getType();
	int getScore();

	void addHp(double value);

	int getHp();

	virtual void update() = 0;
	
	void render(std::shared_ptr<sf::RenderTarget> target);

	sf::FloatRect getBounds();

};

class Type1 : public Enemy
{
	void initAttributes();
public:
	Type1(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	~Type1();

	void update();
};

class Type2 : public Enemy
{
	bool goClockwise;
	void initAttributes();
public:
	Type2(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	~Type2();

	void update();
};

class Type3 : public Enemy
{
	void initAttributes();
public:
	Type3(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	~Type3();

	void update();
};

class Type4 : public Enemy
{
	bool goDown, goLeft, goRight, wentLeft, wentRight;
	void initAttributes();
public:
	Type4(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	~Type4();

	void update();
};

class Type5 : public Enemy
{
	bool goLeft, goRight;
	void initAttributes();
public:
	Type5(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	~Type5();

	void update();
};

class Type6 : public Enemy
{
	bool goLeft, goRight;
	void initAttributes();
public:
	Type6(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font);
	~Type6();

	void update();
};


#endif

