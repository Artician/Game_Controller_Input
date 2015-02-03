SDL_Game_Input

This is a program meant to accept and properly manipulate a screen using the SDL libraries. Specifically it uses SDL, SDL_IMG
and SDL_TTF for various functions. All assets and code created myself with the exception of the Asenine TTF and the gamecontrollerdb.txt. Disclosures for each provided below this document. All code is written in C++. This code is distributed under the GPL 3.0 license, and as such can be distrubuted and used freely, for any commercial and noncommercial projects. Please attribute if the code is useful, but this is not required.

How to use:
Ensure that your gamepad is plugged in. Run the .exe file in the same folder as all of the assets. 

*Important note*
If your controller is not registering, then you must follow the instructions at https://github.com/gabomdq/SDL_GameControllerDB to add an entry to your gamecontrollerdb.txt file.  

For gamecontrollerdb.txt:
This was sourced from https://github.com/gabomdq/SDL_GameControllerDB, which is a community maintained project to create a useable database of controller mappings for use with SDL.

for Asenine.ttf:
This was sourced from 1001fonts.com/asenine-font.html and was created by Apostrophic Labs. 

Known Issues/Bugs:

When using the left and right triggers, the screen will freeze on those inputs until another button is pressed. This is a result of how SDL processes trigger input, and will hopefully be fixed in future, but this will alway be sluggish as it will likely involve a deadzone. 

Required from SDL:

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.