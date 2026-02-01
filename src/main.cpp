#include "engine/main_app.h"

int main(int argc, char* argv[])
{
    AuroraEngine::MainApp app({1920, 1080}, {640, 320}, "Aurora Engine Tutorial");
    AuroraEngine::MainApp::Error init_error = app.initialize();

    if (init_error != AuroraEngine::MainApp::Error::None)
    {
        return static_cast<int>(init_error);
    }
    else
    {
        return static_cast<int>(app.run());
    }
}