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