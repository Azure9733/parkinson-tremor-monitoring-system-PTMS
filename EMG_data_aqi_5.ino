#include <SD.h>
#include <SPI.h>
#include "Wire.h"

#define SAMPLE_RATE  500
#define BAUD_RATE 115200
#define INPUT_PIN A0
#define BUFFER_SIZE 128

int circular_buffer[BUFFER_SIZE];
int data_index, sum;
int chipSelect = 4; //set chipselect to pin 4 (change number to change pin)

File EMGD; //variable for working with our file object

void setup() 
{
  Serial.begin(BAUD_RATE);
  while (!Serial)
  { }
  while (!SD.begin(4)) {
  Serial.println("SD card not initialised !!!"); } //SD.begin(chip_select pin)
  Serial.println("SD card ready to use!");
  

  pinMode(10, OUTPUT); //reserve pin 10 as an output dont use for other parts of circuit.
  SD.begin(chipSelect); //initialise the sd card with chipselect connected to pin 4.
}

void loop() 
{

  EMGD = SD.open("PTR9.txt" , FILE_WRITE); //open PRT3.txt to write data onto the file. File can already be preexisting or will be made by code itself. make new file every time there is new patient or for every new module we make.
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 0;
  timer -= interval;

  // Sample and get envelop
  if(timer < 0) 
  {
    timer += 1000000 / SAMPLE_RATE;
    int sensor_value = analogRead(INPUT_PIN);
    int signal = EMGFilter(sensor_value);
    int envelop = getEnvelop(abs(signal));
    if(EMGD)
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
    
  }
}

// Envelop detection algorithm
int getEnvelop(int abs_emg){
  sum -= circular_buffer[data_index];
  sum += abs_emg;
  circular_buffer[data_index] = abs_emg;
  data_index = (data_index + 1) % BUFFER_SIZE;
  return (sum/BUFFER_SIZE) * 2;
}

// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 500.0 Hz, frequency: [74.5, 149.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference: 
// https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
// https://courses.ideate.cmu.edu/16-223/f2020/Arduino/FilterDemos/filter_gen.py
float EMGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.05159732*z1 - 0.36347401*z2;
    output = 0.01856301*x + 0.03712602*z1 + 0.01856301*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.53945795*z1 - 0.39764934*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.47319594*z1 - 0.70744137*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.00211112*z1 - 0.74520226*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}
