#ifndef _GAME
#define _GAME

#include "Display.h"
#include "Buzzer.h"
#include "Timer.h"

// for the wifi and calculating the distance
#include <ESP8266WiFi.h>
#include <math.h>
#include "Kalman.h"

// game parameters
#define MAX_TREASURES_NUMBER 2
#define CLOSE_ENOUGH_DIST 0.3 // approximately 0.3 meter = 30 cm
#define CLOSE_1_DIST 2
#define CLOSE_2_DIST 5
#define CLOSE_3_DIST 10

#define MIN_DISTANCE_TO_USE_WIFI_FILTER 0.5 // CHECK maybe delete this

extern int currentBtn1State; // variables to read buttons
extern int currentBtn2State;
extern int currentBtn3State;

Kalman myFilter(0.125, 32, 1023, 0); // suggested initial values for high noise filtering
const char *ssids[MAX_TREASURES_NUMBER] = {"TREASURE1", "AndroidAPA"};
const char *passwords[MAX_TREASURES_NUMBER] = {"78907890", "78907890"};

class Game
{
  Display display;
  Buzzer buzzer;
  Timer timer;
  // parameters of the game:
  int treasuresNumber = 2;     // CHECK change to 1 // number of active treasures in the game. can be 1 or 2 in this case
  bool withTimer = true;       // is there timer or not? 1 if there is, 0 if not
  int timerTimeForTheGame = 4; //  initial time (minutes) for the game
  bool withSound = true;       // is there sound or not? 1 if there is, 0 if not
  ////////////////////////////////////////////////////////////////////////////////////////////
  double current_dist;
  int current_treasure_index = 0;

  bool game_over = false;
  // gets RSSI value, or prints an "out of range" error
  int getRSSI();
  // calculate distance by given rssi signal, using this formula:
  // distance[meters] = 10 ^ ( (27.55 - 20 * log(frequency[2400 MHZ])) /20)
  // the formula was taken from here: https://stackoverflow.com/questions/11217674/how-to-calculate-distance-from-wifi-router-using-signal-strength
  double calcDistFromRSSI(double rssi);
  // returns calculated distance using average of points_number samples, and a filter at far distances
  double getDist(int points_number = 10);

  // combimations of sound and animations/screens for some events
  void endGameSuccess_ind();
  void endGameTimer_ind();
  void treasureFound_ind();

public:
  // default constructor
  Game() = default;

  // runs the start menu and updates the game parameters accordingly
  void runStartGameMenu();
  // tries to connect to wifi of tresure of index current_treasure_index
  void connectToWifi();
  // run the game itself. To be called at "loop"
  void play_game();
  // start again the game
  void startAgain();
};

void Game::runStartGameMenu()
{
  display.startGameMenu();
  treasuresNumber = display.treasuresNumber;
  withTimer = display.withTimer;
  timerTimeForTheGame = display.timerTimeForTheGame;
  withSound = display.withSound;

  buzzer.withSound = withSound;

  if (withTimer)
  {
    timer.setTimeForGame(timerTimeForTheGame);
  }
}

void Game::play_game()
{

  int sound_index = 0; // at some values of this variable, the buzzer plays
  timer.startTimer();
  while (!game_over)
  {
    timer.tick();

    if (digitalRead(DOWN_BTN) == LOW)
    {             // we can mute/unmute the buzzer
      delay(130); // prevent double-click
      buzzer.withSound = 1 - buzzer.withSound;
    }

    if (withTimer && timer.isTimeUp())
    { // check if time is up

      endGameTimer_ind();
      game_over = true;
      continue;
    }

    current_dist = getDist();
    if (current_dist <= CLOSE_ENOUGH_DIST)
    {
      if (sound_index % 2 == 0)
      {
        buzzer.playgettingCloseSound();
      }
      display.drawMainGameScreen(current_treasure_index + 1, treasuresNumber, current_dist, withTimer, withTimer ? timer.getTimeLeftStr() : "", true, sound_index);

      currentBtn1State = digitalRead(OK_BTN);
      if (currentBtn1State == LOW) // button pressed at close enough distance - treasure found
      {

        if (current_treasure_index == treasuresNumber - 1)
        { // if the last treasure was found
          endGameSuccess_ind();

          delay(1000);
          game_over = true;
          // CHECK save the time somewhere
        }
        else
        {
          // find the next treasure
          timer.pauseTimer(); // stop the timer until we are connected to the next treasure
          delay(300);         // to make sure (kind of) that OK button was released
          treasureFound_ind();
          // CHECK add sound
          while (digitalRead(OK_BTN) != LOW)
          {
            delay(50); // wait for the button to be pressed
          }
          delay(300);               // again, wait for the button to be released
          current_treasure_index++; // change index to next treasure
          // button was pressed, trying to connect to the next treasure's wifi

          connectToWifi(); // connect to next treasure
          timer.resumeTimer();
        }
      }
    }
    else
    {
      if (current_dist <= CLOSE_1_DIST) // very very close
      {
        if (sound_index % 4 == 0)
        {
          buzzer.playgettingCloseSound();
        }
      }
      else if (current_dist <= CLOSE_2_DIST) // very close
      {
        if (sound_index % 7 == 0)
        {
          buzzer.playgettingCloseSound();
        }
      }
      else if (current_dist <= CLOSE_3_DIST) // getting closer
      {
        if (sound_index % 20 == 0)
        {
          buzzer.playgettingCloseSound();
        }
      }
      display.drawMainGameScreen(current_treasure_index + 1, treasuresNumber, current_dist, withTimer, withTimer ? timer.getTimeLeftStr() : "");
    }
    if (sound_index > __INT_MAX__ - 100)
    {
      sound_index = 0;
    }
    sound_index++;
    delay(5);
  }
}

void Game::startAgain() // CHECK implement or delete this
{
  ESP.reset();
  // game_over == false;
  // current_treasure_index = 0;
  // display.game_ready = false;
  // connectToWifi();

  // // runStartGameMenu();
  // play_game();
}
void Game::connectToWifi()
{
  display.drawSearchingScreen(current_treasure_index);
  WiFi.begin(ssids[current_treasure_index], passwords[current_treasure_index]); // try to connect to wifi network of i'th treasure
  int time_to_wait = 10000;                                                     // max time to wait before reporting error
                                                                                //  10000 misiseconds which are 10 seconds
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    if (time_to_wait == 0)
    {
      display.drawNotFoundScreen();
    }
    else
    {
      display.drawSearchingScreen(current_treasure_index);
      time_to_wait -= 500;
    }
  }
}

double Game::getDist(int points_number)
{
  double total_rssi = 0;
  double avg_rssi;
  if (current_dist < MIN_DISTANCE_TO_USE_WIFI_FILTER)
  {                                         // if we were very close last time
    for (int i = 0; i < points_number; i++) // only 5 point for a fast-game at this case
    {
      total_rssi += getRSSI(); // without filter
      delay(5);
    }
    avg_rssi = total_rssi / points_number;
  }
  else
  {
    for (int i = 0; i < points_number; i++)
    {
      total_rssi += myFilter.getFilteredValue(getRSSI());
      delay(5);
    }
    avg_rssi = total_rssi / points_number;
  }
  return calcDistFromRSSI(avg_rssi);
}

double Game::calcDistFromRSSI(double rssi)
{
  double power = (-40.054 - rssi) / 20;
  return pow(10, power);
}

int Game::getRSSI()
{
  int rssi = WiFi.RSSI();
  if (rssi < 0)
  {
    return rssi;
  }
  else
  { // error with thw wifi
    timer.pauseTimer();
    int time_to_wait = 10000; // max time to wait before reporting error (10000 misiseconds which are 10 seconds)
    while (rssi > 0)
    { // as long as there is an error
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        timer.tick();
        if (time_to_wait == 0)
        {
          display.drawNotFoundScreen();
        }
        else
        {
          display.drawSearchingScreen(current_treasure_index);
          time_to_wait -= 500;
        }
      }
  
      rssi = WiFi.RSSI();
    }
    timer.resumeTimer();
    // if we are here, rssi is not positive
    return rssi;
  }
}

void Game::endGameSuccess_ind()
{
  buzzer.playSuccessSound();
  display.drawWellDoneScreen();
}

void Game::endGameTimer_ind()
{
  int score = (current_treasure_index) / treasuresNumber * 100;
  String scoreStr = String(score) + "/" + "100";
  display.drawTimeUpScreen(scoreStr);
  buzzer.playTimeUpSound();
}

void Game::treasureFound_ind()
{
  buzzer.playTreasureFoundSound();
  display.drawTreasureFoundScreen();
}
#endif