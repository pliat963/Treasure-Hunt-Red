// connections: (using  board d1 mini)
// display: scl -> D1
// display: sda -> D2
// UP_BTN -> D6 (gpio12)
// DOWN_BTN -> D7 (gpio13)
//OK_BTN -> D3 (gpio0)
// BUZZER -> D5 (gpio14)
//led: red -> TX (gpio 1)
//led: green -> RX (gpio 3)



#define UP_BTN 12 //D6
#define DOWN_BTN 13 //D7
#define OK_BTN 0 //D3
#define BUZZER 14 //D0

#define RED 1 //TX
#define GREEN 3 //RX

#include "Game.h"

int currentBtn1State; // variables to read buttons that affects the display ang game
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
  //rgb led
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  game.runStartGameMenu(); 
  game.connectToWifi();

}

void loop()
{

  game.play_game();
  //here game is over
  if (digitalRead(OK_BTN) == LOW)
  { // start again
    game.startAgain();
  }
  delay(10);
}
