////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_SUBSYSTEMS_INPUT_SUBSYSTEM_H
#define ENGINE_SUBSYSTEMS_INPUT_SUBSYSTEM_H

#include "engine/engine_types.h"
#include "engine/time_keeper.h"

#include <array>
#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>
#include <set>
#include <string>

namespace AuroraEngine
{

using InputCallback = std::function<void()>;

constexpr std::uint8_t DEFAULT_CALLBACK_PRIORITY = 100U;

class InputSubsystem
{
public:
    InputSubsystem() = default;
    ~InputSubsystem() = default;

    void register_callback(InputAction const& input_action, InputCallback callback, std::optional<InputActionArgs> args = std::nullopt);

    bool test();

private:
    struct InputActionCallback
    {
        InputAction input_action;
        InputCallback callback;
        InputActionArgs args;
        bool triggered = false;
    };

    enum class EKeyState
    {
        Depressed,
        Pressed,
        Held,
        Released,
    };

    struct KeyState
    {
        EKeyState key_state = EKeyState::Depressed;
        std::uint64_t pressed_frame = 0;
        std::uint64_t current_frame = 0;

        float get_held_duration() const
        {
            return time_delta<TIME_UNITS>(pressed_frame, current_frame);
        }

        std::string to_string() const
        {
            std::string msg = "KeyState{";
            std::string state_str = "";
            switch (key_state)
            {
                case EKeyState::Depressed:
                    state_str = "Depressed";
                    break;
                case EKeyState::Pressed:
                    state_str = "Pressed";
                    break;
                case EKeyState::Held:
                    state_str = "Held";
                    break;
                case EKeyState::Released:
                    state_str = "Released";
                    break;
                default:
                    state_str = "Invalid";
                    break;
            }
            msg += ".key_state = EKeyState::" + state_str +
                 ", .pressed_frame = " + std::to_string(pressed_frame) +
                 ", .current_frame = " + std::to_string(current_frame) +
                 ", .held_duration = " + std::to_string(get_held_duration());
            msg += "}\n";
            return msg;
        }
    };

    bool is_action_triggered(KeyState const& key_state, InputActionCallback const& action) const
    {
        bool triggered = false;

        // Trigger on press
        if (action.input_action.get_trigger() == InputAction::ETriggerCondition::FireOnPress &&
            key_state.key_state == EKeyState::Pressed)
        {
            triggered = true;
        }
        // Trigger on release
        else if (action.input_action.get_trigger() == InputAction::ETriggerCondition::FireOnRelease &&
                 key_state.key_state == EKeyState::Released)
        {
            triggered = true;
        }
        // Trigger after duration
        else if (action.input_action.get_trigger() == InputAction::ETriggerCondition::FireAfterDuration &&
                 ((!action.triggered || action.args.repeat_after_initial_trigger) &&
                 key_state.get_held_duration() >= action.input_action.get_held_duration()))
        {
            triggered = true;
        }
        else
        {
            triggered = false;
        }

        return triggered;
    }

    void update_cached_keyboard_map();
    void update_keyboard_state();

    std::set<SDL_Scancode> m_keys_we_care_about{};
    std::unordered_map<SDL_Scancode, KeyState> m_keyboard_state{};
    std::unordered_map<SDL_Scancode, std::vector<InputActionCallback>> m_callbacks{};
    bool m_recalculate_cache = false;
    void call_event_callbacks();
};

} // namespace AuroraEngine

#endif //ENGINE_SUBSYSTEMS_INPUT_SUBSYSTEM_H
