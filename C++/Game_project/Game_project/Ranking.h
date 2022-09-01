#ifndef RANKING_H
#define RANKING_H

#include <SFML/Graphics.hpp>
#include <filesystem>

class Ranking
{
	sf::Font font;
	float width, height;
	std::vector<std::pair<std::string, int>> ranking;
	std::vector<sf::Text> first_column;
	std::vector<sf::Text> second_column;
public:

	Ranking(std::string sciezka_pliku, float width, float height); //To do
	void render(std::shared_ptr<sf::RenderTarget> target);
	std::vector<std::pair<std::string, int>> getVector();
	void addScore(std::string playerName, int playerScore);
	void writeToFile(std::filesystem::path pathToScoresFile);
};

#endif