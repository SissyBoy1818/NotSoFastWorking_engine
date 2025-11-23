#include "Engine.h"
#include "Rectangle.h"

auto rand_float = [](const float beg, const float end) -> auto {
    return static_cast<float>(rand())/static_cast<float>(RAND_MAX) * (end - beg) + beg;
};


int main()
{
    const nsfw::engine::EngineConfig config{800, 450, std::string("NSFW TEST")};
    nsfw::engine::Engine game(config);

    game.run();

    return 0;
}