#ifndef PAUSEMENU_H
#define PAUSEMENU_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>
#include <iostream>


class Menu
{
protected:
	int itemSelected;
	float itemWidth;
	float itemHeight;
	sf::Font font;
	sf::Vector2f itemSize;

	std::vector<sf::RectangleShape> menu_squares;
	std::vector<sf::Text> menu_strings;
public:
	Menu(float width, float height, std::string first, std::string second, std::string third);
	~Menu();
	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);
	void moveDown();
	void moveUp();
	void updateInput();
	int getItemSelected();

};

#endif 