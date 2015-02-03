/* The generic variables and functions to be used in the entire program.
 * This is meant to declare global variables and functions that require
 * other libraries and variables used elsewhere in the program.
 *
 * Project Name: SDL_Game_Input
 * Author:       Jake Moses
 *
 * Purpose: This project is meant to test gamepad input using the SDL
 * suite. Parts of this may be used to ignore XInput for DirectX projects
 * without need of using the RawInput library. SDL can be found at https://www.libsdl.org
 *
 * Dependencies: SDL.dll
 *               SDL_ttf.dll
 *               SDL_img.dll
 */


#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

// Defines for numeric constants used throughout the program
#define BUTTON_DEFAULT  0
#define BUTTON_1        1
#define BUTTON_2        2
#define BUTTON_3        3
#define BUTTON_4        4
#define BUTTON_5        5
#define BUTTON_6        6
#define BUTTON_7        7
#define BUTTON_8        8
#define BUTTON_9        9
#define BUTTON_10       10
#define BUTTON_11       11
#define BUTTON_12       12
#define BUTTON_13       13
#define BUTTON_TOTAL    14

//Initialization for the SDL window. Also initializes SDL in general
bool init_window(SDL_Window*&, SDL_Renderer*&, const char*, int, int, int, int, Uint32);
//Initialization of the SDL surface Renderer. Requires an uninitialized renderer variable
bool init_Renderer(SDL_Renderer*&, SDL_Window*);
//Loads all media needed for the project
bool loadMedia(const char*[], SDL_Texture*[], SDL_Renderer*, TTF_Font*& font);

//Class to keep the window open after running to keep polling for input
class KeepOpen
{
public:
    KeepOpen();
    ~KeepOpen();
};



#endif // GLOBAL_H_INCLUDED
