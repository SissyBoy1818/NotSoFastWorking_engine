#include "Engine.h"

int main()
{
    const nsfw::core::EngineConfig config{800, 450, std::string("NSFW TEST")};
    nsfw::core::Engine game(config);

    game.run();

    return 0;
}