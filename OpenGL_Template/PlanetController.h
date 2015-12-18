//PlanetController.h

#ifndef PLANETCONTROLLER_H
#define PLANETCONTROLLER_H

#include "GameObjectComponent.h"

class GameObject;
class TransformComponent;

class PlanetController : public GameObjectComponent
{
private:
    GameObject* m_pOrbitee;

    float m_rotationSpeed;

public:
    PlanetController(GameObject* pGameObject, TransformComponent* pTransform);
    ~PlanetController();

    virtual void Update() override;

    void SetRotationSpeed(float value);
    void SetOrbitee(GameObject* pGameObject);
};

#endif // !PLANETCONTROLLER_H