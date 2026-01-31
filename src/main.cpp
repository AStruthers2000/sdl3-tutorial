#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

using namespace std;

void cleanup(SDL_Window* window)
{
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                 "Error",
                                 "Failed to initialize SDL3!",
                                 nullptr);
        return -1;
    }

    int width = 800;
    int height = 600;
    SDL_Window* window = SDL_CreateWindow("SDL3 Tutorial",
                                          width,
                                          height,
                                          0);
    if (!window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                 "Error",
                                 "Failed to create window!",
                                 nullptr);
        cleanup(window);
        return -1;
    }
    SDL_Delay(3000); // Keep the window open for 3 seconds
    cleanup(window);
    return 0;
}