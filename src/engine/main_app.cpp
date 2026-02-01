#include "engine/main_app.h"

#include <SDL3_image/SDL_image.h>

namespace AuroraEngine
{

MainApp::MainApp(Vector2<int> windowSize, Vector2<int> logicalSize, std::string_view windowTitle)
    : m_windowTitle(windowTitle)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to initialize SDL3!",
                                 nullptr);
        m_last_error = Error::SDLInitFailed;
    }

    m_sdl_state.window_size = windowSize;
    m_sdl_state.logical_size = logicalSize;
}

MainApp::~MainApp()
{
    cleanup();
}

MainApp::Error MainApp::initialize()
{
    // Create the SDL window
    m_sdl_state.window = SDL_CreateWindow(
        m_windowTitle.data(),
        m_sdl_state.window_size.x,
        m_sdl_state.window_size.y,
        SDL_WINDOW_RESIZABLE);

    if (!m_sdl_state.window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to create window!",
                                 nullptr);
        m_last_error = Error::WindowCreationFailed;
    }

    // Create the SDL renderer
    m_sdl_state.renderer = SDL_CreateRenderer(m_sdl_state.window, nullptr);

    if (!m_sdl_state.renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 "Failed to create renderer!",
                                 nullptr);
        m_last_error = Error::RendererCreationFailed;
    }

    SDL_SetRenderLogicalPresentation(m_sdl_state.renderer,
                                     m_sdl_state.logical_size.x,
                                     m_sdl_state.logical_size.y,
                                     SDL_RendererLogicalPresentation::SDL_LOGICAL_PRESENTATION_LETTERBOX);

    load_assets();
    
    m_sdl_state.keyboard_state = SDL_GetKeyboardState(nullptr);

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
    Vector2<float> player_position{0.f, 0.f};
    Vector2<float> floor_size{
        static_cast<float>(m_sdl_state.logical_size.x),
        static_cast<float>(m_sdl_state.logical_size.y)
    };
    bool flip_horizontal = false;
    std::uint64_t previous_frame_time = SDL_GetTicks();
    while (running)
    {
        // std::int64_t start_time = 0;
        // SDL_GetCurrentTime(&start_time);

        std::uint64_t frame_start_time = SDL_GetTicks();
        float delta_time = static_cast<float>(frame_start_time - previous_frame_time) / 1'000.0f;
        
        handle_events(running, delta_time, player_position, flip_horizontal);
        render_frame(player_position, flip_horizontal);
        
        // SDL_DelayPrecise(6'900'000); // Approx ~144 FPS

        // std::int64_t end_time = 0;
        // SDL_GetCurrentTime(&end_time);
        // printf("Frame Time: %f ns\n", 1.0 / (static_cast<double>(end_time - start_time) / 1'000'000'000.0));
        previous_frame_time = frame_start_time;
    }

    for (SDL_Texture* texture : m_sdl_state.loaded_textures)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    return m_last_error;
}

void MainApp::load_assets()
{
    SDL_Texture* idle_tex = IMG_LoadTexture(m_sdl_state.renderer, "data/GraveRobber_idle.png");

    if (idle_tex)
    {
        SDL_SetTextureScaleMode(idle_tex, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
        m_sdl_state.loaded_textures.push_back(idle_tex);
    }
}

void MainApp::handle_events(bool& running, float delta_time, Vector2<float>& player_position, bool& flip_horizontal)
{
    SDL_Event event{ 0 };
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EventType::SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EventType::SDL_EVENT_WINDOW_RESIZED:
                m_sdl_state.window_size.x = event.window.data1;
                m_sdl_state.window_size.y = event.window.data2;
                break;
        }
    }

    float move_amount = 0;
    if (m_sdl_state.keyboard_state[SDL_SCANCODE_RIGHT])
    {
        move_amount += 75.f * delta_time;
        flip_horizontal = false;
    }
    
    if (m_sdl_state.keyboard_state[SDL_SCANCODE_LEFT])
    {
        move_amount += -75.f * delta_time;
        flip_horizontal = true;
    }

    player_position.x += move_amount;
}

void MainApp::render_frame(Vector2<float> player_position, bool flip_horizontal)
{
    // Perform rendering
    SDL_SetRenderDrawColor(m_sdl_state.renderer, 20, 10, 30, 255);
    SDL_RenderClear(m_sdl_state.renderer);

    SDL_FRect src{
        .x = 0.0f,
        .y = 0.0f,
        .w = 48.0f,
        .h = 48.0f
    };
    SDL_FRect dst{
        .x = player_position.x,
        .y = m_sdl_state.logical_size.y - src.h,
        .w = src.w,
        .h = src.h,
    };
    // SDL_RenderTexture(m_sdl_state.renderer, m_sdl_state.loaded_textures[0], &src, &dst);
    SDL_RenderTextureRotated(m_sdl_state.renderer,
                             m_sdl_state.loaded_textures[0],
                             &src,
                             &dst,
                             0,
                             nullptr,
                             flip_horizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    // Swap buffers and present
    SDL_RenderPresent(m_sdl_state.renderer);
}

MainApp::Error MainApp::cleanup()
{
    // Destroy renderer BEFORE window
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
    return Error::None;
}

} // namespace AuroraEngine
