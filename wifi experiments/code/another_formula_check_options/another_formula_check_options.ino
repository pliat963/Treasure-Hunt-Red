
#include <ESP8266WiFi.h>
#include <math.h>
#include "Kalman.h"
#include "movingAverage.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>

#define BUTTON_PIN D3 // the number of the pushbutton pin

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int currentState;                      // the current reading from the input pin
double current_dist;


double measurement, filteredMeasurement;
Kalman myFilter(0.125, 32, 1023, 0); // suggested initial values for high noise filtering

//for exponential smoothing
double exp_sm_last=WiFi.RSSI();
double exp_sm_current=0;
double exp_sm_alpha = 0.1;


const char *ssid = "TREASURE1";
const char *password = "pasword1";

//functions declarations
void getDistAverage(int pointsNumber=20);
void getDistKalmanFilter(int pointsNumber=10);
void write_text(String txt, int size=1);
void exponential_smoothing();
void exponential_smoothing_with_kalman();
void getDistMovingAverage();


void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }


  write_text("Connecting to "+ String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    write_text("Not connected",2);
  }
  write_text(" Connected",2);
  

}

void loop()
{
  getDistKalmanFilter();
  delay(5);
}


void getDistKalmanFilter(int pointsNumber)
{
  double total_rssi = 0;
  double dist;
  for (int i = 0; i < pointsNumber; i++)
  {
    total_rssi +=  myFilter.getFilteredValue(WiFi.RSSI());
    delay(5);
  }
  double avg_rssi = total_rssi/pointsNumber;

  double power =(-40.054-avg_rssi)/20; 
  dist = pow(10, power);
  write_text(String(dist),3);
 
}


void exponential_smoothing(){
  
  exp_sm_current = exp_sm_alpha*WiFi.RSSI() +(1-exp_sm_alpha)*exp_sm_last;
  exp_sm_last = exp_sm_current;
  
  double power =(-40.054-exp_sm_current)/20; 
  current_dist = pow(10, power);
  write_text(String(current_dist),2);
  
}


//for the moving average
SimpleMovingAverage obj(20);
void getDistMovingAverage(){
  int per = 20;

  obj.addData(WiFi.RSSI());
  delay(5);
  
  double power =(-40.054-obj.getMean())/20; 
  current_dist = pow(10, power);
  write_text(String(current_dist),3);
}

void exponential_smoothing_with_kalman(){
  
  exp_sm_current = exp_sm_alpha*myFilter.getFilteredValue(WiFi.RSSI()) +(1-exp_sm_alpha)*exp_sm_last;
  exp_sm_last = exp_sm_current;
  
  double power =(-40.054-exp_sm_current)/20; 
  current_dist = pow(10, power);
  write_text(String(current_dist),2);
  
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
