#include <SPI.h>
#include <SD.h>

#define SAMPLE_RATE 500
#define BAUD_RATE 9600
#define INPUT_PIN 35

File myFile;
const int CS = 5;

void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);
  delay(500);

  // SD card initialization
  while (!Serial) { ; }  // Wait for serial port to connect (needed for native USB port only)
  Serial.println("Initializing SD card...");
  if (!SD.begin(CS)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialization done.");

  // Create or open the file
  myFile = SD.open("/EMGData.txt", FILE_WRITE);
  if (!myFile) {
    Serial.println("Error opening EMGData.txt");
  } else {
    myFile.println("Timestamp (us), Filtered EMG Signal");  // Adding a header to the file
    myFile.flush(); // Ensure header is written
  }
}

void loop() {
  // Calculate elapsed time
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 0;
  timer -= interval;

  // Sample and log data
  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;
    float sensor_value = analogRead(INPUT_PIN);
    float signal = EMGFilter(sensor_value);

    // Write data to the file
    if (myFile) {
      myFile.print(micros());
      myFile.print(",");
      myFile.println(signal);
      myFile.flush(); // Flush to ensure the data is written
    } else {
      Serial.println("File not open!");
    }

    // Print the filtered signal for visualization (optional)
    Serial.print(125);
    Serial.print(",");
    Serial.print(-125);
    Serial.print(",");
    Serial.println(signal);
  }
}

// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 500.0 Hz, frequency: [74.5, 149.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
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
