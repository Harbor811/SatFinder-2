#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "../external/json.hpp"
#include "RoutePlanner.h" // For iostream & fstream
#include <cstdlib>		// for std::getenv
#include <filesystem>
#include <iostream>

using json = nlohmann::json;

static class SettingsManager
{
private:
	static std::filesystem::path settingsFile;

	static std::filesystem::path getSettingsPath();
	static json settings;

public:
	static bool soundEnabled;
	static bool instantCalc;
	
	static void init();
	static void save();
};

#endif