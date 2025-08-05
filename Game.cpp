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

	window = new sf::RenderWindow(videoMode, "SatFinder v2.0", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window->setFramerateLimit(60);

    // Set icon
    sf::Image icon;
    icon.loadFromFile("Assets/icon.png");
    window->setIcon(200, 200, icon.getPixelsPtr());
}

void Game::initSatButtons()
{
    auto addToggleButton = [&](sf::Vector2f pos, const std::string& id)
        {
            std::string basePath = "Assets/Sprites/Map/Button_";
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

	activeButtons.emplace_back(new Button(sf::Vector2f(335, 339), "Assets/Sprites/Map/Button_A1.png", [this] 
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
    /* PIRATESOFTWARE HACKED MY PROJECT AND ADDED THIS WTF !!!!!
	activeButtons.emplace_back(new Button(sf::Vector2f(285, 239), "Assets/Sprites/Map/Button_B0.png", [] { }));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_B1.png");
	activeButtons.emplace_back(new Button(sf::Vector2f(335, 239), "Assets/Sprites/Map/Button_C0.png", [] { }));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_C1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(385, 239), "Assets/Sprites/Map/Button_D0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_D1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(435, 289), "Assets/Sprites/Map/Button_E0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_E1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(435, 339), "Assets/Sprites/Map/Button_F0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_F1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(435, 389), "Assets/Sprites/Map/Button_G0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_G1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(385, 439), "Assets/Sprites/Map/Button_H0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_H1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(335, 439), "Assets/Sprites/Map/Button_I0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_I1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(285, 439), "Assets/Sprites/Map/Button_J0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_J1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(235, 389), "Assets/Sprites/Map/Button_K0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_K1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(235, 339), "Assets/Sprites/Map/Button_L0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_L1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(235, 289), "Assets/Sprites/Map/Button_M0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_M1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(189, 189), "Assets/Sprites/Map/Button_N0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_N1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(481, 189), "Assets/Sprites/Map/Button_O0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_O1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(481, 489), "Assets/Sprites/Map/Button_P0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_P1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(189, 489), "Assets/Sprites/Map/Button_Q0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_Q1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(93, 93), "Assets/Sprites/Map/Button_R0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_R1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(335, 93), "Assets/Sprites/Map/Button_S0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_S1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(577, 93), "Assets/Sprites/Map/Button_T0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_T1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(577, 335), "Assets/Sprites/Map/Button_U0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_U1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(577, 577), "Assets/Sprites/Map/Button_V0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_V1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(335, 577), "Assets/Sprites/Map/Button_W0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_W1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(93, 577), "Assets/Sprites/Map/Button_X0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_X1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(93, 335), "Assets/Sprites/Map/Button_Y0.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_Y1.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(530, 425), "Assets/Sprites/Map/Button_10.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_11.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(68, 450), "Assets/Sprites/Map/Button_20.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_21.png");
    activeButtons.emplace_back(new Button(sf::Vector2f(145, 103), "Assets/Sprites/Map/Button_30.png", [] {}));
    activeButtons.at(activeButtons.size() - 1)->setIsToggle("Assets/Sprites/Map/Button_31.png");*/
}

void Game::initGui()
{
    if (fontMonoBold == nullptr) { return; }

    // Delete all current objects
    activeButtons.erase(activeButtons.begin(), activeButtons.end());
    activeAssets.erase(activeAssets.begin(), activeAssets.end());
    activeSpecial.erase(activeSpecial.begin(), activeSpecial.end());

    SoundManager* soundManager = SoundManager::get();
	sf::Text* curText = nullptr;       // C++ is a learning experience
	sf::Sprite* curSprite = nullptr;   // C++ is a learning experience
	sf::Texture* curTexture = nullptr; // C++ is a learning experience
	curConsole = nullptr;     // C++ is a learning experience

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
        activeButtons.emplace_back(new Button(sf::Vector2f(48.f, 176.f), "Assets/Sprites/MapIcon_0.png", [this]
            {
                switchGui(MAP);
            }));
		// Route Planner button
        activeButtons.emplace_back(new Button(sf::Vector2f(456.f, 176.f), "Assets/Sprites/RoutePlannerIcon_0.png", [this]
            {
				switchGui(ROUTE_PLANNER);
            }));
		// Log button
        activeButtons.emplace_back(new Button(sf::Vector2f(868.f, 176.f), "Assets/Sprites/LogIcon_0.png", [this]
            {
                switchGui(LOG);
            }));
		// Info button
        activeButtons.emplace_back(new Button({ 1147.f, 590.f }, "Assets/Sprites/InfoIcon.png", [this]
            {
                switchGui(INFO);
			}));

        break;

	case ROUTE_PLANNER: 

        // -- Objects --
        // Map
        curSprite = new sf::Sprite();
		curTexture = new sf::Texture();
        curTexture->loadFromFile("Assets/Sprites/Map/Map.png");
        curSprite->setTexture(*curTexture);
		activeAssets.push_back(curSprite);

        // Empty Console
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("Assets/Sprites/Map/ConsoleBlank.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition({739.f, 20.f});
        activeAssets.push_back(curSprite);

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
        activeButtons.emplace_back(new Button({271.f, 635.f}, "Assets/Sprites/Map/Button_RESET.png", [this] 
            {
                if (!curRoute.empty())
                {
                    SoundManager* soundManager = SoundManager::get();
                    soundManager->play(SoundManager::sfx::SWITCH_OFF);
                    curRoute.clear();
                    initGui();
                }
            }));
        activeButtons.emplace_back(new Button({ 911.f, 635.f }, "Assets/Sprites/Map/Button_PLOT1.png", [this]
            {
                if (!curRoute.empty())
                {
                    curRoute.calculateBest();
                    switchGui(ROUTE_PLANNING);
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
        curTexture->loadFromFile("Assets/Sprites/Map/Map.png");
        curSprite->setTexture(*curTexture);
        activeAssets.push_back(curSprite);

        // Empty Console
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("Assets/Sprites/Map/ConsoleBlank.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition({ 739.f, 20.f });
        activeAssets.push_back(curSprite);

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
        curTexture->loadFromFile("Assets/Sprites/Map/Map.png");
        curSprite->setTexture(*curTexture);
        activeAssets.push_back(curSprite);

        // Empty Console
        curSprite = new sf::Sprite();
        curTexture = new sf::Texture();
        curTexture->loadFromFile("Assets/Sprites/Map/ConsoleBlank.png");
        curSprite->setTexture(*curTexture);
        curSprite->setPosition({ 739.f, 20.f });
        activeAssets.push_back(curSprite);

        // Console Text
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("> Best route found!\n> " + curRoute.getBestString() + "\n       ...with a total distance of " + std::to_string(curRoute.getBestDistance()) + "u.\n> This route has been copied to your clipboard.");
        curText->setFillColor({ 0, 255, 0 });
        curText->setCharacterSize(16);
        curText->setPosition(757.f, 30.f);
        activeAssets.push_back(curText);

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
        activeButtons.emplace_back(new Button(sf::Vector2f(1210.f, 20.f), "Assets/Sprites/glooby.png", [this]
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
        curText->setString("WIP");
        curText->setFillColor(sf::Color(0, 255, 0));
        curText->setCharacterSize(64);
		curText->setPosition(30.f, 20.f);
        activeAssets.emplace_back(curText);

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

        // Close prompt
        curText = new sf::Text();
        curText->setFont(*fontMono);
        curText->setString("\"...but nobody came.\" ass menu");
        curText->setFillColor(sf::Color(200, 200, 200));
        curText->setCharacterSize(32);
        curText->setPosition(30.f, 660.f);
        activeAssets.push_back(curText);
    }
    /* Old button code ...
    mapButton = new Button(sf::Vector2f(48.f, 176.f), []
    {
        std::cout << "Map button clicked!" << std::endl;
    });
    mapButton->setTexture("Assets/Sprites/MapIcon_0.png");
    mapButton->setColor(sf::Color(120, 120, 120));
    menuButtons[0] = mapButton;

    routePlannerButton = new Button(sf::Vector2f(456.f, 176.f), []
    {
        std::cout << "Route Planner button clicked!" << std::endl;
    });
    routePlannerButton->setTexture("Assets/Sprites/RoutePlannerIcon_0.png");
    routePlannerButton->setColor(sf::Color(120, 120, 120));
    menuButtons[1] = routePlannerButton;

    logButton = new Button(sf::Vector2f(868.f, 176.f), []
    {
        std::cout << "Log button clicked!" << std::endl;
    });
    logButton->setTexture("Assets/Sprites/LogIcon_0.png");
    logButton->setColor(sf::Color(120, 120, 120));
    menuButtons[2] = logButton;*/
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
    case ROUTE_PLANNER:
    case INFO:
        soundManager->stopAllSounds();
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
            if (ev.key.code == sf::Keyboard::LControl)
            {
                if (ev.key.code == sf::Keyboard::R) switchGui(ROUTE_PLANNED);
            }
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