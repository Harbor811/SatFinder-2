#ifndef GAME_H
#define GAME_H

#include "DrawingManager.h"
#include "RoutePlanner.h"
#include "Console.h"

/*
	Class that acts as the engine.
	Wrapper class.
	It's called 'Game' because that's what this was originally going to be
*/

class Game
{
private:
	// - Variables -
	DrawingManager* drawing = nullptr;
	sf::Clock deltaClock;
	Console* curConsole;
	bool metaParanoia = false;
	RoutePlanner curRoute;
	sf::Vector2i mousePos;
	std::vector<Button*> satButtons;
	std::vector<Console*> activeSpecial;

	// Window
	enum windowState
	{
		MAIN,
		SETTINGS,
		INFO,
		MAP,
		ROUTE_PLANNER,
		ROUTE_PLANNING,
		ROUTE_PLANNED,
		LOG
	};
	windowState curWindowState = MAIN;	
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// - Private Functions -

	void initVariables();
	void initWindow();
	void initGui();
	void initSatButtons();
	
	void handleESC();
	void handleKeyButtons(const sf::Keyboard::Key& key);
	void pollEvents();
	void pollSpecial();

	void switchGui(windowState newState);

public:
	// Constructors and Destructors
	Game();
	virtual ~Game();

	// Functions
	void update();
	void render();

	// Getters and Setters
	const bool isRunning() const;
};

#endif