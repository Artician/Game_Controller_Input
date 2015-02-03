/* The main program entry point. All variables needed in other files not declared elsewhere are declared here
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
#include <string>
#include <sstream>
#include <stdlib.h>
#include "global.h"
#include "Text.h"

//Screen size
const int SCREENW = 1000;
const int SCREENH = 750;

//String constants
const char* title = "13 Button Controller Test";
const char* xText_1 = "Left X";
const char* xText_2 = "Left Y";
const char* zText_1 = "Right X";
const char* zText_2 = "Right Y";
//Filenames
const char* files[BUTTON_TOTAL] = {"Test raw.png",
                                   "Test 1.png",
                                   "Test 2.png",
                                   "Test 3.png",
                                   "Test 4.png",
                                   "Test 5.png",
                                   "Test 6.png",
                                   "Test 7.png",
                                   "Test 8.png",
                                   "Test 9.png",
                                   "Test 10.png",
                                   "Test 11.png",
                                   "Test 12.png",
                                   "Test 13.png"};

//SDL global variables. These are defined in functions from other files
SDL_Window* window = NULL;
SDL_Renderer* tRenderer = NULL;
SDL_Texture* current = NULL;
SDL_Texture* backbuffer[BUTTON_TOTAL];
TTF_Font* font = NULL;
SDL_Color fColor = {0, 0, 0};
SDL_GameController* controller = NULL;
SDL_Haptic* cHaptic = NULL;

//Created a new to_string function for backwards conpatibility
template <class T>
std::string to_string(T x);
void cleanup();

//Program entry point
int main(int argc, char* argv[])
{
    //8 variables for overlay text
    Overlay* X_Coord         = new Overlay();
    Overlay* X_Text          = new Overlay();
    Overlay* Y_Coord         = new Overlay();
    Overlay* Y_Text          = new Overlay();
    Overlay* Z_Pos_Coord     = new Overlay();
    Overlay* Z_Pos_Text      = new Overlay();
    Overlay* Z_Neg_Coord     = new Overlay();
    Overlay* Z_Neg_Text      = new Overlay();

    //Variables for to_string, kept separate to avoid messing up which goes where
    Sint16 x = 0;
    Sint16 y = 0;
    Sint16 rx = 0;
    Sint16 ry = 0;

    //Return variables for to_string
    std::string x_Str;
    std::string y_Str;
    std::string rx_Str;
    std::string ry_Str;

    //Object to keep console window open
    KeepOpen ko;

    //Initializes window. If this fails, a reason will be given from within the function
    if(!init_window(window, tRenderer, title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN))
    {
        printf("Window could not be initialized. See above for specific errors.\n");
        return 1;
    }
    else
    {
        //Loads media from file name array. If this fails, a reason will be given from within the function
        if(!loadMedia(files, backbuffer, tRenderer, font))
        {
            printf("Unable to load media. See above for specific errors.\n");
        }
        // Creates the static textboxes for labeling joystick output
        else
        {
            X_Text->createFromText(xText_1, fColor, font, tRenderer);
            Y_Text->createFromText(xText_2, fColor, font, tRenderer);
            Z_Pos_Text->createFromText(zText_1, fColor, font, tRenderer);
            Z_Neg_Text->createFromText(zText_2, fColor, font, tRenderer);

            //Workaround for SDL not having a similar function for gamepads
            if(SDL_NumJoysticks() < 1)
            {
                printf("No controllers are connected. Code: %s\n", SDL_GetError());

            }
            else
            {
                //Displays the number of detected, connected controllers and haptic (Force Feedback) devices
                printf("%d: Number of connected controllers\n%d: Number of haptic devices\n", SDL_NumJoysticks(), SDL_NumHaptics());
                //Initializes the controller object
                controller = SDL_GameControllerOpen(0);

                //If controller is not initialized, a code is given, and the program closes
                if (controller == NULL)
                {
                    printf("Error opening controller. Code: %s\n", SDL_GetError());
                    return 2;
                }
            }

            bool done = false;

            //Creates the controller event variable
            SDL_Event e;

            //Sets the default screen
            current = backbuffer[BUTTON_DEFAULT];

            while(!done)
            {
                while(SDL_PollEvent(&e)!= 0)
                {
                    //Generic events for killing the program window
                    if(e.type == SDL_QUIT)
                    {
                       done = true;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            done = true;
                            break;
                        }
                    }
                    //If the event is a movement of the joystick
                    else if(e.type == SDL_CONTROLLERAXISMOTION)
                    {
                        if(e.caxis.which == 0)
                        {
                            switch(e.caxis.axis)
                            {
                                //Each of these case statements takes which input is being detected, creates a string from it, and
                                //initializes the corresponding Overlay object with that value. Deadzones are intentionally omitted
                                //as the purpose of this program is to test raw controller output
                            case SDL_CONTROLLER_AXIS_LEFTX:
                                x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
                                x_Str = to_string(x);
                                X_Coord->createFromText(x_Str.c_str(), fColor, font, tRenderer);
                               // printf("%s = Left X axis report\n", x_Str.c_str());
                                break;

                            case SDL_CONTROLLER_AXIS_LEFTY:
                                y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
                                y_Str = to_string(y);
                                Y_Coord->createFromText(y_Str.c_str(), fColor, font, tRenderer);
                                //printf("%s = Left Y axis report\n", y_Str.c_str());
                                break;

                            case SDL_CONTROLLER_AXIS_RIGHTX:
                                rx = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
                                rx_Str = to_string(rx);
                                Z_Pos_Coord->createFromText(rx_Str.c_str(), fColor, font, tRenderer);
                                //printf("%s = Right X Axis Report\n", rx_Str.c_str());
                                break;

                            case SDL_CONTROLLER_AXIS_RIGHTY:
                                ry = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
                                ry_Str = to_string(ry);
                                Z_Neg_Coord->createFromText(ry_Str.c_str(), fColor, font, tRenderer);
                                //printf("%s = Right Y Axis Report\n", ry_Str.c_str());
                                break;

                            // Source of only known bug at present:
                            // As SDL interprets trigger presses as joystick events, there is no button up event
                            case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                                current = backbuffer[BUTTON_7];
                                break;

                            case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                                current = backbuffer[BUTTON_8];
                                break;


                            default:
                                break;
                            }
                        }
                    }
                    //Detects if a button is pressed. If it is, it changes the image shown on screen
                    else if(e.type == SDL_CONTROLLERBUTTONDOWN)
                    {
                        if(e.cbutton.which == 0)
                        {
                            switch(e.cbutton.button)
                            {
                                case SDL_CONTROLLER_BUTTON_X:
                                    current = backbuffer[BUTTON_1];
                                    break;
                                case SDL_CONTROLLER_BUTTON_A:
                                    current = backbuffer[BUTTON_2];
                                    break;
                                case SDL_CONTROLLER_BUTTON_B:
                                    current = backbuffer[BUTTON_3];
                                    break;
                                case SDL_CONTROLLER_BUTTON_Y:
                                    current = backbuffer[BUTTON_4];
                                    break;
                                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                                    current = backbuffer[BUTTON_5];
                                    break;
                                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                                    current = backbuffer[BUTTON_6];
                                    break;
                                case SDL_CONTROLLER_BUTTON_BACK:
                                    current = backbuffer[BUTTON_9];
                                    break;
                                case SDL_CONTROLLER_BUTTON_START:
                                    current = backbuffer[BUTTON_10];
                                    break;
                                case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                                    current = backbuffer[BUTTON_11];
                                    break;
                                case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                                    current = backbuffer[BUTTON_12];
                                    break;
                                case SDL_CONTROLLER_BUTTON_GUIDE:
                                    current = backbuffer[BUTTON_13];
                                    break;
                                default:
                                    current = backbuffer[BUTTON_DEFAULT];
                                    break;
                            }
                        }
                    }
                    //When the controller button is released, the default screen is loaded
                    else if(e.type == SDL_CONTROLLERBUTTONUP)
                    {
                        current = backbuffer[BUTTON_DEFAULT];
                    }

                }
                //Drawing functions on screen. This uses the Painter's Algorithm
                SDL_RenderClear(tRenderer);
                SDL_RenderCopy(tRenderer, current, NULL, NULL);
                X_Text->render(50, 100, tRenderer);
                //Each Overlay object marked as Coord inherits its position from the static box above it
                X_Coord->render(50, (100 + X_Text->getHeight() + 10), tRenderer);
                Y_Text->render(50, (250), tRenderer);
                Y_Coord->render(50, (250 + Y_Text->getHeight() + 10), tRenderer);
                Z_Pos_Text->render((SCREENW - (Z_Pos_Text->getWidth() + 50)), 100, tRenderer);
                Z_Pos_Coord->render((SCREENW - (Z_Pos_Text->getWidth() + 50)), (100 + Z_Pos_Text->getHeight() + 10), tRenderer);
                Z_Neg_Text->render((SCREENW - (Z_Neg_Text->getWidth() + 50)), 250, tRenderer);
                Z_Neg_Coord->render((SCREENW - (Z_Neg_Text->getWidth() + 50)), (250 + (Z_Neg_Text->getHeight() + 10)), tRenderer);
                //Update the screen
                SDL_RenderPresent(tRenderer);
            }
            //Releases all unreleased objects from memory before ending the program
            cleanup();
        }
    }

    return 0;
}
template <class T>
std::string to_string(T x)
{
    std::ostringstream oss;
    oss << x;
    return oss.str();

}

void cleanup()
{
    for (int i = 0; i < BUTTON_TOTAL; i++)
    {
        SDL_DestroyTexture(backbuffer[i]);
    }
    SDL_DestroyTexture(current);
    SDL_DestroyRenderer(tRenderer);
    SDL_DestroyWindow(window);

    SDL_GameControllerClose(controller);
    SDL_HapticClose(cHaptic);

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
