#include "engine/subsystems/input_subsystem.h"

namespace AuroraEngine
{

//--------------------------------------------------------------------------------------------------
bool InputSubsystem::register_callback(KeyPress const& keypress, InputCallback callback)
{
    return register_callback(keypress, std::move(callback), DEFAULT_CALLBACK_PRIORITY);
}

//--------------------------------------------------------------------------------------------------
bool InputSubsystem::register_callback(KeyPress const& keypress, InputCallback callback, std::uint8_t priority)
{
    if (m_callbacks.contains(keypress))
    {
        auto& callbacks_vec = m_callbacks[keypress];
        auto it = std::find_if(callbacks_vec.begin(), callbacks_vec.end(),
            [priority](auto const& pair)
            {
                return pair.first > priority;
            });

        m_callbacks[keypress].insert(it, std::make_pair(priority, std::move(callback)));
    }
    else
    {
        m_callbacks[keypress].emplace_back(priority, std::move(callback));
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
void InputSubsystem::handle_event(KeyPress const& keypress)
{
    if (m_callbacks.contains(keypress))
    {
        for (auto const& [priority, callback] : m_callbacks[keypress])
        {
            EInputProcessedState input_state = callback(InputValue{});
            if (input_state == EInputProcessedState::ConsumeInput)
            {
                break;
            }
        }
    }
}

} // namespace AuroraEngine
