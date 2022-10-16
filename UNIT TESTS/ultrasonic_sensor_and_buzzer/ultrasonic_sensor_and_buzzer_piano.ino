// calculate the avg distance and write to the serial monitor
// plays do re mi fa sol accorsing to the (avg) distance

// code modified from: https://pastebin.com/raw/bB5ydN4shttps://pastebin.com/raw/bB5ydN4s
// explanation: https://gabbyshimoni.wixsite.com/arduino-programming/blank-19

// Board: D1 mini

// ultrasonic_sensor:
// vcc->5v
// trig ->D2
// echo ->D3
// gnd -> gnd

// buzzer:
//- -> gnd
// middle ->3.3v
// s -> D6

#define BUZZER D6

#define trigPin D2
#define echoPin D3
long duration;
long distance;
int numberOfSamples = 10, counter = 0, avg_dist = 0;
long sum = 0;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while (counter < numberOfSamples)
  {

    getDistance();

    if (distance > 3 && distance < 400)
    {
      sum += distance;
      counter++;
    }
  }
  avg_dist = sum * 1.0 / counter;
  Serial.print("average distance[cm] = ");
  Serial.println(avg_dist);
  delay(100);
  counter = 0;
  sum = 0;

  if (avg_dist < 10)
  { // less than 10 cm
    tone(BUZZER, 261.63, 400);
  }
  else if (avg_dist < 20)
  {
    tone(BUZZER, 293.66, 400);
  }
  else if (avg_dist < 30)
  {
    tone(BUZZER, 329.63, 400);
  }
  else if (avg_dist < 40)
  {
    tone(BUZZER, 349.23, 400);
  }
  else if (avg_dist < 60)
  {
    tone(BUZZER, 392.00, 400);
  }
}

void getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.1;
}