#ifndef DRAWINGMANAGER_H
#define DRAWINGMANAGER_H

#include "Button.h"

class DrawingManager
{

// Static members
private:
	static DrawingManager* instance;
public:
	static DrawingManager* get();

// Non-static members
private:
	DrawingManager();

	// Track whether or not we should delete buttons on clear() with this
	struct ButtonEntry
	{
		Button* ptr = nullptr;
		bool owned = true;

		ButtonEntry(Button* newPtr, bool isOwned = true) : ptr(newPtr), owned(isOwned) {}
	};

	std::vector<sf::Font*> fonts;

	std::vector<ButtonEntry> activeButtons;
	std::vector<sf::Drawable*> activeAssets;
	std::vector<sf::Texture*> activeTextures;

public:

	enum FontType
	{
		Normal,
		Bold,
		NumFonts
	};

	~DrawingManager();

	// Drawing
	void clear();
	sf::Text* addText(FontType font, std::string string, const sf::Color& col, size_t size, const sf::Vector2f& pos);
	void addText(sf::Text* text);
	void addSprite(std::string filePath, const sf::Vector2f& pos = { 0, 0 }, const sf::Vector2f& scale = { 1.0, 1.0 });
	sf::RectangleShape* addRect(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& col = { 255, 0, 0 });
	Button* addButton(const sf::Vector2f& pos, std::string textureFile, std::function<void()> onClick, bool isOwned = true);
	Button* addButton(Button* btn, bool isOwned = true);
	void addToggleButton(const sf::Vector2f& pos, std::string textureFile, std::string textureOnFile = "none", std::function<void()> onClick = {}, bool isOwned = true, bool isToggleSfx = true, bool setOn = false);
	void addLine(const sf::Vector2f pos1, const sf::Vector2f pos2, const sf::Color col = {0, 255, 255}, float thickness = 4.f);
	void draw(sf::RenderWindow* window) const;

	// Buttons
	void handleLMB(sf::RenderWindow* window);
	void pollMouseOver(const sf::Vector2f& mousePos);

	// Getters
	sf::Font* getFont(FontType leFont);

	// Setters
	void setFont(sf::Font* fonty, FontType newFont);
};

#endif