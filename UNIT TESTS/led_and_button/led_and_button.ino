
// Board: d1 mini

// BUTTON
//  One pin to gnd
//  The pin next to it to D2

// LED 
// D6 and 5v

///////////////////////////////////////////////////////////////////////
//button

const int BUTTON_PIN = D2; 
const int LED = D6;

int currentState;    

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  //read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);
  if (currentState==LOW){
    digitalWrite(LED, HIGH); // LED on
    Serial.println("LOW");
  }
  else{
     digitalWrite(LED, LOW); // LED on
     Serial.println("HIGH");
  }
  delay(200);
}


