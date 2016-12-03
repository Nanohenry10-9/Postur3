/*

  Measures back angle 1500 times (500 * 3), every second = for 25 minutes

*/

#include <Wire.h> // Libraries
#include <SD.h>
#include <SPI.h>

#define scaling 10,100,0,75 // The scaling from raw read to degrees

byte I2Cread = 0; // Reading from I2C bus
int count1 = 0; // Counter
int count2 = 0; // Another counter to prevent lock-ups
bool flag = false; // Variable to see if data has been received
bool fin = false; // Variable to see if the measurements are finished
int address = 0x04; // I2C address (4)
bool des = false; // Destroy old file(s)?

File logFile; // SD card file

void setup() {
  Serial.begin(57600); // Baudrate for Serial communication
  Serial.print("Initialising");
  Wire.begin(address); // Initializing the Wire library with the I2C address
  Wire.onReceive(rec); // Set function to catch the I2C bus data
  Serial.print(".");
  if (!SD.begin(4)) { // Initialise SD card library
    Serial.println(" SD error!");
    fin = true; // Tell the data catching function to stop
    while (1) {}
  }
  Serial.print(".");
  if (des) { // Delete old files
    SD.remove("log.txt");
    Serial.print(".");
  }
  logFile = SD.open("log.txt", FILE_WRITE); // Open/create log file from SD card
  Serial.print(". ");
  Serial.println("Init done!\n");
}

void loop() {
  if (flag) { // Check if data is received
    flag = false; // Reset the "flag"
    count1++; // Increase the first counter
    Serial.print("Received\t");
    Serial.println(I2Cread);
    logFile.println(I2Cread); // Write received data to the log file
    if (count1 >= 500) { // Check if  the first counter has reached 500
      count2++; // Increase the second counter
      count1 = 0; // Reset the first counter
      if (count2 >= 3) { // Check if the second counter has reached 3
        logFile.close(); // Close the log file (so the SD card can be removed)
        Serial.print("\nFinished, safe to remove SD card!");
        fin = true; // Tell the data catching function that the program is finished
        while (1) {} // Stop executing the program
      }
    }
  }
  delay(10);
}

void rec(int byteCount) {
  if (!fin) { // If program has not finished
    Serial.print("Reading... ");
    I2Cread = Wire.read(); // Read byte from Wire (I2C)
    I2Cread = map(I2Cread, scaling); // Map the reading from raw read to degrees
    if (I2Cread > 100) { // If the reading is over 100, set it to zero (to make sure there are no weird spikes)
      I2Cread = 0;
    }
    flag = true; // Tell the other parts of the program that data has been received
  }
}

