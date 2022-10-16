// Robo India Tutorial
// Digital Input and Output on LED
// Hardware: NodeMCU

//Board is D1 mini and these are the connections:
const int RED = 1;    //TX
const int GREEN = 3;  //RX
// const int BLUE = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  // pinMode(BLUE, OUTPUT);
}

void loop() {
  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  // analogWrite(BLUE, 0);
  delay(2000);

  // analogWrite(RED, 100);
  // analogWrite(GREEN, 100);
  // analogWrite(BLUE, 100);
  // delay (1000);
}