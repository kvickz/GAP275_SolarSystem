//GameObjectFactory.h

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

const unsigned int k_planetID = 1;

class GameObjectFactory
{
public:
    GameObject* CreatePlanet();
};
#endif // !GAMEOBJECTFACTORY_H