//InputManager.cpp

#include "InputManager.h"

#include <SDL.h>

//-------------------------------------------------------------------------------------- -
//  Handle Events Function
//      -Encapsulates the handling of events
//      -Returns 0 or FALSE for quitting
//-------------------------------------------------------------------------------------- -
int InputManager::HandleEvents()
{
    SDL_Event appEvent;
    while (SDL_PollEvent(&appEvent))
    {
        //-------------------------
        // WINDOW EVENT HANDLING
        //-------------------------
        if (appEvent.type == SDL_QUIT || appEvent.key.keysym.sym == SDLK_ESCAPE)
            return 0;   //QUIT

        //-------------------------
        //KEY HANDLING
        //-------------------------

        //KEY DOWN EVENTS
        if (appEvent.type == SDL_KEYDOWN)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {

            }

            //W key
            if (appEvent.key.keysym.sym == SDLK_s)
            {

            }

            if (appEvent.key.keysym.sym == SDLK_a)
            {

            }

            if (appEvent.key.keysym.sym == SDLK_d)
            {

            }
        }

        //KEY UP EVENTS
        if (appEvent.type == SDL_KEYUP)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {

            }

            //W key
            if (appEvent.key.keysym.sym == SDLK_s)
            {

            }

            if (appEvent.key.keysym.sym == SDLK_a)
            {

            }

            if (appEvent.key.keysym.sym == SDLK_d)
            {

            }
        }
    }

    return 1;   //SUCCESS
}