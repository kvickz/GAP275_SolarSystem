//Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>

class Renderer;
class GameObject;

class Game
{
private:
    Renderer* m_pRenderer;

    bool m_running;

    std::vector<GameObject*> m_gameObjects;

public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Shutdown();

    //Refactor to renderer
    int HandleEvents();
    void SwapWindow();
};

#endif // !GAME_H