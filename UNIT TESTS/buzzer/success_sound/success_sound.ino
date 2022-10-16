//Board: d1 mini

//BUZZER:
//- -> gnd
// middle -> 3.3 V
// S -> D6


void setup() {
  pinMode(D6, OUTPUT);
}

void loop() {

    tone(D6, 261.63, 200);
    delay(200);
     tone(D6, 329.63, 200);
    delay(200);
     tone(D6, 392.63, 200);
    delay(200);
     tone(D6, 523.25, 300);
    delay(400);
     tone(D6, 392.63, 200);
    delay(200);
     tone(D6, 523.25, 400);
    delay(100);
    
    delay(1000);
 

}