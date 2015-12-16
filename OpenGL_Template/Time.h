//Time.h

#ifndef TIME_H
#define TIME_H

class Time
{
private:
    static int s_deltaTime;
    static unsigned long s_elapsedTicks;

public:
    Time();

    void Update();
    static int GetDeltaTime() { return s_deltaTime; }
    static long GetElapsedTime() { return s_elapsedTicks; }
};

#endif // !TIME_H
