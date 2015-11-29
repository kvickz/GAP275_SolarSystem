//GameObject.h

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_map>

class GameObjectComponent;
class TransformComponent;

typedef unsigned int ComponentID;
typedef unsigned int ObjectInstanceID;
typedef unsigned int ObjectID;

class GameObject
{
    typedef std::unordered_map<ComponentID, GameObjectComponent*> GameObjectComponents;

private:
    //This var tracks how many objects have ever been created and
    //assigns the current number to the most recent instance then iterates
    //in order to create a GUID for every gameobject instance.
    static unsigned int s_objectInstanceCounter;
    ObjectInstanceID m_objectInstanceID;
    const ObjectID k_objectID;

    GameObjectComponents m_components;

    bool m_deleteMe;

public:
    GameObject(ObjectID id);
    ~GameObject();

    void Update();
    void DeleteObject();
    bool IsReadyToDelete() { return m_deleteMe; }

    void AddComponent(ComponentID key, GameObjectComponent* pNewComponent);
    void RemoveComponent(ComponentID key);

    TransformComponent* GetTransformComponent();

private:
    void DestroyObject();
    void UpdateComponents();
    void MarkForRemoval() { m_deleteMe = true; }
};

#endif // !GAMEOBJECT_H
