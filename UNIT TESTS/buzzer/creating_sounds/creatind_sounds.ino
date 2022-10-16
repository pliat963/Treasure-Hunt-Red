//Board: d1 mini
//BUZZER:
//- -> gnd
// middle -> 3.3 V
// S -> D6

const int BUZZER = D6;

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
////////////////////////////////////////////////////////////////////////////////////////////
 //for beep beep
    tone(BUZZER, 780, 180);
    delay(1000);
/////////////////////////////////////////////////////////////////////////////////////////////
// //changing sound
//    for (int freq = 255; freq < 1000; freq = freq + 100){
//      Serial.println(freq);
//      tone(D6, freq, 180);
//      delay(1000);
//    }

}


