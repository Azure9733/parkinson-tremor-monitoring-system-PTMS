#include<SPI.h>
#include<SD.h>

File myfile;//create file object
void setup()
{
  Serial.begin(9600); //initialising serial monitor
  while (!Serial)
  { }
  while (!SD.begin(4)) {
  Serial.println("SD card not initialised !!!"); } //SD.begin(chip_select pin)
  Serial.println("SD card ready to use!");
  
  myfile=SD.open("file1.txt",FILE_WRITE);
  if (myfile){
    myfile.println("hola amigo");
    Serial.println("All changes saved"); 
    myfile.close();
    }
  else {
    Serial.println("Unable to open file"); }
}
void loop()
{
  
}
