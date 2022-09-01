#include "PauseMenu.h"

Menu::Menu(float width, float height, std::string first, std::string second, std::string third)
{
	
	this->itemWidth = 300.f;
	this->itemHeight = 100.f;
	this->itemSize = sf::Vector2f(this->itemWidth, this->itemHeight);
	this->itemSelected = 1;
	
	if (!this->font.loadFromFile((std::filesystem::current_path() / "Fonts" / "arial.ttf").string()))
		std::cout << "ERROR::PAUSEMENU::FONT" << std::endl;
	this->itemSelected = 0;

	this->menu_squares.push_back(sf::RectangleShape());
	this->menu_squares.push_back(sf::RectangleShape());
	this->menu_squares.push_back(sf::RectangleShape());
	this->menu_strings.push_back(sf::Text("", this->font));
	this->menu_strings.push_back(sf::Text("", this->font));
	this->menu_strings.push_back(sf::Text("", this->font));
	this->menu_strings[0].setFillColor(sf::Color::White);
	this->menu_strings[1].setFillColor(sf::Color::White);
	this->menu_strings[2].setFillColor(sf::Color::White);

	this->menu_squares[0].setSize(this->itemSize);
	this->menu_squares[0].setOrigin(this->itemWidth / 2, this->itemHeight / 2);
	this->menu_squares[0].setPosition(width / 2, height * 1 / 4);
	this->menu_squares[0].setFillColor(sf::Color::Green);

	this->menu_squares[1].setSize(this->itemSize);
	this->menu_squares[1].setOrigin(this->itemWidth / 2, this->itemHeight / 2);
	this->menu_squares[1].setPosition(width / 2, height * 2 / 4);
	this->menu_squares[1].setFillColor(sf::Color::Green);

	this->menu_squares[2].setSize(this->itemSize);
	this->menu_squares[2].setOrigin(this->itemWidth / 2, this->itemHeight / 2);
	this->menu_squares[2].setPosition(width / 2, height * 3 / 4);
	this->menu_squares[2].setFillColor(sf::Color::Green);

	this->menu_strings[0].setString(first);
	this->menu_strings[1].setString(second);
	this->menu_strings[2].setString(third);

	sf::FloatRect textRect = this->menu_strings[0].getLocalBounds();
	this->menu_strings[0].setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	this->menu_strings[0].setPosition(width / 2, height * 1 / 4);

	textRect = this->menu_strings[1].getLocalBounds();
	this->menu_strings[1].setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	this->menu_strings[1].setPosition(width / 2, height * 2 / 4);

	textRect = this->menu_strings[2].getLocalBounds();
	this->menu_strings[2].setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	this->menu_strings[2].setPosition(width / 2, height * 3 / 4);
}

Menu::~Menu()
{

}

void Menu::update()
{
}

void Menu::render(std::shared_ptr<sf::RenderTarget> target)
{
	for (size_t i = 0; i < this->menu_squares.size(); i++)
	{
		target->draw(this->menu_squares[i]);
	    target->draw(this->menu_strings[i]);
	}
}

void Menu::moveDown()
{
	++itemSelected;
	if (this->itemSelected > this->menu_squares.size() - 1)
		this->itemSelected = 0;
}

void Menu::moveUp()
{
	--itemSelected;
	if (this->itemSelected < 0)
		this->itemSelected = this->menu_squares.size() - 1;
}

void Menu::updateInput()
{

	for (int i = 0; i < this->menu_squares.size(); i++)
	{
		if (i == this->itemSelected)
		{
			this->menu_squares[i].setFillColor(sf::Color::Red);
		}
		else
			this->menu_squares[i].setFillColor(sf::Color::Green);
	}
}

int Menu::getItemSelected()
{
	return this->itemSelected;
}

