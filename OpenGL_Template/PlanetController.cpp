//PlanetController.h

#include "PlanetController.h"

#include "Constants.h"
#include <cml/cml.h>

#include "GameObject.h"
#include "TransformComponent.h"

PlanetController::PlanetController(GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(k_planetComponentID, pGameObject, pTransform)
{

}

PlanetController::~PlanetController()
{

}

void PlanetController::Update()
{
    if (m_pOrbitee)
    {
        //Rotate about parent
        m_pOrbitee->GetTransformComponent()->Rotate(0, m_rotationSpeed, 0);
    }
}

void PlanetController::SetOrbitee(GameObject* pGameObject)
{
    //Set parent
    m_pOrbitee = pGameObject;
    m_pTransform->SetParent(pGameObject->GetTransformComponent());
}

void PlanetController::SetRotationSpeed(float value)
{
    m_rotationSpeed = value;
}