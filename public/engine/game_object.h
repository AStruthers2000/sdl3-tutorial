////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "engine/animation.h"
#include "engine/components/transform_component.h"

#include <SDL3/SDL.h>

#include <cstdint>
#include <vector>

namespace AuroraEngine
{
enum class GameObjectType : std::uint8_t
{
    Player,
    Enemy,
    Level,
};

class GameObject
{
public:
    GameObject(GameObjectType type, const TransformComponent& transform)
        : m_type(type), m_transform(transform)
    {
    }
    ~GameObject() = default;


private:
    GameObjectType m_type;
    TransformComponent m_transform;

    // Rendering stuff
    SDL_Texture* m_texture{ nullptr };
    std::vector<Animation> m_animations{};
    int m_current_animation{ -1 };
};

}

#endif // ENGINE_GAME_OBJECT_H
