//RenderComponent.h

#include "GameObjectComponent.h"

class RenderComponent : public GameObjectComponent
{
    //mesh
    //material/shader

public:
    RenderComponent(ComponentID id);
    ~RenderComponent();

    virtual void Update() override;
};