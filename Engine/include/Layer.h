#pragma once

#include <memory>
#include "Event.h"

namespace nsfw::core {

class Layer {
public:
    virtual ~Layer() = default;

    virtual void onEvent(Event &e) {}

    virtual void onUpdate(float dt) {}
    virtual void onRender() {}
};

}
