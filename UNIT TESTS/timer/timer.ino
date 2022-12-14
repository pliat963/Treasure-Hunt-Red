//Boards: ESP32 or D1 mini

//This background, up-to-hour timer prints the time to the Serial Monitor.
//How to use?
//1. Create a Timer instance with the wanted amount of time (minutes)
//2. Call the function startTimer()
//3. Call the function tick() at intervals of less than 1 sec, when the timer is not paused
//4. Use the function getTimeLeftStr() to get the time and print it somewhere


class Timer {
  int startTime, currTime, timeElapsed;
  int newSecStart;                   //the time when a new second starts
  int timerTimeForTheGame;           //minutes
  int timerTimeForTheGameInSeconds;  //seconds
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
  void tick();  // should be called at intervals of less than 1 second
  void pauseTimer();
  void resumeTimer();
  void setTimeForGame(int time);
  String getTimeLeftStr(); //returns a steing of the current time
  bool isTimeUp();
};

Timer::Timer(int minutes = 10) //default initial value
  : timerTimeForTheGame(minutes),
    timerTimeForTheGameInSeconds(60 * minutes),
    timeIsUp(false),
    totalPauseTimeElapsed(0) {
}


void Timer::startTimer() {
  startTime = millis() / 1000;
  newSecStart = startTime;
  minutesLeft = timerTimeForTheGameInSeconds / 60;
  secondsLeft = timerTimeForTheGameInSeconds % 60;
}

void Timer::tick() {
  if (!paused) {
    currTime = millis() / 1000;
    timeElapsed = currTime - startTime - totalPauseTimeElapsed;

    if (timerTimeForTheGameInSeconds - timeElapsed <= 0) {
      Serial.println("Game Over");

    } else if (currTime - newSecStart >= 1) {  // a second passed
      newSecStart = currTime;
      minutesLeft = (timerTimeForTheGameInSeconds - timeElapsed) / 60;
      secondsLeft = (timerTimeForTheGameInSeconds - timeElapsed) % 60;
      Serial.println(getTimeLeftStr());
    }
  } else {  //timer is paused, we don't want to add this time to the count

    currTime = millis() / 1000;
    pauseTimeElapsed = currTime - pauseTime;
    pauseTime = currTime;
    totalPauseTimeElapsed += pauseTimeElapsed;
  }
}

void Timer::pauseTimer() {
  pauseTime = millis() / 1000;
  paused = true;
}

void Timer::resumeTimer() {
  tick();
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
/////////////////////////////////

Timer timer;
void setup() {
  Serial.begin(9600);
  timer.startTimer();
}

void loop() {
  timer.tick();

  
}