#include <SoftwareSerial.h>

SoftwareSerial mySerial(4,5); //4 is the receiver pin, 5 if for the transmitter - an unused pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  while(!Serial) {
    ; // wait for serial port to connect
  }

  // set data rate for the SoftwareSerial
  mySerial.begin(1200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()) {
    Serial.write(mySerial.read());
  }
}