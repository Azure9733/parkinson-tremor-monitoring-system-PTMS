//uncomment the line below and try once
//#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 5 // Chip Select pin for SD card
#define SPI_MOSI 23 // SD Card MOSI
#define SPI_MISO 19 // SD Card MISO
#define SPI_SCK 18 // SD Card Clock

void setup() {
    // Start Serial communication
    Serial.begin(115200);

    // Set the CS pin as output
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH); // Deselect the SD card

    // Initialize SPI
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_CS);

    // Initialize SD card
    if (!SD.begin(SD_CS)) {
        Serial.println("Error talking to SD card!");
        while (true); // Stay here if the card is not found
    }

    // Print message if the SD card is identified
    Serial.println("SD card identified.");
}

void loop() {
    // Your loop code here
}
