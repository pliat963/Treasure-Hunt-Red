
#include <ESP8266WiFi.h>
#include "Kalman.h"

#define BUTTON_PIN  D2 // the number of the pushbutton pin
int currentState;    // the current reading from the input pin
int distances[14]= {800,700,600,500,400,350,300,250,200,150,100,80,50,20};
int i =0;
int change_dist=0; //false, indicates if we want to use the next distance when we press the button next time

// Creates the variables:
double measurement, filteredMeasurement;
Kalman myFilter(0.125, 32, 1023, 0); // suggested initial values for high noise filtering

const char *ssid = "TREASURE1";
const char *password = "password1";

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);


  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Not connected");
  }
  Serial.println(" Connected");
}

void loop()
{
  
  
  measurement =  WiFi.RSSI();;
  filteredMeasurement = myFilter.getFilteredValue(measurement);

  Serial.print(measurement);
  Serial.print('\t');
  Serial.print(filteredMeasurement);
  Serial.print('\t');

  currentState = digitalRead(BUTTON_PIN);
  if (currentState==LOW){ //pressing the button when we stay at the same place 
     change_dist=1;   //true, when the button will be released we want to be at the next distance             
    Serial.print(distances[i]);
    Serial.print('\t');  
  }
  else if (change_dist){ //if the button was released and we want to be at the next distance
    if (digitalRead(BUTTON_PIN)==HIGH){
      i=i+1;  // go to the next distance at the array of distances
      change_dist=0; 
    }
  }
  
  Serial.println('\t');
  delay(20);
}
