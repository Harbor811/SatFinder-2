#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "SoundManager.h"

class Button
{
private:
	bool isMouseOver = false;
	bool isToggle = false;
	bool toggled = false;
	sf::Texture texture;
	sf::Texture textureOn;
	sf::Sprite* sprite;

	std::function<void()> callback;

public:
	Button(const sf::Vector2f& pos, std::function<void()> onClick);
	Button(const sf::Vector2f& pos, const std::string textureFile, std::function<void()> onClick);
	virtual ~Button();

	sf::FloatRect getGlobalBounds();
	bool getMouseOver(sf::RenderWindow& window) const;

	void setIsToggle(std::string newFile = "none");
	void setMouseOver(bool mouseOver);
	void setScale(const sf::Vector2f& scale);
	void setAnchor(const sf::Vector2f anchorMod);
	void setColor(sf::Color col);
	void setTexture(const sf::Texture& newTexture);
	void setTexture(const std::string& file);
	void draw(sf::RenderWindow& window);
	void switchToggleState(bool withSfx = false);
	void onClick();
};

#endif