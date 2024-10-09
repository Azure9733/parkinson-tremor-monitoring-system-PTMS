#include <SPI.h>
#include <SD.h>

#define SD_CS 10 // Chip Select pin for SD card
#define SPI_MOSI 11 // SD Card MOSI
#define SPI_MISO 13 // SD Card MISO
#define SPI_SCK 12 // SD Card Clock

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
