#include "engine/engine.h"

#include "engine/world.h"

namespace AuroraEngine
{

//--------------------------------------------------------------------------------------------------
AuroraEngine::AuroraEngine(glm::vec2 window_size, glm::vec2 logical_size, std::string_view window_title)
    : m_window_title(window_title)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to initialize SDL3!",
                                 nullptr);
    }

    m_sdl_state.window_size = window_size;
    m_sdl_state.logical_size = logical_size;
}

//--------------------------------------------------------------------------------------------------
AuroraEngine::~AuroraEngine()
{
    m_managed_world->cleanup();
    m_managed_world.reset();
    cleanup();
}

//--------------------------------------------------------------------------------------------------
void AuroraEngine::initialize(std::unique_ptr<GameWorld> managed_world)
{
    if (managed_world == nullptr)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Can't initialize engine with invalid world; please create a valid world instance.",
                                 nullptr);
        return;
    }

    m_managed_world = std::move(managed_world);

    // Create the SDL window
    m_sdl_state.window = SDL_CreateWindow(m_window_title.data(),
                                          m_sdl_state.window_size.x,
                                          m_sdl_state.window_size.y,
                                          SDL_WINDOW_RESIZABLE);
    if (!m_sdl_state.window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to create window!",
                                 nullptr);
        return;
    }

    // Create the SDL renderer
    m_sdl_state.renderer = SDL_CreateRenderer(m_sdl_state.window, nullptr);
    if (!m_sdl_state.renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to create renderer!",
                                 nullptr);
        return;
    }

    SDL_SetRenderLogicalPresentation(m_sdl_state.renderer,
                                     m_sdl_state.logical_size.x,
                                     m_sdl_state.logical_size.y,
                                     SDL_RendererLogicalPresentation::SDL_LOGICAL_PRESENTATION_LETTERBOX);

    m_managed_world->initialize(m_sdl_state);
    
    m_initialized = true;
}

//--------------------------------------------------------------------------------------------------
void AuroraEngine::run()
{
    if (!m_initialized)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Can't run AuroraEngine; must call initialize() first",
                                 nullptr);
        return;
    }

    // Probably come up with some more official way to track whether the engine is running or not
    bool running = true;

    // Using a variable time step method
    std::uint64_t previous_frame_time = SDL_GetTicks();
    while (running)
    {
        std::uint64_t frame_start_time = SDL_GetTicks();
        float delta_time = static_cast<float>(frame_start_time - previous_frame_time) / 1'000.f;

        running = process_input();
        update(delta_time);
        render();

        previous_frame_time = frame_start_time;
    }
}

//--------------------------------------------------------------------------------------------------
bool AuroraEngine::process_input()
{
    SDL_Event event{ 0 };
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EventType::SDL_EVENT_QUIT:
                return false;
            case SDL_EventType::SDL_EVENT_WINDOW_RESIZED:
                m_sdl_state.window_size.x = event.window.data1;
                m_sdl_state.window_size.y = event.window.data2;
                break;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
void AuroraEngine::update(float delta_time)
{
    m_managed_world->update(delta_time);
}

//--------------------------------------------------------------------------------------------------
void AuroraEngine::render()
{
    SDL_SetRenderDrawColor(m_sdl_state.renderer, 20, 10, 30, 255);
    SDL_RenderClear(m_sdl_state.renderer);

    // Perform all rendering
    m_managed_world->render(m_sdl_state.renderer);

    // Swap buffers and present
    SDL_RenderPresent(m_sdl_state.renderer);
}

//--------------------------------------------------------------------------------------------------
void AuroraEngine::cleanup()
{
    m_managed_world->cleanup();

    // Destroy renderer before destroying window
    if (m_sdl_state.renderer)
    {
        SDL_DestroyRenderer(m_sdl_state.renderer);
        m_sdl_state.renderer = nullptr;
    }

    // Destroy window
    if (m_sdl_state.window)
    {
        SDL_DestroyWindow(m_sdl_state.window);
        m_sdl_state.window = nullptr;
    }

    // Quit SDL
    SDL_Quit();
}

} // namespace AuroraEngine
