#include "SettingsManager.h"

std::filesystem::path SettingsManager::settingsFile;
json SettingsManager::settings;
bool SettingsManager::soundEnabled;
bool SettingsManager::instantCalc;

// For storing settings in APPDATA
std::filesystem::path SettingsManager::getSettingsPath()
{
	char* buffer = nullptr;
	size_t size = 0;
	_dupenv_s(&buffer, &size, "LOCALAPPDATA");

	std::filesystem::path settingsPath;
	if (buffer) {
		settingsPath = std::filesystem::path(buffer) / "SatFinder2" / "settings.json";
		free(buffer); // remember to free it!
	}
	else {
		// fallback or error handling
		settingsPath = "settings/settings.json";
	}

	return settingsPath;
}

void SettingsManager::init()
{
	settingsFile = getSettingsPath();

	// Create parent dir if missing
	std::filesystem::create_directories(settingsFile.parent_path());

	// Load settings to "settings"
	if (std::filesystem::exists(settingsFile))
	{	
		std::cout << "Found settings.json!!!!! here: " << settingsFile << std::endl;
		std::ifstream in(settingsFile);
		in >> settings;
		in.close();
	}
	else 
	{	
		std::cout << "Failed to find settings, creating new settings.json..." << std::endl;
		// We gotta make one with default values
		settings["audio"]["soundEnabled"] = true;
		settings["routePlanner"]["instant"] = false;

		std::ofstream out(settingsFile);
		out << settings.dump(2);
		out.close();
		std::cout << "Made settings file at: " << settingsFile << std::endl;
	}
	
	soundEnabled = settings["audio"]["soundEnabled"];
	instantCalc = settings["routePlanner"]["instant"];
}

void SettingsManager::save()
{
	settings["audio"]["soundEnabled"] = soundEnabled;
	settings["routePlanner"]["instant"] = instantCalc;

	std::ofstream out(settingsFile);
	out << settings.dump(2);
	out.close();
}