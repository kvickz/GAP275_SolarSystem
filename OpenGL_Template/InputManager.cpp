//InputManager.cpp

#include "InputManager.h"

#include "Game.h"

#include <SDL.h>

InputManager::InputManager(Game* pGame)
    :m_pGame(pGame)
{
    //
}

InputManager::~InputManager()
{
    m_pGame = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Handle Events Function
//      -Encapsulates the handling of events
//      -Returns 0 or FALSE for quitting
//-------------------------------------------------------------------------------------- -

//TODO: Refactor the input, command pattern
#include "GameObject.h"
#include "TransformComponent.h"

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
                m_pGame->GetCameraObject()->GetTransformComponent()->Translate(0, 0, -1.f);
            }

            //S key
            if (appEvent.key.keysym.sym == SDLK_s)
            {
                m_pGame->GetCameraObject()->GetTransformComponent()->Translate(0, 0, 1.f);
            }

            //A key
            if (appEvent.key.keysym.sym == SDLK_a)
            {
                m_pGame->GetCameraObject()->GetTransformComponent()->Translate(-1.f, 0, 0);
            }

            //D key
            if (appEvent.key.keysym.sym == SDLK_d)
            {
                m_pGame->GetCameraObject()->GetTransformComponent()->Translate(1.f, 0, 0);
            }

            //Q key
            if (appEvent.key.keysym.sym == SDLK_q)
            {
                m_pGame->GetCameraObject()->GetTransformComponent()->Translate(0, -1.f, 0);
            }

            //E key
            if (appEvent.key.keysym.sym == SDLK_e)
            {
                m_pGame->GetCameraObject()->GetTransformComponent()->Translate(0, 1.f, 0);
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