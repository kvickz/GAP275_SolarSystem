//BoostCommand.cpp

#include "BoostCommand.h"

#include "CameraComponent.h"

BoostCommand::BoostCommand(GameObject* pGameObject, CameraComponent* pCameraComponent)
    :Command(pGameObject)
    , m_pCameraComponent(pCameraComponent)
{
    //
}

BoostCommand::~BoostCommand()
{
    //
}

void BoostCommand::Execute()
{
    m_pCameraComponent->Boost();
}