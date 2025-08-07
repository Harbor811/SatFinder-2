#ifndef CONSOLE_H
#define CONSOLE_H

#include "Button.h"
#include <vector>
#include <string>

class Console
{
private:
	bool deb = true;

	sf::Text* text;
	std::string curText;
	std::string queuedText;
	unsigned int maxChars;
	unsigned int maxLines;
	float charTime;
	float totalTime = 0.f;

	unsigned int stringLength = 0;
	unsigned int curChar = 0;
	unsigned int curLine = 0;

	std::function<void()> callback = {};

	void addNextChar();

public:
	Console(sf::Text* text, int maxChars, int maxLines, float charTime = 0.05f);
	~Console();

	void update(float deltaTime);
	void setText(std::string newText);
	void addText(std::string newText);
	void setCallback(std::function<void()> callback);
	void clear();
};

#endif