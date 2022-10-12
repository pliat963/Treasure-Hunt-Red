
///////////////////////////////////////////////
// functions to "draw" the different screens:

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start menu screens:

void Display::drawFirstScreen(void) //welcome screen
{
  screen_index = 1;
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(16, 10);
  display.println("Hello!");
  display.display();
  delay(700);
  display.setCursor(5, 45);
  display.setTextSize(1);
  display.println("Press OK to continue");
  display.display();
}

void Display::drawSecondScreen(void)
{ //"Choose number of treasures" screen
  screen_index = NUM_OF_TREASURES_SCR; // 2
  questionID = 2;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  // display.setCursor(28, 6);
  printHorizontallyCentered("Choose", 1);
  printHorizontallyCentered("number of", 19);
  printHorizontallyCentered("treasures", 37);
  display.display();
  delay(200);
  display.setTextSize(1);
  printHorizontallyCentered("Continue", 57);
  display.display();
}

void Display::drawFourthScreen(void)
{                                      //"should we set a timer?" screen
  screen_index = SHOULD_USE_TIMER_SCR; // 4
  questionID = 4;
  currentOption = 1; // use sound as default
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Set timer?", 20);
  display.display();
  delay(200);
  display.setTextSize(1);
  printHorizontallyCentered("Continue", 57);
  display.display();
}

// void Display::drawFifthScreen(void) { //"how much time?" screen
//   screen_index = 5;
//   questionID = 5;
//   currentOption=1; //use sound as default
//   display.clearDisplay();
//   display.setTextSize(2);
//   display.setTextColor(WHITE);
//   printHorizontallyCentered("Set timer?", 20);
//   delay(200);
//   display.setTextSize(1);
//   printHorizontallyCentered("Continue", 57);
//   display.display();
// }

void Display::drawSixthScreen(void)
{                                      //"should we use sound?" screen
  screen_index = SHOULD_USE_SOUND_SCR; // 6
  questionID = 6;
  currentOption = 1; // use sound as default
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Use sound?", 20);
  display.display();
  delay(200);
  display.setTextSize(1);
  printHorizontallyCentered("Continue", 57);
  display.display();
}

void Display::drawEndMenuScreen(void)
{ // choices accepted
  screen_index = END_OF_MENU_SCR;
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Saved", 10);
  display.display();
  delay(200);
  display.setTextSize(1);
  printHorizontallyCentered("Press OK to start", 40);
  printHorizontallyCentered("Press UP to go back", 50);
  display.display();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//game screens



void Display::drawMainGameScreen(int currentTreasure, int treasuresNumber, double dist, String time, bool closeEnough)
{ //the main screen of the game. shows the distance, the time left and the current treasure
  screen_index = MAIN_GAME_SCR;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 3);
  display.print("Treasure "+ String(currentTreasure) + "/" + String(treasuresNumber)); //print treasure number

  display.setCursor(95, 3);
  display.print(time); //print time left
  
  display.setTextSize(3);
  display.setCursor(10, 27);
  display.print(dist); //print current distance
  display.display();

  if(closeEnough){
    closeEnoughAnimation();
   }

}


void Display::drawTreasureFoundScreen(void)
{                                      //"should we use sound?" screen
  screen_index = TREASURE_FOUND_SCR; 
  questionID = 6;
  currentOption = 1; // use sound as default
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Greate!", 1);
  printHorizontallyCentered("Find next", 19);
  printHorizontallyCentered("treasure", 37);

  
  display.setTextSize(1);
  printHorizontallyCentered("Continue", 57);
  display.display();
}