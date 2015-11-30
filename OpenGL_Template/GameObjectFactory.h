//GameObjectFactory.h

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

#include "Constants.h"

class Game;

class GameObjectFactory
{
public:
    GameObject* CreatePlanet(Game* pGame);
    GameObject* CreateCamera(Game* pGame);
};
#endif // !GAMEOBJECTFACTORY_H