//GameObject.cpp

#include "GameObject.h"
#include "GameObjectComponent.h"

unsigned int GameObject::s_objectInstanceCounter = 0;

GameObject::GameObject(ObjectID id)
    :k_objectID(id)
{
    m_objectInstanceID = s_objectInstanceCounter;
    ++s_objectInstanceCounter;
}

GameObject::~GameObject()
{
    //
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
//  Delete Object Function
//      -This function marks an object for deletion, at the end
//       of the game's update loop it will delete all objects that
//       are marked for deletion.
//-------------------------------------------------------------------------------------- -
void GameObject::DeleteObject()
{
    MarkForRemoval();
}