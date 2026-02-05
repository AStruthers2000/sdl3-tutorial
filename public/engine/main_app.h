////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief The main application class for the Aurora Engine.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_MAIN_APP_H
#define ENGINE_MAIN_APP_H

#include "engine/game_object.h"

#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string_view>
#include <vector>

namespace AuroraEngine
{

/// @brief Holds SDL related state.
struct SDLState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    glm::vec2 window_size{};
    glm::vec2 logical_size{};
    const bool* keyboard_state = nullptr;
    // std::vector<SDL_Texture*> loaded_textures;
};

struct Resources
{
    constexpr static int ANIM_PLAYER_IDLE = 0;

    std::vector<Animation> player_animations;
    std::vector<SDL_Texture*> textures;
    SDL_Texture* idle_texture = nullptr;

    SDL_Texture* load_texture(SDL_Renderer* renderer, std::string_view file_path)
    {
        SDL_Texture* tex = IMG_LoadTexture(renderer, file_path.data());

        if (tex)
        {
            SDL_SetTextureScaleMode(tex, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
            textures.push_back(tex);
        }

        return tex;
    }

    void load(SDLState& sdl_state)
    {
        player_animations.resize(5);
        player_animations[ANIM_PLAYER_IDLE] = Animation(4, 0.4f);

        idle_texture = load_texture(sdl_state.renderer, "data/GraveRobber_idle.png");
    }

    void unload()
    {
        for (SDL_Texture* tex : textures)
        {
            SDL_DestroyTexture(tex);
        }
        textures.clear();
    }
};

/// @brief The main application class for the Aurora Engine.
class MainApp
{
public:
    /// @brief Possible error states for MainApp.
    enum class Error : std::uint8_t
    {
        None,
        SDLInitFailed,
        WindowCreationFailed,
        RendererCreationFailed,
        SDLDestroyFailed,
    };

    /// @brief Constructs the main application with the specified window size and title.
    /// @param windowSize The size of the application window.
    /// @param windowTitle The title of the application window.
    MainApp(glm::vec2 windowSize, glm::vec2 logicalSize, std::string_view windowTitle);

    /// @brief Destructor for MainApp. Cleans up resources and quits SDL safely.
    ~MainApp();

    /// @brief Initializes the main application, creating the window and renderer.
    /// @return An Error enum indicating success or failure of initialization.
    Error initialize();

    /// @brief  Runs the main application loop.
    /// @return An Error enum indicating success or failure of the run loop.
    Error run();

    /// @brief Retrieves the last error that occurred in the application.
    /// @return An Error enum indicating the last error state.
    Error check_error() const { return m_last_error; }

private:
    void handle_events(bool& running, float delta_time, glm::vec2& player_position, bool& flip_horizontal);
    void render_frame(glm::vec2 player_position, bool flip_horizontal);

    /// @brief Cleans up SDL resources and shuts down SDL.
    /// @return An Error enum indicating success or failure of cleanup.
    Error cleanup();

    /// @brief Holds the SDL state for the application.
    SDLState m_sdl_state{};

    /// @brief Manages game resources such as textures and animations.
    Resources m_resources{};

    // /// @brief The size of the application window.
    // Vector2<int> m_windowSize;

    /// @brief The title of the application window.
    std::string_view m_windowTitle;

    /// @brief The last error that occurred in the application.
    Error m_last_error = Error::None;
};

} // namespace AuroraEngine

#endif // ENGINE_MAIN_APP_H
