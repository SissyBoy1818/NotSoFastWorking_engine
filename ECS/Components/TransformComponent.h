#pragma once

#include "Component.h"
#include "Rectangle.h"

namespace nsfw::ecs {

/**
 * \class TransformComponent
 * \brief Компонент, отвечающий за положение объекта в пространстве
 */
class TransformComponent final : public Component {
public:
    explicit TransformComponent(const utils::Rectangle &rect, const float rotation = 0, const utils::Vector2f scale = {1, 1})
        : m_rect(rect)
        , m_rotation(rotation)
        , m_scale(scale) {}

    /// Ничего не обновляется
    void FrameUpdate(float dt) override {}

    /// Ничего не обновляется
    void TickUpdate(float dt) override {}

    /**
     * \brief Метод-геттер позиции
     * \return Вектор позиции объекта
     */
    [[nodiscard]] utils::Vector2f position() const {
        return m_rect.position;
    }

    /**
     * \brief Метод-геттер размеров
     * \return Вектор размеров объекта
     */
    [[nodiscard]] utils::Vector2f size() const {
        return m_rect.size;
    }

    /**
     * \brief Метод-геттер прямоугольной области
     * \return Прямоугольная область объекта
     */
    [[nodiscard]] utils::Rectangle rect() const {
        return m_rect;
    }

    /**
     * \brief Метод-геттер поворота
     * \return Угол поворота в градусах
     */
    [[nodiscard]] float rotation() const {
        return m_rotation;
    }

    /**
     * \brief Метод-геттер масштаба
     * \return Вектор масштаба объекта
     */
    [[nodiscard]] utils::Vector2f scale() const {
        return m_scale;
    }

    /**
     * \brief Задать новую позицию
     * \param position Новая позиция объекта
     */
    void setPosition(const utils::Vector2f position) {
        m_rect.position = position;
    }

    /**
     * \brief Задать новый размер
     * \param size Новый размер объекта
     */
    void setSize(const utils::Vector2f size) {
        m_rect.size = size;
    }

    /**
     * \brief Задать новую позицию и размер
     * \param rect Новый прямоугольник
     */
    void setRect(const utils::Rectangle &rect) {
        m_rect = rect;
    }

    /**
     * \brief Задать новый поворот
     * \param rotation Новый угол поворота
     */
    void setRotation(const float rotation) {
        m_rotation = rotation;
    }

    /**
     * \brief Задать новый масштаб объекту
     * \param scale Новый масштаб
     */
    void setScale(const utils::Vector2f scale) {
        m_scale = scale;
    }

    /**
     * \brief Сдвинуть объект на заданный вектор
     * \param offset Вектор смещения
     */
    void move(const utils::Vector2f offset) {
        m_rect.position += offset;
    }

    /**
     * \brief Повернуть объект на указанное число градусов
     * \param angle Угол поворота
     */
    void rotate(const float angle) {
        m_rotation += angle;
        if (m_rotation > 360)
            m_rotation -= 360;
    }

    /**
     * \brief Умножить масштаб на заданный коэффициент
     * \param multX Коэффициент по X
     * \param multY Коэффициент по Y
     */
    void scale(const float multX, const float multY) {
        m_scale.x *= multX;
        m_scale.y *= multY;
    }

private:
    utils::Rectangle m_rect; ///< Прямоугольная область объекта
    float m_rotation; ///< Поворот объекта в градусах
    utils::Vector2f m_scale; ///< Масштаб объекта по x и y

    // TODO: иерархия трансформов
    // TODO: Матрицы преобразований
};

}
