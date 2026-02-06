#include "game/player.h"

namespace TestGame
{

//--------------------------------------------------------------------------------------------------
void Player::initialize(AuroraEngine::SDLState const& sdl_state)
{
    m_texture = IMG_LoadTexture(sdl_state.renderer, "data/GraveRobber_idle.png");
    if (m_texture)
    {
        SDL_SetTextureScaleMode(m_texture, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
    }
}

//--------------------------------------------------------------------------------------------------
void Player::update(float delta_time)
{

}

//--------------------------------------------------------------------------------------------------
void Player::render(SDL_Renderer* renderer)
{
    SDL_FRect src{
        .x = 0.0f,
        .y = 0.0f,
        .w = 48.0f,
        .h = 48.0f,
    };

    SDL_FRect dst{
        .x = get_transform().get_position().x,
        .y = get_transform().get_position().y,
        .w = src.w,
        .h = src.h,
    };

    SDL_RenderTextureRotated(renderer, m_texture, &src, &dst, 0, nullptr, SDL_FlipMode::SDL_FLIP_NONE);
}

//--------------------------------------------------------------------------------------------------
void Player::cleanup()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

} // namespace TestGame
