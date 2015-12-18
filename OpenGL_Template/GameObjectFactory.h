//GameObjectFactory.h

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

#include "Constants.h"

class Game;
class Renderer;
class Time;
class GameObjectComponentFactory;

class GameObjectFactory
{
private:
    Renderer* const k_pRenderer;
    Time* const k_pTime;

    GameObjectComponentFactory* m_pComponentFactory;

public:
    GameObjectFactory(Renderer* const pRenderer, Time* const pTime);
    ~GameObjectFactory();

    GameObject* CreateEmptyGameObject(Game* pGame);
    GameObject* CreatePlanet(Game* pGame);
    GameObject* CreateCamera(Game* pGame);
    GameObject* CreatePointLight(Game* pGame);
};
#endif // !GAMEOBJECTFACTORY_H