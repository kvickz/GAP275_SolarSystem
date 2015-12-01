//CameraMoveCommand.h

#ifndef CAMERAMOVECOMMAND_H
#define CAMERAMOVECOMMAND_H

#include "Command.h"

class CameraComponent;

class CameraMoveCommand : public Command
{
private:
    const AxisValue k_maxStickInputValue = 0x7fffffff;
    const AxisValue k_deadZoneRange = 8000;
    AxisValue m_pLeftStickX;
    AxisValue m_pLeftStickY;
    AxisValue m_pKeyboardUpAxis;

    CameraComponent* const m_pCameraComponent;  //TODO: Figure out case for if component gets deleted

public:
    CameraMoveCommand(GameObject* const pGameObject, CameraComponent* const pCameraComponent);
    ~CameraMoveCommand();

    virtual void Execute() override;
    virtual void SetAxisXValue(AxisValue value) override { m_pLeftStickX = value; }
    virtual void SetAxisYValue(AxisValue value) override { m_pKeyboardUpAxis = value; }
    virtual void SetAxisZValue(AxisValue value) override { m_pLeftStickY = value; }
};

#endif // !MOVECOMMAND_H
