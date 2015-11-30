//InputManager.h

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class Game;

class InputManager
{
private:
    Game* m_pGame;

public:
    InputManager(Game* pGame);
    ~InputManager();

    int HandleEvents();
};

#endif // !INPUTMANAGER_H
