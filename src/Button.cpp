#include "Button.h"

Button::Button(const sf::Vector2f& pos, std::function<void()> onClick)
{
	sprite = new sf::Sprite();
	callback = onClick;

	sprite->setTexture(texture);
	sprite->setPosition(pos);
}

Button::Button(const sf::Vector2f& pos, const std::string textureFile, std::function<void()> callback)
{
	sprite = new sf::Sprite();
	this->callback = callback;

	texture.loadFromFile(textureFile);
	sprite->setTexture(texture);
	sprite->setPosition(pos);
	sprite->setColor(sf::Color(120, 120, 120));
}

Button::~Button()
{
	delete sprite;
}

sf::FloatRect Button::getGlobalBounds()
{
	return sprite->getGlobalBounds();
}

bool Button::getMouseOver(sf::RenderWindow& window) const
{
	return sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

// Called when you want to make a button a toggle, supply On Image
void Button::setIsToggle(std::string onImage, bool isToggleSfx)
{
	if (onImage == "none") 
	{ 
		textureOn = texture; 
	}
	else
	{
		if (!textureOn.loadFromFile(onImage))
		{
			std::cout << "ERROR - BAD FILE SUPPLY" << std::endl;
		}
	}
	
	isToggle = true;
	this->isToggleSfx = isToggleSfx;
}

void Button::setMouseOver(bool mouseOver)
{
	if (mouseOver == isMouseOver) return;
	isMouseOver = mouseOver;

	if (isMouseOver)
	{
		setColor(sf::Color(255, 255, 255));
		if (!isToggleSfx)
		{
			SoundManager* soundManager = SoundManager::get();
			soundManager->play(soundManager->sfx::ROLLOVER);
		}
	} 
	else 
	{
		setColor(sf::Color(120, 120, 120));
	}
}

void Button::setScale(const sf::Vector2f& scale)
{
	sprite->setScale(scale);
}

void Button::setAnchor(const sf::Vector2f anchorMod)
{
	sf::FloatRect bounds = sprite->getLocalBounds();
	sprite->setOrigin(sf::Vector2f(bounds.left + (bounds.width  * anchorMod.x),
								   bounds.top  + (bounds.height * anchorMod.y)));
}

void Button::setColor(sf::Color col)
{
	sprite->setColor(col);
}

void Button::setTexture(const sf::Texture& newTexture)
{
	sf::IntRect newSize;
	newSize.width  = newTexture.getSize().x;
	newSize.height = newTexture.getSize().y;

	texture = newTexture;
	sprite->setTexture(texture);
	sprite->setTextureRect(newSize);
}

void Button::setTexture(const std::string& file)
{
	texture.loadFromFile(file);

	sf::IntRect newSize;
	newSize.width = texture.getSize().x;
	newSize.height = texture.getSize().y;
	
	sprite->setTexture(texture);
	sprite->setTextureRect(newSize);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}

void Button::switchToggleState(bool withSfx)
{
	if (!isToggle) { std::cout << "SwitchToggleState called on non-toggle button!" << std::endl; return; }
	SoundManager* soundManager = SoundManager::get();

	toggled = !toggled;
	if (toggled)
	{
		if (withSfx && isToggleSfx) soundManager->play(soundManager->sfx::SWITCH_ON);
		sprite->setTexture(textureOn);
	}
	else
	{
		if (withSfx && isToggleSfx) soundManager->play(soundManager->sfx::SWITCH_OFF);
		sprite->setTexture(texture);
	}
}

void Button::onClick()
{
	callback();

	SoundManager* soundManager = SoundManager::get();
	if (!isToggleSfx) soundManager->play(soundManager->sfx::SWITCH_FAIL);
	if (!isToggle) return;

	switchToggleState(true);
	
	setColor(sf::Color(120, 120, 120));
}