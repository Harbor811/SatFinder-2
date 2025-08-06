#include "Game.h"

int main()
{
    std::cout << "Embrace the Unknown." << std::endl;

    // Init Settings
    SettingsManager::init();

    // Init Game Engine Thing
    Game game;
    sf::Font* curFont = new sf::Font();
    if (!curFont->loadFromFile("assets/fonts/PixelOperatorMono.ttf"))
    {
        std::cerr << "Error loading font file!" << std::endl;
        return -1;
    }
    game.initFontNormal(curFont);

    curFont = new sf::Font();
    if (!curFont->loadFromFile("assets/fonts/PixelOperatorMono-Bold.ttf"))
    {
        std::cerr << "Error loading font file!" << std::endl;
        return -1;
    }
    game.initFontBold(curFont);
    
    // "Game" Loop
    while (game.isRunning())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    SoundManager* soundManager = SoundManager::get();
    delete soundManager;

    return 0;
}