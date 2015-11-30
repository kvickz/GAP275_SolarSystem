//Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <queue>

#include <cml/cml.h>

class Renderer;
class InputManager;
class GameObject;

typedef unsigned int GLuint;
typedef int GLint;

class RenderComponent;

class Game
{
private:
    unsigned int m_deltaTime;
    unsigned int m_elapsed;
    bool m_running;

    std::vector<GameObject*> m_gameObjects;
    std::queue<GameObject*> m_gameObjectsToDelete;
    GameObject* m_pCamera;

    Renderer* m_pRenderer;
    InputManager* m_pInputManager;

public:
    Game();
    ~Game();

    void Init();
    int Update();
    void Shutdown();

    GameObject* GetCameraObject() { return m_pCamera; }

private:
    void UpdateGameLogic();
    void CreateGameObjects();
    void UpdateGameObjects();
    void RemoveGameObject(GameObject* pGameObject);
    void DeleteQueuedObjects();

    //This is a shutdown function
    void DeleteAllObjects();
};

#endif // !GAME_H