/* Definitions for functions declared in Text.h
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
#include "Text.h"

Overlay::Overlay()
{
    oTexture = NULL;
    width = 0;
    height = 0;
}

Overlay::~Overlay()
{
    free();
}

void Overlay::createFromText(const char* text, SDL_Color fColor, TTF_Font* font, SDL_Renderer* renderer)
{
    //Before creating the new texture, destroy the old one
    free();

    //Attempt to create surface. If this is unsuccessful, a reason will be given by the program in the console output
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, fColor);

    if(textSurface == NULL)
    {
        printf("Could not create surface from the text. Code: %s", TTF_GetError());
    }
    //If prior process is successful, a texture is created from the created surface
    else
    {
        oTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (oTexture == NULL)
        {
            printf("Could not create texture. Code: %s", SDL_GetError());
        }
        //If prior process is successful, sets width and height variables for the text box
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }
    }
    //Destroys previously created surface
    SDL_FreeSurface(textSurface);
}

//Clears all data used in the class, making it ready for reinitialization
void Overlay::free()
{
    if(oTexture != NULL)
    {
        SDL_DestroyTexture(oTexture);
        oTexture = NULL;
        width = 0;
        height = 0;
    }
}

void Overlay::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(oTexture, r, g, b);
}

void Overlay::SetAlpha(Uint8 a)
{
    SDL_SetTextureAlphaMod(oTexture, a);
}

void Overlay::setBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(oTexture, blendMode);
}

//Renders the text on screen
void Overlay::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE

    SDL_Rect renderQuad = {x, y, width, height};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, oTexture, clip, &renderQuad, angle, center, flip);
}

int Overlay::getWidth()
{
    return width;
}

int Overlay::getHeight()
{
    return height;
}


