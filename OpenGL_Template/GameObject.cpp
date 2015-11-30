//GameObject.cpp

#include "GameObject.h"

#include "Game.h"
#include "GameObjectComponent.h"
#include "TransformComponent.h"

#include "Constants.h"

unsigned int GameObject::s_objectInstanceCounter = 0;

GameObject::GameObject(const ObjectID id, Game* pGameInstance)
    :k_objectID(id)
    , m_pGame(pGameInstance)
    , m_deleteMe(false)
{
    m_objectInstanceID = s_objectInstanceCounter;
    ++s_objectInstanceCounter;
}

GameObject::~GameObject()
{
    DestroyObject();
}

//-------------------------------------------------------------------------------------- -
//  Game Object Initialization Function
//      -Calls Init() on all game object's components
//-------------------------------------------------------------------------------------- -
void GameObject::Init()
{
    //Initialize all components
    auto iterator = m_components.begin();

    while (iterator != m_components.end())
    {
        iterator->second->Init();
        ++iterator;
    }
}

//-------------------------------------------------------------------------------------- -
//  Destroy Object Function
//      -Actually removes the object.
//      -Calls delete on all components within the object
//-------------------------------------------------------------------------------------- -
void GameObject::DestroyObject()
{
    //Cleanup all components
    auto iterator = m_components.begin();

    while (iterator != m_components.end())
    {
        delete iterator->second;
        iterator->second = nullptr;

        auto tempIterator = iterator;
        ++iterator;

        m_components.erase(tempIterator);
    }

    m_pTransform = nullptr;
    m_pGame = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  GameObject Update Function
//      -Handles any runtime logic for individual game objects.
//-------------------------------------------------------------------------------------- -
void GameObject::Update()
{
    UpdateComponents();
}

//-------------------------------------------------------------------------------------- -
//  Update Components Function
//      -Creates an iterator that loops through all the gameObject's
//       components and calls update on each one.
//-------------------------------------------------------------------------------------- -
void GameObject::UpdateComponents()
{
    auto iterator = m_components.begin();

    while (iterator != m_components.end())
    {
        iterator->second->Update();
        ++iterator;
    }
}

//-------------------------------------------------------------------------------------- -
//  Add Component Function
//      -Adds a component to game object given a pointer to the component.
//      -Only meant to be called by the factory that creates this object.
//-------------------------------------------------------------------------------------- -
void GameObject::AddComponent(const ComponentID key, GameObjectComponent* pNewComponent)
{
    
    //If the new component is a transform component, add it to m_pTransform
    if (key == k_transformComponentID)
    {
        //Only allow 1 transform
        if (m_pTransform)
            return;
     
        m_pTransform = static_cast<TransformComponent*>(pNewComponent);
    }
    
    //Otherwise add as usual
    m_components.emplace(key, pNewComponent);
}

//-------------------------------------------------------------------------------------- -
//  Remove Component Function
//      -Removes component
//      -Not tested but might have issues with duplicate components.
//      -TODO: Test for duplicate functionality errors
//-------------------------------------------------------------------------------------- -
void GameObject::RemoveComponent(const ComponentID key)
{
    //TODO: Mark for deletion? probably needs to happen
    m_components.erase(key);
}

//-------------------------------------------------------------------------------------- -
//  Delete Object Function
//      -This function marks an object for deletion, at the end
//       of the game's update loop it will delete all objects that
//       are marked for deletion.
//-------------------------------------------------------------------------------------- -
void GameObject::DeleteObject()
{
    MarkForRemoval();
}