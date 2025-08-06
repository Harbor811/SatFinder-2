#include "SettingsManager.h"

json SettingsManager::settings;
bool SettingsManager::soundEnabled;
bool SettingsManager::instantCalc;

void SettingsManager::init()
{
	// Load settings to "settings"
	if (std::filesystem::exists("settings.json"))
	{	
		// Check if settings.json already exists
		std::ifstream in("settings.json");
		in >> settings;
		in.close();
	}
	else 
	{	
		// We gotta make one with default values
		settings["audio"]["soundEnabled"] = true;
		settings["routePlanner"]["instant"] = false;

		std::ofstream out("settings.json");
		out << settings.dump(2);
		out.close();
	}
	
	soundEnabled = settings["audio"]["soundEnabled"];
	instantCalc = settings["routePlanner"]["instant"];
}

void SettingsManager::save()
{
	settings["audio"]["soundEnabled"] = soundEnabled;
	settings["routePlanner"]["instant"] = instantCalc;

	std::ofstream out("settings.json");
	out << settings.dump(2);
	out.close();
}