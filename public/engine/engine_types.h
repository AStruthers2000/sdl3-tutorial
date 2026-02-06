////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Common type definitions for the Aurora Engine.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_ENGINE_TYPES_H
#define ENGINE_ENGINE_TYPES_H

#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string>
#include <type_traits>

namespace AuroraEngine
{

struct SDLState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    glm::vec2 window_size{};
    glm::vec2 logical_size{};
};

struct InputValue
{

};

enum class EKeyPressedState
{
    NONE,
    KEY_DOWN,
    KEY_UP,
};

struct KeyPress
{
    EKeyPressedState key_state;
    SDL_Scancode key_code;
};

// Equality operator for KeyPress
inline bool operator==(const KeyPress& lhs, const KeyPress& rhs)
{
    return lhs.key_state == rhs.key_state && lhs.key_code == rhs.key_code;
}

// Less-than operator for ordered containers (std::map, std::set)
inline bool operator<(const KeyPress& lhs, const KeyPress& rhs)
{
    if (lhs.key_state != rhs.key_state)
        return static_cast<int>(lhs.key_state) < static_cast<int>(rhs.key_state);
    return lhs.key_code < rhs.key_code;
}

} // namespace AuroraEngine

// Hash specialization for std::unordered_map
namespace std
{
template <>
struct hash<AuroraEngine::KeyPress>
{
    size_t operator()(const AuroraEngine::KeyPress& key) const
    {
        // Combine hashes using FNV-1a inspired approach for good distribution
        size_t h1 = std::hash<int>()(static_cast<int>(key.key_state));
        size_t h2 = std::hash<SDL_Scancode>()(key.key_code);
        
        // FNV-1a-like combining
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
} // namespace std

#endif // ENGINE_ENGINE_TYPES_H
