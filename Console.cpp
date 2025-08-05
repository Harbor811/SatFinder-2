#include "Console.h"
#include <iostream>

void Console::addNextChar()
{
	//std::cout << "CUR_CHAR: " << queuedText[0] << " CHAR#: " << std::to_string(curChar) << std::endl;
	curChar++;

	if (queuedText[0] == '\n' || curChar > maxChars)
	{
		curText += "\n";
		curChar = 0;
		curLine++;
	}
	else
	{
		curText += queuedText[0];
	}

	queuedText = queuedText.substr(1, queuedText.size() - 1);
	
	text->setString(curText);
}

Console::Console(sf::Text* text, int maxChars, int maxLines, float charTime)
{
	this->text = text;
	this->maxChars = maxChars;
	this->maxLines = maxLines;
	this->charTime = charTime;

	if (text->getString() != "") { setText(text->getString()); }
}

Console::~Console()
{
}

void Console::update(float deltaTime)
{
	if (stringLength == curText.length()) 
	{ 
		callback();
		delete this;
		return;
	}

	totalTime += deltaTime;

	if (totalTime >= charTime)
	{
		totalTime -= charTime;

		addNextChar();
	}
}

void Console::setText(std::string newText)
{
	stringLength = newText.length();
	queuedText = newText;
}

void Console::addText(std::string newText)
{
	stringLength += newText.length();
	queuedText += "\n" + newText;
}

void Console::setCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void Console::clear()
{
	curText = "";
	queuedText = "";
	text->setString("");

	curChar = 0;
	curLine = 0;
}