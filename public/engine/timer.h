////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2026 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief A simple timer class for tracking elapsed time.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

namespace AuroraEngine
{

class Timer
{
public:
    Timer(float length) : m_length(length), m_time(0.0f), m_timeout(false) {}

    void update(float delta_time);
    void reset();

    float get_length() const { return m_length; }
    float get_time() const { return m_time; }
    bool is_finished() const { return m_timeout; }

private:
    float m_length;
    float m_time;
    bool m_timeout;
};

}

#endif // ENGINE_TIMER_H
