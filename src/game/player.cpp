#include "game/player.h"
#include "engine/engine.h"

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

    get_world().get_engine().get_input_subsystem().register_callback(
        AuroraEngine::KeyPress{
            .key_state = AuroraEngine::EKeyPressedState::KEY_DOWN,
            .key_code = SDL_Scancode::SDL_SCANCODE_LEFT
        },
        [this](AuroraEngine::InputValue const& value)
        {
            // printf("Player moving left\n");
            // this->get_transform().update_position(glm::vec2{-100.f, 0.f});
            this->direction = -1;
            return AuroraEngine::EInputProcessedState::ConsumeInput;
        }
    );

    get_world().get_engine().get_input_subsystem().register_callback(
        AuroraEngine::KeyPress{
            .key_state = AuroraEngine::EKeyPressedState::KEY_DOWN,
            .key_code = SDL_Scancode::SDL_SCANCODE_RIGHT
        },
        [this](AuroraEngine::InputValue const& value)
        {
            // printf("Player moving left\n");
            // this->get_transform().update_position(glm::vec2{100.f, 0.f});
            this->direction = 1;
            return AuroraEngine::EInputProcessedState::ConsumeInput;
        }
    );

    get_world().get_engine().get_input_subsystem().register_callback(
        AuroraEngine::KeyPress{
            .key_state = AuroraEngine::EKeyPressedState::KEY_UP,
            .key_code = SDL_Scancode::SDL_SCANCODE_LEFT
        },
        [this](AuroraEngine::InputValue const& value)
        {
            // printf("Player moving left\n");
            // this->get_transform().update_position(glm::vec2{-100.f, 0.f});
            this->direction = 0;
            return AuroraEngine::EInputProcessedState::ConsumeInput;
        }
    );

    get_world().get_engine().get_input_subsystem().register_callback(
        AuroraEngine::KeyPress{
            .key_state = AuroraEngine::EKeyPressedState::KEY_UP,
            .key_code = SDL_Scancode::SDL_SCANCODE_RIGHT
        },
        [this](AuroraEngine::InputValue const& value)
        {
            // printf("Player moving left\n");
            // this->get_transform().update_position(glm::vec2{100.f, 0.f});
            this->direction = 0;
            return AuroraEngine::EInputProcessedState::ConsumeInput;
        }
    );
}

//--------------------------------------------------------------------------------------------------
void Player::update(float delta_time)
{
    if (direction)
    {
        float move_delta = direction * speed * delta_time;
        get_transform().update_position(glm::vec2(move_delta, 0.f));
    }
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
