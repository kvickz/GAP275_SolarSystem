//PointLightComponent.h

#include "PointLightComponent.h"

#include "Constants.h"

#include "GameObject.h"
#include "TransformComponent.h"

PointLightComponent::PointLightComponent(GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(k_pointLightComponentID, pGameObject, pTransform)
    , m_attenuation(0)
    , m_intensity(0)
{
    m_pTransform->SetPosition(0.f, -50.f, 0.f);
}

PointLightComponent::~PointLightComponent()
{

}
