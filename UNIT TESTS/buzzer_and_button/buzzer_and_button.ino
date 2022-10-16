// Board: d1 mini

// BUTTON
//  One pin to gnd
//  The pin next to it to D2

// BUZZER:
//- -> gnd
//  middle -> 3.3 V
//  S -> D6

const int BUTTON_PIN = D2; // the number of the pushbutton pin
const int BUZZER = D6;
// Variables will change:
int currentState; // the current reading from the input pin

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  // sound with button
  currentState = digitalRead(BUTTON_PIN);
  if (currentState == LOW)
  {
    tone(D6, 300, 180);
    delay(1000);
  }
  delay(400);
}