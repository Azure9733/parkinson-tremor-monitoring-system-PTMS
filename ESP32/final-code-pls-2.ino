#include <WiFi.h>
#include <WebSocketsServer.h>
#include <SD.h>
#include <SPI.h>
#include "Wire.h"

#define SAMPLE_RATE  500
#define BAUD_RATE 115200
#define INPUT_PIN 35
#define BUFFER_SIZE 128

// WiFi credentials
const char* ssid = "Galaxy_F23_5G_E192";
const char* password = "bspe0280";

// Create a WebSocket server object
WebSocketsServer webSocket = WebSocketsServer(81);

int circular_buffer[BUFFER_SIZE];
int data_index, sum;
int chipSelect = 5; // Set chip select to pin 5

File EMGD; // Variable for working with our file object

// Forward declaration of the event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

void setup() 
{
  Serial.begin(BAUD_RATE);
  while (!Serial) { }
  while (!SD.begin(chipSelect)) {
    Serial.println("SD card not initialised !!!");
  }
  Serial.println("SD card ready to use!");

  pinMode(10, OUTPUT); // Reserve pin 10 as an output
  SD.begin(chipSelect); // Initialize the SD card

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to Wi-Fi. IP address: ");
  Serial.println(WiFi.localIP());

  // Start the WebSocket server and set the event handler
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() 
{
  webSocket.loop();

  EMGD = SD.open("PTR9.txt", FILE_WRITE); // Open PTR9.txt to write data
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 0;
  timer -= interval;

  // Sample and get envelope
  if (timer < 0) 
  {
    timer += 1000000 / SAMPLE_RATE;
    int sensor_value = analogRead(INPUT_PIN);
    int signal = EMGFilter(sensor_value);
    int envelop = getEnvelop(abs(signal));
    
    if (EMGD)
    {
      EMGD.print(millis());
      EMGD.print(",");
      EMGD.print(signal);
      EMGD.print(",");
      EMGD.println(envelop);
      EMGD.close();

      Serial.print(signal);
      Serial.print(",");
      Serial.println(envelop);
    }

    // Create a JSON string with the data
    String payload = "{";
    payload += "\"time\": \"" + String(millis()) + "\",";
    payload += "\"signal\": " + String(signal) + ",";
    payload += "\"envelope\": " + String(envelop);
    payload += "}";

    // Broadcast the data
    webSocket.broadcastTXT(payload);
    delay(10);
  }
}

// Envelope detection algorithm
int getEnvelop(int abs_emg) {
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
  // ... (other filter sections)
  return output;
}

// Event handler for WebSocket events
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      // Handle disconnection event
      break;
    case WStype_CONNECTED:
      // Handle new connection event
      break;
    case WStype_TEXT:
      // Handle incoming text message event
      break;
  }
}
