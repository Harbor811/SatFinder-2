#include "DrawingManager.h"

DrawingManager* DrawingManager::instance = nullptr;

DrawingManager::~DrawingManager()
{
	delete instance;
}

DrawingManager* DrawingManager::get()
{
	if (instance == nullptr)
		instance = new DrawingManager();
	return instance;
}

DrawingManager::DrawingManager()
{
	clear();
}

void DrawingManager::clear()
{
	// Delete all current objects
	for (auto& obj : activeButtons)
	{
		if (obj.owned) delete obj.ptr;
	}
	activeButtons.clear();

	for (auto& obj : activeAssets) delete obj;
	activeAssets.clear();

	for (auto& obj : activeTextures) delete obj;
	activeTextures.clear();
}

sf::Text* DrawingManager::addText(FontType font, std::string string, const sf::Color& col, size_t size, const sf::Vector2f& pos)
{
	// Make text object
	sf::Text* curText = new sf::Text();
	curText->setFont(*getFont(font));
	curText->setString(string);
	curText->setFillColor(col);
	curText->setCharacterSize(size);
	curText->setPosition(pos);

	// Add to activeAssets
	activeAssets.push_back(curText);

	// Return text pointer
	return curText;
}

void DrawingManager::addText(sf::Text* text)
{
	activeAssets.push_back(text);
}

void DrawingManager::addSprite(std::string filePath, const sf::Vector2f& pos, const sf::Vector2f& scale)
{
	// Make sprite & texture
	sf::Sprite* curSprite = new sf::Sprite();
	sf::Texture* curTexture = new sf::Texture();
	curTexture->loadFromFile(filePath);
	curSprite->setTexture(*curTexture);
	curSprite->setPosition(pos);
	curSprite->setScale(scale);

	// Add to activeAssets and activeTextures
	activeTextures.push_back(curTexture);
	activeAssets.push_back(curSprite);
}

void DrawingManager::addRect(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& col)
{
	// Make rectangle shape
	sf::RectangleShape* curRect = new sf::RectangleShape();
	curRect->setSize(size);
	curRect->setPosition(pos);
	curRect->setFillColor(col);
	
	// Add to activeAssets
	activeAssets.push_back(curRect);
}

void DrawingManager::addButton(const sf::Vector2f& pos, std::string textureFile, std::function<void()> onClick, bool isOwned)
{
	// Create button object
	Button* curButton = new Button(pos, textureFile, onClick);
	
	// Add to activeButtons
	activeButtons.push_back(ButtonEntry(curButton, isOwned));
}

void DrawingManager::addButton(Button* btn, bool isOwned)
{
	activeButtons.push_back(ButtonEntry(btn, isOwned));
}

void DrawingManager::addToggleButton(const sf::Vector2f& pos, std::string textureFile, std::string textureOnFile, std::function<void()> onClick, bool isOwned, bool isToggleSfx, bool setOn)
{
	// Create button object
	Button* curButton = new Button(pos, textureFile, onClick);
	curButton->makeToggle(textureOnFile, isToggleSfx);
	curButton->setToggleState(setOn, false);

	// Add to activeButtons
	activeButtons.push_back(ButtonEntry(curButton, isOwned));
}

void DrawingManager::draw(sf::RenderWindow* window) const
{
	window->clear();

	// Draw game objects
	for (auto& asset : activeAssets)
	{
		window->draw(*asset);
	}
	for (auto& button : activeButtons)
	{
		button.ptr->draw(*window);
	}

	window->display();
}

void DrawingManager::handleLMB(sf::RenderWindow* window)
{
	for (auto& button : activeButtons)
	{
		if (button.ptr->getMouseOver(*window))
		{
			button.ptr->onClick();
			return;
		}
	}
}

void DrawingManager::pollMouseOver(const sf::Vector2f& mousePos)
{
	for (auto& button : activeButtons)
	{
		if (button.ptr->getGlobalBounds().contains(mousePos))
		{
			button.ptr->setMouseOver(true);
		}
		else
		{
			button.ptr->setMouseOver(false);
		}
	}
}

sf::Font* DrawingManager::getFont(FontType leFont)
{
	return fonts.at(leFont);
}

void DrawingManager::setFont(sf::Font* fonty, FontType newFont)
{
	if (fonts.empty()) { fonts.resize(FontType::NumFonts); }
	fonts.at(newFont) = fonty;
}
