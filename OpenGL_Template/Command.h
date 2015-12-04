//Command.h

#ifndef COMMAND_H
#define COMMAND_H

class GameObject;

typedef int AxisValue;

class Command
{
protected:
    GameObject* const m_pGameObject;

public:
    Command(GameObject* const pGameObject);

    virtual void Execute() = 0;
    virtual void SetAxisXValue(AxisValue value) {}
    virtual void SetAxisYValue(AxisValue value) {}
    virtual void SetAxisZValue(AxisValue value) {}
    virtual void ResetAxisValues();
};

#endif // !COMMAND_H
