//calculate the distance and write to the serial monitor

//code modified from: https://pastebin.com/raw/bB5ydN4shttps://pastebin.com/raw/bB5ydN4s
//explanation: https://gabbyshimoni.wixsite.com/arduino-programming/blank-19

//Board: d1 mini

//vcc->5v
//trig ->D2
//echo ->D3
//gnd -> gnd


#define trigPin D2
#define echoPin D3
long duration;
long distance;


void setup()
{
  pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  getDistance();
    if(distance>3 && distance <700){
       Serial.print("distance[cm] = ");
       Serial.println(distance);
    }
  delay(100);
}

void getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin,HIGH);
  distance = duration/58.1;
  
}