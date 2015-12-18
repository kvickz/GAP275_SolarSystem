//Game.h

#ifndef GAME_H
#define GAME_H

#include "Vector3.h"
#include <vector>
#include <queue>

#include <cml/cml.h>

class Renderer;
class AssetManager;
class InputManager;
class GameObject;
class Time;
class Mesh;
class Material;

typedef unsigned int GLuint;
typedef int GLint;

//class RenderComponent;

class Game
{
private:
    bool m_running;

    std::vector<GameObject*> m_gameObjects;
    std::queue<GameObject*> m_gameObjectsToDelete;
    GameObject* m_pCamera;

    Renderer* m_pRenderer;
    AssetManager* m_pAssetManager;
    InputManager* m_pInputManager;
    Time* m_pTime;

    GameObject* m_pPointLight;

public:
    Game();
    ~Game();

    void Init();
    int Update();
    void Shutdown();

    GameObject* GetCameraObject() { return m_pCamera; }
    int GetDeltaTime();
    unsigned long GetElapsedTime();

    GameObject* GetPointLight() { return m_pPointLight; }

private:
    void UpdateGameLogic();
    void CreateGameObjects();
    void UpdateGameObjects();
    void RemoveGameObject(GameObject* pGameObject);
    void DeleteQueuedObjects();

    GameObject* CreateEmptyObject();
    GameObject* CreatePointLightObject();
    GameObject* CreatePlanet(Vector3 position, GameObject* pParent, float scale, float rotationSpeed, Mesh* pMesh, Material* pMaterial);

    //This is a shutdown function
    void DeleteAllObjects();
};

#endif // !GAME_H