#include <SPI.h>
#include <SD.h>

const int chipSelect = 5;

void setup() {
  Serial.begin(9600);

  // Initialize SPI bus
  SPI.begin();

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");
}

void loop() {
  // Create a file named "test.txt"
  File dataFile = SD.open("test.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Hello, world!");
    dataFile.close();
    Serial.println("File created successfully.");
  } else {
    Serial.println("Failed to create file");
  }
}
