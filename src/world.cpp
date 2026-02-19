#include "engine/world.h"

#include "engine/engine.h"
#include "engine/game_object.h"

#include <algorithm>

namespace AuroraEngine
{

//--------------------------------------------------------------------------------------------------
GameWorld::GameWorld(Engine& owning_engine)
    : m_engine(owning_engine)
{

}

//--------------------------------------------------------------------------------------------------
GameWorld::~GameWorld() = default;

//--------------------------------------------------------------------------------------------------
void GameWorld::initialize()
{
    for (auto& [_, game_object] : m_game_objects)
    {
        game_object->initialize();
    }
}

//--------------------------------------------------------------------------------------------------
void GameWorld::cleanup()
{
    for (auto& [_, game_object] : m_game_objects)
    {
        if (game_object)
        {
            game_object->cleanup();
        }
    }
}

//--------------------------------------------------------------------------------------------------
bool GameWorld::add_object(std::unique_ptr<GameObject> object, int update_order)
{
    // Find the first element with a higher update order
    auto it = std::find_if(m_game_objects.begin(), m_game_objects.end(),
        [update_order](const auto& pair) {
            return pair.first > update_order;
        });
    
    // Insert before that element (or at the end if not found)
    m_game_objects.insert(it, std::make_pair(update_order, std::move(object)));
    
    return true;
}

//--------------------------------------------------------------------------------------------------
void GameWorld::update(float delta_time)
{
    for (auto& [_, game_object] : m_game_objects)
    {
        game_object->update(delta_time);
    }
}

//--------------------------------------------------------------------------------------------------
void GameWorld::render(SDL_Renderer* renderer)
{
    for (auto& [_, game_object] : m_game_objects)
    {
        game_object->render(renderer);
    }
}

} // namespace AuroraEngine
