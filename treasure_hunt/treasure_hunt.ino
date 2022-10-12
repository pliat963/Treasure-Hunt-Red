//connections
#define UP_BTN D3
#define DOWN_BTN D8
#define OK_BTN D5
#define BUZZER D6 



#include "Game.h"


  int currentBtn1State; // variables to read buttons that affects the display
  int currentBtn2State;
  int currentBtn3State;

Game game;

void setup()
{
  // buttons
  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(OK_BTN, INPUT_PULLUP);
  // buzzer
  pinMode(BUZZER, OUTPUT);

  
  Serial.begin(9600);

 
  game.runStartGameMenu();  //CHECK uncomment this

  game.connectToWifi();
}

void loop()
{
  game.play_game();
}
