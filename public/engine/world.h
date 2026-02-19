////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_GAMEWORLD_H
#define ENGINE_GAMEWORLD_H

#include "engine/engine_types.h"

#include <SDL3/SDL.h>

#include <list>
#include <memory>
#include <utility>

namespace AuroraEngine
{

class Engine;
class GameObject;

class GameWorld
{
public:
    GameWorld(Engine& owning_engine);
    ~GameWorld();

    void initialize();
    void cleanup();

    Engine& get_engine() { return m_engine; }
    bool add_object(std::unique_ptr<GameObject> object, int update_order);

    void update(float delta_time);
    void render(SDL_Renderer* renderer);

private:
    Engine& m_engine;

    std::list<std::pair<int, std::unique_ptr<GameObject>>> m_game_objects;
};

} // namespace AuroraEngine

#endif // ENGINE_GAMEWORLD_H
