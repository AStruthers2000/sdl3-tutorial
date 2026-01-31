////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief The main application class for the Aurora Engine.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "types.h"

#include <SDL3/SDL.h>
#include <string_view>

namespace AuroraEngine
{

/// @brief Holds SDL related state.
struct SDLState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
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
        SDLDestroyFailed,
    };

    /// @brief Constructs the main application with the specified window size and title.
    /// @param windowSize The size of the application window.
    /// @param windowTitle The title of the application window.
    MainApp(Vector2<int> windowSize, std::string_view windowTitle);

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
    /// @brief Cleans up SDL resources and shuts down SDL.
    /// @return An Error enum indicating success or failure of cleanup.
    Error cleanup();

    /// @brief Holds the SDL state for the application.
    SDLState m_sdl_state{};

    /// @brief The size of the application window.
    Vector2<int> m_windowSize;

    /// @brief The title of the application window.
    std::string_view m_windowTitle;

    /// @brief The last error that occurred in the application.
    Error m_last_error = Error::None;
};

} // namespace AuroraEngine
