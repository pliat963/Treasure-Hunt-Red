//Boared used: ESP32

 
#define RXD2 16 //unused pin
#define TXD2 17


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(1200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial2.flush();
  String msg = "ABCDEFGHIJ-TEST\n\n";
 
  Serial2.println(msg);
  delay(50);
}