#include "game/player.h"
#include "engine/engine.h"

int clamped_add(int x, int y, int low, int high)
{
    int z = x + y;
    if (z < low)
    {
        z = low;
    }

    if (z > high)
    {
        z = high;
    }

    return z;
}

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

    // get_world().get_engine().get_input_subsystem().register_callback(
    //     AuroraEngine::KeyPress{
    //         .key_state = AuroraEngine::EKeyPressedState::KEY_DOWN,
    //         .key_code = SDL_Scancode::SDL_SCANCODE_LEFT
    //     },
    //     [this](AuroraEngine::InputValue const& value)
    //     {
    //         // printf("Player moving left\n");
    //         // this->get_transform().update_position(glm::vec2{-100.f, 0.f});
    //         // printf("Player moving left\n");
    //         this->direction = clamped_add(this->direction, 1, -1, 1);
    //         return AuroraEngine::EInputProcessedState::ConsumeInput;
    //     }
    // );

    // get_world().get_engine().get_input_subsystem().register_callback(
    //     AuroraEngine::KeyPress{
    //         .key_state = AuroraEngine::EKeyPressedState::KEY_DOWN,
    //         .key_code = SDL_Scancode::SDL_SCANCODE_RIGHT
    //     },
    //     [this](AuroraEngine::InputValue const& value)
    //     {
    //         // printf("Player moving left\n");
    //         // this->get_transform().update_position(glm::vec2{100.f, 0.f});
    //         this->direction = clamped_add(this->direction, -1, -1, 1);
    //         return AuroraEngine::EInputProcessedState::ConsumeInput;
    //     }
    // );

    // get_world().get_engine().get_input_subsystem().register_callback(
    //     AuroraEngine::KeyPress{
    //         .key_state = AuroraEngine::EKeyPressedState::KEY_UP,
    //         .key_code = SDL_Scancode::SDL_SCANCODE_LEFT
    //     },
    //     [this](AuroraEngine::InputValue const& value)
    //     {
    //         // printf("Player moving left\n");
    //         // this->get_transform().update_position(glm::vec2{-100.f, 0.f});
    //         // this->direction = clamped_add(this->direction, 1, -1, 1);
    //         this->direction = 0;
    //         return AuroraEngine::EInputProcessedState::ConsumeInput;
    //     }
    // );

    // get_world().get_engine().get_input_subsystem().register_callback(
    //     AuroraEngine::KeyPress{
    //         .key_state = AuroraEngine::EKeyPressedState::KEY_UP,
    //         .key_code = SDL_Scancode::SDL_SCANCODE_RIGHT
    //     },
    //     [this](AuroraEngine::InputValue const& value)
    //     {
    //         // printf("Player moving left\n");
    //         // this->get_transform().update_position(glm::vec2{100.f, 0.f});
    //         // this->direction = clamped_add(this->direction, -1, -1, 1);;
    //         this->direction = 0;
    //         return AuroraEngine::EInputProcessedState::ConsumeInput;
    //     }
    // );

//    get_world().get_engine().get_input_subsystem().register_callback(
//        AuroraEngine::InputAction(SDL_Scancode::SDL_SCANCODE_A, 1.f),
//        [this]()
//        {
//            // this->direction = clamped_add(this->direction, -1, -1, 1);
//            // printf("Held A for 1 second\n");
//            this->direction -= 1;
//        },
//        AuroraEngine::InputActionArgs
//        {
//            .repeat_after_initial_trigger = true,
//        }
//    );
//
//    get_world().get_engine().get_input_subsystem().register_callback(
//        AuroraEngine::InputAction(SDL_Scancode::SDL_SCANCODE_A, false),
//        [this]()
//        {
//            // this->direction = clamped_add(this->direction, -1, -1, 1);
//            // printf("Pressed A\n");
//            this->direction += 1;
//        }
//    );
//
//    get_world().get_engine().get_input_subsystem().register_callback(
//        AuroraEngine::InputAction(SDL_Scancode::SDL_SCANCODE_W, true),
//        [this]()
//        {
//            // this->direction = clamped_add(this->direction, 1, -1, 1);
//            printf("Pressed W\n");
//        }
//    );
//
//    get_world().get_engine().get_input_subsystem().register_callback(
//        AuroraEngine::InputAction(SDL_Scancode::SDL_SCANCODE_D, 0.5f),
//        [this]()
//        {
//            // this->direction = 0;
//            // printf("Held D for 0.5 seconds\n");
//            this->direction += 1;
//        },
//        AuroraEngine::InputActionArgs
//        {
//            .repeat_after_initial_trigger = true,
//        }
//    );
//
//    get_world().get_engine().get_input_subsystem().register_callback(
//        AuroraEngine::InputAction(SDL_Scancode::SDL_SCANCODE_D, false),
//        [this]()
//        {
//            // this->direction = 0;
//            // printf("Held D for 0.5 seconds\n");
//            // this->direction -= 1;
//        }
//    );
//
//    get_world().get_engine().get_input_subsystem().register_callback(
//        AuroraEngine::InputAction(SDL_Scancode::SDL_SCANCODE_S, false),
//        [this]()
//        {
//            // this->direction = 0;
//            printf("Released S\n");
//        }
//    );
//    get_world().get_engine().get_input_subsystem().register_callback(
    AuroraEngine::AuroraEngine::get().get_input_subsystem().register_callback(
            AuroraEngine::InputAxis(AuroraEngine::InputAxis::Axis{SDL_Scancode::SDL_SCANCODE_D, SDL_Scancode::SDL_SCANCODE_A},
                                    AuroraEngine::InputAxis::Axis{SDL_Scancode::SDL_SCANCODE_W, SDL_Scancode::SDL_SCANCODE_S}),
            [this](glm::vec4 axis)
            {
//                printf("[%2.3f, %2.3f, %2.3f, %2.3f]\n", axis[0], axis[1], axis[2], axis[3]);
                float x_in = axis[0] - axis[1];
                float y_in = axis[2] - axis[3];
                move_vec = glm::normalize(glm::vec2{x_in, -y_in});
                if (glm::isnan(move_vec) != glm::vec<2, bool>{false, false})
                {
                    move_vec = glm::vec2{0, 0};
                }
//                move_vec = glm::normalize(axis);
//                get_transform().update_position()
            });
}

//--------------------------------------------------------------------------------------------------
void Player::update(float delta_time)
{
//    if (direction)
//    {
//        float move_delta = direction * speed * delta_time;
//        get_transform().update_position(glm::vec2(move_delta, 0.f));
//        direction = 0;
//    }

//    printf("[%2.3f, %2.3f]\n", get_transform().get_position()[0], get_transform().get_position()[1]);
    if (move_vec != glm::vec2{0, 0})
    {
        glm::vec2 move_delta = move_vec * speed * delta_time;
        get_transform().update_position(move_delta);
        move_vec = {0, 0};
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

//    SDL_RenderTextureRotated(renderer, m_texture, &src, &dst, 0, nullptr, SDL_FlipMode::SDL_FLIP_NONE);
    std::uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &dst);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
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
