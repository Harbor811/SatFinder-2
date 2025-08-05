#include "Game.h"

int main()
{
    std::cout << "Embrace the Unknown." << std::endl;

    // Init Game Engine Thing
    Game game;
    sf::Font* curFont = new sf::Font();
    if (!curFont->loadFromFile("Assets/Fonts/PixelOperatorMono.ttf"))
    {
        std::cerr << "Error loading font file!" << std::endl;
        return -1;
    }
    game.initFontNormal(curFont);

    curFont = new sf::Font();
    if (!curFont->loadFromFile("Assets/Fonts/PixelOperatorMono-Bold.ttf"))
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


/* Demo Code::
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}*/