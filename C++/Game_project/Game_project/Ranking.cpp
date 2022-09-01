#include "Ranking.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ranges>


Ranking::Ranking(std::string sciezka_pliku, float width, float height)
{

	if (!this->font.loadFromFile((std::filesystem::current_path() / "Fonts" / "arial.ttf").string()))
		std::cout << "ERROR::RANKING::FONT" << std::endl;

	std::ifstream input(sciezka_pliku);
	if (input.good())
	{
		std::string linia;
		std::stringstream ss;
		std::string imie;
		int wynik;
		while (std::getline(input, linia))
		{
			ss << linia;
			ss >> imie >> wynik;
			this->ranking.push_back(std::pair<std::string, int>(imie, wynik));
			ss.clear();
		}
		input.close();
	}
	std::ranges::sort(this->ranking, [](std::pair<std::string, int> el1, std::pair<std::string, int> el2) {return el1.second > el2.second; });
	
	
	for (int i = 0; i < 5; i++)
	{
		if (i < this->ranking.size())
		{
			this->first_column.push_back(sf::Text(this->ranking[i].first, this->font));
			this->second_column.push_back(sf::Text(std::to_string(this->ranking[i].second), this->font));
		}
		else
		{
			this->first_column.push_back(sf::Text("", this->font));
			this->second_column.push_back(sf::Text("", this->font));
		}
		this->first_column[i].setFillColor(sf::Color::White);
		this->second_column[i].setFillColor(sf::Color::White);

		sf::FloatRect textRect = this->first_column[i].getLocalBounds();
		this->first_column[i].setPosition(width * 1 / 3, height * (i + 1) / 6);
		this->second_column[i].setPosition(width * 2 / 3, height * (i + 1) / 6);
	}
	
}

void Ranking::render(std::shared_ptr<sf::RenderTarget> target)
{
	for (int i = 0; i < this->first_column.size(); i++)
	{
		target->draw(this->first_column[i]);
		target->draw(this->second_column[i]);
	}
}

std::vector<std::pair<std::string, int>> Ranking::getVector()
{
	return this->ranking;
}

void Ranking::addScore(std::string playerName, int playerScore)
{
	if (playerScore > 0)
	{
		this->ranking.push_back(std::pair<std::string, int>(playerName, playerScore));
		std::ranges::sort(this->ranking, [](std::pair<std::string, int> el1, std::pair<std::string, int> el2) {return el1.second > el2.second; });
		for (int i = 0; i < this->ranking.size() && i < 5; i++)
		{
			this->first_column[i].setString(this->ranking[i].first);
			this->second_column[i].setString(std::to_string(this->ranking[i].second));
		}
		this->writeToFile((std::filesystem::current_path() / "Scores.txt"));
	}
}

void Ranking::writeToFile(std::filesystem::path pathToScoresFile)
{
	std::ofstream output(pathToScoresFile);
	if (output.good())
	{
		for (int i = 0; i < this->ranking.size(); i++)
		{
			output << this->ranking[i].first << " " << this->ranking[i].second << std::endl;
		}
		
		output.close();
	}
}


