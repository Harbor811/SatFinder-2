# > CHANGELOG

## [v0.3.3] - 2025-08-13

### ADDED:

- Recalc button to RoutePlanned screen, to calculate the same route again

### CHANGED:

- RoutePlanner best route calculation now uses Simulated Annealing method
	- Will not crash
	- Non-deterministic results
- ZAP sound effect is now a priority sound so it won't get cut off



## [v0.3.2] - 2025-08-12

### CHANGED:

- RoutePlanner best route calculation now uses Nearest Neighbor method
	- Will not crash, but way more prone to being innaccurate

### FIXED:

- Fixed lines on RoutePlanned screen
	- Now uses my own line creation method instead of VertexArray
	- They're cyan now also
- RoutePlanner keybinds for Enter and Spacebar working as intended again



## [v0.3.1] - 2025-08-08

### ADDED:

- New DrawingManager class now handles all drawings & button interactions

### CHANGED:

- Temporarily removed RoutePlanner keybinds for Spacebar and Enter
	- NOTE: It was hacked together, working on a fix before next patch trust
- Temporarily removed RoutePlanner lines
	- NOTE: SFML vertexArrays don't let you set a thickness, so I'll do my own lines soon trust



## [v0.3] - 2025-08-07

### ADDED:

- New RoutePlanner keybinds
	- Each location has its own respective keybind
	- ENTER key will Plot
	- SPACE key will Reset
- Best Route is now pathed out on the map with small red lines
- Added new Plot and Back button sprites
- Added a back button to every menu besides MAIN

### CHANGED:

- Removed unused Plot button sprite
- Removed debug window refresh button left in by mistake
- Buttons now have ownership variable to prevent nullptr dereferencing

### FIXED:

- Fixed memory leak where game objects weren't freeing up as intented, this is what I get for not using smart pointers...
- Best Route text no longer removes a letter when wrapping



## [v0.2.2] - 2025-08-06

### CHANGED:

- Moved Settings button to the top left corner cus I felt like it
- Moved Icon button to the top right corner for the same reason
- Changed title text to "SatFinder 2" from "SatFinder v2.0"
- Screen graphics are now created from lambda functions to reduce repeated code
- Updated CHANGELOG.md [v0.2.1] to more accurately reflect the changes made
- Removed /settings/ directory that was not being used



## [v0.2.1] - 2025-08-06

### CHANGED:

- Relocated most files, complete list is here:
	- All headers into /include/
	- All source files into /src/
	- json.hpp into /external/
- settings.json is now stored in /AppData/Local/SatFinder2/
	- Not even by choice, I moved settings.json into its own /settings/ folder and for some reason filesystem::exists() refused to acknowledge it
- Removed old SFML-Test.x files that were left over after manually renaming the project.
	- All "SFML-Test" files should be gone now



## [v0.2] - 2025-08-06

### ADDED:

- Added Settings menu - settings stored in 'settings.json'
	- Enable Sound
	- Enable Instant Calc
- Added sound effect for instant calculation

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
