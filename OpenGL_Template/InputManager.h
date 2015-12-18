//InputManager.h

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Vector2.h"

class Game;
class Command;
class GameObject;

class InputManager
{
private:
    Game* m_pGame;

    struct KeyboardCommands
    {
        Command* axis_XYZ;
        Command* axis_XYZ_rotation;

        ~KeyboardCommands();
    };

    struct ControllerCommands
    {
        Command* axis_LeftStickX;

        ~ControllerCommands();
    };

    KeyboardCommands* m_pKeyboardCommands;
    ControllerCommands* m_pControllerCommands;

    //TODO: I haven't thought this through completely, probably not necessary
    bool m_WKey_Pressed = false;
    bool m_SKey_Pressed = false;
    bool m_AKey_Pressed = false;
    bool m_DKey_Pressed = false;
    bool m_QKey_Pressed = false;
    bool m_EKey_Pressed = false;
    bool m_RKey_Pressed = false;
    bool m_FKey_Pressed = false;

    //****************************//
    //      Mouse variables       //
    //****************************//
    //Mouse Buttons
    bool m_leftMouse_Pressed = false;
    bool m_rightMouse_Pressed = false;

    bool m_mouseMovedThisUpdate;

    //Input Sensitivity
    const int k_mouseSensitivity;
    bool m_mouseXInverted;
    bool m_mouseYInverted;

    Vector2_i m_currentMousePosition;
    Vector2_i m_previousMousePosition;
    //Last clicked position
    Vector2_i m_lastClickedMousePosition_Left;
    Vector2_i m_lastClickedMousePosition_Right;
    //Offset from last clicked position
    Vector2_i m_mouseDragOffset_Left;
    Vector2_i m_mouseDragOffset_Right;
    //****************************//

public:
    InputManager(Game* pGame);
    ~InputManager();

    int HandleEvents();

    void AddPlayer(unsigned int playerIndex, GameObject* pGameObject);

private:
    void ApplyKeyboardInput();
    void ApplyMouseInput();
    void ResetUpdateVariables();
};

#endif // !INPUTMANAGER_H
