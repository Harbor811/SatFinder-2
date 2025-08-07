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

	window = new sf::RenderWindow(videoMode, "SatFinder 2", sf::Style::Titlebar | sf::Style::Close);
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
    auto createText = [](sf::Font* font, std::string string, const sf::Color& col, unsigned int size, const sf::Vector2f& pos)
        {
            sf::Text* curText = new sf::Text();
            curText->setFont(*font);
            curText->setString(string);
            curText->setFillColor(col);
            curText->setCharacterSize(size);
            curText->setPosition(pos);
            return curText;
        };

    auto createSprite = [&](std::string filePath, const sf::Vector2f& pos = { 0.0, 0.0 }, const sf::Vector2f& scale = { 1.0, 1.0 })
        {
            sf::Sprite* curSprite = new sf::Sprite();
            sf::Texture* curTexture = new sf::Texture();
            curTexture->loadFromFile(filePath);
            curSprite->setTexture(*curTexture);
            curSprite->setPosition(pos);
            curSprite->setScale(scale);
            activeTextures.push_back(curTexture);
            return curSprite;
        };

    auto createRect = [](const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& col = { 255, 0, 0 }) 
        {
            sf::RectangleShape* curRect = new sf::RectangleShape();
            curRect->setSize(size);
            curRect->setPosition(pos);
            curRect->setFillColor(col);
            return curRect;
        };

    if (fontMonoBold == nullptr) { return; }

    // Delete all current objects
    activeButtons.erase(activeButtons.begin(), activeButtons.end());
    activeAssets.erase(activeAssets.begin(), activeAssets.end());
    activeTextures.erase(activeTextures.begin(), activeTextures.end());
    activeSpecial.erase(activeSpecial.begin(), activeSpecial.end());

    SoundManager* soundManager = SoundManager::get();
    
    // C++ is a learning experience
    sf::Text* curText = nullptr;
	curConsole = nullptr;

    // Create objects based on window state
    switch (curWindowState)
    {
    case MAIN:
        // -- Objects --
        // Title
        activeAssets.push_back(createText(fontMonoBold, "SatFinder 2",     { 0, 255, 0 },     64, { 463.f, 45.f }));

        // Close prompt
        activeAssets.push_back(createText(fontMono,     "Press ESC to close", { 200, 200, 200 }, 32, { 30.f, 660.f }));

        // -- Buttons --
        // Map button
        activeButtons.push_back(new Button({ 48.f  , 176.f }, "assets/sprites/MapIcon_0.png",          [this] { switchGui(MAP); }));

        // Route Planner button
        activeButtons.push_back(new Button({ 456.f , 176.f }, "assets/sprites/RoutePlannerIcon_0.png", [this] { switchGui(ROUTE_PLANNER); }));

		// Log button
        activeButtons.push_back(new Button({ 868.f , 176.f }, "assets/sprites/LogIcon_0.png",          [this] { switchGui(LOG); }));

		// Info button
        activeButtons.push_back(new Button({ 1147.f, 38.f  }, "assets/sprites/InfoIcon.png",           [this] { switchGui(INFO); }));

        // Settings button
        activeButtons.push_back(new Button({ 50.f  , 38.f  }, "assets/sprites/SettingsIcon.png",       [this] { switchGui(SETTINGS); }));

        break;

    case SETTINGS:

        // -- Objects --
        // Title
        activeAssets.push_back(createText(fontMonoBold, "Settings", { 0, 255, 0 }, 69, { 30.f, 20.f }));

        // Line
        activeAssets.push_back(createRect({ 1180.f, 5.f }, { 50.f, 130.f }, { 20, 20, 20 }));

        // Setting:Enable Sounds
        activeAssets.push_back(createText(fontMono, "Enable Sound", { 255, 255, 255 }, 56, { 60.f, 140.f }));

        // Setting:Enable Sounds - Subtext
        activeAssets.push_back(createText(fontMono, "Toggle all audio on/off. Does not impact performance.", { 120, 120, 120 }, 32, { 60.f, 200.f }));

        // Line
        activeAssets.push_back(createRect({ 1180, 5 }, { 50.f, 260.f }, { 20, 20, 20 }));

        // Setting:Enable Instant Calc
        activeAssets.push_back(createText(fontMono, "Enable Instant Calc", { 255, 255, 255 }, 56, { 60.f, 270.f }));

        // Setting:Enable Instant Calc - Subtext
        activeAssets.push_back(createText(fontMono, "Makes route plotting as fast as your computer can calculate\nit. Calc is short for calculator btw I'm just using slang", { 120, 120, 120 }, 32, { 60.f, 330.f }));

        // Line
        activeAssets.push_back(createRect({ 1180, 5 }, { 50.f, 420.f }, { 20, 20, 20 }));

        // Back prompt
        activeAssets.push_back(createText(fontMono, "Press ESC to go back", { 200, 200, 200 }, 32, { 30.f, 660.f }));

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
        activeAssets.push_back(createSprite("assets/sprites/map/Map.png"));

        // Empty Console
        activeAssets.push_back(createSprite("assets/sprites/map/ConsoleBlank.png", { 739.f, 20.f }));

        // Fake Console Text
        activeAssets.push_back(createText(fontMono, "Awaiting Input...", { 0, 255, 0 }, 16, { 757.f, 30.f }));

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
        activeAssets.push_back(createSprite("assets/sprites/map/Map.png"));

        // Empty Console
        activeAssets.push_back(createSprite("assets/sprites/map/ConsoleBlank.png", { 739.f, 20.f }));

        // Console Text
        curText = createText(fontMono, "", { 0, 255, 0 }, 16, { 757.f, 30.f });
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
        activeAssets.push_back(createSprite("assets/sprites/map/Map.png"));

        // Empty Console
        activeAssets.push_back(createSprite("assets/sprites/map/ConsoleBlank.png", { 739.f, 20.f }));

        // Console Text
        curText = createText(fontMono, "", { 0, 255, 0 }, 16, { 757.f, 30.f });
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
        activeAssets.push_back(createText(fontMonoBold, "Info", { 0, 255, 0 }, 69, { 30.f, 20.f }));

		// Main text
        activeAssets.push_back(createText(fontMono, "How to Use : Go to Route Planner and select the satellites you need to\nvisit, then hit 'Plot'\n\nAbout : idk I wanted to learn SFML and revamp my old VotV SatFinder project\nso here it is. Uses brute force algorithm (for now ;>) so may bug >10\nlocations at once (thats like 3 million routes to check)\n\nFont : Pixel Operator\n\nMade by Harbor\n\nVoices of the Void made by EternityDev", { 200, 200, 200 }, 32, { 30.f, 100.f }));

        // Back prompt
        activeAssets.push_back(createText(fontMono, "Press ESC to go back", { 200, 200, 200 }, 32, { 30.f, 660.f }));

        // -- Buttons --
        // Glooby
        activeButtons.emplace_back(new Button(sf::Vector2f(1210.f, 20.f), "assets/sprites/glooby.png", [this]
            {
                SoundManager* soundManager = SoundManager::get();
                soundManager->playInChannel(soundManager->sfx::GLOOBY, 3);
			}));

        break;

    case MAP:
        // -- Objects --
		// Title
        activeAssets.push_back(createText(fontMonoBold, "THE MAP!!!!", { 0, 255, 0 }, 64, { 30.f, 20.f }));

        // Map
        activeAssets.push_back(createSprite("assets/sprites/map/Map.png", { 620.f, 80.f }, { 0.7, 0.7 }));

        // Alien funny
        activeAssets.push_back(createSprite("assets/sprites/alienjak.png", { 420.f, 180.f }));

        // Back prompt
        activeAssets.push_back(createText(fontMono, "Press ESC to go back", { 200, 200, 200 }, 32, { 30.f, 660.f }));

        break;

    case LOG:
		// -- Objects --
        // Title
        activeAssets.push_back(createText(fontMonoBold, "Log", { 0, 255, 0 }, 64, { 30.f, 20.f }));

        // Log
        activeAssets.push_back(createSprite("assets/sprites/log.png", { 420.f, 180.f }, { 2.0, 2.0 }));

        // Back prompt
        activeAssets.push_back(createText(fontMono, "Press ESC to go back", { 200, 200, 200 }, 32, { 30.f, 660.f }));
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