#include "Game.h"

// Private Functions
void Game::initVariables()
{
	window = nullptr;
}

void Game::initWindow()
{
	videoMode.height = 720;
	videoMode.width = 1280;

	window = new sf::RenderWindow(videoMode, "SatFinder v2.0", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

    // Set icon
    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    window->setIcon(200, 200, icon.getPixelsPtr());
}

void Game::initSatButtons()
{
    auto addToggleButton = [&](sf::Vector2f pos, const std::string& id)
        {
            std::string basePath = "assets/sprites/map/Button_";
            Button* btn = new Button(pos, basePath + id + "0.png", [id, this] 
                {
                    if (RoutePlanner::stringToLocation.find(id) == RoutePlanner::stringToLocation.end())
                    {
                        throw std::runtime_error("ERROR: ID \"" + id + "\" NOT FOUND IN STRING_TO_LOC");
                    }

                    RoutePlanner::location locId = RoutePlanner::stringToLocation.at(id);

                    if (curRoute.contains(locId)) 
                    { 
                        curRoute.remove(locId); 
                    }
                    else
                    {
                        curRoute.add(locId);
                    }
                });

            btn->setIsToggle(basePath + id + "1.png");

            for (auto& loc : curRoute.getToVisit())
            {
                if (RoutePlanner::stringToLocation.at(id) == loc)
                {
                    btn->switchToggleState();
                }
            }

            activeButtons.emplace_back(btn);
        };

	activeButtons.emplace_back(new Button(sf::Vector2f(335, 339), "assets/sprites/map/Button_A1.png", [this] 
        { 
            if (curRoute.getToVisit() == std::vector<RoutePlanner::location>{
                RoutePlanner::N, RoutePlanner::U, RoutePlanner::Y, RoutePlanner::O, RoutePlanner::W
            }) {
                switchGui(ROUTE_PLANNING);
                SoundManager* soundManager = SoundManager::get();
                activeAssets.erase(activeAssets.begin());
                soundManager->playInChannel(SoundManager::sfx::DEATH, 0);
                curConsole->setText(
                    ":::::--==-------======----========++==+=======++++++=====--:\n::---=-==--====+++++++++++++++++**#******++++++++=++====-:::\n:::::::------=+++++==-------==++++=+**++*+******+======-::::\n:::::----==+++==-==*++*+++===========-=---===+++===--==---::\n:::::--======-----------=+===+=++==-----------====+====:::::\n::::--------:::::::::---=---------=----::::::--------=--::::\n:::-+*+=-:::::::::::::-------==------:::::::::::::--=++:::::\n---++-::::::::::::::::::::::--------=-:::::::::::::--=*+=--:\n---==:::::::::-:-*::-:-----=+==-----::::::::::::::::::-*--::\n::-=::::::::::::::::::::-===++++====---::::::::::::::::-::::\n:--==::::::::::::::::---++=-::-===--:::::::::::::::::::--:::\n:----:::::::::::::::---+=-::::::-----::::::::::::::::-=+*--=\n::----:::::::::::::---==-:::-:::-+===+=-::::::::::---=--=:::\n:--===-::::::::-====-==-:::::::::-==--=--=--:::::--=+=----::\n:---=++===++++=+=---==--::::::::::-=-====----===+=--=-----::\n:--======+==------==++=-:::::::::::===----:::--====--------:\n--+==+=+=--:::----=+==-::::::::::::-----::::---+=---::::::::\n:::---------:::----====--::-:--::::-=-==------------::::---:\n-:------=+***=--::--===-==-=+*=----:-=======---:::::::::::::\n:::::::::::::::::::===--==++*****++=====---:::::::::::::::::\n:::--:::::::::-----=----+++*+=+++==+=++==--:::::::::::::::::\n::::::::::::::::---======++++*#%%%*+=+=--:::::::::::::-:::::\n::::::::::::::------=+==+****#%%%%#*==-=---:::::::::::::::::\n::::-:::::::-=-::---+#*=*=++++**#%###+==---:::::::::-:::::::\n:::==--:::::+=---=#%%%%*%%*#%#%%%#%%%=%##**++-::::::-=::::::\n::::----::::=*----*####=%%*%%%%%%##%%#*#*****+:::::--:::::::"
                );
                curConsole->setCallback([this] { window->close(); });
            }
        }));

    addToggleButton({ 285, 239 }, "B");
    addToggleButton({ 335, 239 }, "C");
    addToggleButton({ 385, 239 }, "D");
    addToggleButton({ 435, 289 }, "E");
    addToggleButton({ 435, 339 }, "F");
    addToggleButton({ 435, 389 }, "G");
    addToggleButton({ 385, 439 }, "H");
    addToggleButton({ 335, 439 }, "I");
    addToggleButton({ 285, 439 }, "J");
    addToggleButton({ 235, 389 }, "K");
    addToggleButton({ 235, 339 }, "L");
    addToggleButton({ 235, 289 }, "M");
    addToggleButton({ 189, 189 }, "N");
    addToggleButton({ 481, 189 }, "O");
    addToggleButton({ 481, 489 }, "P");
    addToggleButton({ 189, 489 }, "Q");
    addToggleButton({ 93 , 93  }, "R");
    addToggleButton({ 335, 93  }, "S");
    addToggleButton({ 577, 93  }, "T");
    addToggleButton({ 577, 335 }, "U");
    addToggleButton({ 577, 577 }, "V");
    addToggleButton({ 335, 577 }, "W");
    addToggleButton({ 93 , 577 }, "X");
    addToggleButton({ 93 , 335 }, "Y");
    addToggleButton({ 530, 425 }, "1");
    addToggleButton({ 68 , 450 }, "2");
    addToggleButton({ 145, 103 }, "3");
}

void Game::initGui()
{
    if (fontMonoBold == nullptr) { return; }

    // Delete all current objects
    activeButtons.erase(activeButtons.begin(), activeButtons.end());
    activeAssets.erase(activeAssets.begin(), activeAssets.end());
    activeTextures.erase(activeTextures.begin(), activeTextures.end());
    activeSpecial.erase(activeSpecial.begin(), activeSpecial.end());

    SoundManager* soundManager = SoundManager::get();
    
    // C++ is a learning experience
    sf::Text* curText = nullptr;
	sf::Sprite* curSprite = nullptr;
	sf::Texture* curTexture = nullptr;
    sf::RectangleShape* curRect = nullptr; 
	curConsole = nullptr;

    // Create objects based on window state
    switch (curWindowState)
    {
    case MAIN:
        // -- Objects --
        // Title
        curText = new sf::Text();
        curText->setFont(*fontMonoBold);
        curText->setString("SatFinder v2.0");
        curText->setFillColor(sf::Color(0, 255, 0));
        curText->setCharacterSize(64);
		curText->setPosition(423.f, 45.f);
        activeAssets.push_back(curText);

        // Close prompt
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Press ESC to close");
        curText->setFillColor({ 200, 200, 200 });
        curText->setCharacterSize(32);
        curText->setPosition(30.f, 660.f);
        activeAssets.push_back(curText);

        // -- Buttons --
        // Map button
        activeButtons.emplace_back(new Button(sf::Vector2f(48.f, 176.f), "assets/sprites/MapIcon_0.png", [this]
            {
                switchGui(MAP);
            }));
		// Route Planner button
        activeButtons.emplace_back(new Button(sf::Vector2f(456.f, 176.f), "assets/sprites/RoutePlannerIcon_0.png", [this]
            {
				switchGui(ROUTE_PLANNER);
            }));
		// Log button
        activeButtons.emplace_back(new Button(sf::Vector2f(868.f, 176.f), "assets/sprites/LogIcon_0.png", [this]
            {
                switchGui(LOG);
            }));
		// Info button
        activeButtons.emplace_back(new Button({ 1147.f, 590.f }, "assets/sprites/InfoIcon.png", [this]
            {
                switchGui(INFO);
			}));
        activeButtons.emplace_back(new Button({ 1147.f, 38.f }, "assets/sprites/SettingsIcon.png", [this]
            {
                switchGui(SETTINGS);
            }));

        break;

    case SETTINGS:

        // -- Objects --
        // Title
        curText = new sf::Text();
        curText->setFont(*fontMonoBold);
        curText->setString("Settings");
        curText->setFillColor(sf::Color(0, 255, 0));
        curText->setCharacterSize(69);
        curText->setPosition(30.f, 20.f);
        activeAssets.push_back(curText);

        // Line
        curRect = new sf::RectangleShape();
        curRect->setSize({ 1180, 5 });
        curRect->setPosition(50.f, 130.f);
        curRect->setFillColor({ 20, 20, 20 });
        activeAssets.push_back(curRect);

        // Setting:Enable Sounds
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Enable Sound");
        curText->setFillColor(sf::Color(255, 255, 255));
        curText->setCharacterSize(56);
        curText->setPosition(60.f, 140.f);
        activeAssets.push_back(curText);

        // Setting:Enable Sounds - Subtext
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Toggle all audio on/off. Does not impact performance.");
        curText->setFillColor(sf::Color(120, 120, 120));
        curText->setCharacterSize(32);
        curText->setPosition(60.f, 200.f);
        activeAssets.push_back(curText);

        // Line
        curRect = new sf::RectangleShape();
        curRect->setSize({ 1180, 5 });
        curRect->setPosition(50.f, 260.f);
        curRect->setFillColor({ 20, 20, 20 });
        activeAssets.push_back(curRect);

        // Setting:Enable Instant Calc
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Enable Instant Calc");
        curText->setFillColor(sf::Color(255, 255, 255));
        curText->setCharacterSize(56);
        curText->setPosition(60.f, 270.f);
        activeAssets.push_back(curText);

        // Setting:Enable Instant Calc - Subtext
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Makes route plotting as fast as your computer can calculate\nit. Calc is short for calculator btw I'm just using slang");
        curText->setFillColor(sf::Color(120, 120, 120));
        curText->setCharacterSize(32);
        curText->setPosition(60.f, 330.f);
        activeAssets.push_back(curText);

        // Line
        curRect = new sf::RectangleShape();
        curRect->setSize({ 1180, 5 });
        curRect->setPosition(50.f, 420.f);
        curRect->setFillColor({ 20, 20, 20 });
        activeAssets.push_back(curRect);

        // Close prompt
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Press ESC to go back");
        curText->setFillColor(sf::Color(200, 200, 200));
        curText->setCharacterSize(32);
        curText->setPosition(30.f, 660.f);
        activeAssets.push_back(curText);

        // -- Buttons --
        // Enable Sounds
        activeButtons.emplace_back(new Button({ 1120.f, 160.f }, "assets/sprites/ToggleOff.png", [] 
            {
                SettingsManager::soundEnabled = !SettingsManager::soundEnabled;
            }));
        activeButtons.at(activeButtons.size() - 1)->setIsToggle("assets/sprites/ToggleOn.png", false);
        if (SettingsManager::soundEnabled) { activeButtons.at(activeButtons.size() - 1)->switchToggleState(); }

        // Enable Instant Calc
        activeButtons.emplace_back(new Button({ 1120.f, 300.f }, "assets/sprites/ToggleOff.png", []
            {
                SettingsManager::instantCalc = !SettingsManager::instantCalc;
            }));
        activeButtons.at(activeButtons.size() - 1)->setIsToggle("assets/sprites/ToggleOn.png", false);
        if (SettingsManager::instantCalc) { activeButtons.at(activeButtons.size() - 1)->switchToggleState(); }

        break;

	case ROUTE_PLANNER: 

        // -- Objects --
        // Map
        curSprite = new sf::Sprite();
		curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/Map.png");
        curSprite->setTexture(*curTexture);
		activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Empty Console
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/ConsoleBlank.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition({739.f, 20.f});
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Console Text
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Awaiting Input...");
        curText->setFillColor({ 0, 255, 0 });
        curText->setCharacterSize(16);
        curText->setPosition(757.f, 30.f);
        activeAssets.push_back(curText);

		// -- Buttons --
        // Sat buttons are huge so reorganized
        initSatButtons();
        activeButtons.emplace_back(new Button({271.f, 635.f}, "assets/sprites/map/Button_RESET.png", [this] 
            {
                if (!curRoute.empty())
                {
                    SoundManager* soundManager = SoundManager::get();
                    soundManager->play(SoundManager::sfx::SWITCH_OFF);
                    curRoute.clear();
                    initGui();
                }
            }));
        activeButtons.emplace_back(new Button({ 911.f, 635.f }, "assets/sprites/map/Button_PLOT1.png", [this]
            {
                SoundManager* soundManager = SoundManager::get();
                if (!curRoute.empty())
                {
                    curRoute.calculateBest();
                    if (SettingsManager::instantCalc)
                    {
                        soundManager->play(SoundManager::sfx::ZAP);
                        switchGui(ROUTE_PLANNED);
                    }
                    else
                    {
                        switchGui(ROUTE_PLANNING);
                    }
                }
                else
                {
                    std::cout << "Tried to plot empty path!" << std::endl;
                }
                // do other stuff I assume
            }));

        break;

    case ROUTE_PLANNING:
        metaParanoia = true;

        // -- Objects --
        // Map
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/Map.png");
        curSprite->setTexture(*curTexture);
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Empty Console
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/ConsoleBlank.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition({ 739.f, 20.f });
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Console Text
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("");
        curText->setFillColor({ 0, 255, 0 });
        curText->setCharacterSize(16);
        curText->setPosition(757.f, 30.f);
        activeAssets.push_back(curText);

        // Console 61x36
        curConsole = new Console(curText, 61, 36, 0.f);
        soundManager->playInChannel(SoundManager::sfx::PROCESSING, 0);
        curConsole->setText(
            "> Establishing telemetry link to base station...........GOOD\n> Verifying data integrity................................OK\n> Avoiding interference zones...........................GOOD\n> Sat path stability...................................97.1%\n> Pinging server UNIFORM..............[0/4 PACKETS RETURNED]\n                                      [1/4 PACKETS RETURNED]\n                                      [2/4 PACKETS RETURNED]\n                                      [3/4 PACKETS RETURNED]\n                                      [4/4 PACKETS RETURNED]\n> [ERROR] Packet echo delay exceeds expected return by 48s\n> Predictive routing active: anticipating solar flare impact\n> Analyzing effect on the TROUT population...........MINIMAL\n> [ERROR] I have no mouth and I must scream\n> Pinging server TREE_HOUSE...................no response :(\n> Obstruction detected, ignoring\n> There's no way it takes this long to compute a route......\n> oh god\n> its here\n> help\n> help\n> help\n> help\n> help\n> help\n> help"
        );
        curConsole->setCallback([this] {switchGui(ROUTE_PLANNED); });
        activeSpecial.emplace_back(curConsole);

        break;
    case ROUTE_PLANNED:
        metaParanoia = false;

        // -- Objects --
        // Map
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/Map.png");
        curSprite->setTexture(*curTexture);
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Empty Console
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/ConsoleBlank.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition({ 739.f, 20.f });
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Console Text
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("");
        curText->setFillColor({ 0, 255, 0 });
        curText->setCharacterSize(16);
        curText->setPosition(757.f, 30.f);
        activeAssets.push_back(curText);

        // Console Object
        curConsole = new Console(curText, 61, 36, 0.f);
        curConsole->setText(
            "> Best route found!\n> " + curRoute.getBestString() + "\n       ...with a total distance of " + std::to_string(curRoute.getBestDistance()) + "u.\n> This route has been copied to your clipboard."
        );
        curConsole->setCallback([&] { activeSpecial.erase(activeSpecial.begin(), activeSpecial.end()); });
        activeSpecial.emplace_back(curConsole);

        // Copy route to clipboard lol
        sf::Clipboard::setString(curRoute.getBestString());

        break;
    case INFO:

		// -- Objects --
		// Title
		curText = new sf::Text();
		curText->setFont(*fontMonoBold);
		curText->setString("Info");
		curText->setFillColor(sf::Color(0, 255, 0));
		curText->setCharacterSize(69);
		curText->setPosition(30.f, 20.f);
		activeAssets.push_back(curText);

		// Close prompt
		curText = new sf::Text();
		curText->setFont(*fontMono);
        curText->setString("How to Use : Go to Route Planner and select the satellites you need to\nvisit, then hit 'Plot'\n\nAbout : idk I wanted to learn SFML and revamp my old VotV SatFinder project\nso here it is. Uses brute force algorithm (for now ;>) so may bug >10\nlocations at once (thats like 3 million routes to check)\n\nFont : Pixel Operator\n\nMade by Harbor\n\nVoices of the Void made by EternityDev\n\nPress ESC to go back");
		curText->setFillColor(sf::Color(200, 200, 200));
		curText->setCharacterSize(32);
		curText->setPosition(30.f, 100.f);
		activeAssets.push_back(curText);

        // -- Buttons --
        activeButtons.emplace_back(new Button(sf::Vector2f(1210.f, 20.f), "assets/sprites/glooby.png", [this]
            {
                SoundManager* soundManager = SoundManager::get();
                soundManager->playInChannel(soundManager->sfx::GLOOBY, 3);
			}));

        break;

    case MAP:
        // -- Objects --
		// Title
        curText = new sf::Text();
        curText->setFont(*fontMonoBold);
        curText->setString("THE MAP!!!!");
        curText->setFillColor(sf::Color(0, 255, 0));
        curText->setCharacterSize(64);
		curText->setPosition(30.f, 20.f);
        activeAssets.emplace_back(curText);

        // Map
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/map/Map.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition(620.f, 80.f);
        curSprite->setScale(0.7, 0.7);
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Alien funny
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/alienjak.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition(420.f, 180.f);
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

		// Close prompt
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Press ESC to go back");
        curText->setFillColor(sf::Color(200, 200, 200));
        curText->setCharacterSize(32);
        curText->setPosition(30.f, 660.f);
        activeAssets.push_back(curText);

        break;

    case LOG:
		// -- Objects --
        // Title
        curText = new sf::Text();
        curText->setFont(*fontMonoBold);
        curText->setString("Log");
        curText->setFillColor(sf::Color(0, 255, 0));
        curText->setCharacterSize(64);
        curText->setPosition(30.f, 20.f);
        activeAssets.emplace_back(curText);

        // Log
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("assets/sprites/log.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition(420.f, 180.f);
        curSprite->setScale(2, 2);
        activeAssets.push_back(curSprite);
        activeTextures.push_back(curTexture);

        // Close prompt
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("Press ESC to go back");
        curText->setFillColor(sf::Color(200, 200, 200));
        curText->setCharacterSize(32);
        curText->setPosition(30.f, 660.f);
        activeAssets.push_back(curText);
    }
}

void Game::handleLMB()
{
    for (auto& button : activeButtons)
    {
        if (button->getMouseOver(*window))
        {
            button->onClick();
            return;
        }
    }
}

void Game::handleESC()
{
    SoundManager* soundManager = SoundManager::get();

    if (metaParanoia)
    {
        soundManager->play(SoundManager::sfx::META);
        return;
    }

    switch (curWindowState)
    {
    case MAIN:
        window->close();
        break;
    case SETTINGS:
        SettingsManager::save();
        switchGui(MAIN);
        break;
    case ROUTE_PLANNED:
        switchGui(ROUTE_PLANNER);
        break;
    case INFO:
        soundManager->stopAllSounds();
        switchGui(MAIN);
        break;
    default:
        switchGui(MAIN);
        break;
    }
}

void Game::pollEvents()
{
    // Event Polling
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::MouseButtonPressed:
            if (ev.mouseButton.button == sf::Mouse::Left) handleLMB();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) handleESC();
            if (ev.key.code == sf::Keyboard::F5) initGui();
            break;
        case sf::Event::Resized:
            window->setSize( sf::Vector2u(window->getSize().y * 1.777779f, window->getSize().y) );
            break;
        }
    }
}

void Game::pollMouseOver()
{
	mousePos = sf::Mouse::getPosition(*window);

    for (auto& button : activeButtons)
    {
        if (button->getGlobalBounds().contains(window->mapPixelToCoords(mousePos)))
        {
            button->setMouseOver(true);
        }
        else
        {
            button->setMouseOver(false);
		}
    }
}

void Game::pollSpecial()
{
    for (auto& object : activeSpecial)
    {
        object->update(deltaClock.restart().asSeconds());
    }
}

void Game::switchGui(windowState newState)
{
    curWindowState = newState;
    initGui();
}

// Constructors and Destructors
Game::Game()
{
	initVariables();
	initWindow();
    initGui();
}

Game::~Game()
{
	delete window;
}

// Functions
void Game::update()
{
	pollEvents();
	pollMouseOver();
    pollSpecial();
}

void Game::render()
{
    window->clear();

    // Draw game objects
    for (auto& asset : activeAssets)
    {
        window->draw(*asset);
    }
    for (auto& button : activeButtons)
    {
        button->draw(*window);
    }

	window->display();
}

// Accessors
const bool Game::isRunning() const
{
	return this->window->isOpen();
}

// Called before update/render loop
void Game::initFontBold(sf::Font* font)
{
    fontMonoBold = font;
    initGui(); // its so hacky lmaooo
}

void Game::initFontNormal(sf::Font* font)
{
    fontMono = font;
}