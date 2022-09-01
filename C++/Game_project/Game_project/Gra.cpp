#include "Gra.h"

void Gra::init_paths()
{
	this->pathToAudio = std::filesystem::current_path() / "Music";
	this->pathToTextures = std::filesystem::current_path() / "Textures";
	this->pathToFonts = std::filesystem::current_path() / "Fonts";
}

void Gra::init_okno()
{
	this->okno = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->window_width, this->window_height), "Space Smasher", sf::Style::Close | sf::Style::Titlebar);
	this->okno->setFramerateLimit(60);
	this->okno->setMouseCursorGrabbed(1);
	this->okno->requestFocus();
	this->okno->setMouseCursorVisible(0);

	this->Background.setTexture(*this->tekstury["Background"]);
	this->Background.setPosition(0.f, 0.f);
	this->Background.setScale(0.25f, 0.25f);

	this->EnemySpawnCooldown = 1.3f;

	this->isLoading = 0;
}

void Gra::init_tekstury()
{

	this->tekstury["Pocisk"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Pocisk"]->loadFromFile((this->pathToTextures / "Bullet.png").string()))
		std::cout << "ERROR::GRA::POCISK" << std::endl;
	this->tekstury["Statek"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Statek"]->loadFromFile((this->pathToTextures / "Ship.png").string()))
		std::cout << "ERROR::GRA::STATEK" << std::endl;
	this->tekstury["Background"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Background"]->loadFromFile((this->pathToTextures / "Background.png").string()))
		std::cout << "ERROR::GRA::BACKGROUND" << std::endl;
	this->tekstury["Asteroida"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Asteroida"]->loadFromFile((this->pathToTextures / "Asteroida.png").string()))
		std::cout << "ERROR::GRA::ASTEROIDA" << std::endl;
	this->tekstury["UFO"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["UFO"]->loadFromFile((this->pathToTextures / "Ufo.png").string()))
		std::cout << "ERROR::GRA::UFO" << std::endl;
	this->tekstury["Rakieta"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Rakieta"]->loadFromFile((this->pathToTextures / "Rocket.png").string()))
		std::cout << "ERROR::GRA::RAKIETA" << std::endl;
	this->tekstury["Kosmita"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Kosmita"]->loadFromFile((this->pathToTextures / "Alien.png").string()))
		std::cout << "ERROR::GRA::KOSMITA" << std::endl;
	this->tekstury["Meteor"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Meteor"]->loadFromFile((this->pathToTextures / "Meteor.png").string()))
		std::cout << "ERROR::GRA::METEOR" << std::endl;
	this->tekstury["Astronauta"] = std::make_shared<sf::Texture>();
	if (!this->tekstury["Astronauta"]->loadFromFile((this->pathToTextures / "Astronaut.png").string()))
		std::cout << "ERROR::GRA::ASTRONAUTA" << std::endl;
}

void Gra::init_gracz(std::shared_ptr<sf::Texture> texture)
{
	this->moj_gracz = std::make_shared<Gracz>(texture);
}

void Gra::init_music()
{
	if (!this->buffer.loadFromFile((this->pathToAudio / "bensound-happyrock.wav").string()))
		std::cout << "ERROR::GRA::AUDIO" << std::endl;
	else
	{
		sound.setBuffer(this->buffer);
		sound.setLoop(true);
	}
}

void Gra::init_fonts()
{
	if (!this->font.loadFromFile((this->pathToFonts / "arial.ttf").string()))
		std::cout << "ERROR::GRA::FONT" << std::endl;
}

void Gra::init_menu()
{
	this->menuPause = std::make_shared<Menu>(this->window_width, this->window_height, "Continue", "Main Menu", "Exit");
	this->menuMain = std::make_shared<Menu>(this->window_width, this->window_height, "Play", "Ranking", "Exit");
}

void Gra::init_ranking()
{
	this->gameRanking = std::make_shared<Ranking>("Scores.txt", this->window_width, this->window_height);
}

void Gra::init_interface()
{
	this->init_fonts();
	this->Instruction.setFont(this->font);
	this->Instruction.setFillColor(sf::Color::White);
	this->Instruction.setPosition(100.f, 100.f);
	this->Instruction.setString(L"Zestrzel jak najwiêcej przeciwników, aby zdobyæ punkty.\nJeœli zderzysz siê z przeciwnikiem b¹dŸ ten spadnie poni¿ej ekranu, \nstracisz czêœæ ¿ycia i punktów.\nNIE STRZELAJ DO ASTRONAUTÓW, POMÓ¯ IM!!!\n\nKlawiatura\n\nWASD lub strzalki - poruszanie statkiem\nLPM lub spacja - strzelanie\nEscape - pauza\n\nJoystick\n\nLewa galka - poruszanie statkiem\nA (Xbox) lub X (Playstation) - strzelanie");
	this->GameOver.setFont(this->font);
	this->GameOver.setFillColor(sf::Color::White);
	this->GameOver.setCharacterSize(40);
	this->GameOver.setString("GAME OVER");
	this->GameOver.setOrigin(this->GameOver.getLocalBounds().width / 2, this->GameOver.getLocalBounds().height / 2);
	this->GameOver.setPosition(this->window_width / 2, this->window_height / 2);
	this->ScoreWhenGameOver.setFont(this->font);
	this->ScoreWhenGameOver.setFillColor(sf::Color::White);
	this->ScoreWhenGameOver.setCharacterSize(40);
	this->ScoreString.setFont(this->font);
	this->ScoreString.setFillColor(sf::Color::Red);
	this->PlayerName.setFont(this->font);
	this->PlayerName.setFillColor(sf::Color::White);
	this->PlayerName.setString(this->nickname);
	this->PlayerName.setScale(0.5f, 0.5f);
	this->PlayerName.setOrigin(this->PlayerName.getLocalBounds().width / 2, this->PlayerName.getLocalBounds().height / 2);
}

void Gra::init_attributes()
{
	this->statePaused = false;
	this->statePlay = false;
	this->stateMainMenu = true;
	this->stateRanking = false;
	this->stateInstruction = false;
	this->stateGameOver = false;
	this->isLoading = true;

	this->window_height = 800;
	this->window_width = 1200;
}

void Gra::input_name()
{
	std::regex playerNamePattern("[A-Za-z][a-zA-Z0-9_-]{1,19}");
	do {
		std::cout << "Nazwa musi zaczynac sie od litery i moze zawierac do 20 znakow (liczby, podkreslenia i myslniki)" << std::endl;
		std::cout << "Wprowadz nazwe gracza: ";
		std::cin >> this->nickname;
		std::system("cls");
	} while (!std::regex_match(this->nickname, playerNamePattern));
}

void Gra::loading()
{
	while (this->isLoading)
	{
		std::cout << "Wczytywanie";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::system("cls");
		std::cout << "Wczytywanie.";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::system("cls");
		std::cout << "Wczytywanie..";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::system("cls");
		std::cout << "Wczytywanie...";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::system("cls");
	}
}

void Gra::doIfPlay()
{

}



Gra::Gra()
{
	this->init_attributes();
	std::thread t7(&Gra::init_paths, this);
	this->input_name();
	std::thread t4(&Gra::loading, this);
	t7.join();
	std::thread t2(&Gra::init_music, this);
	std::thread t6(&Gra::init_interface, this);
	std::thread t3(&Gra::init_menu, this);
	std::thread t1(&Gra::init_ranking, this);
	this->init_tekstury();
	this->init_okno();
	this->init_gracz(this->tekstury["Statek"]);
	t1.join();
	t4.join();
	t3.join();
	t2.join();
	t6.join();
}

Gra::~Gra()
{
	std::cout << "Thank you, www.bensound.com, for providing music for this project." << std::endl;
	std::cout << "Thank you emojipng.com, pngwing.com and OpenGameArt.org authors: Tiny Speck, Fupi, SanderGameArts, vergil1018, FunwithPixels for providing textures for this project." << std::endl;
}

void Gra::uruchom()
{
	while (this->okno->isOpen())
	{
		this->update();
		this->render();
	}
}

void Gra::event_polling()
{
	sf::Event ev;

	bool isDone = 0;

	while (this->okno->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->okno->close();

		if (this->statePlay)
		{
			if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape && this->EscapeTimer.getElapsedTime().asSeconds() > 1.f)
			{
				this->statePaused = true;
				this->statePlay = false;
				this->stateMainMenu = false;
				this->stateRanking = false;
				this->stateInstruction = false;
				this->stateGameOver = false;
				this->EscapeTimer.restart();
				this->sound.pause();
			}
		}
		else if (this->statePaused)
		{
			if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape && this->EscapeTimer.getElapsedTime().asSeconds() > 1.f)
			{
				this->statePaused = false;
				this->statePlay = true;
				this->stateMainMenu = false;
				this->stateRanking = false;
				this->stateInstruction = false;
				this->stateGameOver = false;
				this->EscapeTimer.restart();
				this->sound.play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				this->menuPause->moveUp();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				this->menuPause->moveDown();
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
			{
				if (this->menuPause->getItemSelected() == 0)
				{
					this->statePaused = false;
					this->statePlay = true;
					this->stateMainMenu = false;
					this->stateRanking = false;
					this->stateInstruction = false;
					this->stateGameOver = false;
					this->EscapeTimer.restart();
					this->sound.play();
				}
				else if (this->menuPause->getItemSelected() == 1)
				{
					this->stateMainMenu = true;
					this->statePaused = false;
					this->statePlay = false;
					this->stateRanking = false;
					this->stateInstruction = false;
					this->stateGameOver = false;
					isDone = 1;
					this->sound.stop();
					this->reset_game();
					this->EnemySpawnTimer.restart();
				}
				else if (this->menuPause->getItemSelected() == 2)
				{
					this->gameRanking->addScore(this->nickname, this->score);
					this->okno->close();
				}
			}
			this->EnemySpawnTimer.restart();
		}
		else if(this->stateMainMenu && !isDone)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				this->menuMain->moveUp();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				this->menuMain->moveDown();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				if (this->menuMain->getItemSelected() == 0)
				{
					this->statePaused = false;
					this->statePlay = false;
					this->stateMainMenu = false;
					this->stateRanking = false;
					this->stateInstruction = true;
					this->stateGameOver = false;
				}
				else if (this->menuMain->getItemSelected() == 1)
				{
					this->statePaused = false;
					this->statePlay = false;
					this->stateMainMenu = false;
					this->stateRanking = true;
					this->stateInstruction = false;
					this->stateGameOver = false;
				}
				else if (this->menuMain->getItemSelected() == 2)
				{
					this->okno->close();
				}
			}
			this->EnemySpawnTimer.restart();
		}
		else if (this->stateRanking)
		{
			if (ev.Event::type == sf::Event::KeyPressed)
			{
				this->statePaused = false;
				this->statePlay = false;
				this->stateMainMenu = true;
				this->stateRanking = false;
				this->stateInstruction = false;
				this->stateGameOver = false;
			}
		}
		else if (this->stateInstruction)
		{
			if (ev.Event::type == sf::Event::KeyPressed)
			{
				this->statePaused = false;
				this->statePlay = true;
				this->stateMainMenu = false;
				this->stateRanking = false;
				this->stateInstruction = false;
				this->stateGameOver = false;
				this->EscapeTimer.restart();
				this->sound.play();
			}
		}
		else if (this->stateGameOver)
		{
			if (ev.Event::type == sf::Event::KeyPressed && this->GameOverTimer.getElapsedTime().asSeconds() > 1.f)
			{
				this->statePaused = false;
				this->statePlay = false;
				this->stateMainMenu = true;
				this->stateRanking = false;
				this->stateInstruction = false;
				this->stateGameOver = false;
				this->EscapeTimer.restart();
				this->sound.stop();
			}
		}
	}
}

void Gra::input()
{
	//Ruch przy pomocy klawiatury
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->moj_gracz->move(0.f, -1.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->moj_gracz->move(-1.f, 0.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->moj_gracz->move(0.f, 1.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->moj_gracz->move(1.f, 0.f);

	//Ruch przy pomocy pada
	if (sf::Joystick::isConnected(0))
	{
		this->moj_gracz->move(sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100, sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100);
		
		if (sf::Joystick::isButtonPressed(0, 0) and this->moj_gracz->isAllowedToAttack())
			this->pociski.push_back(std::make_shared<Pocisk>(this->tekstury["Pocisk"], this->moj_gracz->getPosition().x, this->moj_gracz->getPosition().y - 50.f, 0.f, -1.f));
	}

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && this->moj_gracz->isAllowedToAttack())
	{
		this->pociski.push_back(std::make_shared<Pocisk>(this->tekstury["Pocisk"], this->moj_gracz->getPosition().x, this->moj_gracz->getPosition().y - 50.f, 0.f, -1.f));
	}

}

void Gra::bullets()
{
	for (size_t i = 0; i < pociski.size(); i++)
	{
		pociski[i]->update();

		if (pociski[i]->getBounds().top + pociski[i]->getBounds().height < 0.f)
		{
			this->pociski.erase(pociski.begin() + i);
			--i;
		}
		
	}

}

void Gra::update()
{
	
	this->event_polling();

	if (this->statePlay)
	{
		this->input();
		this->enemies();
		this->bullets();
		this->update_bounds();
		this->update_interface();
	}
	else if (this->statePaused)
	{
		this->menuPause->updateInput();
	}
	else if (this->stateMainMenu)
	{
		this->menuMain->updateInput();
	}
}

void Gra::update_bounds()
{
	//X axis
	if (this->moj_gracz->getBounds().left < 0.f)
		this->moj_gracz->setPosition(this->moj_gracz->getBounds().width / 2, this->moj_gracz->getBounds().top + this->moj_gracz->getBounds().height / 2);
	else if (this->moj_gracz->getBounds().left + this->moj_gracz->getBounds().width > this->okno->getSize().x)
		this->moj_gracz->setPosition(this->okno->getSize().x - this->moj_gracz->getBounds().width / 2, this->moj_gracz->getBounds().top + this->moj_gracz->getBounds().height / 2);

	//Y axis
	if (this->moj_gracz->getBounds().top < 0.f)
		this->moj_gracz->setPosition(this->moj_gracz->getBounds().left + this->moj_gracz->getBounds().width / 2, 0.f + this->moj_gracz->getBounds().height / 2);
	else if (this->moj_gracz->getBounds().top + this->moj_gracz->getBounds().height > this->okno->getSize().y)
		this->moj_gracz->setPosition(this->moj_gracz->getBounds().left + this->moj_gracz->getBounds().width / 2, this->okno->getSize().y - this->moj_gracz->getBounds().height / 2);
}

void Gra::update_interface()
{
	this->ScoreString.setString("SCORE\n" + std::to_string(this->score));
	this->PlayerName.setPosition(this->moj_gracz->getBounds().left + this->moj_gracz->getBounds().width / 2, this->moj_gracz->getBounds().top + this->moj_gracz->getBounds().height);
}

void Gra::render_gracz()
{
	this->moj_gracz->render(*this->okno);
}

void Gra::render_pociski()
{
	std::ranges::for_each(this->pociski, [this](std::shared_ptr<Pocisk> pocisk) {pocisk->render(this->okno); });
}

void Gra::render_przeciwnicy()
{
	std::ranges::for_each(this->przeciwnicy, [this](std::shared_ptr<Enemy> przeciwnik) {przeciwnik->render(this->okno); });
}

void Gra::render_pause_menu()
{
	this->menuPause->render(this->okno);
}

void Gra::render_main_menu()
{
	this->menuMain->render(this->okno);
}

void Gra::render_ranking()
{
	this->gameRanking->render(this->okno);
}

void Gra::render_instruction()
{
	this->okno->draw(this->Instruction);
}

void Gra::render_background()
{
	this->okno->draw(this->Background);
}

void Gra::render_interface()
{
	this->okno->draw(this->ScoreString);
	this->okno->draw(this->PlayerName);
}

void Gra::render_game_over()
{
	this->okno->draw(this->GameOver);
	this->okno->draw(this->ScoreWhenGameOver);
}

void Gra::reset_game()
{
	int przeciwnicySize = this->przeciwnicy.size();
	int pociskiSize = this->pociski.size();
	this->gameRanking->addScore(this->nickname, this->score);
	this->score = 0;
	this->moj_gracz->setHp(100);
	for (int i = 0; i < przeciwnicySize; i++)
	{
		this->przeciwnicy.pop_back();
	}
	for (int j = 0; j < pociskiSize; j++) 
	{
		this->pociski.pop_back(); 
	}
	this->moj_gracz->setPosition(600, 500);
}

void Gra::render()
{
	this->okno->clear();

	if (this->statePlay)
	{
		this->render_background();
		this->render_gracz();
		this->render_pociski();
		this->render_przeciwnicy();
		this->render_interface();
	}
	else if (this->statePaused)
		this->render_pause_menu();
	else if (this->stateMainMenu)
		this->render_main_menu();
	else if (this->stateRanking)
		this->render_ranking();
	else if (this->stateInstruction)
		this->render_instruction();
	else if (this->stateGameOver)
		this->render_game_over();

	this->okno->display();

}

void Gra::enemies()
{
	if (this->EnemySpawnTimer.getElapsedTime().asSeconds() > this->EnemySpawnCooldown)
	{
		int my_switch = rand() % 6;

		switch (my_switch)
		{
		case 0:
			this->przeciwnicy.push_back(std::make_shared<Type1>(this->tekstury["Asteroida"], rand() % (this->okno->getSize().x - 150) + 50, -50.f, this->font));
			break;
		case 1:
			this->przeciwnicy.push_back(std::make_shared<Type2>(this->tekstury["UFO"], rand() % (this->okno->getSize().x - 150) + 50, -50.f, this->font));
			break;
		case 2:
			this->przeciwnicy.push_back(std::make_shared<Type3>(this->tekstury["Rakieta"], rand() % (this->okno->getSize().x - 150) + 50, -50.f, this->font));
			break;
		case 3:
			this->przeciwnicy.push_back(std::make_shared<Type4>(this->tekstury["Kosmita"], rand() % (this->okno->getSize().x - 150) + 50, -50.f, this->font));
			break;
		case 4:
			this->przeciwnicy.push_back(std::make_shared<Type5>(this->tekstury["Meteor"], rand() % (this->okno->getSize().x - 150) + 50, -50.f, this->font));
			break;
		case 5:
			this->przeciwnicy.push_back(std::make_shared<Type6>(this->tekstury["Astronauta"], rand() % (this->okno->getSize().x - 150) + 50, -50.f, this->font));
			break;
		}

		this->EnemySpawnTimer.restart();

	}

	for (size_t i = 0; i < this->przeciwnicy.size(); i++)
	{
	przeciwnicy[i]->update();

	bool isKilled = false;

		for (size_t j = 0; j < this->pociski.size() && !isKilled; j++)
		{
			if (this->pociski[j]->getBounds().intersects(this->przeciwnicy[i]->getBounds()))
			{
				this->pociski.erase(pociski.begin() + j);
				this->przeciwnicy[i]->addHp(-1);
				if (przeciwnicy[i]->getHp() <= 0)
				{
					if (this->przeciwnicy[i]->getType() == "Astronauta")
						this->score -= this->przeciwnicy[i]->getScore();
					else
						this->score += this->przeciwnicy[i]->getScore();

					this->przeciwnicy.erase(przeciwnicy.begin() + i);
					isKilled = true;
					i--;
				}
			}
		}
		if (!isKilled)
		{
			if (przeciwnicy[i]->getBounds().top > this->okno->getSize().y)
			{
				this->przeciwnicy.erase(przeciwnicy.begin() + i);
				this->score -= 2;
				this->moj_gracz->addHp(-5);
				if (this->moj_gracz->getHp() <= 0)
				{
					this->statePaused = false;
					this->statePlay = false;
					this->stateMainMenu = false;
					this->stateRanking = false;
					this->stateInstruction = false;
					this->stateGameOver = true;
					this->ScoreWhenGameOver.setString("Score: " + std::to_string(this->score));
					this->ScoreWhenGameOver.setOrigin(this->ScoreWhenGameOver.getLocalBounds().width / 2, this->ScoreWhenGameOver.getLocalBounds().height / 2);
					this->ScoreWhenGameOver.setPosition(600.f, 500.f);
					this->reset_game();
					this->sound.stop();
					this->GameOverTimer.restart();
					break;
				}
				i--;
			}
			else if (this->przeciwnicy[i]->getBounds().intersects(this->moj_gracz->getBounds()))
			{
				if (this->przeciwnicy[i]->getType() == "Astronauta")
					this->moj_gracz->addHp(5);
				else
					this->moj_gracz->addHp(-10);

				this->przeciwnicy.erase(przeciwnicy.begin() + i);
				if (this->moj_gracz->getHp() <= 0)
				{
					this->statePaused = false;
					this->statePlay = false;
					this->stateMainMenu = false;
					this->stateRanking = false;
					this->stateInstruction = false;
					this->stateGameOver = true;
					this->ScoreWhenGameOver.setString("Score: " + std::to_string(this->score));
					this->ScoreWhenGameOver.setOrigin(this->ScoreWhenGameOver.getLocalBounds().width / 2, this->ScoreWhenGameOver.getLocalBounds().height / 2);
					this->ScoreWhenGameOver.setPosition(600.f, 500.f);
					this->reset_game();
					this->sound.stop();
					this->GameOverTimer.restart();
					break;
				}
				i--;
			}
		}
	}
}



