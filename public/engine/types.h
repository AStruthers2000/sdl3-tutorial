////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Common type definitions for the Aurora Engine.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include <string>
#include <type_traits>

namespace AuroraEngine
{

/// @brief A 2D vector with arithmetic components.
/// @tparam T The type of the vector components, must be an arithmetic type.
template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
struct Vector2
{
    T x = static_cast<T>(0);
    T y = static_cast<T>(0);

    /// @brief Adds two Vector2 objects.
    /// @param other The other Vector2 to add.
    /// @return A new Vector2 that is the sum of this and other.
    Vector2 operator+(const Vector2& other) const
    {
        return Vector2{x + other.x, y + other.y};
    }
    
    /// @brief Subtracts two Vector2 objects.
    /// @param other The other Vector2 to subtract.
    /// @return A new Vector2 that is the difference of this and other.
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2{x - other.x, y - other.y};
    }

    /// @brief Multiplies the vector by a scalar.
    /// @param scalar The scalar value to multiply by.
    /// @return A new Vector2 that is the product of this vector and the scalar.
    Vector2 operator*(T scalar) const
    {
        return Vector2{x * scalar, y * scalar};
    }

    /// @brief Divides the vector by a scalar.
    /// @param scalar The scalar value to divide by.
    /// @return A new Vector2 that is the quotient of this vector and the scalar.
    Vector2 operator/(T scalar) const
    {
        return Vector2{x / scalar, y / scalar};
    }

    std::string ToString() const
    {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }
};

} // namespace AuroraEngine

#endif // ENGINE_TYPES_H
