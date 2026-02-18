////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Common type definitions for the Aurora Engine.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_ENGINE_TYPES_H
#define ENGINE_ENGINE_TYPES_H

#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <limits>
#include <optional>
#include <string>
#include <type_traits>

namespace AuroraEngine
{

struct SDLState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    glm::vec2 window_size{};
    glm::vec2 logical_size{};
};

class InputAction
{
public:
    enum class ETriggerCondition
    {
        None,
        FireOnPress,
        FireOnRelease,
        FireAfterDuration,
    };

    InputAction(SDL_Scancode key_code, bool fire_when_key_is_pressed)
        : m_key_code(key_code)
        , m_fire_when_key_pressed(fire_when_key_is_pressed)
    {
        if (m_key_code != SDL_Scancode::SDL_SCANCODE_UNKNOWN)
        {
            m_trigger = m_fire_when_key_pressed ? ETriggerCondition::FireOnPress : ETriggerCondition::FireOnRelease;
        }
    }

    InputAction(SDL_Scancode key_code, float fire_after_duration)
        : m_key_code(key_code)
        , m_held_duration(fire_after_duration)
    {
        if (m_key_code != SDL_Scancode::SDL_SCANCODE_UNKNOWN)
        {
            m_trigger = ETriggerCondition::FireAfterDuration;
        }
    }

    ETriggerCondition get_trigger() const
    {
        return m_trigger;
    }

    SDL_Scancode get_key_code() const
    {
        return m_key_code;
    }

    float get_held_duration() const
    {
        return m_held_duration;
    }

private:
    ETriggerCondition m_trigger = ETriggerCondition::None;
    SDL_Scancode m_key_code = SDL_Scancode::SDL_SCANCODE_UNKNOWN;
    bool m_fire_when_key_pressed = true;
    float m_held_duration = -1.f;
};

enum class EInputProcessedState
{
    ConsumeInput,
    DoNotConsumeInput,
};

struct InputActionArgs
{
    EInputProcessedState input_consume_state;
    std::uint8_t callback_priority;
    bool repeat_after_initial_trigger;
};

class InputAxis
{
public:
    struct Axis
    {
        SDL_Scancode positive;
        SDL_Scancode negative;
    };

    explicit InputAxis(Axis const& x_axis, std::optional<Axis> y_axis = std::nullopt)
    {
        m_axes[0] = x_axis;
        m_axes[1] = y_axis.value_or(Axis{SDL_Scancode::SDL_SCANCODE_UNKNOWN, SDL_Scancode::SDL_SCANCODE_UNKNOWN});
    }

    bool update_axis(bool const* keyboard_state)
    {
        m_axis_state[0] = keyboard_state[m_axes[0].positive];
        m_axis_state[1] = keyboard_state[m_axes[0].negative];
        m_axis_state[2] = keyboard_state[m_axes[1].positive];
        m_axis_state[3] = keyboard_state[m_axes[1].negative];

        return m_axis_state != glm::vec4{0, 0, 0, 0};
    }

    glm::vec4 const& get_internal_state() const { return m_axis_state; }

private:
    Axis m_axes[2];
    glm::vec4 m_axis_state{};
};

} // namespace AuroraEngine

#endif // ENGINE_ENGINE_TYPES_H
