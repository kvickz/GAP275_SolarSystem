//GameObjectFactory.h

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

#include "Constants.h"

class Game;
class Renderer;
class Time;

class GameObjectFactory
{
private:
    Renderer* const k_pRenderer;
    Time* const k_pTime;

public:
    GameObjectFactory(Renderer* const pRenderer, Time* const pTime);

    GameObject* CreatePlanet(Game* pGame);
    GameObject* CreateCamera(Game* pGame);
};
#endif // !GAMEOBJECTFACTORY_H