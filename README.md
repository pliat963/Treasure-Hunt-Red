# Treasure-Hunt-Red

A "treasure hunt" game that aims to encourage playing outside.
The game consists of a treasure-searching device ("hunter"), and one or more treasures.


By: Plia Trabelsi, Yonatan Reches, Noam Reches

# Repository Structure

- UNIT TESTS directory - contains seperate components tests 

- treasure_hunt directory - contains the files of the project: 

  - treasure_hunt/treasures directory - the code for the "treasure" devices
   
  - treasure_hunt/hunter directory - the code for the device that dearches the treasures 
   
   - SECRETS.h - placed at treasure_hunt/hunter, treasure_hunt/treasures/treasure1 and treasure_hunt/treasures/treasure2. 
      contains wifi passwords, to be replaced by the real passwords

- ASSETS directory - contains a paraboic reflector 3d-print file, used for one treasure

- user interface.pdf - describes how to use the project




# Used Libraries
1. Adafruit SSD1306 by Adafruit, version 2.5.7
2. Adafruit GFX Library by Adafruit, version 1.11.3
3. Adafruit BusIO by Adafruit, version 1.13.2
4. Kalman filter library: https://github.com/bachagas/Kalman (last commit: 2 Oct 2014)
5. From the esp8266 package version 3.0.2:  
   - ESP8266WiFi by Ivan Grokhotkov version 1.0
   - Wire by Arduino version 1.0


