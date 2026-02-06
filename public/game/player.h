////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "engine/game_object.h"

namespace TestGame
{

class Player : public AuroraEngine::GameObject
{
public:
    Player() : GameObject()
    {}

    Player(AuroraEngine::TransformComponent const& transform) : GameObject(transform)
    {}

    ~Player()
    {
        cleanup();
    }

    void initialize(AuroraEngine::SDLState const& sdl_state);
    void update(float delta_time) override;
    void render(SDL_Renderer* renderer) override;
    void cleanup() override;

private:
    SDL_Texture* m_texture;
};

} // namespace TestGame

#endif // GAME_PLAYER_H
