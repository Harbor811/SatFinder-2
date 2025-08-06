#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "include/json.hpp"
#include "RoutePlanner.h" // For iostream & fstream
#include <filesystem>
#include <iostream>

using json = nlohmann::json;

static class SettingsManager
{
private:
	static json settings;

public:
	static bool soundEnabled;
	static bool instantCalc;
	
	static void init();
	static void save();
};

#endif