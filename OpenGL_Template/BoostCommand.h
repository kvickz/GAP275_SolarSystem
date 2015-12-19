//BoostCommand.h

#ifndef BOOSTCOMMAND_H
#define BOOSTCOMMAND_H

#include "Command.h"

class CameraComponent;

class BoostCommand : public Command
{
private:
    CameraComponent* m_pCameraComponent;

public:
    BoostCommand(GameObject* pGameObject, CameraComponent* pCameraComponent);
    ~BoostCommand();

    virtual void Execute() override;
};

#endif // !BOOSTCOMMAND_H
