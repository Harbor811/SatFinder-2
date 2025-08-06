![image](https://i.imgur.com/3oJh118.png)

## > ABOUT

This program is meant to speed up the process of visiting the servers in [Voices of the Void](https://mrdrnose.itch.io/votv) for those of us who still like to do it manually. All you do is input the locations you want to visit in the Route Planner and hit "Plot," and it'll automatically copy the best route into your clipboard (which you can then paste into your in-game notepad or do whatever you really want with.) This project was made because I wanted to revamp my old SatFinder console project as well as learn the basics of SFML, so I knocked out both birds with the same stone. Also secrets??? Maybe

## > DOWNLOAD

The newest version will be available in the [releases tab](https://github.com/Harbor811/SatFinder-2/releases), alternatively you could build it yourself with Visual Studio 2022 by downloading the source code and linking the SFML dependencies.

## > CHANGELOG

### [v0.2] - 2025-08-06

**ADDED:**

- Added Settings menu - settings stored in 'settings.json'
	- Enable Sound
	- Enable Instant Calc

**CHANGED:**

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
	
**FIXED:**

- Fixed text not wrapping on RoutePlanned
- Fixed texture memory leak (yikes)

### [v0.1] - 2025-08-06
- Inital Project Creation
