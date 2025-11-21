#include "Engine.h"
#include "Examples/SomeGo.h"

auto rand_float = [](const float beg, const float end) -> auto {
    return static_cast<float>(rand())/static_cast<float>(RAND_MAX) * (end - beg) + beg;
};


int main()
{
    constexpr int WindowWidth = 800;
    constexpr int WindowHeight = 450;
    engine::Engine game(WindowWidth, WindowHeight, "TestGame");

    for (int i = 0; i < 100000; i++) {
        utils::Rectangle r{rand_float(0, 10000), rand_float(0, 10000), rand_float(1, 50), rand_float(1, 50)};
        game.addGameObject(std::make_shared<SomeGO>(r));
    }

    game.run();

    return 0;
}