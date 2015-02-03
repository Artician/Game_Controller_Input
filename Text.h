/* Abstraction layer for the SDL_ttf library. Each instance of this creates a dynamically
 * resized text box that will serve to display information on screen. In this instance
 * information about the joystick axes
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

#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

//Class for overlay text to be painted on screen
class Overlay
{
public:
    Overlay();
    ~Overlay();

    //Creates a new surface from text given
    void createFromText(const char*, SDL_Color, TTF_Font*, SDL_Renderer*);
    //Destroys previous surface to prevent repeat initialization issues
    void free();

    //Sets properties for the text displayed, i.e. color, blending, and alpha
    void setColor(Uint8, Uint8, Uint8);
    void setBlendMode(SDL_BlendMode);
    void SetAlpha(Uint8);

    //Renders text on screen
    void render(int, int, SDL_Renderer*, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Get functions used for positioning of the text box
    int getWidth();
    int getHeight();

private:
    SDL_Texture* oTexture;

    int width;
    int height;

};

#endif // TEXT_H_INCLUDED
