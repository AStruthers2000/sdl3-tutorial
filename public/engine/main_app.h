#include "types.h"

#include <string_view>

namespace AuroraEngine
{

class MainApp
{
public:
    enum class Error : std::uint8_t
    {
        None,
        SDLInitFailed,
        WindowCreationFailed,
        SDLDestroyFailed,
    };

    MainApp(Vector2<int> windowSize, std::string_view windowTitle);
    ~MainApp();

    Error initialize();
    Error run();
    Error check_error() const { return m_last_error; }

private:
    Error cleanup();

    Vector2<int> m_windowSize;
    std::string_view m_windowTitle;

    Error m_last_error = Error::None;
};

} // namespace AuroraEngine
