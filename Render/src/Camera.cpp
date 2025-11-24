#include "Camera.h"

#include "../../ECS/include/CoreComponents.h"

namespace nsfw::render {

Camera::Camera(const utils::Rectangle &rect) {

}

Camera::Camera(const utils::Vector2f position, const utils::Vector2f area) {
    utils::Rectangle rect{position, area};
}

}
