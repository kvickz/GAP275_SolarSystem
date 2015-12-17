//InputManager.cpp

#include "InputManager.h"

#include "Game.h"
#include "GameObject.h"
#include "Constants.h"

#include "CameraMoveCommand.h"
#include "CameraRotateCommand.h"

#include "TransformComponent.h"

#include <SDL.h>

//-------------------------------------------------------------------------------------- -
//  Input Manager Constructor
//-------------------------------------------------------------------------------------- -
InputManager::InputManager(Game* pGame)
    :m_pGame(pGame)
    , k_mouseSensitivity(10000)
    , m_mouseXInverted(false)
    , m_mouseYInverted(false)
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
    delete axis_XYZ_rotation;
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
    m_pKeyboardCommands->axis_XYZ_rotation = new CameraRotateCommand(pGameObject, pCamComponent);
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

            //R key
            if (appEvent.key.keysym.sym == SDLK_r)
            {
                m_RKey_Pressed = true;
            }

            //F key
            if (appEvent.key.keysym.sym == SDLK_f)
            {
                m_FKey_Pressed = true;
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

            //R key
            if (appEvent.key.keysym.sym == SDLK_r)
            {
                m_RKey_Pressed = false;
            }

            //F key
            if (appEvent.key.keysym.sym == SDLK_f)
            {
                m_FKey_Pressed = false;
            }
        }
        //-------------------------
        // END OF KEY HANDLING
        //-------------------------

        //-------------------------
        // MOUSE EVENTS
        //-------------------------

        if (appEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            if (appEvent.button.button == SDL_BUTTON_LEFT)
            {
                //Store the last clicked position for mouse drags
                m_lastClickedMousePosition_Left.x = appEvent.button.x;
                m_lastClickedMousePosition_Left.y = appEvent.button.y;

                m_leftMouse_Pressed = true;
            }
            else if (appEvent.button.button == SDL_BUTTON_RIGHT)
            {
                m_lastClickedMousePosition_Right.x = appEvent.button.x;
                m_lastClickedMousePosition_Right.y = appEvent.button.y;

                m_rightMouse_Pressed = true;
            }
        }

        if (appEvent.type == SDL_MOUSEBUTTONUP)
        {
            if (appEvent.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouse_Pressed = false;
            }
            else if (appEvent.button.button == SDL_BUTTON_RIGHT)
            {
                m_rightMouse_Pressed = false;
            }
        }

        if (appEvent.type == SDL_MOUSEMOTION)
        {
            //Assign previous mouse pos
            m_previousMousePosition.x = m_currentMousePosition.x;
            m_previousMousePosition.y = m_currentMousePosition.y;

            //Gathers mouse x and y
            m_currentMousePosition.x = appEvent.button.x;
            m_currentMousePosition.y = appEvent.button.y;
        }
    }

    //Applies held down key logic
    ApplyKeyboardInput();
    ApplyMouseInput();

    //Execute Command Objects
    m_pKeyboardCommands->axis_XYZ->Execute();
    m_pKeyboardCommands->axis_XYZ_rotation->Execute();

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

    // R KEY
    if (m_RKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ_rotation->SetAxisXValue(k_maxIntValue);
    }

    // F KEY
    if (m_FKey_Pressed)
    {
        m_pKeyboardCommands->axis_XYZ_rotation->SetAxisXValue(-k_maxIntValue);
    }

    
}

//-------------------------------------------------------------------------------------- -
//  Apply Keyboard Input
//      -This applies the logic from held down keys
//-------------------------------------------------------------------------------------- -
#include "Utility.h"

void InputManager::ApplyMouseInput()
{
    if (m_leftMouse_Pressed)
    {
        //
    }

    if (m_rightMouse_Pressed)
    {
        //Calculate offset  **This is better for controls that need to be persistent**
        //m_mouseDragOffset_Right.x = m_currentMousePosition.x - m_lastClickedMousePosition_Right.x;
        //m_mouseDragOffset_Right.y = m_currentMousePosition.y - m_lastClickedMousePosition_Right.y;

        //Calculate offset  **This is better for click drag without any continuous movement**
        m_mouseDragOffset_Right.x = m_currentMousePosition.x - m_previousMousePosition.x;
        m_mouseDragOffset_Right.y = m_currentMousePosition.y - m_previousMousePosition.y;

        //Multiply by mouse sensitivity
        int xRotation = -k_mouseSensitivity * m_mouseDragOffset_Right.y;
        int yRotation = -k_mouseSensitivity * m_mouseDragOffset_Right.x;
        
        //Check if user wants inverted controls
        if (m_mouseXInverted)
            yRotation *= -1;

        if (m_mouseYInverted)
            xRotation *= -1;

        //Clamp the rotation value
        Utility::Clamp(xRotation, INT_MIN, INT_MAX);
        Utility::Clamp(yRotation, INT_MIN, INT_MAX);

        //Vertical Rotation
        m_pKeyboardCommands->axis_XYZ_rotation->SetAxisXValue(xRotation);
        
        //Horizontal Rotation
        m_pKeyboardCommands->axis_XYZ_rotation->SetAxisYValue(yRotation);
    }
}

//-------------------------------------------------------------------------------------- -
//  Reset Update Variables
//      -This will reset anything that needs to be reset at the beginning of each
//       game loop update.
//      -An example of this would be resetting keyboard axis to zero
//-------------------------------------------------------------------------------------- -
void InputManager::ResetUpdateVariables()
{
    //Default axes to zero
    m_pKeyboardCommands->axis_XYZ->ResetAxisValues();
    m_pKeyboardCommands->axis_XYZ_rotation->ResetAxisValues();
}