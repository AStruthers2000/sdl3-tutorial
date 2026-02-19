////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "engine/world.h"
#include "engine/components/transform_component.h"

#include <SDL3/SDL.h>

#include <cstdint>
#include <vector>

namespace AuroraEngine
{
// enum class GameObjectType : std::uint8_t
// {
//     Player,
//     Enemy,
//     Level,
// };

// class GameWorld;

class GameObject
{
public:
    GameObject(GameWorld& owning_world);
    GameObject(GameWorld& owning_world, TransformComponent const& initial_transform);

    virtual ~GameObject() = default;

    virtual void initialize() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void cleanup() = 0;

    TransformComponent& get_transform() { return m_transform; }
    GameWorld& get_world() { return m_world; }
    
private:
    // GameObjectType m_type;
    GameWorld& m_world;
    TransformComponent m_transform;

    // Rendering stuff
    // SDL_Texture* m_texture{ nullptr };
    // std::vector<Animation> m_animations{};
    // int m_current_animation{ -1 };
};

}

#endif // ENGINE_GAME_OBJECT_H
