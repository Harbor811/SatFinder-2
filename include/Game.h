#ifndef GAME_H
#define GAME_H

#include "Console.h"
#include "Button.h"
#include "RoutePlanner.h"

/*
	Class that acts as the engine.
	Wrapper class.
	It's called 'Game' because that's what this was originally going to be
*/

class Game
{
private:
	struct ButtonEntry
	{
		Button* ptr = nullptr;
		bool owned = true;
		
		ButtonEntry(Button* newPtr, bool isOwned = true) : ptr(newPtr), owned(isOwned) {}
	};

	// - Variables -
	sf::Clock deltaClock;
	Console* curConsole;
	bool metaParanoia = false;

	//std::string mousePos = "";
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
	sf::Font* fontMonoBold;
	sf::Font* fontMono;
	sf::Vector2i mousePos;

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Objects
	//sf::Text* titleText;
	//Button *mapButton;
	//Button *routePlannerButton;
	//Button *logButton;

	RoutePlanner curRoute;

	std::vector<Button*> satButtons;
	std::vector<ButtonEntry> activeButtons;
	std::vector<sf::Drawable*> activeAssets;
	std::vector<sf::Texture*> activeTextures;
	std::vector<Console*> activeSpecial;
	sf::VertexArray* activeLines;
	//std::vector<sf::Vertex*> activeVertices;

	// - Private Functions -

	void initVariables();
	void initWindow();
	void initGui();
	void initSatButtons();
	
	void handleLMB();
	void handleESC();
	void handleKeyButtons(const sf::Keyboard::Key& key);
	void pollEvents();
	void pollMouseOver();
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

	void initFontBold(sf::Font* font);
	void initFontNormal(sf::Font* font);
};

#endif