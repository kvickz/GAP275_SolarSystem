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
    float valueX = (float)m_xAxis / (float)k_maxStickInputValue;
    float valueY = (float)m_yAxis / (float)k_maxStickInputValue;
    float valueZ = (float)m_zAxis / (float)k_maxStickInputValue;

    //Ignoring dead zone inputs

    //Left stick X
    if (m_xAxis < k_deadZoneRange && m_xAxis > -k_deadZoneRange)
        valueX = 0;

    //Y axis, Not sure if it will have a dead zone or how/if it will be handled by controller
    if (m_yAxis < k_deadZoneRange && m_yAxis > -k_deadZoneRange)
        valueY = 0;

    //Left stick Y
    if (m_zAxis < k_deadZoneRange && m_zAxis > -k_deadZoneRange)
        valueZ = 0;    

    //Calling the component
    /*
    m_pCameraComponent->SetMovementScaleX(valueX);
    m_pCameraComponent->SetMovementScaleY(valueY);
    m_pCameraComponent->SetMovementScaleZ(valueZ);
    */

    m_pCameraComponent->MoveRight(valueX);
    m_pCameraComponent->MoveUp(valueY);
    m_pCameraComponent->MoveForward(-valueZ);
}

void CameraMoveCommand::ResetAxisValues()
{
    m_xAxis = 0;
    m_yAxis = 0;
    m_zAxis = 0;
}