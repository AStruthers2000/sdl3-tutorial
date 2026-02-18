////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "engine/engine_types.h"
#include "engine/subsystems/input_subsystem.h"

#include <memory>
#include <string_view>

namespace AuroraEngine
{

class GameWorld;

class AuroraEngine
{
public:
    AuroraEngine(glm::vec2 window_size, glm::vec2 logical_size, std::string_view window_title);
    ~AuroraEngine();

    void initialize(std::unique_ptr<GameWorld> managed_world);
    void run();

    InputSubsystem& get_input_subsystem() { return m_input_subsystem; }

    static AuroraEngine& get();

private:
    bool process_input();
    void update(float delta_time);
    void render();

    void cleanup();

    SDLState m_sdl_state{};
    std::string_view m_window_title = "";
    bool m_initialized = false;
    std::unique_ptr<GameWorld> m_managed_world;
    InputSubsystem m_input_subsystem;
};

} // namespace AuroraEngine

#endif // ENGINE_ENGINE_H
