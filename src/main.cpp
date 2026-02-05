#include "engine/engine.h"
#include "engine/world.h"

int main(int argc, char* argv[])
{
    AuroraEngine::AuroraEngine app({1920, 1080}, {1920, 1080}, "Aurora Engine Demo");
    std::unique_ptr<AuroraEngine::GameWorld> world = std::make_unique<AuroraEngine::GameWorld>(app);

    app.initialize(std::move(world));
    app.run();
}
