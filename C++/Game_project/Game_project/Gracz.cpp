#include "Gracz.h"


void Gracz::initAttributes()
{
	this->movementSpeed = 9.f;
	this->MaxShootingCooldown = 0.5f;
	this->hp = 100;
	this->hpMax = 100;
}

void Gracz::initShip(std::shared_ptr<sf::Texture> texture)
{
	this->ship.setTexture(*texture);

	this->ship.scale(0.1f, 0.1f);
	this->ship.setOrigin(this->ship.getLocalBounds().width / 2, this->ship.getLocalBounds().height / 2);
	this->ship.setPosition(600.f, 500.f);

	this->hpBar = std::make_shared <HealthBar>(this->ship.getPosition().x, this->ship.getPosition().y + 70);
}

Gracz::Gracz(std::shared_ptr<sf::Texture> texture)
{
	this->initAttributes();
	this->initShip(texture);
}

Gracz::~Gracz()
{
}

bool Gracz::isAllowedToAttack()
{
	if (this->ShootingCooldown.getElapsedTime().asSeconds() > this->MaxShootingCooldown)
	{
		this->ShootingCooldown.restart();
		return true;
	}
	else
		return false;
}

void Gracz::render(sf::RenderTarget& target)
{
	target.draw(this->ship);
	hpBar->render(target);
}

void Gracz::addHp(double value)
{
	int new_hp = this->hp + value;

	if (new_hp <= this->hpMax && new_hp > 0)
	{
		this->hp = new_hp;
		this->hpBar->setHp((new_hp/this->hpMax) * 100);
	}
	else if (new_hp <= 0)
	{
		this->hp = 0;
		this->hpBar->setHp(0);
	}
	else
	{
		this->hp = this->hpMax;
		this->hpBar->setHp(100);
	}
}

double Gracz::getHp()
{
	return this->hp;
}

void Gracz::setHp(double new_hp)
{
	this->hp = new_hp;
	this->hpBar->setHp(new_hp / this->hpMax * 100);
}

void Gracz::move(const float direction_X, const float direction_Y)
{
	this->ship.move(movementSpeed * direction_X, movementSpeed * direction_Y);
	this->hpBar->move(movementSpeed * direction_X, movementSpeed * direction_Y);
}

void Gracz::setPosition(const sf::Vector2f vec)
{
	this->ship.setPosition(vec);
}

sf::Vector2f Gracz::getPosition()
{
	return this->ship.getPosition();
}

sf::FloatRect Gracz::getBounds()
{
	return this->ship.getGlobalBounds();
}

sf::FloatRect Gracz::getLocalBounds()
{
	return this->ship.getLocalBounds();
}

void Gracz::setPosition(float X, float Y)
{
	this->ship.setPosition(X, Y);
	this->hpBar->setPosition(this->ship.getPosition().x, this->ship.getPosition().y + 70);
}

