#include "engine/game_object.h"

namespace AuroraEngine
{

//--------------------------------------------------------------------------------------------------
GameObject::GameObject()
    : m_transform({0.f, 0.f}, {0.f, 0.f}, {0.f, 0.f}, 0.f, {1.f, 1.f})
{
}

//--------------------------------------------------------------------------------------------------
GameObject::GameObject(TransformComponent const& initial_transform)
    : m_transform(initial_transform)
{
}

} // namespace AuroraEngine
