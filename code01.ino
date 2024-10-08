#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// Sensor-specific setup (replace with your actual sensor configuration)
#define SENSOR_PIN 34 // Adjust this pin based on your sensor connection
#define SENSOR_TYPE "YourSensorType" // Replace with the actual sensor type

// SD card setup
#define SD_CS_PIN 5 // Adjust this pin based on your SD card module
#define CSV_FILENAME "sensor_data.csv"

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (1); // Stop execution if SD card initialization fails
  }

  // Initialize sensor (replace with your specific sensor initialization code)
  // ...

  // Create a new CSV file or open an existing one
  File file = SD.open(CSV_FILENAME, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  // Write the CSV header (adjust column names as needed)
  file.println("Timestamp,SensorValue");
  file.close();
}

void loop() {
  // Read sensor data (replace with your specific sensor reading code)
  float sensorValue = analogRead(SENSOR_PIN); // Example for an analog sensor

  // Convert sensor value to desired units (if necessary)
  // ...

  // Get current timestamp
  unsigned long timestamp = millis();

  // Print data to serial monitor for debugging
  Serial.print("Timestamp: ");
  Serial.print(timestamp);
  Serial.print(", Sensor Value: ");
  Serial.println(sensorValue);

  // Write data to CSV file
  File file = SD.open(CSV_FILENAME, FILE_APPEND);
  if (file) {
    file.print(timestamp);
    file.print(",");
    file.println(sensorValue);
    file.close();
  } else {
    Serial.println("Failed to open file for appending");
  }

  // Delay between readings (adjust as needed)
  delay(1000); // Example: 1 second delay
}
