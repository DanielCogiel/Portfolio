#include "Pocisk.h"


Pocisk::Pocisk(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, float direction_X, float direction_Y)
{
	this->movementSpeed = 8.f; 

	this->bullet.setTexture(*texture);
	this->bullet.setOrigin(this->bullet.getLocalBounds().width / 2, this->bullet.getLocalBounds().height / 2);
	this->bullet.setPosition(position_X, position_Y);

	this->direction.x = direction_X;
	this->direction.y = direction_Y;
}

Pocisk::~Pocisk()
{

}

const sf::FloatRect Pocisk::getBounds() const
{
	return this->bullet.getGlobalBounds();
}

void Pocisk::update()
{
	this->bullet.move(this->movementSpeed * this->direction);
}

void Pocisk::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(this->bullet);
}

sf::Sprite Pocisk::getSprite()
{
	return this->bullet;
}

