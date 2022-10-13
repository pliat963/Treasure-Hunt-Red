#define UP_BTN 12
#define DOWN_BTN 13
#define OK_BTN 0
#define BUZZER 14

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
  game.connectToWifi();

}

void loop()
{

  game.play_game();
  //here game is over //CHECK implement or delete this
  if (digitalRead(OK_BTN) == LOW)
  { // start again
    game.startAgain();
  }
  delay(10);
}
