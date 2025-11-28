#pragma once

#include <cmath>
#include <type_traits>
#include <exception>
#include "raylib.h"

namespace nsfw::utils {

/**
 * \class Vector2
 * \brief Шаблонный класс двумерного вектора
 */
template <class T> requires std::is_arithmetic_v<T>
class Vector2 {
public:
    T x;
    T y;

public:
    Vector2(T _x = 0, T _y = 0);
    Vector2(::Vector2 &&vec);
    Vector2(Vector2<T> &&vec) = default;
    Vector2(const Vector2<T> &vec) = default;

    /// Сложение векторов
    Vector2<T> operator+(const Vector2<T> &rhs) const;
    /// Сложение векторов
    void operator+=(const Vector2<T> &rhs);
    /// Вычитание векторов
    Vector2<T> operator-(const Vector2<T> &rhs) const;
    /// Вычитание векторов
    void operator-=(const Vector2<T> &rhs);

    /// Умножение вектора на число
    template <typename Rhs> requires std::is_arithmetic_v<T>
    auto operator*(const Rhs rhs) const;
    /// Деление вектора на число
    template <typename Rhs> requires std::is_arithmetic_v<T>
    auto operator/(const Rhs rhs) const;

    /// Скалярное произведение векторов
    template<class U> requires std::is_arithmetic_v<T>
    float operator*(const Vector2<U> &rhs) const;

    Vector2<T>& operator=(const ::Vector2 &rhs);
    Vector2<T>& operator=(const Vector2<T> &rhs) = default;
    Vector2<T>& operator=(Vector2<T> &&rhs) = default;

    operator ::Vector2() const;

    /// Метод для получения нормализованного вектора (с длиной 1)
    [[nodiscard]] Vector2<float> normalized() const;
    /// Метод для получения длины вектора
    [[nodiscard]] float length() const;

    void rotate(float angle);
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;

// Реализация

template<class T> requires std::is_arithmetic_v<T>
Vector2<T>::Vector2(T _x, T _y)
    : x(_x), y(_y) {}

template<class T> requires std::is_arithmetic_v<T>
Vector2<T>::Vector2(::Vector2 &&vec)
    : x(vec.x), y(vec.y) {}

template<class T> requires std::is_arithmetic_v<T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &rhs) const {
    return {x + rhs.x, y + rhs.y};
}

template<class T> requires std::is_arithmetic_v<T>
void Vector2<T>::operator+=(const Vector2<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
}

template<class T> requires std::is_arithmetic_v<T>
void Vector2<T>::operator-=(const Vector2<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

template<class T> requires std::is_arithmetic_v<T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> &rhs) const {
    return {x - rhs.x, y - rhs.y};
}

template<class T> requires std::is_arithmetic_v<T>
template <typename Rhs> requires std::is_arithmetic_v<T>
auto Vector2<T>::operator*(const Rhs rhs) const {
    return Vector2{x*rhs, y*rhs};
}

template<class T> requires std::is_arithmetic_v<T>
template <typename Rhs> requires std::is_arithmetic_v<T>
auto Vector2<T>::operator/(const Rhs rhs) const {
    constexpr auto epsilon = 1e-6;
    if (abs(rhs) < epsilon)
        throw std::exception{"Division by zero"};

    return Vector2{x/rhs, y/rhs};
}

template<class T> requires std::is_arithmetic_v<T>
template<class U> requires std::is_arithmetic_v<T>
float Vector2<T>::operator*(const Vector2<U> &rhs) const {
    return x*rhs.x + y*rhs.y;
}

template<class T> requires std::is_arithmetic_v<T>
Vector2<T>& Vector2<T>::operator=(const ::Vector2 &rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
}

template<class T> requires std::is_arithmetic_v<T>
Vector2<T>::operator ::Vector2() const {
    return ::Vector2{static_cast<float>(x), static_cast<float>(y)};
}

template<class T> requires std::is_arithmetic_v<T>
Vector2<float> Vector2<T>::normalized() const {
    float len = length();
    constexpr auto epsilon = 1e-6;
    if (abs(len) < epsilon)
                throw std::exception{"Cannot normalize zero-length vector"};
    return {static_cast<float>(x) / len, static_cast<float>(y) / len};
}

template<class T> requires std::is_arithmetic_v<T>
float Vector2<T>::length() const {
    return sqrt(x*x + y*y);
}

template<class T> requires std::is_arithmetic_v<T>
void Vector2<T>::rotate(const float angle) {
    T newX = x * std::cos(angle/180.0 * PI) - y * std::sin(angle/180 * PI);
    T newY = x * std::sin(angle/180.0 * PI) - y * std::cos(angle/180 * PI);

    x = newX;
    y = newY;
}

}
