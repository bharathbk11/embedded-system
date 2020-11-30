#include <Wire.h>
#include <EEPROM.h>
#include <RTC.h>
static DS3231 RTC;

#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
/***************************************************************************************************************************/
const int TIME_KEY=4;
const int ON_KEY=5;
const int OFF_KEY=6;
const int OK_KEY=7;
const int start_stop = 3;
const int motor_pin = 2;
int ON_STATUS,OFF_STATUS,OK_STATUS,TIME_STATUS,start_stop_status,toggle=0;

const int hourPin = A0;
const int minPin = A1;

int hourValue = 0;       // the sensor value
int hourMin = 1023;      // minimum sensor value
int hourMax = 0;         // maximum sensor value
int minValue = 0;        // the sensor value
int minMin = 800;        // minimum sensor value
int minMax = 0;          // maximum sensor value
/***************************************************************************************************************************/

long previousMillis = 0;
long interval = 1000;   
int on_hour,on_min,off_hour,off_min,time_hour,time_min;
int on_hour1,on_min1,off_hour1,off_min1;
int count=60;

/***************************************************************************************************************************/
void setup() 
{
  Serial.begin(9600);
  RTC.begin();

  lcd.begin(16, 2);

  pinMode(TIME_KEY,INPUT_PULLUP);
  pinMode(ON_KEY,INPUT_PULLUP);
  pinMode(OFF_KEY,INPUT_PULLUP);
  pinMode(OK_KEY,INPUT_PULLUP);
  pinMode(start_stop,INPUT_PULLUP);
  pinMode(motor_pin,OUTPUT);
}

void loop() 
{ 
  eeprom_read();
  gettime();
  ON_STATUS=digitalRead(ON_KEY);
  OFF_STATUS=digitalRead(OFF_KEY);
  OK_STATUS=digitalRead(OK_KEY);
  start_stop_status=digitalRead(start_stop);
  //Serial.println(ON_STATUS);
  //Serial.println(OFF_STATUS);
  //Serial.println(OK_STATUS);
  if(ON_STATUS==LOW)
  {
    motorON();
  }
  if(OFF_STATUS==LOW)
  {
    motorOFF();
  }
  if(start_stop_status==LOW)
  {
    if(toggle==0)
    {
      ONTIMER();
      digitalWrite(motor_pin,LOW);
    }  
    else
    {
      clocktimer();
      digitalWrite(motor_pin,HIGH);
    }
  }
  Serial.print("Toggle=");
  Serial.println(toggle);
  eeprom_write();
}

void gettime()
{
  if (RTC.isRunning())
  { 
    lcd.clear();
   /* lcd.setCursor(0, 1);
    lcd.print("Date:");
    lcd.print(RTC.getDay());
    lcd.print("-");
    lcd.print(RTC.getMonth());
    lcd.print("-");
    lcd.print(RTC.getYear());
    lcd.print(" ");*/

    lcd.setCursor(0, 0);
    lcd.print("Time=");
    lcd.print(RTC.getHours());
    lcd.print(":");
    lcd.print(RTC.getMinutes());
    lcd.print(":");
    lcd.print(RTC.getSeconds());
    lcd.print("");
    
    Serial.print(RTC.getDay());
    Serial.print("-");
    Serial.print(RTC.getMonth());
    Serial.print("-");
    Serial.print(RTC.getYear());
    Serial.print(" ");
    Serial.print(RTC.getHours());
    Serial.print(":");
    Serial.print(RTC.getMinutes());
    Serial.print(":");
    Serial.print(RTC.getSeconds());
    Serial.print("");
    if (RTC.getHourMode() == CLOCK_H12)
    {
      switch (RTC.getMeridiem()) {
      case HOUR_AM:
        Serial.print(" AM");
        lcd.print(" AM");
        break;
      case HOUR_PM:
        Serial.print(" PM");
        lcd.print(" PM");
        break;
      }
    }
    Serial.println("");
    period1();
    delay(1000);
  }
}

void period1()
{ 
  if(toggle==0)
  {
    lcd.setCursor(0, 1);
    lcd.print("RUNNING ");
    lcd.print(on_hour);
    lcd.print(":");
    if(on_min!=0)
    {
      lcd.print(on_min-1);
      lcd.print(":");
      lcd.print(count);
    }
    else
      lcd.print("0:0");
   }
   else
   {
    lcd.setCursor(0, 1);
    lcd.print("STARTS AT ");
    lcd.print(off_hour);
    lcd.print(":");
    lcd.print(off_min);
   }
}

void motorON()
{ 
  while(OK_STATUS==HIGH)
  {
  hourValue = analogRead(hourPin);
  hourValue = map(hourValue,hourMin,hourMax,0,13);
  hourValue = constrain(hourValue,0,13);

  minValue = analogRead(minPin);
  minValue = map(minValue,minMin,minMax,0,60);
  minValue = constrain(minValue,0,60);

  Serial.print("HOUR:");
  Serial.print(hourValue);
  Serial.print(" ");
  Serial.print("MINUTE:");
  Serial.println(minValue);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor ON period");
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.print(hourValue);
  lcd.print(":");
  lcd.print(minValue);
  delay(200);
  OK_STATUS=digitalRead(OK_KEY);
  }
  if(OK_STATUS==LOW)
  {
    on_hour=hourValue;
    on_min=minValue;
    on_hour1=hourValue;
    on_min1=minValue;
    count=60;
  }
}

void motorOFF()
{
  while(OK_STATUS==HIGH)
  {
  hourValue = analogRead(hourPin);
  hourValue = map(hourValue,hourMin,hourMax,0,13);
  hourValue = constrain(hourValue,0,13);

  minValue = analogRead(minPin);
  minValue = map(minValue,minMin,minMax,0,60);
  minValue = constrain(minValue,0,60);

  Serial.print("HOUR:");
  Serial.print(hourValue);
  Serial.print(" ");
  Serial.print("MINUTE:");
  Serial.println(minValue);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor OFF period");
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.print(hourValue);
  lcd.print(":");
  lcd.print(minValue);
  delay(200);
  OK_STATUS=digitalRead(OK_KEY);
  }
  if(OK_STATUS==LOW)
  {
    off_hour=hourValue;
    off_min=minValue;
    off_hour1=hourValue;
    off_min1=minValue;
  }
}

void ONTIMER()
{
  unsigned long currentMillis = millis();  
  if(on_min!=0 || on_hour!=0)
  {
  if(currentMillis - previousMillis > interval) 
  {
    previousMillis = currentMillis; 
    count--;  
    if(count==0 && on_min!=0)
    {
      count=60;
      on_min=on_min-1;
    }
    if(on_min==0 && on_hour!=0)
    {
      on_hour=on_hour-1;
      on_min=60;
    }
    Serial.print(on_hour);
    Serial.print(":");
    if(on_min!=0)
    {
      Serial.print(on_min-1);
      Serial.print(":");
      Serial.println(count);
    }
    else
      Serial.print("0:0");
    }  
  }
  if(on_min==0 && on_hour==0 && count==60)
  {
    toggle=1;
    off_hour=off_hour1+(RTC.getHours());
    off_min=off_min1+(RTC.getMinutes());
    
    if(off_hour>=24)
      off_hour=off_hour-24;
    if(off_min>=60)
      off_min=off_min-60;
    Serial.println(off_hour);
    Serial.println(off_min);
  }
}

void clocktimer()
{
  if(off_hour<=RTC.getHours())
    if(off_min<=RTC.getMinutes())
    {
      toggle=0;
      on_hour=on_hour1;
      on_min=on_min1;
    }
}

void eeprom_write()
{
  EEPROM.write(0, on_hour);
  EEPROM.write(1, on_hour1);
  EEPROM.write(2, off_hour);
  EEPROM.write(3, off_hour1);
  EEPROM.write(4, on_min);
  EEPROM.write(5, on_min1);
  EEPROM.write(6, off_min);
  EEPROM.write(7, off_min1);
  EEPROM.write(8, toggle);
  EEPROM.write(9, count);
}
void eeprom_read()
{
  on_hour=EEPROM.read(0);
  on_hour1=EEPROM.read(1);
  off_hour=EEPROM.read(2);
  off_hour1=EEPROM.read(3);
  on_min=EEPROM.read(4);
  on_min1=EEPROM.read(5);
  off_min=EEPROM.read(6);
  off_min1=EEPROM.read(7);
  toggle=EEPROM.read(8);
  count=EEPROM.read(9);
}
