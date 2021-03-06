//GameObjectComponent.h

#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H

typedef unsigned int ComponentID;

class GameObject;
class TransformComponent;

class GameObjectComponent
{
private:
    bool m_active;
    ComponentID m_componentID;

protected:
    GameObject* m_pGameObject;
    TransformComponent* m_pTransform;

public:
    GameObjectComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform);
    virtual ~GameObjectComponent() {};

    virtual void Init() {};
    virtual void Update() {};
    virtual void Destroy() {};

    TransformComponent* GetTransform() { return m_pTransform; }

    ComponentID GetComponentID() { return m_componentID; }
	GameObject* GetGameObject() { return m_pGameObject; }
};

#endif // !GAMEOBJECTCOMPONENT_H

