#include "raylib.h"
#include "QuadTree.h"
#include <iostream>
#include <string>
#include <vector>

#include "Examples/FollowingCamera.h"
#include "Camera.h"

struct drawableObj {
    nsfw::utils::Rectangle rect;
    Color color;

    drawableObj(nsfw::utils::Rectangle r, Color c)
        : rect(r), color(c) {}

    void draw() const {
        DrawRectangle(rect.position.x, rect.position.y, rect.size.x, rect.size.y, color);
    }
};

int main()
{
    const nsfw::utils::Vector2f windowSize{800,450};

    InitWindow(windowSize.x, windowSize.y, "QuadTree demo");

    auto rand_float = [&](const float beg, const float end) -> auto {
        return static_cast<float>(rand())/static_cast<float>(RAND_MAX) * (end - beg) + beg;
    };

    nsfw::render::Camera camera{{0,0}, windowSize};
    nsfw::utils::Rectangle r{{0,0}, {100,100}};
    auto toDraw = std::make_shared<nsfw::render::Camera>(r);
    auto mouse = std::make_shared<Mouse>();

    toDraw->addComponent<ecs::TransformComponent>(r);
    toDraw->addComponent<FollowingCamera>(toDraw, mouse);

    nsfw::utils::QuadTree<drawableObj> tree{camera.getComponent<ecs::TransformComponent>()->rect()};
    std::vector<drawableObj> allObj;

    for (int i = 0; i < 100000; i++) {
        nsfw::utils::Rectangle r{rand_float(0,windowSize.x), rand_float(0,windowSize.y), rand_float(2,10),rand_float(2,10)};
        Color c{(unsigned char)(rand() % 255), (unsigned char)(rand() % 255),(unsigned char)(rand() % 255),255};

        drawableObj o(r,c);

        allObj.push_back(o);
        tree.insert(o, r);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        auto toDrawRect = toDraw->getComponent<ecs::TransformComponent>()->rect();

        auto objs = tree.objectsInArea(toDrawRect);
        for (const auto &o : objs)
            o.draw();

        DrawRectangleLines(toDrawRect.position.x, toDrawRect.position.y,
                           toDrawRect.size.x, toDrawRect.size.y, BLACK);


        toDraw->FrameUpdate(GetFrameTime());
        mouse->FrameUpdate(GetFrameTime());

        DrawText(std::to_string(GetFPS()).c_str(), 10,10, 15, BLACK);
        DrawText(std::to_string(GetFrameTime()).c_str(), 10,30, 15, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}