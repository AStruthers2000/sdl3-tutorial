#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string_view>

namespace AuroraEngine
{

class AuroraEngine
{
public:
    AuroraEngine(glm::vec2 window_size, glm::vec2 logical_size, std::string_view window_title);
    ~AuroraEngine();

    void initialize();
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
};

} // namespace AuroraEngine
