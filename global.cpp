/* The generic variables and functions to be used in the entire program.
 * This is meant to define global variables and functions that require
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

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include "global.h"

//Initialize SDL, along with the window that SDL will be using
bool init_window(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int x, int y, int w, int h, Uint32 flags)
{
    bool success = true;

    //Attempt to initialize SDL. If this fails, a reason will be given, and the program will not continue
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0)
    {
        printf("SDL failed to initialize. Code: %s\n", SDL_GetError());
        success = false;
    }
    //Attempt to initialize SDL_TTF. If this fails, a reason will be given, and the program will not continue
    else if (TTF_Init() < 0)
    {
        printf("SDL_TTF failed to initialize. Code: %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        //Creates the window for the program
        window = SDL_CreateWindow(title, x, y, w, h, flags);

        //Loads gamepad mappings from gamecontrollerdb.txt. This information was used from https://github.com/gabomdq/SDL_GameControllerDB
        int maps = SDL_GameControllerAddMappingsFromRW(SDL_RWFromFile("gamecontrollerdb.txt", "rb"), 1);

        //Debug line, shows how many mappings were discovered. If this is different than expected, check above line
        printf("%d\n", maps);

        //If the window failed to create, a reason will be given, and the program will not continue
        if(window == NULL)
        {
            printf("SDL could not create the window. Code: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Attempts to create the renderer. If this fails, a reason will be given, and the program will not continue
            if(!init_Renderer(renderer, window))
            {
                printf("Renderer could not be initialized. See above this line for details.\n");
                success = false;
            }
        }
    }

    return success;
}

//Function to initialize the renderer
bool init_Renderer(SDL_Renderer*& renderer, SDL_Window* window)
{
    bool success = true;

    //Renderer modes
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //If renderer could not be created, a reason will be given, and the program will not continue
    if(renderer == NULL)
    {
        printf("Renderer could not be created. Code: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Sets basic draw colors
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        //Sets flag for the program so it knows the images used will be .png
        int imgflags = IMG_INIT_PNG;

        //Attempts to initialize SDL_IMG. If this fails, a reason will be given and the program will not continue
        if(!(IMG_Init(imgflags) & imgflags))
           {
               printf("PNG image could not be initialized. Code: %s\n", IMG_GetError());
               success = false;
           }
    }

    return success;
}

//Function to load all media to be used in this program. As the program is small, dynamic allocation is not preferred
bool loadMedia(const char* files[], SDL_Texture* textures[], SDL_Renderer* renderer, TTF_Font*& font)
{
    bool success = true;

    //Opens TrueType font to be used.
    font = TTF_OpenFont("ASENINE.ttf", 28);

    //If the font cannot be loaded, a reason will be given, and the program will not continue
    if(font == NULL)
    {
        printf("Unable to open %s. Code: %s\n", "ASENINE.ttf", TTF_GetError());
        success = false;
    }
    else
    {
        //For loop that loads all images into the program. Takes input defined in global.h
        for(int i = 0; i < BUTTON_TOTAL; i++)
        {
            SDL_Surface* tSurface = NULL;
            //Attempt to create the surface from the filename provided in main.cpp
            tSurface = IMG_Load(files[i]);

            //If the any of the surfaces cannot be loaded, a reason will be given, and the program will not continue
            if(tSurface == NULL)
            {
                printf("Could not load surface from file %s. Code: %s", files[i], IMG_GetError());
                success = false;
                break;
            }
            else
            {
                //Creates a texture from the given surface
                textures[i] = SDL_CreateTextureFromSurface(renderer, tSurface);

                //If the any of the textures cannot be created, a reason will be given, and the program will not continue
                if (textures[i] == NULL)
                {
                    printf("Unable to create texture. Code: %s", SDL_GetError());
                    success = false;
                }
                SDL_FreeSurface(tSurface);
            }

        }
    }

    return success;
}

KeepOpen::KeepOpen()
{
    //blank process
}
//Destructor automatically called, prompting user to kill the console window
KeepOpen::~KeepOpen()
{
    std::cout << "Press enter to kill program.\n";
    std::cin.ignore();
}
