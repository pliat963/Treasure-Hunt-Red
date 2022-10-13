
///////////////////////////////////////////////
// functions to "draw" the different screens:

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start menu screens:

void Display::drawFirstScreen(void) // welcome screen
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
  printHorizontallyCentered("Press OK to start", 40); // using default settings
  printHorizontallyCentered("Press UP for menu", 50);
  display.display();
}

void Display::drawSecondScreen(void)
{                                      //"Choose number of treasures" screen
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
  printHorizontallyCentered("Continue (Press OK)", 57);
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
  printHorizontallyCentered("Continue (Press OK)", 57);
  display.display();
}

// CHECK should appear only if the answer to "shoud use timer" was yes
void Display::drawFifthScreen(void)
{ //"how much time?" screen
  screen_index = HOW_MUCH_TIME_SCR;
  questionID = 5;
  currentOption = 2;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("How much", 1);
  printHorizontallyCentered("time?", 19);
  printHorizontallyCentered("(minutes)", 37);
  display.display();
  delay(200);
  display.setTextSize(1);
  printHorizontallyCentered("Continue (Press OK)", 57);
  display.display();
}

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
  printHorizontallyCentered("Continue (Press OK)", 57);
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
  // delay(200);
  display.setTextSize(1);
  printHorizontallyCentered("Press OK to start", 40);
  printHorizontallyCentered("Press UP to go back", 50);
  display.display();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// game screens

void Display::drawMainGameScreen(int currentTreasure, int treasuresNumber, double dist, bool withTimer, String time, bool closeEnough, int animationIndex)
{ // the main screen of the game. shows the distance, the time left and the current treasure
  screen_index = MAIN_GAME_SCR;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 3);
  display.print("Treasure " + String(currentTreasure) + "/" + String(treasuresNumber)); // print treasure number

  if (withTimer)
  {
    display.setCursor(95, 3);
    display.print(time); // print time left
  }

  display.setTextSize(3);
  display.setCursor(10, 27);
  display.print(dist); // print current distance
  display.display();

  if (closeEnough)
  {
    closeEnoughAnimation(animationIndex);
  }
}

void Display::drawTreasureFoundScreen(void)
{ //"should we use sound?" screen
  screen_index = TREASURE_FOUND_SCR;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Greate!", 1);
  printHorizontallyCentered("Find next", 19);
  printHorizontallyCentered("treasure", 37);

  display.setTextSize(1);
  printHorizontallyCentered("Continue (Press OK)", 57);
  display.display();
}

void Display::drawTimeUpScreen(String scoreStr)
{
  screen_index = TIME_UP_SCR;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Time's up!", 0);
  display.setTextSize(1);
  printHorizontallyCentered("Score:", 20);
  display.setTextSize(2);
  printHorizontallyCentered(scoreStr, 36);

  display.setTextSize(1);
  printHorizontallyCentered("Play again (press OK)", 56); 
  display.display();
}

void Display::drawWellDoneScreen()
{
  screen_index = WELL_DONE_SCR;
  display.clearDisplay();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  printHorizontallyCentered("Well Done!", 0);
  display.setTextSize(1);
  printHorizontallyCentered("Score:", 20);
  display.setTextSize(2);
  printHorizontallyCentered("100/100", 36);

  wellDoneAnimation();
  display.setTextSize(1);
  printHorizontallyCentered("Play again (press OK)", 56); 
  display.display();
}

// searching wifi
void Display::drawSearchingScreen(int treasureIndex)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("Searching ");
  display.setCursor(0, 30);
  display.println("treasure " + String(treasureIndex + 1) + "...");
  display.display();
}

void Display::drawNotFoundScreen()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Treasure not found.");
  display.println("Please Make sure it");
  display.println("is connected to");
  display.println("powerbank and within");
  display.println("wifi range.");
  printHorizontallyCentered("Searching...", 55);

  display.display();
}