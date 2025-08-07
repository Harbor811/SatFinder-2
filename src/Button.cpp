#include "Button.h"

Button::Button(const sf::Vector2f& pos, std::function<void()> onClick)
{
	sprite = new sf::Sprite();
	callback = onClick;

	sprite->setTexture(texture);
	sprite->setPosition(pos);

	isToggle = false;
}

Button::Button(const sf::Vector2f& pos, const std::string textureFile, std::function<void()> callback)
{
	sprite = new sf::Sprite();
	this->callback = callback;

	this->textureFile = textureFile;
	texture.loadFromFile(textureFile);
	sprite->setTexture(texture);
	sprite->setPosition(pos);
	sprite->setColor(sf::Color(120, 120, 120));
	isToggle = false;
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

sf::Vector2f Button::getPosition() const
{
	return sprite->getPosition();
}

bool Button::getIsToggle() const
{
	return isToggle;
}

std::string Button::getToggledTextureFile() const
{
	return textureOnFile;
}

std::string Button::getTextureFile() const
{
	return textureFile;
}

// Called when you want to make a button a toggle, supply On Image
void Button::makeToggle(std::string onImage, bool isToggleSfx)
{
	if (onImage == "none") 
	{ 
		textureOnFile = textureFile;
		textureOn = texture; 
	}
	else
	{
		textureOnFile = onImage;
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

void Button::setTexture(const std::string& file)
{
	textureFile = file;
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

void Button::setToggleState(bool newState, bool withSfx)
{
	if (!isToggle) { std::cout << "SwitchToggleState called on non-toggle button!" << std::endl; return; }
	SoundManager* soundManager = SoundManager::get();

	toggled = newState;
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
	SoundManager* soundManager = SoundManager::get();
	if (!isToggleSfx) soundManager->play(soundManager->sfx::SWITCH_FAIL);
	if (!isToggle)
	{
		callback();
		return;
	}

	callback();

	setToggleState(!toggled, true);
	
	setColor(sf::Color(120, 120, 120));
}