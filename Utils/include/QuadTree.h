#pragma once

#include "Rectangle.h"
#include <list>
#include <array>
#include <memory>

namespace nsfw::utils {
/**
 * \class QuadTree
 * \brief Класс для создания квадрантного дерева.
 *
 * Шаблонный класс, реализующий квадрантное дерево для быстрого поиска объектов на сцене.
 */
template <class OBJECT_TYPE>
class QuadTree {
public:
    explicit QuadTree(const Rectangle &rect);
    ~QuadTree();

    /**
     * \brief Добавляет объект в дерево.
     * \param object Добавляемый в дерево объект
     */
    void insert(const OBJECT_TYPE object, const Rectangle &objectRect);

    /**
     * \brief Метод для поиска всех объектов, находящихся в заданной прямоугольной области
     * \param area Область, в которой происходит поиск
     * \return Список ссылок на объекты
     */
    std::list<OBJECT_TYPE> objectsInArea(const Rectangle &area) const;

    /**
     * \brief Метод-геттер всех объектов в дереве
     * \param result Список, в который вставляются объекты
     */
    void objects(std::list<OBJECT_TYPE> &result) const;

    /**
     * \brief Метод-геттер прямоугольной области дерева
     * \return Область дерева
     */
    Rectangle rectangle() const;

private:
    Rectangle m_rect; ///< Область дерева

    /**
     * \struct QuadTreeChild
     * \brief Структура для хранения дочерних квадрантных деревьев
     */
    struct QuadTreeChild {
        Rectangle rect; ///< Область поддерева
        std::shared_ptr<QuadTree> ptr; ///< Указатель на поддерево
    };

    /**
     * \struct QuadTreeObject
     * \brief Структура хранимых объектов и их положения
     */
    struct QuadTreeObject {
        Rectangle rect; ///< Область объекта
        OBJECT_TYPE object; ///< Сам объект
    };

    std::list<QuadTreeObject> m_objects; ///<  список объектов принадлежащих дереву
    std::array<QuadTreeChild, 4> m_subTrees; ///< статический массив поддеревьев


private:
    /**
     * \brief Приватная реализация метода поиска в области для рекурсивного вызова
     * \param area Область поиска объектов
     * \param result Список для хранения найденных объектов
     */
    void find(const Rectangle &area, std::list<OBJECT_TYPE> &result) const;
};

}

// =========================== Реализация ===========================
namespace nsfw::utils {

template<class OBJECT_TYPE>
QuadTree<OBJECT_TYPE>::QuadTree(const Rectangle &rect)
    : m_rect(rect)
{
    // fill m_subTreeRects
}

template<class OBJECT_TYPE>
QuadTree<OBJECT_TYPE>::~QuadTree() = default;

template<class OBJECT_TYPE>
void QuadTree<OBJECT_TYPE>::insert(OBJECT_TYPE object, const Rectangle &objectRect) {
    for (auto &subTree : m_subTrees) {
        // Проверяем, может ли какое-то из поддеревьев полностью вместить в себя объект
        if (subTree.rect.contains(objectRect)) {
            // Если да, то рекурсивно вызываем метод у поддерева и выходим из метода
            if (!subTree.ptr)
                subTree.ptr = std::make_shared<QuadTree>(subTree.rect);

            subTree.ptr->insert(object, objectRect);
            return;
        }
    }
    // Если никакое из поддеревьев не вмещает объект, добавляем его себе
    m_objects.push_back({objectRect, object});
}

template<class OBJECT_TYPE>
std::list<OBJECT_TYPE> QuadTree<OBJECT_TYPE>::objectsInArea(const Rectangle &area) const {
    std::list<OBJECT_TYPE> result;
    find(area, result);
    return result;
}

template<class OBJECT_TYPE>
void QuadTree<OBJECT_TYPE>::objects(std::list<OBJECT_TYPE> &result) const {
    // Добавляем все объекты дерева
    for (auto &object : m_objects)
        result.push_back(object.object);

    // Добавляем все объекты в существующих поддеревьях
    for (auto &subTree : m_subTrees)
        if (subTree.ptr)
            subTree.ptr->objects(result);
}

template<class OBJECT_TYPE>
Rectangle QuadTree<OBJECT_TYPE>::rectangle() const {
    return m_rect;
}

template<class OBJECT_TYPE>
void QuadTree<OBJECT_TYPE>::find(const Rectangle &area, std::list<OBJECT_TYPE> &result) const {
    // Если область полностью перекрывает дерево, то возвращаем все объекты
    if (area.contains(m_rect)) {
        objects(result);
        return;
    }

    // Иначе, проверяем все объекты в дереве
    for (auto object: m_objects) {
        if (area.overlaps(object.rect))
            result.push_back(object.object);
    }

    // И проверяем объекты в поддеревьях
    for (auto &subTree: m_subTrees) {
        if (area.overlaps(subTree.rect))
            subTree.ptr->find(area, result);
    }
}

}