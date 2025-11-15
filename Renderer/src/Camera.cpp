#include "Camera.h"

namespace nsfw::render {

Camera::Camera(const utils::Rectangle &rect)
    : m_capturedArea(rect)
{}

Camera::Camera(const utils::Vector2f position, const utils::Vector2f area)
    : m_capturedArea(position, area)
{}

utils::Vector2f Camera::CameraToWorldPosition(const utils::Vector2i point) const {
    return {static_cast<float>(point.x) + m_capturedArea.position.x,
            static_cast<float>(point.y) + m_capturedArea.position.y};
}

utils::Vector2i Camera::WorldToCameraPosition(const utils::Vector2f point) const {
    return {static_cast<int>(point.x) - static_cast<int>(m_capturedArea.position.x),
            static_cast<int>(point.y) - static_cast<int>(m_capturedArea.position.y)};
}

void Camera::move(const utils::Vector2f offset) {
    m_capturedArea.position = m_capturedArea.position + offset;
}

void Camera::setPosition(const utils::Vector2f newPosition) {
    m_capturedArea.position = newPosition;
}

void Camera::resize(const utils::Vector2f newArea) {
    m_capturedArea.size = newArea;
}

void Camera::zoom(const float factor) {
    m_capturedArea.size = m_capturedArea.size * factor;
}

Camera::operator Camera2D() const {
    return Camera2D{m_capturedArea.position.x, m_capturedArea.position.y,
                    m_capturedArea.size.x/2 + m_capturedArea.position.x, m_capturedArea.size.y/2 + m_capturedArea.position.y,
                    0, 1.0f};
}

utils::Rectangle Camera::getCapturedArea() const {
    return m_capturedArea;
}

utils::Vector2f Camera::getPosition() const {
    return m_capturedArea.position;
}

utils::Vector2f Camera::getSize() const {
    return m_capturedArea.size;
}

}
