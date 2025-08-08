#include "Game.h"

int main()
{
    std::cout << "Embrace the Unknown." << std::endl;

    // Init Settings
    SettingsManager::init();

    // Init DrawingManager
    DrawingManager* drawingManager = DrawingManager::get();
    sf::Font* curFont = new sf::Font();
    if (!curFont->loadFromFile("assets/fonts/PixelOperatorMono.ttf"))
    {
        std::cerr << "Error loading font file!" << std::endl;
        return -1;
    }
    drawingManager->setFont(curFont, DrawingManager::FontType::Normal);

    curFont = new sf::Font();
    if (!curFont->loadFromFile("assets/fonts/PixelOperatorMono-Bold.ttf"))
    {
        std::cerr << "Error loading font file!" << std::endl;
        return -1;
    }
    drawingManager->setFont(curFont, DrawingManager::FontType::Bold);

    // Init Game Engine Thing
    Game game;
    
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