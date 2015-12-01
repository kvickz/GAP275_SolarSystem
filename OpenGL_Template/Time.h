//Time.h

#ifndef TIME_H
#define TIME_H

class Time
{
private:
    int m_deltaTime;
    unsigned long m_elapsedTicks;

public:
    Time();

    void Update();
    int GetDeltaTime() { return m_deltaTime; }
    long GetElapsedTime() { return m_elapsedTicks; }
};

#endif // !TIME_H
