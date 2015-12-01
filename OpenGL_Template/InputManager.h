//InputManager.h

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

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

        ~KeyboardCommands();
    };

    struct ControllerCommands
    {
        Command* axis_LeftStickX;

        ~ControllerCommands();
    };

    KeyboardCommands* m_pKeyboardCommands;
    ControllerCommands* m_pControllerCommands;

    //TODO: I haven't thought this through, probably not necessary
    bool m_WKey_Pressed = false;
    bool m_SKey_Pressed = false;
    bool m_AKey_Pressed = false;
    bool m_DKey_Pressed = false;
    bool m_QKey_Pressed = false;
    bool m_EKey_Pressed = false;

public:
    InputManager(Game* pGame);
    ~InputManager();

    int HandleEvents();

    void AddPlayer(unsigned int playerIndex, GameObject* pGameObject);

private:
    void ApplyKeyboardInput();
    void ResetUpdateVariables();
};

#endif // !INPUTMANAGER_H
