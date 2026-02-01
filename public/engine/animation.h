////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_ANIMATION_H
#define ENGINE_ANIMATION_H

#include "timer.h"

namespace AuroraEngine
{

class Animation
{
public:
    Animation() : m_frame_timer(0), m_frame_count(0) {}
    Animation(int frame_count, float frame_length) : m_frame_timer(frame_length), m_frame_count(frame_count) {}

    float get_length() const;
    int current_frame() const;
    void update(float delta_time);

private:
    Timer m_frame_timer;
    int m_frame_count;
};

} // namespace AuroraEngine

#endif // ENGINE_ANIMATION_H
