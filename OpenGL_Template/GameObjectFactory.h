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

GameObject* GameObjectFactory::CreatePlanet()
{
    GameObject* pObject = new GameObject(k_planetID);

    //TODO:
    //Add components here!

    return pObject;
}

#endif // !GAMEOBJECTFACTORY_H