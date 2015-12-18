//PointLightComponent.h

#ifndef POINTLIGHTCOMPONENT_H
#define POINTLIGHTCOMPONENT_H

#include "GameObjectComponent.h"

class PointLightComponent : public GameObjectComponent
{
private:
    float m_attenuation;
    float m_intensity;

public:
    PointLightComponent(GameObject* pGameObject, TransformComponent* pTransform);
    ~PointLightComponent();
};

#endif // !POINTLIGHTCOMPONENT_H
