#include <SD.h>
#include <SPI.h>

#define SAMPLE_RATE 500
#define BAUD_RATE 115200
#define INPUT_PIN 35
#define BUFFER_SIZE 128
#define CS_PIN 5 // Chip select for SD card

int circular_buffer[BUFFER_SIZE];
int data_index = 0, sum = 0;

File EMGD; // File object for EMG data

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) { }

  // Configure ADC for ESP32
  analogReadResolution(12); // Set ADC resolution to 12 bits
  analogSetPinAttenuation(INPUT_PIN, ADC_11db); // Set attenuation for full range

  // Initialize SD card
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (true); // Halt execution if SD fails
  }
  Serial.println("SD card ready to use!");

  // Open or create the file
  EMGD = SD.open("/EMGData001.txt", FILE_WRITE);
  if (!EMGD) {
    Serial.println("Error opening EMGData001.txt");
    while (true); // Halt if file can't be opened
  } else {
    //EMGD.println("Timestamp (ms), Signal, Envelope"); //Header for the file
    EMGD.flush(); // Ensure header is written
  }
}

void loop() {
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  static long timer = 0;
  timer -= interval;

  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;
    
    int sensor_value = analogRead(INPUT_PIN);
    int signal = EMGFilter(sensor_value);
    int envelope = getEnvelope(abs(signal));

    if (EMGD) {
      EMGD.print(millis());
      EMGD.print(",");
      EMGD.print(signal);
      EMGD.print(",");
      EMGD.println(envelope);
      EMGD.flush(); // Ensure data is written properly

      Serial.print(signal);
      Serial.print(",");
      Serial.println(envelope);
    } else {
      Serial.println("Error writing to file!");
    }
  }
}

// Envelope detection algorithm
int getEnvelope(int abs_emg) {
  sum -= circular_buffer[data_index];
  sum += abs_emg;
  circular_buffer[data_index] = abs_emg;
  data_index = (data_index + 1) % BUFFER_SIZE;
  return (sum / BUFFER_SIZE) * 2;
}

// Band-Pass Butterworth IIR digital filter
float EMGFilter(float input) {
  float output = input;
  {
    static float z1, z2; // Filter section state
    float x = output - 0.05159732 * z1 - 0.36347401 * z2;
    output = 0.01856301 * x + 0.03712602 * z1 + 0.01856301 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // Filter section state
    float x = output - -0.53945795 * z1 - 0.39764934 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // Filter section state
    float x = output - 0.47319594 * z1 - 0.70744137 * z2;
    output = 1.00000000 * x + 2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // Filter section state
    float x = output - -1.00211112 * z1 - 0.74520226 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}
