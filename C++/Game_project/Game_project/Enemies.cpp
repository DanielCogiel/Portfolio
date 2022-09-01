#include "Enemies.h"

int Enemy::getScore()
{
	return this->score;
}

void Enemy::addHp(double value)
{
	
	double new_hp = this->health + value;

	if (new_hp < this->healthMax || new_hp > 0)
	{
		this->health = new_hp;
		this->hpBar->setHp(new_hp / this->healthMax * 100);
	}
	
}

int Enemy::getHp()
{
	return this->health;
}

Enemy::Enemy(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(position_X, position_Y);
	this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);
	this->font = font;
	this->name.setFont(this->font);
	this->name.setFillColor(sf::Color::White);
	this->name.setCharacterSize(16);

	this->hpBar = std::make_shared<HealthBar>(this->shape.getPosition().x, this->shape.getPosition().y + 70);
}


Enemy::~Enemy()
{
}

std::string Enemy::getType()
{
	return this->type;
}



void Enemy::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(this->shape);
	target->draw(this->name);
	this->hpBar->render(*target);
}

sf::FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds();
}

void Type1::initAttributes()
{
	this->type = "Asteroida";
	this->damage = 1;
	this->health = 2;
	this->healthMax = this->health;
	this->score = 7;
	this->speedX = 0.f;
	this->speedY = 2.f;
}

Type1::Type1(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font) : Enemy(texture, position_X, position_Y, font)
{
	this->initAttributes();
	
	this->name.setString(this->type);
	this->name.setOrigin(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2);
	this->name.setPosition(position_X, position_Y + 50.f);
	this->shape.setScale(0.7f, 0.7f);

}

Type1::~Type1()
{
}

void Type1::update()
{
	this->shape.move(speedX, speedY);
	this->name.move(speedX, speedY);
	this->hpBar->move(speedX, speedY);
	
    this->shape.rotate(1.f);
}

void Type2::initAttributes()
{
	this->type = "UFO";
	this->damage = 25;
	this->health = 1;
	this->healthMax = this->health;
	this->score = 5;
	this->speedX = 0;
	this->speedY = 6;
	this->goClockwise = false;
}

Type2::Type2(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font) : Enemy(texture, position_X, position_Y, font)
{
	this->initAttributes();

	this->name.setString(this->type);
	this->name.setOrigin(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2);
	this->name.setPosition(position_X, position_Y + 50.f);
	this->shape.setScale(0.08f, 0.08f);
	this->shape.rotate(50.f);
}

Type2::~Type2()
{
}

void Type2::update()
{
	this->shape.move(speedX, speedY);
	this->name.move(speedX, speedY);
	this->hpBar->move(speedX, speedY);
	float rotation = 50.f;
	 
	if (this->clock.getElapsedTime().asSeconds() > 0.5f)
	{
		if (!this->goClockwise)
		{
			this->shape.rotate(-rotation);
			this->clock.restart();
			this->goClockwise = true;
		}
		else
		{
			this->shape.rotate(rotation);
			this->clock.restart();
			this->goClockwise = false;
		}
	}

}

void Type3::initAttributes()
{
	this->type = "Rakieta";
	this->damage = 10;
	this->health = 1;
	this->healthMax = this->health;
	this->score = 3;
	this->speedX = 0;
	this->speedY = 10;
}

Type3::Type3(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font) : Enemy(texture, position_X, position_Y, font)
{
	this->initAttributes();

	this->name.setString(this->type);
	this->name.setOrigin(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2);
	this->name.setPosition(position_X, position_Y + 50.f);
	this->shape.setScale(0.015f, 0.015f);
	this->shape.rotate(180);
	///this->shape
}

Type3::~Type3()
{
	//Enemy::~Enemy();
}

void Type3::update()
{
	this->shape.move(speedX, speedY);
	this->name.move(speedX, speedY);
	this->hpBar->move(speedX, speedY);
}

void Type4::initAttributes()
{
	this->type = "Kosmita";
	this->damage = 4;
	this->health = 3;
	this->healthMax = this->health;
	this->score = 10;
	this->speedX = 0;
	this->speedY = 2;

	this->goDown = true;
	this->goLeft = false;
	this->goRight = false;
	this->wentLeft = true;
	this->wentRight = false;

}

Type4::Type4(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font) : Enemy(texture, position_X, position_Y, font)
{
	this->initAttributes();

	this->name.setString(this->type);
	this->name.setOrigin(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2);
	this->name.setPosition(position_X, position_Y + 50.f);
	this->shape.setScale(0.5f, 0.5f);
}

Type4::~Type4()
{
	//Enemy::~Enemy();
}

void Type4::update()
{
	if (this->goDown)
	{
		this->speedX = 0;
		this->speedY = 2;
	}
	else if (this->goLeft)
	{
		this->speedX = -2;
		this->speedY = 0;
	}
	else if (this->goRight)
	{
		this->speedX = 2;
		this->speedY = 0;
	}
	if (this->clock.getElapsedTime().asSeconds() > 1.f)
	{
		if (this->goLeft)
		{
			this->goLeft = false;
			this->wentLeft = true;
			this->goDown = true;
			this->goRight = false;
			this->wentRight = false;
		}
		else if (this->goRight)
		{
			this->goLeft = false;
			this->wentLeft = false;
			this->goDown = true;
			this->goRight = false;
			this->wentRight = true;
		}
		else if (this->goDown)
		{
			if (this->wentLeft)
			{
				this->goLeft = false;
				this->wentLeft = false;
				this->goDown = false;
				this->goRight = true;
				this->wentRight = false;
			}
			else if (this->wentRight)
			{
				this->goLeft = true;
				this->wentLeft = false;
				this->goDown = false;
				this->goRight = false;
				this->wentRight = false;
			}
		}
		this->clock.restart();
	}

	this->shape.move(speedX, speedY);
	this->name.move(speedX, speedY);
	this->hpBar->move(speedX, speedY);
}

void Type5::initAttributes()
{
	this->type = "Meteor";
	this->damage = 1;
	this->health = 3;
	this->healthMax = this->health;
	this->score = 10;
	this->speedX = 0;
	this->speedY = 3;
	this->goLeft = true;
	this->goRight = false;
}

Type5::Type5(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font) : Enemy(texture, position_X, position_Y, font)
{
	this->initAttributes();
	
	this->name.setString(this->type);
	this->name.setOrigin(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2);
	this->name.setPosition(position_X - 10.f, position_Y + 100.f);
	this->hpBar->setPosition(position_X - 10.f, position_Y + 120.f);
	this->shape.setScale(0.5f, 0.5f);
	
}

Type5::~Type5()
{
	//Enemy::~Enemy();
}

void Type5::update()
{
	if (this->goLeft)
		this->speedX = -4;
	else if (this->goRight)
		this->speedX = 4;

	if (this->clock.getElapsedTime().asSeconds() > 0.05f)
	{
		if (this->goLeft)
		{
			this->goLeft = false;
			this->goRight = true;
		}
		else if (this->goRight)
		{
			this->goLeft = true;
			this->goRight = false;
		}
		this->clock.restart();
	}
	

	this->shape.move(speedX, speedY);
	this->name.move(0.f, speedY);
	this->hpBar->move(0.f, speedY);
}

void Type6::initAttributes()
{
	this->type = "Astronauta";
	this->damage = 15;
	this->health = 1;
	this->healthMax = this->health;
	this->score = 10;
	this->speedX = 0;
	this->speedY = 5;
	this->goLeft = false;
	this->goRight = true;
}

Type6::Type6(std::shared_ptr<sf::Texture> texture, float position_X, float position_Y, sf::Font& font) : Enemy(texture, position_X, position_Y, font)
{
	this->initAttributes();

	this->name.setString(this->type);
	this->name.setOrigin(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2);
	this->name.setPosition(position_X, position_Y + 50.f);
	this->shape.setScale(0.2f, 0.2f);
}

Type6::~Type6()
{
	//Enemy::~Enemy();
}

void Type6::update()
{
	if (this->goRight)
		this->speedX = 2;
	else if (this->goLeft)
		this->speedX = -2;

	if (this->clock.getElapsedTime().asSeconds() > 0.5f)
	{
		if (this->goRight)
		{
			this->goRight = false;
			this->goLeft = true;
		}
		else if (this->goLeft)
		{
			this->goRight = true;
			this->goLeft = false;
		}
		this->clock.restart();
	}

	this->shape.rotate(1);
	this->shape.move(speedX, speedY);
	this->name.move(speedX, speedY);
	this->hpBar->move(speedX, speedY);
}
