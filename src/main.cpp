#include "engine/engine.h"
#include "engine/world.h"

#include "game/player.h"

int main(int argc, char* argv[])
{
    AuroraEngine::AuroraEngine app({1920, 1080}, {1920, 1080}, "Aurora Engine Demo");
    std::unique_ptr<AuroraEngine::GameWorld> world = std::make_unique<AuroraEngine::GameWorld>(app);

    std::unique_ptr<TestGame::Player> player = std::make_unique<TestGame::Player>(*world);
    world->add_object(std::move(player), 0);

    app.initialize(std::move(world));
    app.run();
}
