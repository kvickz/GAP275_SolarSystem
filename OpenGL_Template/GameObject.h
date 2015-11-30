//GameObject.h

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <unordered_map>

class GameObjectComponent;
class TransformComponent;
class Game;

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

    Game* m_pGame;
    GameObjectComponents m_components;
    TransformComponent* m_pTransform;

    bool m_deleteMe;

public:
    GameObject(const ObjectID id, Game* pGameInstance);
    ~GameObject();

    void Init();
    void Update();
    void DeleteObject();
    bool IsReadyToDelete() { return m_deleteMe; }

    void AddComponent(const ComponentID key, GameObjectComponent* pNewComponent);
    void RemoveComponent(const ComponentID key);

    Game* GetGame() { return m_pGame; }

    //----------------------------------------------------------------------------------
    //  Get Component Functions
    //----------------------------------------------------------------------------------
    template<class ComponentType>
    ComponentType* GetComponent(ComponentID id);

    TransformComponent* GetTransformComponent() { return m_pTransform; }
    void SetTransform(TransformComponent* pTransform) { m_pTransform = pTransform; }
    //----------------------------------------------------------------------------------
private:
    void DestroyObject();
    void UpdateComponents();
    void MarkForRemoval() { m_deleteMe = true; }
};

//[???] Is there any way to get this into the cpp file? or is it just how it is with templates
//-------------------------------------------------------------------------------------- -
//  Get Component Function
//      -Generic templated function that returns a casted component.
//-------------------------------------------------------------------------------------- -
template<typename ComponentType>
ComponentType* GameObject::GetComponent(ComponentID id)
{
    return static_cast<ComponentType*>(m_components[id]);
}

#endif // !GAMEOBJECT_H
