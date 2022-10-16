#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>
// #include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define START_SCR 1 // SCR stands for screen
#define NUM_OF_TREASURES_SCR 2
#define OPTIONS_SCR 3
#define SHOULD_USE_TIMER_SCR 4
#define HOW_MUCH_TIME_SCR 5
#define SHOULD_USE_SOUND_SCR 6
#define END_OF_MENU_SCR 20

#define MAIN_GAME_SCR 21
#define TREASURE_FOUND_SCR 22
#define TIME_UP_SCR 23
#define WELL_DONE_SCR 24

#define TIMER_OPTION1 2
#define TIMER_OPTION2 4
#define TIMER_OPTION3 6

extern int currentBtn1State; // variables to read buttons
extern int currentBtn2State;
extern int currentBtn3State;
class Display
{
public:
  Adafruit_SSD1306 display;
  int screen_index; // index of current screen
  int questionID;   // equals to the screen_index of the question:
  //                                            2 - num of treasures
  //                                            4 - is there timer
  //                                            5 - how much time

  int currentOption; // in the start menu, we need to choose between a few options
                     // for a few parameters. This is the curren option

  bool game_ready; // true if all game parameters are known, and we can start

  //////////////////////////////////////////////////////////
  // parameters of the game, to be passed later
  int treasuresNumber;     // number of active treasures in the game. can be 1 or 2 in this case
  bool withTimer;          // is there timer or not? 1 if there is, 0 if not
  int timerTimeForTheGame; // time left for the game
  bool withSound = true;   // is there sound or not? 1 if there is, 0 if not

  Display();
  // start and manage the start-game menu
  void startGameMenu(void); 
  // handles the different cases of screens and buttons choices interactively
  void interactiveScreen(void);
  ///////////////////////////////////////////////
  //"draw" the different screens. Implementation at "DisplayDrawScreens.ino"
  // welcome screen
  void drawFirstScreen(void);
  //"Choose number of treasures" screen
  void drawSecondScreen(void);
  //"should we set a timer?" screen
  void drawFourthScreen(void);
  //"how much time" screen
  void drawFifthScreen(void);
  ///// //"should we use sound?" screen - removed from start menu
  ///// void drawSixthScreen(void); - removed from start menu
  // choices accepted screen
  void drawEndMenuScreen(void);

  // the main screen of the game. shows the distance, the time left and the current treasure
  void drawMainGameScreen(int currentTreasure, int treasuresNumber, double dist, bool withTimer, String time, bool closeEnough = false, int animationIndex = 0);
  // screen of finding a tressure that is not the last one
  void drawTreasureFoundScreen(void);
  // screen to say that the time is up
  void drawTimeUpScreen(String scoreStr);
  // well done screen (after finfing all treasures)
  void drawWellDoneScreen();
  // searching wifi
  void drawSearchingScreen(int treasureIndex);
  // wifi became unavailable
  void drawOutOfRangeScreen(int treasureIndex);
  // wifi not found screen
  void drawNotFoundScreen();
  //get ready to start after "number" seconds screen
  void getReadyNumber(int number);
  //////////////////////////////////////////
  // functions to draw and manage the screen of replacing and choosing options. Implementation at "DisplayManageOptionsScreen.ino"

  // draw options screen with specific numeric option. Also update currentOption
  void drawOptionScreenNum(int optionNum);
  // draw options screen with specific text option (Yes or No). Also update currentOption
  void drawOptionScreenText(char *optionText);
  // update the currentOption and screen accordingly, with numeric options
  void updateOptionsScreenByChoice(void);
  // update the currentOption and screen accordingly, with text options
  void updateOptionsScreenByChoiceYesNo(void);
  // save the choice of current question
  void saveChoice(void);

  ////////////////////////////////////////////
  // functions for animations on the screen. Implementation at "DisplayAnimations.ino"
  void removeFirstScreenAnimation(void);
  // up arrow "blinks"
  void upChoiceAnimation(void);
  // down arrow "blinks"
  void downChoiceAnimation(void);
  // replace between two options with upward scroll animation. Also update currentOption
  void replaceOption1With2UpAnimation(int option1, int option2);
  // replace between two options with downward scroll animation. Also update currentOption
  void replaceOption1With2DownAnimation(int option1, int option2);

  void wellDoneAnimation();
  void closeEnoughAnimation(int animationIndex);
  ////////////////////////////////////////
  // helper function to print text centered horizontally at given dustance from top
  void printHorizontallyCentered(char *str, int distanceFromTop);  
  void printHorizontallyCentered(String str, int distanceFromTop); 
};

Display::Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
                     screen_index(START_SCR),
                     currentOption(1),
                     game_ready(false)
{
  // start the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("Display screen unavailable"));
    for (;;)
      ;
  }
}

void Display::startGameMenu(void)
{
  drawFirstScreen();
  while (!game_ready)
  {
    interactiveScreen();
    delay(120); // to prevent "two choices" with one click
  }
}
void Display::interactiveScreen(void)
{

  if (screen_index == START_SCR)
  { // first "welcome" screen
    // read the state of the button:

    currentBtn1State = digitalRead(OK_BTN);
    currentBtn2State = digitalRead(UP_BTN);
    if (currentBtn2State == LOW) // up btn clicked, go to menu
    {                            // continue to next screen

      removeFirstScreenAnimation();
      delay(5);
      drawSecondScreen();
    }
    else if (currentBtn1State == LOW)
    {                      // ok btn clicked, use default settings and start game
      treasuresNumber=1;     
      withTimer = true;          
      timerTimeForTheGame = 4; 
      withSound = true;
      display.clearDisplay();
      game_ready = true;
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  else if (screen_index == NUM_OF_TREASURES_SCR)
  { // second screen, with instruction to choose number of treasures
    // read the state of the button:
    currentBtn1State = digitalRead(OK_BTN);
    if (currentBtn1State == LOW)
    { // if OK button was clicked
      display.clearDisplay();
      drawOptionScreenNum(1); // go to choose an option
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  else if (screen_index == OPTIONS_SCR)
  { // screen of choosing options. with up and down btns.

    // read the state of the button:
    currentBtn1State = digitalRead(UP_BTN);
    currentBtn2State = digitalRead(DOWN_BTN);
    currentBtn3State = digitalRead(OK_BTN);
    if (currentBtn3State == LOW)
    { // OK button was clicked
      saveChoice();
    }
    else if (currentBtn1State == LOW || currentBtn2State == LOW)
    { // one of the up and down buttons was clicked
      if (questionID == SHOULD_USE_TIMER_SCR || questionID == SHOULD_USE_SOUND_SCR)
      {                                     // yes/no questions
        updateOptionsScreenByChoiceYesNo(); // update choice in accordance to the clicked button
      }
      else
      {
        updateOptionsScreenByChoice(); // update choice in accordance to the clicked button
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  else if (screen_index == SHOULD_USE_TIMER_SCR)
  { //"should we set a timer?" screen
    currentBtn3State = digitalRead(OK_BTN);
    if (currentBtn3State == LOW)
    { // if OK button was clicked
      display.clearDisplay();
      drawOptionScreenText("Yes"); // go to choose an option
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  else if (screen_index == HOW_MUCH_TIME_SCR)
  { // Fifth screen, with instruction to choose time for the game
    // read the state of the button:
    currentBtn1State = digitalRead(OK_BTN);
    if (currentBtn1State == LOW)
    {                                     // if OK button was clicked
      drawOptionScreenNum(TIMER_OPTION1); // go to choose an option
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  else if (screen_index == SHOULD_USE_SOUND_SCR)
  { //"should we use sound?" screen
    delay(1000);
    currentBtn3State = digitalRead(OK_BTN);
    if (currentBtn3State == LOW)
    { // if OK button was clicked
      display.clearDisplay();
      drawOptionScreenText("Yes"); // go to choose an option
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////
  else if (screen_index == END_OF_MENU_SCR)
  { // end of start menu, we want to start the game on click
    if (digitalRead(OK_BTN) == LOW)
    { // if OK button was clicked
      display.clearDisplay();
      game_ready = true;
    }
    else if (digitalRead(UP_BTN) == LOW)
    { // up button was clicked - start the menu again
      drawFirstScreen();
    }
  }
}

/////////////////////////////////////////////
void Display::printHorizontallyCentered(char *str, int distanceFromTop)
{
  int16_t x1, y1;
  uint16_t width, height;
  display.getTextBounds(str, 0, 0, &x1, &y1, &width, &height);

  display.setCursor((SCREEN_WIDTH - width) / 2, distanceFromTop);

  display.println(str);
}
void Display::printHorizontallyCentered(String str, int distanceFromTop)
{
  int16_t x1, y1;
  uint16_t width, height;
  display.getTextBounds(str.c_str(), 0, 0, &x1, &y1, &width, &height);

  display.setCursor((SCREEN_WIDTH - width) / 2, distanceFromTop);

  display.println(str);
}

#endif