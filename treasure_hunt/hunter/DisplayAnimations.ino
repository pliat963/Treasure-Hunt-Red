//////////////////////////////////////////////
// functions for animations on the screen:

///////////////////////////////////////////////////////////////////////////////////
// for the start menu:

void Display::removeFirstScreenAnimation(void)
{
  for (int loop_var = 0; loop_var < 15; loop_var++)
  {
    display.clearDisplay();
    display.setTextSize(3);
    // display.setTextColor(WHITE);
    display.setCursor(16, 10 - 5 * loop_var);
    display.println("Hello!");
    display.setCursor(5, 50 - 5 * loop_var);
    display.setTextSize(1);
    display.println("Click OK to continue");
    display.display();
  }
}

// Choice screen animations:
// up arrow "blinks"
void Display::upChoiceAnimation(void)
{
  display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
  display.fillTriangle(90, 25, 100, 15, 110, 25, BLACK);
  display.display();
  delay(100);
  display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
  display.display();
}
// down arrow "blinks"
void Display::downChoiceAnimation(void)
{
  display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
  display.fillTriangle(90, 40, 100, 50, 110, 40, BLACK);
  display.display();
  delay(100);
  display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
  display.display();
}

// replace between two options with upward scroll animation. Also update currentOption
void Display::replaceOption1With2UpAnimation(int option1, int option2)
{
  display.setTextSize(4);
  display.setTextColor(WHITE);

  if (questionID == 4 || questionID == 6)
  { // spacial question because it displays text options
    for (int loop_var = 0; loop_var <= 8; loop_var++)
    {
      display.clearDisplay();
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(25, 20 - 8 * loop_var);
      option1 == 0 ? display.println("No") : display.println("Yes");
      // display.println(option1);
      display.setCursor(25, 20 + 64 - 8 * loop_var);
      option2 == 0 ? display.println("No") : display.println("Yes");
      // draw up and down arrows
      display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.display();
    }
  }
  else
  { // for numeric options
    for (int loop_var = 0; loop_var <= 8; loop_var++)
    {
      display.clearDisplay();
      // draw current number
      display.setCursor(54, 17 - 8 * loop_var);
      display.println(option1);
      display.setCursor(54, 17 + 64 - 8 * loop_var);
      display.println(option2);
      // draw up and down arrows
      display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.display();
    }
  }
  currentOption = option2;
}

// replace between two options with downward scroll animation. Also update currentOption
void Display::replaceOption1With2DownAnimation(int option1, int option2)
{
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if (questionID == 4 || questionID == 6)
  { // spacial question because it displays text options
    for (int loop_var = 0; loop_var <= 8; loop_var++)
    {
      display.clearDisplay();
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(25, 20 + 8 * loop_var);
      option1 == 0 ? display.println("No") : display.println("Yes");
      display.setCursor(25, 20 - 64 + 8 * loop_var);
      option2 == 0 ? display.println("No") : display.println("Yes");
      // draw up and down arrows
      display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.display();
    }
  }
  else
  { // for numeric options
    for (int loop_var = 0; loop_var <= 8; loop_var++)
    {
      display.clearDisplay();
      // draw current number
      display.setCursor(54, 17 + 8 * loop_var);
      display.println(option1);
      display.setCursor(54, 17 - 64 + 8 * loop_var);
      display.println(option2);
      // draw up and down arrows
      display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
      display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
      display.display();
    }
  }
  currentOption = option2;
}

///////////////////////////////////////////////////////////////////////////////////
// for the game:



void Display::closeEnoughAnimation(int animationIndex)
{
  display.setTextSize(1);
  if (animationIndex % 2000 < 1000)
  {
    display.setTextColor(WHITE);
    printHorizontallyCentered("Press OK!", 57); // print current distance
    display.display();
  }
  else
  {
    display.setTextColor(BLACK);
    printHorizontallyCentered("Press OK!", 57); // print current distance
    display.display();
  }
}

void Display::wellDoneAnimation()
{

  // Invert and restore display, pausing in-between
  delay(500);
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
}
