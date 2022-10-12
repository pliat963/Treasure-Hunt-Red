/////////////////////////////////////////////
// functions to draw and manage the screen of replacing and choosing options

// draw options screen with specific numeric option. Also update currentOption
void Display::drawOptionScreenNum(int optionNum)
{ // screen index - 3 = OPTIONS_SCR
  screen_index = OPTIONS_SCR;
  display.clearDisplay();
  // draw current number
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(54, 17);
  display.println(optionNum);
  // draw up and down arrows
  display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
  display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
  display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
  display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
  display.display();
  currentOption = optionNum;
  delay(100);
}

// draw options screen with specific text option (Yes or No). Also update currentOption
void Display::drawOptionScreenText(char *optionText)
{ // screen index - 3 = OPTIONS_SCR
  screen_index = OPTIONS_SCR;
  display.clearDisplay();
  // draw current number
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println(optionText);
  // draw up and down arrows
  display.drawTriangle(90, 25, 100, 15, 110, 25, WHITE);
  display.fillTriangle(90, 25, 100, 15, 110, 25, WHITE);
  display.drawTriangle(90, 40, 100, 50, 110, 40, WHITE);
  display.fillTriangle(90, 40, 100, 50, 110, 40, WHITE);
  display.display();
  currentOption = (optionText[0] == 'Y' ? 1 : 0); // if option is Yes (starts with Y), 1, else 0
  delay(100);
}

// update the currentOption and screen accordingly, with numeric options
void Display::updateOptionsScreenByChoice(void)
{
 
  if (currentOption == 1)
  { // if the current option on the screen is 1
    if (currentBtn1State == LOW)
    { // and the UP btn was clicked
      upChoiceAnimation();
      replaceOption1With2UpAnimation(1, 2); // replace current option1 1 by current option 2
    }
    else if (currentBtn2State == LOW)
    { // DOWN btn was clicked
      downChoiceAnimation();
      drawOptionScreenNum(1); // if button DOWN was clicked and we are already at lowest option, stay the same
    }
  }
  else if (currentOption == 2)
  {
    if (currentBtn2State == LOW)
    { // DOWN btn was clicked
      downChoiceAnimation();
      replaceOption1With2DownAnimation(2, 1); // replace current option1 2 by current option 1
    }
    else if (currentBtn1State == LOW)
    { // UP btn was clicked
      upChoiceAnimation();
      drawOptionScreenNum(2); // if button UP was clicked and we are already at lowhighest option, stay the same
    }
  }
}

// update the currentOption and screen accordingly, with text options
void Display::updateOptionsScreenByChoiceYesNo(void)
{
  
  if (currentOption == 1)
  { // if the current option on the screen is "yes"
    if (currentBtn1State == LOW)
    { // and the UP btn was clicked
      upChoiceAnimation();
      replaceOption1With2UpAnimation(1, 0); // replace current option1 1 by current option 2
    }
    else if (currentBtn2State == LOW)
    { // DOWN btn was clicked
      downChoiceAnimation();
      replaceOption1With2DownAnimation(1, 0); // replace current option1 2 by current option 1
    }
  }
  else if (currentOption == 0)
  {
    if (currentBtn2State == LOW)
    { // DOWN btn was clicked
      downChoiceAnimation();
      replaceOption1With2DownAnimation(0, 1); // replace current option1 2 by current option 1
    }
    else if (currentBtn1State == LOW)
    { // UP btn was clicked
      upChoiceAnimation();
      replaceOption1With2UpAnimation(0, 1); // replace current option1 1 by current option 2
    }
  }
}

//save the choice of current question
void Display::saveChoice(void)
{
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  switch (questionID)
  {
  case 2:
    treasuresNumber = currentOption;
    drawFourthScreen(); //"should we set a timer?" screen
    break;
  case 4:
    withTimer = currentOption;
    drawSixthScreen();  //"should we use sound?" screen
    break;
  case 6:
    withSound = currentOption;
    drawEndMenuScreen();
    break;

  default:
    break;
  }
}
