//InputManager.cpp

#include "InputManager.h"

#include "Game.h"
#include "GameObject.h"
#include "Constants.h"

#include "CameraMoveCommand.h"

#include "TransformComponent.h"

#include <SDL.h>

//-------------------------------------------------------------------------------------- -
//  Input Manager Constructor
//-------------------------------------------------------------------------------------- -
InputManager::InputManager(Game* pGame)
    :m_pGame(pGame)
{
    m_pKeyboardCommands = new KeyboardCommands();
    m_pControllerCommands = new ControllerCommands();
}

//-------------------------------------------------------------------------------------- -
//  Input Manager Destructor
//-------------------------------------------------------------------------------------- -
InputManager::~InputManager()
{
    m_pGame = nullptr;

    delete m_pKeyboardCommands;
    m_pKeyboardCommands = nullptr;

    delete m_pControllerCommands;
    m_pControllerCommands = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Keyboard Commands Destructor
//      -Cleans up Keyboard Command Objects
//-------------------------------------------------------------------------------------- -
InputManager::KeyboardCommands::~KeyboardCommands()
{
    delete axis_XYZ;
}

//-------------------------------------------------------------------------------------- -
//  Controller Commands Destructor
//      -Cleans up Controller Command Objects
//-------------------------------------------------------------------------------------- -
InputManager::ControllerCommands::~ControllerCommands()
{
    if (!axis_LeftStickX)
    {
        delete axis_LeftStickX;
    }
}

//-------------------------------------------------------------------------------------- -
//  Add Player Function
//      -Adds a user control to a gameobject if it has the appropriate component
//      -Currently only singleplayer supported
//      -Only working component right now is CameraComponent
//-------------------------------------------------------------------------------------- -
void InputManager::AddPlayer(unsigned int playerIndex, GameObject* pGameObject)
{
    //[???] Why doesn't this work with a static_cast like in my GameObject::GetComponent?
    CameraComponent* pCamComponent = pGameObject->GetComponentReinterpret<CameraComponent>(k_cameraComponentID);
    m_pKeyboardCommands->axis_XYZ = new CameraMoveCommand(pGameObject, pCamComponent);
}

//-------------------------------------------------------------------------------------- -
//  Handle Events Function
//      -Encapsulates the handling of events
//      -Returns 0 or FALSE for quitting
//-------------------------------------------------------------------------------------- -

int InputManager::HandleEvents()
{
    ResetUpdateVariables();

    SDL_Event appEvent;
    while (SDL_PollEvent(&appEvent))
    {
        //-------------------------
        // WINDOW EVENT HANDLING
        //-------------------------
        if (appEvent.type == SDL_QUIT || appEvent.key.keysym.sym == SDLK_ESCAPE)
            return 0;   //QUIT

        //-------------------------
        // KEY HANDLING
        //-------------------------
        //KEY DOWN EVENTS
        if (appEvent.type == SDL_KEYDOWN)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {
                m_WKey_Pressed = true;
            }

            //S key
            if (appEvent.key.keysym.sym == SDLK_s)
            {
                m_SKey_Pressed = true;
            }

            //A key
            if (appEvent.key.keysym.sym == SDLK_a)
            {
                m_AKey_Pressed = true;
            }

            //D key
            if (appEvent.key.keysym.sym == SDLK_d)
            {
                m_DKey_Pressed = true;
            }

            //Q key
            if (appEvent.key.keysym.sym == SDLK_q)
            {
                m_QKey_Pressed = true;
            }

            //E key
            if (appEvent.key.keysym.sym == SDLK_e)
            {
                m_EKey_Pressed = true;
            }
        }

        //KEY UP EVENTS
        if (appEvent.type == SDL_KEYUP)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {
                m_WKey_Pressed = false;
            }

            //S key
            if (appEvent.key.keysym.sym == SDLK_s)
            {
                m_SKey_Pressed = false;
            }

            //A key
            if (appEvent.key.keysym.sym == SDLK_a)
            {
                m_AKey_Pressed = false;
            }

            //D key
            if (appEvent.key.keysym.sym == SDLK_d)
            {
                m_DKey_Pressed = false;
            }

            //Q key
            if (appEvent.key.keysym.sym == SDLK_q)
            {
                m_QKey_Pressed = false;
            }

            //E key
            if (appEvent.key.keysym.sym == SDLK_e)
            {
                m_EKey_Pressed = false;
            }
        }
        //-------------------------
        // END OF KEY HANDLING
        //-------------------------
    }

    //Applies held down key logic
    ApplyKeyboardInput();

    return 1;   //SUCCESS
}

//-------------------------------------------------------------------------------------- -
//  Apply Keyboard Input
//      -This applies the logic from held down keys
//-------------------------------------------------------------------------------------- -
void InputManager::ApplyKeyboardInput()
{
    // A KEY
    if (m_AKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ->SetAxisXValue(-k_maxIntValue);
    }

    // D KEY
    if (m_DKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ->SetAxisXValue(k_maxIntValue);
    }

    // Q KEY
    if (m_QKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ->SetAxisYValue(-k_maxIntValue);
    }

    // E KEY
    if (m_EKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ->SetAxisYValue(k_maxIntValue);
    }

    // W KEY
    if (m_WKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ->SetAxisZValue(-k_maxIntValue);
    }

    // S KEY
    if (m_SKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ->SetAxisZValue(k_maxIntValue);
    }

    m_pKeyboardCommands->axis_XYZ->Execute();
}

//-------------------------------------------------------------------------------------- -
//  Reset Update Variables
//      -This will reset anything that needs to be reset at the beginning of each
//       game loop update.
//      -An example of this would be resetting keyboard axis to zero
//-------------------------------------------------------------------------------------- -
void InputManager::ResetUpdateVariables()
{
    //Default keyboard axis to zero
    m_pKeyboardCommands->axis_XYZ->SetAxisXValue(0);
    m_pKeyboardCommands->axis_XYZ->SetAxisYValue(0);
    m_pKeyboardCommands->axis_XYZ->SetAxisZValue(0);
}