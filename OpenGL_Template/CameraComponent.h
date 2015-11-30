//CameraComponent.h

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "GameObjectComponent.h"

#include "Constants.h"

class CameraComponent : public GameObjectComponent
{
public:
    CameraComponent(const ComponentID id, GameObject* pGameObject);
    ~CameraComponent();

};

#endif // !CAMERACOMPONENT_H
