#include <String.h>

class Timer
{
    int startTime, currTime, timeElapsed;
    int newSecStart;                  // the time when a new second starts
    int timerTimeForTheGame;          // minutes
    int timerTimeForTheGameInSeconds; // seconds
    bool timeIsUp;

    int minutesLeft;
    int secondsLeft;

    bool paused;
    int pauseTime;
    int pauseTimeElapsed;
    int totalPauseTimeElapsed;

public:
    Timer(int minutes);
    void startTimer();
    void tick();
    void pauseTimer();
    void resumeTimer();
    void setTimeForGame(int time);
    String getTimeLeftStr();
    bool isTimeUp();
};

Timer::Timer(int minutes = 10) : timerTimeForTheGame(minutes),
                                 timerTimeForTheGameInSeconds(60 * minutes),
                                 timeIsUp(false),
                                 totalPauseTimeElapsed(0)
{
}
void Timer::startTimer()
{
    startTime = millis() / 1000;
    newSecStart = startTime;
}

void Timer::tick()
{ // should be called at intervals of less than 1 second
    if (!paused)
    {
        currTime = millis() / 1000;
        timeElapsed = currTime - startTime - totalPauseTimeElapsed;

        if (timerTimeForTheGameInSeconds - timeElapsed <= 0)
        {
            timeIsUp = true;
        }
        else if (currTime - newSecStart >= 1)
        { // a second passed
            newSecStart = currTime;
            minutesLeft = (timerTimeForTheGameInSeconds - timeElapsed) / 60;
            secondsLeft = (timerTimeForTheGameInSeconds - timeElapsed) % 60;
         
        }
    }
    else
    { // timer is paused, we don't want to add this time to the count

        currTime = millis() / 1000;
        pauseTimeElapsed = currTime - pauseTime;
        pauseTime = currTime;
        totalPauseTimeElapsed +=pauseTimeElapsed;

    }
}

void Timer::pauseTimer()
{
    pauseTime = millis() / 1000;
    paused = true;
}

void Timer::resumeTimer()
{
    totalPauseTimeElapsed += pauseTimeElapsed;
    paused = false;
    newSecStart = millis() / 1000;
}

void Timer::setTimeForGame(int minutes)
{
    timerTimeForTheGame = minutes;               // minutes
    timerTimeForTheGameInSeconds = 60 * minutes; // seconds
}

String Timer::getTimeLeftStr()
{
    String min = minutesLeft < 10 ? ("0" + String(minutesLeft)) : String(minutesLeft);
    String sec = secondsLeft < 10 ? ("0" + String(secondsLeft)) : String(secondsLeft);
    return min + ":" + sec;
}

bool Timer::isTimeUp(){
    return timeIsUp;
}