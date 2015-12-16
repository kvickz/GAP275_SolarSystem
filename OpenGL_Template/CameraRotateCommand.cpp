//CameraRotateCommand.cpp

#include "CameraRotateCommand.h"

#include "CameraComponent.h"

CameraRotateCommand::CameraRotateCommand(GameObject* pGameObject, CameraComponent* pCameraComponent)
    :Command(pGameObject)
    , m_pCameraComponent(pCameraComponent)
{
    //
}

CameraRotateCommand::~CameraRotateCommand()
{
    m_pCameraComponent = nullptr;
}

void CameraRotateCommand::Execute()
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

    m_pCameraComponent->Pitch(valueX);
    m_pCameraComponent->Yaw(valueY);
    m_pCameraComponent->Roll(valueZ);
}

void CameraRotateCommand::ResetAxisValues()
{
    m_xAxis = 0;
    m_yAxis = 0;
    m_zAxis = 0;
}