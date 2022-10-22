
#include <ESP8266WiFi.h>
#include <math.h>
#include "Kalman.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>

#define BUTTON_PIN D3 // the number of the pushbutton pin

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#define distances_cal_length 3
int currentState;                      // the current reading from the input pin
double distances[distances_cal_length] = {0.5, 1, 1.5}; // distances in meters for "calibration" at new environment
                                       // distances[1] is the parameter d0
int dist_index = 0;                    // index
int change_dist = 0;                   // false
int number_of_samples = 0;

double RSSI[3] = {0, 0, 0}; // average RSSIs at closest, middle and farthest distances
double B_param = 0;           //RSSI[1] will be the parameter B
double n_param_0 = 0; // n parameter from closest distance
double n_param_2 = 0; // n parameter from farthest distance
double n_param_avg = 0;



double measurement, filteredMeasurement;
Kalman myFilter(0.125, 32, 1023, 0); // suggested initial values for high noise filtering


const char *ssid = "TREASURE1";
const char *password = "password1";
/////////////////////////////////////////
//functions declarations
void getDistAverage(int pointsNumber=20);
void getDistKalmanFilter(int pointsNumber=7);
void find_parameters();
void get_wifi_data();
void write_text(String txt, int size=1);

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
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  find_parameters();
}

void loop()
{
  //getDistAverage();
  getDistKalmanFilter();

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
}

//get average RSSI values at three distances
void get_wifi_data()
{
  // Serial.print("Press the button at distance of ");
  // Serial.print(distances[dist_index]*100);
  // Serial.println( " cm" );
    write_text("Press the button at distance of "+String(distances[dist_index]*100) + " cm");
 
  while (dist_index < distances_cal_length)
  {
    measurement = WiFi.RSSI();
    currentState = digitalRead(BUTTON_PIN);


    if (currentState == LOW)
    {                  // pressing the button when we stay at the same place
      change_dist = 1; // true, noe when the button will be released we want to be at the next distance
      number_of_samples++;

      RSSI[dist_index] += measurement;
    }
    else if (change_dist)
    { // the button was pressed and released

      RSSI[dist_index] = RSSI[dist_index] / number_of_samples;

      dist_index = dist_index + 1;
      number_of_samples = 0;
      change_dist = 0;
      if (dist_index < distances_cal_length){ //to prevent printing it at the last time, when we do not need to press the button
        write_text("Press the button at distance of "+String(distances[dist_index]*100)+" cm");  
      }
    }

    delay(20);
  }
}


void getDistAverage(int pointsNumber)
{
  double cur_rssi, cur_dist;
  double toal_rssi = 0, total_dist=0;

  for (int i = 0; i < pointsNumber; i++)
  {
    cur_rssi= WiFi.RSSI();
    toal_rssi += cur_rssi;
    cur_dist = pow(10,((B_param-cur_rssi)  / (10*n_param_avg))  + log10(distances[1])  ); 
    total_dist +=cur_dist;


    delay(10);
  }
  //getting average:
  double average_rssi = toal_rssi / pointsNumber;
  double dist1 = pow(10,((B_param-average_rssi)  / (10*n_param_avg))  + log10(distances[1])  );
  double dist2 = total_dist/pointsNumber;

  Serial.print("dist1, ");
  Serial.print(dist1);
  Serial.print(", ");
  Serial.print("dist2, ");
  Serial.println(dist2);

  // return averageRSSI;
}

void getDistKalmanFilter(int pointsNumber)
{
  double total_rssi = 0;
  double dist;
  for (int i = 0; i < pointsNumber; i++)
  {
    total_rssi +=  myFilter.getFilteredValue(WiFi.RSSI());
    delay(10);
  }
  double avg_rssi = total_rssi/pointsNumber;
  dist = pow(10,((B_param-avg_rssi)  / (10*n_param_avg))  + log10(distances[1])  ); 
  write_text(String(dist),2);
  
//  Serial.print("dist, ");
//  Serial.println(dist);
  delay(10);
}



void write_text(String txt,int size){
 display.clearDisplay();

 display.setTextSize(size);
 display.setTextColor(WHITE);
 display.setCursor(0, 10);
 // Display static text
 display.println(txt);
 display.display(); 
}
