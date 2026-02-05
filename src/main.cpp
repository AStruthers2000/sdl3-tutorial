#include "engine/engine.h"

int main(int argc, char* argv[])
{
    // AuroraEngine::MainApp app({1920, 1080}, {640, 320}, "Aurora Engine Tutorial");
    // AuroraEngine::MainApp::Error init_error = app.initialize();

    // if (init_error != AuroraEngine::MainApp::Error::None)
    // {
    //     return static_cast<int>(init_error);
    // }
    // else
    // {
    //     return static_cast<int>(app.run());
    // }

    AuroraEngine::AuroraEngine app({1920, 1080}, {1920, 1080}, "Aurora Engine Demo");
    app.initialize();
    app.run();
}
