
#include <ESP8266WiFi.h>
#include <math.h>

#define distances_cal_length 3
#define BUTTON_PIN D2 // the number of the pushbutton pin

int currentState;                      // the current reading from the input pin
double distances[distances_cal_length] = {0.2, 0.5, 0.8}; // distances in meters to use for 
                                                         //"calibration" at new environment
                                       // distances[1] is the parameter d0
int dist_index = 0;                    // index
int change_dist = 0;                   // false
int number_of_samples = 0;

double RSSI[3] = {0, 0, 0}; // average RSSIs at closest, middle and farthest distances
double B_param = 0;           //RSSI[1] will be the parameter B
double n_param_0 = 0; // n parameter from closest distance
double n_param_2 = 0; // n parameter from farthest distance
double n_param_avg = 0;

double measurement;

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
  find_parameters();
}

void loop()
{
   delay(100);
}

//find and save n_param_avg and B_param parameters
void find_parameters()
{
  get_wifi_data();
  B_param=RSSI[1];
  //now RSSI[1] is the parameter B, distances[1] is the parameter d0
  n_param_0 = (B_param - RSSI[0])/(10*log10(distances[0]/distances[1]));
  n_param_2 = (B_param - RSSI[2])/(10*log10(distances[2]/distances[1]));

  n_param_avg=(n_param_0+n_param_2)/2;

  for (int i = 0; i < distances_cal_length; i++)
  {
    Serial.print(RSSI[i]);
    Serial.print('\t');
  }
  Serial.println(" ");
  Serial.print("average n parameter is: ");
  Serial.println(n_param_avg);
  Serial.print("B parameter is: ");
  Serial.println(B_param);
}

//get average RSSI values at three distances
void get_wifi_data()
{
  Serial.print("Press the button at distance of ");
  Serial.print(distances[dist_index]*100);
  Serial.println( " cm" );

  while (dist_index < distances_cal_length)
  {
    measurement = WiFi.RSSI();
    currentState = digitalRead(BUTTON_PIN);


    if (currentState == LOW)
    {                  // pressing the button when we stay at the same place
      change_dist = 1; // true, now when the button will be released we want to be at the next distance
      number_of_samples++;

      RSSI[dist_index] += measurement;
    }
    else if (change_dist)
    { // the button was pressed and released

      RSSI[dist_index] = RSSI[dist_index] / number_of_samples;

      dist_index = dist_index + 1;
      number_of_samples = 0;
      change_dist = 0;
      if (dist_index <distances_cal_length){ //to prevent printing it at the last time, when we do not need to press the button
        Serial.print("Press the button at distance of ");
        Serial.print(distances[dist_index]*100);
        Serial.println( " cm" );   
      }
    }

    delay(20);
  }
}
