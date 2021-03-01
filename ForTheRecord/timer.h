#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void pause()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        if (m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
            m_TotalTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
            m_bRunning = false;
        }
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_TotalTime = 0;
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return m_TotalTime + std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    double m_TotalTime = 0.0;
    bool                                               m_bRunning = false;
};
