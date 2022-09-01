#ifndef GRA_H
#define GRA_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <vector>
#include <thread>
#include <ranges>
#include <filesystem>
#include <regex>
#include <string>
#include "Gracz.h"
#include "Pocisk.h"
#include "Enemies.h"
#include "PauseMenu.h"
#include "Ranking.h"
#include "HealthBar.h"

class Gra
{
	//Obiekty
	std::shared_ptr<sf::RenderWindow> okno;
	std::shared_ptr<Menu> menuPause;
	std::shared_ptr<Menu> menuMain;
	std::shared_ptr<Ranking> gameRanking;
	sf::Sprite Background;
	std::shared_ptr<Gracz> moj_gracz;

	//Paths
	std::filesystem::path pathToTextures;
	std::filesystem::path pathToAudio;
	std::filesystem::path pathToFonts;

	//Containers
	std::map<std::string, std::shared_ptr<sf::Texture>> tekstury;
	std::vector<std::shared_ptr<Pocisk>> pociski;
	std::vector<std::shared_ptr<Enemy>> przeciwnicy;
	
	//Clocks
	sf::Clock EnemySpawnTimer;
	sf::Clock EscapeTimer;
	sf::Clock GameOverTimer;

	//Fonts
	sf::Font font;

	//Texts
	sf::Text Instruction;
	sf::Text ScoreString;
	sf::Text GameOver;
	sf::Text ScoreWhenGameOver;
	sf::Text PlayerName;

	//Audio
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//States
	bool statePlay;
	bool statePaused;
	bool stateMainMenu;
	bool stateRanking;
	bool stateInstruction;
	bool stateGameOver;
	bool isLoading;

	//Attributes
	int window_height;
	int window_width;
	int score;
	float EnemySpawnCooldown;
	std::string nickname;

	//Private functions
	void init_paths();
	void init_okno();
	void init_tekstury();
	void init_gracz(std::shared_ptr<sf::Texture> texture);
	void init_music();
	void init_fonts();
	void init_menu();
	void init_ranking();
	void init_interface();
	void init_attributes();
	void input_name();
	void loading();
	void doIfPlay();
public:
	//Public functions
	Gra();
	~Gra();
	void uruchom();
	void event_polling();
	void input();
	void bullets();
	void update();
	void update_bounds();
	void update_interface();
	void render_gracz();
	void render_pociski();
	void render_przeciwnicy();
	void render_pause_menu();
	void render_main_menu();
	void render_ranking();
	void render_instruction();
	void render_background();
	void render_interface();
	void render_game_over();
	void reset_game();
	void render();
	void enemies();
};

#endif