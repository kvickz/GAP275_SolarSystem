//TransformComponent.h

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GameObjectComponent.h"

#include "Vector3.h"

class TransformComponent : public GameObjectComponent
{
private:
    Vector3 m_position;
    Vector3 m_eulerRotation;

public:
    TransformComponent(const ComponentID id, GameObject* pGameObject);
    ~TransformComponent();

    virtual void Update() override;

    Vector3 GetPosition() { return m_position; }
    void SetPosition(float x, float y, float z);
    void Translate(float x, float y, float z);
    void SetEulerRotation(float x, float y, float z);
    void Rotate(float x, float y, float z);
};

#endif // !TRANSFORMCOMPONENT_H