//CameraRotateCommand.h

#ifndef CAMERAROTATECOMMAND_H
#define CAMERAROTATECOMMAND_H

#include "Command.h"

class CameraComponent;

class CameraRotateCommand : public Command
{
private:
    const AxisValue k_maxStickInputValue = 0x7fffffff;
    const AxisValue k_deadZoneRange = 8000;
    AxisValue m_xAxis;
    AxisValue m_yAxis;
    AxisValue m_zAxis;

    CameraComponent* m_pCameraComponent;

public:
    CameraRotateCommand(GameObject* pGameObject, CameraComponent* pCameraComponent);
    ~CameraRotateCommand();

    virtual void Execute() override;
    virtual void SetAxisXValue(AxisValue value) override { m_xAxis = value; }
    virtual void SetAxisYValue(AxisValue value) override { m_yAxis = value; }
    virtual void SetAxisZValue(AxisValue value) override { m_zAxis = value; }
    virtual void ResetAxisValues() override;
};

#endif // !CAMERAROTATECOMMAND_H
