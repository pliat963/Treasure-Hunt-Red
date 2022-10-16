
#include <ESP8266WiFi.h>

const char* ssid = "wifi_name";
const char* password = "verysecret1";

long rssi = WiFi.RSSI();
double n = 2, A=-37; //parameters of the used formula
double ratio, wifiDistance;

int distance;

 
void setup(){
  Serial.begin(9600);
 

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Not connected");  
  }
  Serial.println(" Connected");
}
 
void loop(){

  rssi = getStrength(10);
  ratio = (A-rssi)/(10*n);
  wifiDistance = pow(10, ratio) * 100; //*100 to measure in cm



  Serial.print("wifiDistance: ");
  Serial.print(wifiDistance);
  Serial.print(" cm, ");
 Serial.print("rssi: ");
  Serial.println(rssi);
  Serial.println(" dBm, ");
  delay(100);
 
}

//to get the average rssi
int getStrength(int pointsNumber){
    long rssi = 0;
    long averageRSSI = 0;
    
    for (int i=0;i < pointsNumber;i++){
        rssi += WiFi.RSSI();
        delay(20);
    }

   averageRSSI = rssi/pointsNumber;
    return averageRSSI;
}
