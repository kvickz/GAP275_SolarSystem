//CameraMoveCommand.cpp

#include "CameraMoveCommand.h"

#include "CameraComponent.h"

CameraMoveCommand::CameraMoveCommand(GameObject* const pGameObject, CameraComponent* const pCameraComponent)
    :Command(pGameObject)
    , m_pCameraComponent(pCameraComponent)
{
    //
}

CameraMoveCommand::~CameraMoveCommand()
{
    //
}

void CameraMoveCommand::Execute()
{
    //Returns value from -1.0 to 1.0
    float valueX = (float)m_pLeftStickX / (float)k_maxStickInputValue;
    float valueY = (float)m_pKeyboardUpAxis / (float)k_maxStickInputValue;
    float valueZ = (float)m_pLeftStickY / (float)k_maxStickInputValue; 

    //Ignoring dead zone inputs

    //Left stick X
    if (m_pLeftStickX < k_deadZoneRange && m_pLeftStickX > -k_deadZoneRange)
        valueX = 0;

    //Y axis, Not sure if it will have a dead zone or how/if it will be handled by controller
    if (m_pKeyboardUpAxis < k_deadZoneRange && m_pKeyboardUpAxis > -k_deadZoneRange)
        valueY = 0;

    //Left stick Y
    if (m_pLeftStickY < k_deadZoneRange && m_pLeftStickY > -k_deadZoneRange)
        valueZ = 0;    

    //Calling the component
    m_pCameraComponent->SetMovementScaleX(valueX);
    m_pCameraComponent->SetMovementScaleY(valueY);
    m_pCameraComponent->SetMovementScaleZ(valueZ);
}