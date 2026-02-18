#include "engine/subsystems/input_subsystem.h"

namespace AuroraEngine
{

//--------------------------------------------------------------------------------------------------
void InputSubsystem::register_callback(InputAction const& input_action, std::function<void()> callback, std::optional<InputActionArgs> args)
{
    // auto& action_vector = [=](InputAction::ETriggerCondition trigger) -> std::vector<InputActionCallback>&
    // {
    //     static std::vector<InputActionCallback> error_vec{};
    //     switch (trigger)
    //     {
    //     case InputAction::ETriggerCondition::FireOnPress:
    //         return m_trigger_on_press_actions;
    //     case InputAction::ETriggerCondition::FireOnRelease:
    //         return m_trigger_on_release_actions;
    //     case InputAction::ETriggerCondition::FireAfterDuration:
    //         return m_trigger_on_held_actions;
    //     default:
    //         printf("InputSubsystem::register_callback: unrecognized InputAction trigger condition: %d\n", static_cast<std::uint8_t>(trigger));
    //         return error_vec;
    //     }
    // }(input_action.get_trigger());

    // Construct default args if args aren't present
    InputActionArgs action_args = args.value_or(
        InputActionArgs{
            .input_consume_state = EInputProcessedState::DoNotConsumeInput,
            .callback_priority = DEFAULT_CALLBACK_PRIORITY,
            .repeat_after_initial_trigger = false,
        }
    );

    auto [it, insert] = m_keys_we_care_about.emplace(input_action.get_key_code());
    if (insert)
    {
        m_recalculate_cache = true;
    }
    // action_vector.push_back({input_action, std::move(callback), action_args});

    // Eventually this should be inserting the InputActionCallback into the right place according to
    // the priority stored in action_args
    m_callbacks[input_action.get_key_code()].push_back({
        .input_action = input_action,
        .callback = std::move(callback),
        .args = action_args,
    });
}

void InputSubsystem::register_callback(const InputAxis &input_axis, InputCallback_Axis callback)
{
    m_axis_callbacks.push_back({
        .input_axis = input_axis,
        .callback = std::move(callback)
    });
}

void InputSubsystem::update_cached_keyboard_map()
{
    for (auto const& key_code : m_keys_we_care_about)
    {
        // If the key code isn't already in the map
        if (!m_keyboard_state.contains(key_code))
        {
            // Add state to the map
            m_keyboard_state[key_code] = KeyState{};
        }
    }

    // Eventually we will support unregistering callbacks, so we will need a part of the cache
    // function to remove states from the keyboard map
}

//--------------------------------------------------------------------------------------------------
void InputSubsystem::update_keyboard_state(bool const* states, std::uint64_t current_frame)
{
    if (m_recalculate_cache)
    {
        update_cached_keyboard_map();
        m_recalculate_cache = false;
    }

    for (auto const& key_code : m_keys_we_care_about)
    {
        // Get the state of this key. Update this key's state in the keyboard map as follows:
        // * If states[key_code] == true, m_keyboard_state[key_code].key_state transitions with:
        //      - Depressed -> Pressed, pressed_frame = SDL_GetTicks()
        //      - Pressed -> Held
        //      - Held -> current_frame = SDL_GetTicks()
        // * If states[key_code] == false, m_keyboard_state[key_code].key_state transitions with:
        //      - Pressed, Held -> Released
        //      - Released -> Depressed, pressed_frame = 0, current_frame = 0

        KeyState& key_state = m_keyboard_state[key_code];
        if (states[key_code])
        {
            switch (key_state.key_state)
            {
                case EKeyState::Depressed:
                    key_state.key_state = EKeyState::Pressed;
                    key_state.pressed_frame = current_frame;
                    key_state.current_frame = current_frame;
                    break;
                case EKeyState::Pressed:
                    key_state.key_state = EKeyState::Held;
                    key_state.current_frame = current_frame;
                    break;
                case EKeyState::Held:
                    key_state.current_frame = current_frame;
                    break;
                case EKeyState::Released:
                    [[fallthrough]];
                default:
                    break;
            }
        }
        else
        {
            switch (key_state.key_state)
            {
                case EKeyState::Pressed:
                    [[fallthrough]];
                case EKeyState::Held:
                    key_state.key_state = EKeyState::Released;
                    key_state.current_frame = current_frame;
                    break;
                case EKeyState::Released:
                    // Reset key state
                    key_state = KeyState{};
                    for (auto& input_action_callback : m_callbacks[key_code])
                    {
                        input_action_callback.triggered = false;
                    }
                    break;
                case EKeyState::Depressed:
                    [[fallthrough]];
                default:
                    break;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
bool InputSubsystem::test()
{
    SDL_Event event{ 0 };
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EventType::SDL_EVENT_QUIT:
                return false;
        }
    }

    bool const* states = SDL_GetKeyboardState(nullptr);
    std::uint64_t current_frame = get_current_time();

    update_keyboard_state(states, current_frame);
    call_event_callbacks();

    for (auto& input_axis_callback : m_axis_callbacks)
    {
        if (input_axis_callback.input_axis.update_axis(states))
        {
            input_axis_callback.callback(input_axis_callback.input_axis.get_internal_state());
        }
    }

    return true;
}

void InputSubsystem::call_event_callbacks()
{
    for (auto const &key_code: m_keys_we_care_about)
    {
        for (auto &input_action_callback: m_callbacks[key_code])
        {
            if (is_action_triggered(m_keyboard_state[key_code], input_action_callback))
            {
                input_action_callback.triggered = true;
                input_action_callback.callback();
//                if (input_action_callback.args.input_consume_state == EInputProcessedState::ConsumeInput)
//                {
//                    break;
//                }
            }
        }
    }
}

} // namespace AuroraEngine
