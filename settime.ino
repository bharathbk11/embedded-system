#include <Wire.h>
#include <RTC.h>

static DS3231 RTC;


void setup() 
{
  Serial.begin(9600);
  RTC.begin();
  settime();
}

void loop() 
{
}
void settime()
{   
    Serial.print("Is Clock Running: ");
    Serial.println("No");
    Serial.println("Setting Time");
    RTC.setHourMode(CLOCK_H12);
    //RTC.setHourMode(CLOCK_H24);
    RTC.setDateTime(__DATE__, __TIME__);
    Serial.println("New Time Set");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);
    RTC.startClock();
}
