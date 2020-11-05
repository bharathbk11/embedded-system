#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial gsm(2,3); // RX, TX

LiquidCrystal lcd(12,13,7,6,5,4);

int FloatSensor1 = 8;
int FloatSensor2 = 9;
int motorpin = 10;
int valvepin = 11;
int level1,level2,mts1=0,mts2=0,motor=0 ;

int minitank1 = A0;
int minitank2 = A1;

char Msg[100]="";
char Msg1[]="";
char PreMsg[100]="";


void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  gsm.begin(9600);
  
  pinMode(FloatSensor1, INPUT_PULLUP);
  pinMode(FloatSensor2, INPUT_PULLUP); 
  pinMode(motorpin, OUTPUT);
  pinMode(valvepin, OUTPUT);
  pinMode(minitank1, INPUT);
  pinMode(minitank2, INPUT);
  
}

void loop() 
{
  strcpy(Msg,Msg1);
  motorcontrol();
  valvecontrol();
  turbidity();
 
  if(strcmp(PreMsg,Msg))
  {
    SendMessage(Msg);
    Serial.println(Msg);
  }
}

void motorcontrol()
{
  level1 = digitalRead(FloatSensor1);
  level2 = digitalRead(FloatSensor2);
  if(level1==LOW)
    motor=0;
  if(level2==HIGH)
    motor=1;
    
  if(!motor)
  {
    digitalWrite(motorpin,LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor ON");
      delay(500);
      strcat(Msg,"Motor ON");
      strcat(Msg,"\r\n");
  }
  else
  {
    digitalWrite(motorpin,HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor OFF");
      delay(500);
      strcat(Msg,"Motor OFF");
      strcat(Msg,"\r\n");
  }
}

void valvecontrol()
{
  mts1 = analogRead(minitank1);
  mts2 = analogRead(minitank2);
  
  if(mts1)
  {
    strcat(Msg,"Mini tank1 Valve is OPEN");
    strcat(Msg,"\r\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mini tank1 Valve");
    lcd.setCursor(0, 1);
    lcd.print("is OPEN");
    delay(500);
  }
  else
  {
    strcat(Msg,"Mini tank1 Valve is CLOSED");
    strcat(Msg,"\r\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mini tank1 Valve");
    lcd.setCursor(0, 1);
    lcd.print("is CLOSED");
    delay(500);
  }
  if(mts2)
  {
    strcat(Msg,"Mini tank2 Valve is OPEN");
    strcat(Msg,"\r\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mini tank2 Valve");
    lcd.setCursor(0, 1);
    lcd.print("is OPEN");
    delay(500);
  }
  else
  {
    strcat(Msg,"Mini tank2 Valve is CLOSED");
    strcat(Msg,"\r\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mini tank2 Valve");
    lcd.setCursor(0, 1);
    lcd.print("is CLOSED");
    delay(500);
  }
  if(mts1 | mts2)
  {
    digitalWrite(valvepin,LOW);
    strcat(Msg,"Main tank Valve is OPEN");
    strcat(Msg,"\r\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Main tank Valve");
    lcd.setCursor(0, 1);
    lcd.print("is OPEN");
    delay(500);
  }  
  else
  {
    digitalWrite(valvepin,HIGH);
    strcat(Msg,"Main tank Valve is CLOSED");
    strcat(Msg,"\r\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Main tank Valve");
    lcd.setCursor(0, 1);
    lcd.print("is CLOSED");
    delay(500);
  }
}



int SendMessage(char message[])
{
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm.println("AT+CMGS=\"+918088446427\"\r");
  delay(1000);
  gsm.println(message);
  delay(100);
  gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  strcpy(PreMsg,message);
}
 void turbidity()
 {
  int sensorValue = analogRead(A3); 
  //Serial.println(sensorValue);
  //float voltage = sensorValue * (5.0 / 1024.0); 
  //Serial.println(voltage);
  //delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("turbidity=");
  lcd.setCursor(10, 0);
  lcd.print(sensorValue);
  delay(500);
 }
