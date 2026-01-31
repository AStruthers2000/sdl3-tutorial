#include "engine/main_app.h"

#include <SDL3/SDL.h>

namespace AuroraEngine
{

MainApp::MainApp(Vector2<int> windowSize, std::string_view windowTitle)
    : m_windowSize(windowSize)
    , m_windowTitle(windowTitle)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to initialize SDL3!",
                                 nullptr);
        m_last_error = Error::SDLInitFailed;
    }
}

MainApp::~MainApp()
{
    cleanup();
}

MainApp::Error MainApp::initialize()
{
    SDL_Window* window = SDL_CreateWindow(
        m_windowTitle.data(),
        m_windowSize.x,
        m_windowSize.y,
        0);

    if (!window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to create window!",
                                 nullptr);
        m_last_error = Error::WindowCreationFailed;
    }
    
    return m_last_error;
}

MainApp::Error MainApp::run()
{
    if (m_last_error != Error::None)
    {
        return m_last_error;
    }

    // main game loop
    bool running = true;
    while (running)
    {
        SDL_Event event{ 0 };
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }
        SDL_Delay(16); // Simulate ~60 FPS
    }

    return m_last_error;
}

MainApp::Error MainApp::cleanup()
{
    SDL_Quit();
    return Error::None;
}

} // namespace AuroraEngine
