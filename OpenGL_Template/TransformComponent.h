//TransformComponent.h

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GameObjectComponent.h"

#include "Vector3.h"

class TransformComponent : public GameObjectComponent
{
private:
    Vector3 m_position;

public:
    TransformComponent();
    ~TransformComponent();
};

#endif // !TRANSFORMCOMPONENT_H
