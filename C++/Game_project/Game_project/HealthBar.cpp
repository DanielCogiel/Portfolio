#include "HealthBar.h"


HealthBar::HealthBar(float X, float Y)
{
	this->initialSize = sf::Vector2f(90.f, 8.f);
	this->hpBar.setSize(sf::Vector2f(90.f, 8.f));
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setOrigin(this->hpBar.getGlobalBounds().width / 2, this->hpBar.getGlobalBounds().height / 2);
	this->hpBar.setPosition(X, Y);
	this->hpBarBackground = this->hpBar;
	this->hpBarBackground.setFillColor(sf::Color(25, 25, 25, 200));
}

void HealthBar::move(float X, float Y)
{
	this->hpBarBackground.move(X, Y);
	this->hpBar.move(X, Y);
}

void HealthBar::render(sf::RenderTarget& target)
{
	target.draw(this->hpBarBackground);
	target.draw(this->hpBar);
}

void HealthBar::setHp(int percent)
{
	this->hpBar.setSize(sf::Vector2f(this->initialSize.x * ((double)percent / 100), this->hpBar.getSize().y));
}

void HealthBar::setPosition(float X, float Y)
{
	this->hpBarBackground.setPosition(X, Y);
	this->hpBar.setPosition(X, Y);
}

sf::Vector2f HealthBar::getInitialSize()
{
	return this->initialSize;
}


