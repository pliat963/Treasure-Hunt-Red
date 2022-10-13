#define UP_BTN 0
#define DOWN_BTN 13
#define OK_BTN 14
#define BUZZER 12

#include "Game.h"

int currentBtn1State; // variables to read buttons that affects the display
int currentBtn2State;
int currentBtn3State;

Game game;
void setup()
{
  Serial.begin(9600);

  // buttons
  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(OK_BTN, INPUT_PULLUP);
  // buzzer
  pinMode(BUZZER, OUTPUT);
  game.runStartGameMenu(); 
}

void loop()
{

  game.play_game();
  // //here game is over //CHECK implement or delete this
  // if (digitalRead(OK_BTN) == LOW)
  // { // start again
  //   game.startAgain();
  // }
}
