#pragma once

namespace nsfw::utils {

/**
 * \class Vector2
 * \brief Шаблонный класс двумерного вектора
 */
template <class T>
class Vector2 {
public:
    T x;
    T y;

public:
    Vector2(T _x, T _y);

    Vector2<T> operator+(const Vector2<T> &rhs) const; /// Сложение векторов
    Vector2<T> operator-(const Vector2<T> &rhs) const; /// Вычитание векторов

    Vector2<T> operator*(auto rhs) const; /// Умножение вектора на число
    Vector2<T> operator/(auto rhs) const; /// Деление вектора на число

    template<class U>
    double operator*(const Vector2<U> &rhs) const; /// Скалярное произведение векторов

    [[nodiscard]] Vector2<double> normalized() const; /// Метод для получения нормализованного вектора (с длиной 1)
    [[nodiscard]] double length() const; /// Метод для получения длины вектора
};

// Реализация

template<class T>
Vector2<T>::Vector2(T _x, T _y)
    : x(_x), y(_y)
{}

template<class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &rhs) const {
    return {x + rhs.x, y + rhs.y};
}

template<class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> &rhs) const {
    return {x - rhs.x, y - rhs.y};
}

template<class T>
Vector2<T> Vector2<T>::operator*(auto rhs) const {
    return {x*rhs, y*rhs};
}

template<class T>
Vector2<T> Vector2<T>::operator/(auto rhs) const {
    return {x/rhs, y/rhs};
}

template<class T>
template<class U>
double Vector2<T>::operator*(const Vector2<U> &rhs) const {
    return x*rhs.x + y*rhs.y;
}

template<class T>
Vector2<double> Vector2<T>::normalized() const {
    return *this/length();
}

template<class T>
double Vector2<T>::length() const {
    return sqrt(x*x + y*y);
}

}
