#include <type_traits>

template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
struct Vector2
{
    T x = static_cast<T>(0);
    T y = static_cast<T>(0);

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2{x + other.x, y + other.y};
    }
    
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2{x - other.x, y - other.y};
    }

    Vector2 operator*(T scalar) const
    {
        return Vector2{x * scalar, y * scalar};
    }

    Vector2 operator/(T scalar) const
    {
        return Vector2{x / scalar, y / scalar};
    }
};