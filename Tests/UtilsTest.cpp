#include "gtest/gtest.h"
#include "QuadTree.h"
#include "Rectangle.h"
#include "Vector.h"

using namespace nsfw;


// ============================================================================
// Rectangle Tests
// ============================================================================
namespace {
// Тесты конструкторов
TEST(RectangleTest, DefaultConstructor) {
    utils::Rectangle rect;
    EXPECT_EQ(rect.position.x, 0);
    EXPECT_EQ(rect.position.y, 0);
    EXPECT_EQ(rect.size.x, 0);
    EXPECT_EQ(rect.size.y, 0);
}

TEST(RectangleTest, ConstructorWithFloats) {
    utils::Rectangle rect(10.5f, 20.5f, 30.5f, 40.5f);
    EXPECT_EQ(rect.position.x, 10.5f);
    EXPECT_EQ(rect.position.y, 20.5f);
    EXPECT_EQ(rect.size.x, 30.5f);
    EXPECT_EQ(rect.size.y, 40.5f);
}

TEST(RectangleTest, ConstructorWithVectors) {
    utils::Vector2f pos(5.0f, 10.0f);
    utils::Vector2f size(15.0f, 25.0f);
    utils::Rectangle rect(pos, size);
    EXPECT_EQ(rect.position.x, 5.0f);
    EXPECT_EQ(rect.position.y, 10.0f);
    EXPECT_EQ(rect.size.x, 15.0f);
    EXPECT_EQ(rect.size.y, 25.0f);
}

// Тесты метода contains для точки
TEST(RectangleTest, ContainsPoint_Inside) {
    utils::Rectangle rect(0, 0, 10, 10);
    utils::Vector2f point(5, 5);
    EXPECT_TRUE(rect.contains(point));
}

TEST(RectangleTest, ContainsPoint_Outside) {
    utils::Rectangle rect(0, 0, 10, 10);
    utils::Vector2f point(15, 15);
    EXPECT_FALSE(rect.contains(point));
}

TEST(RectangleTest, ContainsPoint_OnEdge) {
    utils::Rectangle rect(0, 0, 10, 10);
    // Точка на левой границе
    utils::Vector2f pointLeft(0, 5);
    EXPECT_FALSE(rect.contains(pointLeft));

    // Точка на правой границе
    utils::Vector2f pointRight(10, 5);
    EXPECT_FALSE(rect.contains(pointRight));

    // Точка на верхней границе
    utils::Vector2f pointTop(5, 0);
    EXPECT_FALSE(rect.contains(pointTop));

    // Точка на нижней границе
    utils::Vector2f pointBottom(5, 10);
    EXPECT_FALSE(rect.contains(pointBottom));
}

TEST(RectangleTest, ContainsPoint_AtCorner) {
    utils::Rectangle rect(0, 0, 10, 10);
    utils::Vector2f corner(0, 0);
    EXPECT_FALSE(rect.contains(corner));
}

// Тесты метода contains для прямоугольника
TEST(RectangleTest, ContainsRectangle_CompletelyInside) {
    utils::Rectangle rect1(0, 0, 20, 20);
    utils::Rectangle rect2(5, 5, 10, 10);
    EXPECT_TRUE(rect1.contains(rect2));
}

TEST(RectangleTest, ContainsRectangle_CompletelyOutside) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(20, 20, 10, 10);
    EXPECT_FALSE(rect1.contains(rect2));
}

TEST(RectangleTest, ContainsRectangle_PartiallyOverlapping) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(5, 5, 10, 10);
    EXPECT_FALSE(rect1.contains(rect2));
}

TEST(RectangleTest, ContainsRectangle_SameSize) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(0, 0, 10, 10);
    EXPECT_TRUE(rect1.contains(rect2));
}

TEST(RectangleTest, ContainsRectangle_LargerRectangle) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(0, 0, 20, 20);
    EXPECT_FALSE(rect1.contains(rect2));
}

TEST(RectangleTest, ContainsRectangle_TouchingEdge) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(10, 0, 10, 10);
    EXPECT_FALSE(rect1.contains(rect2));
}

// Тесты метода overlaps
TEST(RectangleTest, Overlaps_CompletelyOverlapping) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(0, 0, 10, 10);
    EXPECT_TRUE(rect1.overlaps(rect2));
}

TEST(RectangleTest, Overlaps_PartiallyOverlapping) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(5, 5, 10, 10);
    EXPECT_TRUE(rect1.overlaps(rect2));
    EXPECT_TRUE(rect2.overlaps(rect1));
}

TEST(RectangleTest, Overlaps_NoOverlap) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(20, 20, 10, 10);
    EXPECT_FALSE(rect1.overlaps(rect2));
    EXPECT_FALSE(rect2.overlaps(rect1));
}

TEST(RectangleTest, Overlaps_TouchingEdge) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(10, 0, 10, 10);
    EXPECT_FALSE(rect1.overlaps(rect2));
}

TEST(RectangleTest, Overlaps_OneInsideAnother) {
    utils::Rectangle rect1(0, 0, 20, 20);
    utils::Rectangle rect2(5, 5, 10, 10);
    EXPECT_TRUE(rect1.overlaps(rect2));
    EXPECT_TRUE(rect2.overlaps(rect1));
}

TEST(RectangleTest, Overlaps_VerticalOverlap) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(0, 5, 10, 10);
    EXPECT_TRUE(rect1.overlaps(rect2));
}

TEST(RectangleTest, Overlaps_HorizontalOverlap) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(5, 0, 10, 10);
    EXPECT_TRUE(rect1.overlaps(rect2));
}

TEST(RectangleTest, Overlaps_CornerOverlap) {
    utils::Rectangle rect1(0, 0, 10, 10);
    utils::Rectangle rect2(9, 9, 10, 10);
    EXPECT_TRUE(rect1.overlaps(rect2));
}

// Тесты с отрицательными координатами
TEST(RectangleTest, NegativeCoordinates) {
    utils::Rectangle rect(-10, -10, 20, 20);
    EXPECT_EQ(rect.position.x, -10);
    EXPECT_EQ(rect.position.y, -10);
    EXPECT_EQ(rect.size.x, 20);
    EXPECT_EQ(rect.size.y, 20);

    utils::Vector2f point(0, 0);
    EXPECT_TRUE(rect.contains(point));
}

TEST(RectangleTest, ZeroSize) {
    utils::Rectangle rect(0, 0, 0, 0);
    utils::Vector2f point(0, 0);
    EXPECT_FALSE(rect.contains(point));
}
}

// ============================================================================
// QuadTree Tests
// ============================================================================
namespace {

// Тесты конструктора и базовых методов
TEST(QuadTreeTest, Constructor) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    EXPECT_EQ(tree.rectangle().position.x, 0);
    EXPECT_EQ(tree.rectangle().position.y, 0);
    EXPECT_EQ(tree.rectangle().size.x, 100);
    EXPECT_EQ(tree.rectangle().size.y, 100);
}

TEST(QuadTreeTest, EmptyTree) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    std::list<int> result;
    tree.objects(result);
    EXPECT_TRUE(result.empty());
}

// Тесты вставки объектов
TEST(QuadTreeTest, InsertSingleObject) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    utils::Rectangle objRect(10, 10, 10, 10);
    tree.insert(42, objRect);

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), 42);
}

TEST(QuadTreeTest, InsertMultipleObjects) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(10, 10, 5, 5));
    tree.insert(2, utils::Rectangle(20, 20, 5, 5));
    tree.insert(3, utils::Rectangle(30, 30, 5, 5));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 3);
}

TEST(QuadTreeTest, InsertObjectsInDifferentQuadrants) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    // Объект в верхнем левом квадранте
    tree.insert(1, utils::Rectangle(10, 10, 20, 20));
    // Объект в верхнем правом квадранте
    tree.insert(2, utils::Rectangle(60, 10, 20, 20));
    // Объект в нижнем левом квадранте
    tree.insert(3, utils::Rectangle(10, 60, 20, 20));
    // Объект в нижнем правом квадранте
    tree.insert(4, utils::Rectangle(60, 60, 20, 20));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 4);
}

TEST(QuadTreeTest, InsertObjectSpanningMultipleQuadrants) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    // Объект, который пересекает несколько квадрантов
    tree.insert(99, utils::Rectangle(40, 40, 30, 30));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), 99);
}

// Тесты поиска в области
TEST(QuadTreeTest, ObjectsInArea_ExactMatch) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    utils::Rectangle objRect(10, 10, 10, 10);
    tree.insert(42, objRect);

    auto result = tree.objectsInArea(objRect);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), 42);
}

TEST(QuadTreeTest, ObjectsInArea_LargerSearchArea) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(10, 10, 5, 5));
    tree.insert(2, utils::Rectangle(20, 20, 5, 5));

    auto result = tree.objectsInArea(utils::Rectangle(0, 0, 30, 30));
    EXPECT_EQ(result.size(), 2);
}

TEST(QuadTreeTest, ObjectsInArea_NoOverlap) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(10, 10, 5, 5));
    tree.insert(2, utils::Rectangle(20, 20, 5, 5));

    auto result = tree.objectsInArea(utils::Rectangle(80, 80, 10, 10));
    EXPECT_TRUE(result.empty());
}

TEST(QuadTreeTest, ObjectsInArea_PartialOverlap) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(10, 10, 20, 20));
    tree.insert(2, utils::Rectangle(50, 50, 20, 20));

    auto result = tree.objectsInArea(utils::Rectangle(0, 0, 40, 40));
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), 1);
}

TEST(QuadTreeTest, ObjectsInArea_EntireTree) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(10, 10, 5, 5));
    tree.insert(2, utils::Rectangle(60, 10, 5, 5));
    tree.insert(3, utils::Rectangle(10, 60, 5, 5));
    tree.insert(4, utils::Rectangle(60, 60, 5, 5));

    auto result = tree.objectsInArea(rect);
    EXPECT_EQ(result.size(), 4);
}

TEST(QuadTreeTest, ObjectsInArea_MultipleQuadrants) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(10, 10, 10, 10));
    tree.insert(2, utils::Rectangle(60, 10, 10, 10));
    tree.insert(3, utils::Rectangle(10, 60, 10, 10));
    tree.insert(4, utils::Rectangle(60, 60, 10, 10));

    // Поиск в области, покрывающей два квадранта
    auto result = tree.objectsInArea(utils::Rectangle(0, 0, 80, 50));
    EXPECT_EQ(result.size(), 2);
}

// Тесты с разными типами объектов
TEST(QuadTreeTest, StringObjects) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<std::string> tree(rect);

    tree.insert("first", utils::Rectangle(10, 10, 10, 10));
    tree.insert("second", utils::Rectangle(60, 60, 10, 10));

    std::list<std::string> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 2);
}

struct TestObject {
    int id;
    float value;

    bool operator==(const TestObject& other) const {
        return id == other.id && value == other.value;
    }
};

TEST(QuadTreeTest, CustomObjects) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<TestObject> tree(rect);

    TestObject obj1{1, 1.5f};
    TestObject obj2{2, 2.5f};

    tree.insert(obj1, utils::Rectangle(10, 10, 10, 10));
    tree.insert(obj2, utils::Rectangle(60, 60, 10, 10));

    std::list<TestObject> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 2);
}

// Тесты с большим количеством объектов
TEST(QuadTreeTest, ManyObjects) {
    utils::Rectangle rect(0, 0, 1000, 1000);
    utils::QuadTree<int> tree(rect);

    // Вставляем 100 объектов
    for (int i = 0; i < 100; ++i) {
        float x = static_cast<float>(i % 10) * 100.0f;
        float y = static_cast<float>(i / 10) * 100.0f;
        tree.insert(i, utils::Rectangle(x, y, 50, 50));
    }

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 100);
}

TEST(QuadTreeTest, ManyObjects_SearchInSmallArea) {
    utils::Rectangle rect(0, 0, 1000, 1000);
    utils::QuadTree<int> tree(rect);

    for (int i = 0; i < 100; ++i) {
        float x = static_cast<float>(i % 10) * 100.0f;
        float y = static_cast<float>(i / 10) * 100.0f;
        tree.insert(i, utils::Rectangle(x, y, 50, 50));
    }

    // Ищем в небольшой области
    auto result = tree.objectsInArea(utils::Rectangle(0, 0, 150, 150));
    EXPECT_GT(result.size(), 0);
    EXPECT_LT(result.size(), 100);
}

// Тесты граничных случаев
TEST(QuadTreeTest, ObjectAtTreeBoundary) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    // Объект на границе дерева
    tree.insert(1, utils::Rectangle(0, 0, 10, 10));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 1);
}

TEST(QuadTreeTest, VerySmallObject) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(50, 50, 0.1f, 0.1f));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 1);
}

TEST(QuadTreeTest, ObjectSameAsQuadrantSize) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    // Объект размером с квадрант (50x50)
    tree.insert(1, utils::Rectangle(0, 0, 50, 50));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 1);
}

// Тесты с отрицательными координатами
TEST(QuadTreeTest, NegativeCoordinates) {
    utils::Rectangle rect(-100, -100, 200, 200);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(-50, -50, 20, 20));
    tree.insert(2, utils::Rectangle(30, 30, 20, 20));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 2);
}

TEST(QuadTreeTest, NegativeCoordinates_Search) {
    utils::Rectangle rect(-100, -100, 200, 200);
    utils::QuadTree<int> tree(rect);

    tree.insert(1, utils::Rectangle(-50, -50, 20, 20));
    tree.insert(2, utils::Rectangle(30, 30, 20, 20));

    auto result = tree.objectsInArea(utils::Rectangle(-60, -60, 40, 40));
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), 1);
}

// Тесты рекурсивной вставки в поддеревья
TEST(QuadTreeTest, DeepRecursion) {
    utils::Rectangle rect(0, 0, 1024, 1024);
    utils::QuadTree<int> tree(rect);

    // Вставляем очень маленький объект, который должен попасть глубоко в дерево
    tree.insert(1, utils::Rectangle(10, 10, 2, 2));
    tree.insert(2, utils::Rectangle(11, 11, 1, 1));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 2);
}

TEST(QuadTreeTest, OverlappingObjects) {
    utils::Rectangle rect(0, 0, 100, 100);
    utils::QuadTree<int> tree(rect);

    // Вставляем перекрывающиеся объекты
    tree.insert(1, utils::Rectangle(10, 10, 30, 30));
    tree.insert(2, utils::Rectangle(20, 20, 30, 30));
    tree.insert(3, utils::Rectangle(30, 30, 30, 30));

    std::list<int> result;
    tree.objects(result);
    EXPECT_EQ(result.size(), 3);

    // Поиск в области перекрытия
    auto searchResult = tree.objectsInArea(utils::Rectangle(25, 25, 20, 20));
    EXPECT_EQ(searchResult.size(), 3);
}

}

// ============================================================================
// Vector Tests
// ============================================================================
namespace {

// Тесты конструкторов
TEST(Vector2Test, DefaultConstructor) {
    utils::Vector2f vec;
    EXPECT_EQ(vec.x, 0);
    EXPECT_EQ(vec.y, 0);
}

TEST(Vector2Test, ParameterizedConstructor) {
    utils::Vector2f vec(3.5f, 4.5f);
    EXPECT_EQ(vec.x, 3.5f);
    EXPECT_EQ(vec.y, 4.5f);
}

TEST(Vector2Test, IntegerVector) {
    utils::Vector2i vec(5, 10);
    EXPECT_EQ(vec.x, 5);
    EXPECT_EQ(vec.y, 10);
}

TEST(Vector2Test, NegativeValues) {
    utils::Vector2f vec(-3.0f, -7.0f);
    EXPECT_EQ(vec.x, -3.0f);
    EXPECT_EQ(vec.y, -7.0f);
}

// Тесты оператора сложения
TEST(Vector2Test, Addition_PositiveVectors) {
    utils::Vector2f vec1(3.0f, 4.0f);
    utils::Vector2f vec2(1.0f, 2.0f);
    utils::Vector2f result = vec1 + vec2;
    EXPECT_EQ(result.x, 4.0f);
    EXPECT_EQ(result.y, 6.0f);
}

TEST(Vector2Test, Addition_NegativeVectors) {
    utils::Vector2f vec1(-3.0f, -4.0f);
    utils::Vector2f vec2(-1.0f, -2.0f);
    utils::Vector2f result = vec1 + vec2;
    EXPECT_EQ(result.x, -4.0f);
    EXPECT_EQ(result.y, -6.0f);
}

TEST(Vector2Test, Addition_MixedVectors) {
    utils::Vector2f vec1(5.0f, -3.0f);
    utils::Vector2f vec2(-2.0f, 7.0f);
    utils::Vector2f result = vec1 + vec2;
    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 4.0f);
}

TEST(Vector2Test, Addition_ZeroVector) {
    utils::Vector2f vec1(5.0f, 10.0f);
    utils::Vector2f vec2(0.0f, 0.0f);
    utils::Vector2f result = vec1 + vec2;
    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 10.0f);
}

TEST(Vector2Test, Addition_IntegerVectors) {
    utils::Vector2i vec1(3, 4);
    utils::Vector2i vec2(1, 2);
    utils::Vector2i result = vec1 + vec2;
    EXPECT_EQ(result.x, 4);
    EXPECT_EQ(result.y, 6);
}

// Тесты оператора вычитания
TEST(Vector2Test, Subtraction_PositiveVectors) {
    utils::Vector2f vec1(5.0f, 8.0f);
    utils::Vector2f vec2(2.0f, 3.0f);
    utils::Vector2f result = vec1 - vec2;
    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 5.0f);
}

TEST(Vector2Test, Subtraction_NegativeVectors) {
    utils::Vector2f vec1(-5.0f, -8.0f);
    utils::Vector2f vec2(-2.0f, -3.0f);
    utils::Vector2f result = vec1 - vec2;
    EXPECT_EQ(result.x, -3.0f);
    EXPECT_EQ(result.y, -5.0f);
}

TEST(Vector2Test, Subtraction_ResultingNegative) {
    utils::Vector2f vec1(2.0f, 3.0f);
    utils::Vector2f vec2(5.0f, 8.0f);
    utils::Vector2f result = vec1 - vec2;
    EXPECT_EQ(result.x, -3.0f);
    EXPECT_EQ(result.y, -5.0f);
}

TEST(Vector2Test, Subtraction_ZeroVector) {
    utils::Vector2f vec1(5.0f, 10.0f);
    utils::Vector2f vec2(0.0f, 0.0f);
    utils::Vector2f result = vec1 - vec2;
    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 10.0f);
}

TEST(Vector2Test, Subtraction_SameVectors) {
    utils::Vector2f vec1(5.0f, 10.0f);
    utils::Vector2f vec2(5.0f, 10.0f);
    utils::Vector2f result = vec1 - vec2;
    EXPECT_EQ(result.x, 0.0f);
    EXPECT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, Subtraction_IntegerVectors) {
    utils::Vector2i vec1(10, 20);
    utils::Vector2i vec2(3, 7);
    utils::Vector2i result = vec1 - vec2;
    EXPECT_EQ(result.x, 7);
    EXPECT_EQ(result.y, 13);
}

// Тесты умножения на скаляр
TEST(Vector2Test, ScalarMultiplication_PositiveScalar) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f result = vec * 2.0f;
    EXPECT_EQ(result.x, 6.0f);
    EXPECT_EQ(result.y, 8.0f);
}

TEST(Vector2Test, ScalarMultiplication_NegativeScalar) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f result = vec * -2.0f;
    EXPECT_EQ(result.x, -6.0f);
    EXPECT_EQ(result.y, -8.0f);
}

TEST(Vector2Test, ScalarMultiplication_Zero) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f result = vec * 0.0f;
    EXPECT_EQ(result.x, 0.0f);
    EXPECT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, ScalarMultiplication_One) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f result = vec * 1.0f;
    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 4.0f);
}

TEST(Vector2Test, ScalarMultiplication_Fraction) {
    utils::Vector2f vec(10.0f, 20.0f);
    utils::Vector2f result = vec * 0.5f;
    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 10.0f);
}

TEST(Vector2Test, ScalarMultiplication_IntegerVector) {
    utils::Vector2i vec(3, 4);
    utils::Vector2i result = vec * 2;
    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 8);
}

// Тесты деления на скаляр
TEST(Vector2Test, ScalarDivision_PositiveScalar) {
    utils::Vector2f vec(6.0f, 8.0f);
    utils::Vector2f result = vec / 2.0f;
    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 4.0f);
}

TEST(Vector2Test, ScalarDivision_NegativeScalar) {
    utils::Vector2f vec(6.0f, 8.0f);
    utils::Vector2f result = vec / -2.0f;
    EXPECT_EQ(result.x, -3.0f);
    EXPECT_EQ(result.y, -4.0f);
}

TEST(Vector2Test, ScalarDivision_One) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f result = vec / 1.0f;
    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 4.0f);
}

TEST(Vector2Test, ScalarDivision_Fraction) {
    utils::Vector2f vec(10.0f, 20.0f);
    utils::Vector2f result = vec / 0.5f;
    EXPECT_EQ(result.x, 20.0f);
    EXPECT_EQ(result.y, 40.0f);
}

TEST(Vector2Test, ScalarDivision_IntegerVector) {
    utils::Vector2i vec(10, 20);
    utils::Vector2i result = vec / 2;
    EXPECT_EQ(result.x, 5);
    EXPECT_EQ(result.y, 10);
}

// Тесты скалярного произведения
TEST(Vector2Test, DotProduct_PositiveVectors) {
    utils::Vector2f vec1(3.0f, 4.0f);
    utils::Vector2f vec2(2.0f, 1.0f);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, 10.0f); // 3*2 + 4*1 = 10
}

TEST(Vector2Test, DotProduct_OrthogonalVectors) {
    utils::Vector2f vec1(1.0f, 0.0f);
    utils::Vector2f vec2(0.0f, 1.0f);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(Vector2Test, DotProduct_OppositeVectors) {
    utils::Vector2f vec1(1.0f, 0.0f);
    utils::Vector2f vec2(-1.0f, 0.0f);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, -1.0f);
}

TEST(Vector2Test, DotProduct_SameVectors) {
    utils::Vector2f vec(3.0f, 4.0f);
    float result = vec * vec;
    EXPECT_FLOAT_EQ(result, 25.0f); // 3*3 + 4*4 = 25
}

TEST(Vector2Test, DotProduct_ZeroVector) {
    utils::Vector2f vec1(3.0f, 4.0f);
    utils::Vector2f vec2(0.0f, 0.0f);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(Vector2Test, DotProduct_NegativeVectors) {
    utils::Vector2f vec1(-3.0f, -4.0f);
    utils::Vector2f vec2(2.0f, 1.0f);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, -10.0f); // -3*2 + -4*1 = -10
}

TEST(Vector2Test, DotProduct_IntegerVectors) {
    utils::Vector2i vec1(3, 4);
    utils::Vector2i vec2(2, 1);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, 10.0f);
}

TEST(Vector2Test, DotProduct_MixedTypes) {
    utils::Vector2i vec1(3, 4);
    utils::Vector2f vec2(2.0f, 1.5f);
    float result = vec1 * vec2;
    EXPECT_FLOAT_EQ(result, 12.0f); // 3*2.0 + 4*1.5 = 12.0
}

// Тесты метода length
TEST(Vector2Test, Length_UnitVector) {
    utils::Vector2f vec(1.0f, 0.0f);
    float length = vec.length();
    EXPECT_FLOAT_EQ(length, 1.0f);
}

TEST(Vector2Test, Length_345Triangle) {
    utils::Vector2f vec(3.0f, 4.0f);
    float length = vec.length();
    EXPECT_FLOAT_EQ(length, 5.0f); // sqrt(9 + 16) = 5
}

TEST(Vector2Test, Length_ZeroVector) {
    utils::Vector2f vec(0.0f, 0.0f);
    float length = vec.length();
    EXPECT_FLOAT_EQ(length, 0.0f);
}

TEST(Vector2Test, Length_NegativeValues) {
    utils::Vector2f vec(-3.0f, -4.0f);
    float length = vec.length();
    EXPECT_FLOAT_EQ(length, 5.0f); // Длина не зависит от знака
}

TEST(Vector2Test, Length_EqualComponents) {
    utils::Vector2f vec(1.0f, 1.0f);
    float length = vec.length();
    EXPECT_NEAR(length, 1.41421356f, 0.0001f); // sqrt(2)
}

TEST(Vector2Test, Length_LargeVector) {
    utils::Vector2f vec(30.0f, 40.0f);
    float length = vec.length();
    EXPECT_FLOAT_EQ(length, 50.0f);
}

TEST(Vector2Test, Length_SmallVector) {
    utils::Vector2f vec(0.3f, 0.4f);
    float length = vec.length();
    EXPECT_NEAR(length, 0.5f, 0.0001f);
}

TEST(Vector2Test, Length_IntegerVector) {
    utils::Vector2i vec(3, 4);
    float length = vec.length();
    EXPECT_FLOAT_EQ(length, 5.0f);
}

// Тесты метода normalized
TEST(Vector2Test, Normalized_StandardVector) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f normalized = vec.normalized();
    EXPECT_NEAR(normalized.x, 0.6f, 0.0001f); // 3/5
    EXPECT_NEAR(normalized.y, 0.8f, 0.0001f); // 4/5
}

TEST(Vector2Test, Normalized_Length) {
    utils::Vector2f vec(3.0f, 4.0f);
    utils::Vector2f normalized = vec.normalized();
    float length = normalized.length();
    EXPECT_NEAR(length, 1.0f, 0.0001f);
}

TEST(Vector2Test, Normalized_UnitVector) {
    utils::Vector2f vec(1.0f, 0.0f);
    utils::Vector2f normalized = vec.normalized();
    EXPECT_NEAR(normalized.x, 1.0f, 0.0001f);
    EXPECT_NEAR(normalized.y, 0.0f, 0.0001f);
}

TEST(Vector2Test, Normalized_NegativeVector) {
    utils::Vector2f vec(-3.0f, -4.0f);
    utils::Vector2f normalized = vec.normalized();
    EXPECT_NEAR(normalized.x, -0.6f, 0.0001f);
    EXPECT_NEAR(normalized.y, -0.8f, 0.0001f);
}

TEST(Vector2Test, Normalized_LargeVector) {
    utils::Vector2f vec(300.0f, 400.0f);
    utils::Vector2f normalized = vec.normalized();
    EXPECT_NEAR(normalized.x, 0.6f, 0.0001f);
    EXPECT_NEAR(normalized.y, 0.8f, 0.0001f);
}

TEST(Vector2Test, Normalized_SmallVector) {
    utils::Vector2f vec(0.03f, 0.04f);
    utils::Vector2f normalized = vec.normalized();
    EXPECT_NEAR(normalized.x, 0.6f, 0.0001f);
    EXPECT_NEAR(normalized.y, 0.8f, 0.0001f);
}

TEST(Vector2Test, Normalized_IntegerVector) {
    utils::Vector2i vec(3, 4);
    utils::Vector2f normalized = vec.normalized();
    EXPECT_NEAR(normalized.x, 0.6f, 0.0001f);
    EXPECT_NEAR(normalized.y, 0.8f, 0.0001f);
}

TEST(Vector2Test, Normalized_DiagonalVector) {
    utils::Vector2f vec(1.0f, 1.0f);
    utils::Vector2f normalized = vec.normalized();
    float sqrt2_2 = 0.70710678f; // 1/sqrt(2)
    EXPECT_NEAR(normalized.x, sqrt2_2, 0.0001f);
    EXPECT_NEAR(normalized.y, sqrt2_2, 0.0001f);
}

// Тесты оператора преобразования к raylib::Vector2
TEST(Vector2Test, RaylibConversion_FloatVector) {
    utils::Vector2f vec(3.5f, 4.5f);
    ::Vector2 raylibVec = vec;
    EXPECT_FLOAT_EQ(raylibVec.x, 3.5f);
    EXPECT_FLOAT_EQ(raylibVec.y, 4.5f);
}

TEST(Vector2Test, RaylibConversion_IntegerVector) {
    utils::Vector2i vec(3, 4);
    ::Vector2 raylibVec = vec;
    EXPECT_FLOAT_EQ(raylibVec.x, 3.0f);
    EXPECT_FLOAT_EQ(raylibVec.y, 4.0f);
}

TEST(Vector2Test, RaylibConversion_ZeroVector) {
    utils::Vector2f vec(0.0f, 0.0f);
    ::Vector2 raylibVec = vec;
    EXPECT_FLOAT_EQ(raylibVec.x, 0.0f);
    EXPECT_FLOAT_EQ(raylibVec.y, 0.0f);
}

TEST(Vector2Test, RaylibConversion_NegativeVector) {
    utils::Vector2f vec(-5.0f, -10.0f);
    ::Vector2 raylibVec = vec;
    EXPECT_FLOAT_EQ(raylibVec.x, -5.0f);
    EXPECT_FLOAT_EQ(raylibVec.y, -10.0f);
}

// Комплексные тесты
TEST(Vector2Test, ComplexOperation_ChainedOperations) {
    utils::Vector2f vec1(2.0f, 3.0f);
    utils::Vector2f vec2(1.0f, 1.0f);
    utils::Vector2f result = (vec1 + vec2) * 2.0f - vec1;
    EXPECT_FLOAT_EQ(result.x, 4.0f); // (2+1)*2 - 2 = 4
    EXPECT_FLOAT_EQ(result.y, 5.0f); // (3+1)*2 - 3 = 5
}

TEST(Vector2Test, ComplexOperation_NormalizedAfterOperations) {
    utils::Vector2f vec1(3.0f, 0.0f);
    utils::Vector2f vec2(0.0f, 4.0f);
    utils::Vector2f result = (vec1 + vec2).normalized();
    EXPECT_NEAR(result.x, 0.6f, 0.0001f);
    EXPECT_NEAR(result.y, 0.8f, 0.0001f);
}

TEST(Vector2Test, ComplexOperation_ScalarMultiplicationAndDivision) {
    utils::Vector2f vec(10.0f, 20.0f);
    utils::Vector2f result = vec * 2.0f / 4.0f;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 10.0f);
}

TEST(Vector2Test, ComplexOperation_DotProductOfResults) {
    utils::Vector2f vec1(1.0f, 2.0f);
    utils::Vector2f vec2(3.0f, 4.0f);
    utils::Vector2f vec3 = vec1 + vec2; // (4, 6)
    utils::Vector2f vec4 = vec2 - vec1; // (2, 2)
    float dot = vec3 * vec4;
    EXPECT_FLOAT_EQ(dot, 20.0f); // 4*2 + 6*2 = 20
}

// Граничные случаи
TEST(Vector2Test, EdgeCase_VerySmallValues) {
    utils::Vector2f vec(0.0001f, 0.0001f);
    float length = vec.length();
    EXPECT_GT(length, 0.0f);
}

TEST(Vector2Test, EdgeCase_VeryLargeValues) {
    utils::Vector2f vec(1000000.0f, 1000000.0f);
    utils::Vector2f normalized = vec.normalized();
    float length = normalized.length();
    EXPECT_NEAR(length, 1.0f, 0.001f);
}

TEST(Vector2Test, EdgeCase_MixedPositiveNegative) {
    utils::Vector2f vec1(5.0f, -3.0f);
    utils::Vector2f vec2(-2.0f, 7.0f);
    utils::Vector2f sum = vec1 + vec2;
    EXPECT_FLOAT_EQ(sum.x, 3.0f);
    EXPECT_FLOAT_EQ(sum.y, 4.0f);
}

}