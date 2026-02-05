////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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

private:
    struct SDLState
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        glm::vec2 window_size{};
        glm::vec2 logical_size{};
    };

    bool process_input();
    void update(float delta_time);
    void render();

    void cleanup();

    SDLState m_sdl_state{};
    std::string_view m_window_title = "";
    bool m_initialized = false;
    std::unique_ptr<GameWorld> m_managed_world;
};

} // namespace AuroraEngine

#endif // ENGINE_ENGINE_H
