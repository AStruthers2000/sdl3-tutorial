#include "engine/main_app.h"

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
    m_sdl_state.window = SDL_CreateWindow(
        m_windowTitle.data(),
        m_windowSize.x,
        m_windowSize.y,
        0);

    if (!m_sdl_state.window)
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
        std::int64_t start_time = 0;
        SDL_GetCurrentTime(&start_time);

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
        
        SDL_DelayPrecise(6'900'000); // Approx ~144 FPS

        std::int64_t end_time = 0;
        SDL_GetCurrentTime(&end_time);
        printf("Frame Time: %f ns\n", 1.0 / (static_cast<double>(end_time - start_time) / 1'000'000'000.0));
    }

    return m_last_error;
}

MainApp::Error MainApp::cleanup()
{
    if (m_sdl_state.window)
    {
        SDL_DestroyWindow(m_sdl_state.window);
        m_sdl_state.window = nullptr;
    }
    SDL_Quit();
    return Error::None;
}

} // namespace AuroraEngine
