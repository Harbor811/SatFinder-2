# > CHANGELOG

## [v0.2.1] - 2025-08-06

### CHANGED:

- Relocated most files, complete list is here:
	- All headers into /include/
	- All .cpp's into /src/
	- json.hpp into /external/
- settings.json is now stored in /AppData/Local/SatFinder2/
	- Not even by choice, I moved settings.json into its own /settings/ folder and for some reason filesystem::exists() refused to acknowledge it

### REMOVED:

- Old SFML-Test.x files that were left over after manually renaming the project.
	- All "SFML-Test" naming conventions should be gone now

## [v0.2] - 2025-08-06

### ADDED:

- Added Settings menu - settings stored in 'settings.json'
	- Enable Sound
	- Enable Instant Calc

### CHANGED:

- Temporarily disabled window resizing
- Updated LOG and MAP graphics
- Hitting [ESC] on RoutePlanned now loads RoutePlanner rather than Main
- Renamed some folders
	- /Assets/ to /assets/
	- /Fonts/ to /fonts/
	- /Sounds/ to /sounds/
	- /Sprites/ to /sprites/
	- /Map/ to /map/
- Switched language standard from C\+\+14 to C\+\+20
	
### FIXED:

- Fixed text not wrapping on RoutePlanned
- Fixed texture memory leak (yikes)

## [v0.1] - 2025-08-06
- Inital Project Creation
