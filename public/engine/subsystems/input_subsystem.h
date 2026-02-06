////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_SUBSYSTEMS_INPUT_SUBSYSTEM_H
#define ENGINE_SUBSYSTEMS_INPUT_SUBSYSTEM_H

#include "engine/engine_types.h"

#include <functional>
#include <unordered_map>

namespace AuroraEngine
{
enum class EInputProcessedState
{
    ConsumeInput,
    DoNotConsumeInput,
};

using InputCallback = std::function<EInputProcessedState(InputValue const&)>;

constexpr std::uint8_t DEFAULT_CALLBACK_PRIORITY = 100U;

class InputSubsystem
{
public:
    bool register_callback(KeyPress const& keypress, InputCallback callback);
    bool register_callback(KeyPress const& keypress, InputCallback callback, std::uint8_t priority);

    void handle_event(KeyPress const& keypress);

private:
    using PrioritizedCallback = std::pair<std::uint8_t, InputCallback>;
    std::unordered_map<KeyPress, std::vector<PrioritizedCallback>> m_callbacks;
};

} // namespace AuroraEngine

#endif //ENGINE_SUBSYSTEMS_INPUT_SUBSYSTEM_H
