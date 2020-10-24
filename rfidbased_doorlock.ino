
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,13); // RX, TX
int count = 0;
char tags[10][12]={"55007341D0B7","55007341D1B6","5500734395F0","5500E8C4BBC2","550073455E3D","5900D4E7D1BB","5900D4FC1362","5900D50BD255"};                             
char input[12];                                        
 int flag = 0,a;   
boolean match = 0;

#define Relay 4
#define Warning 6
const int sensor = 3;
const int Switch = A0;
int state,switch_state;

int check(char input[],char tag[])
{
  count =0; // reset counter varibale to 0
  match = 1;
  while(count<12 && match==1)  
  {
    if(input[count]==tag[count])
        match = 1; 
    else
        match= 0; 
    count++; 
   }
   if(match == 1) 
      return 1;
    else
      return 0;
}
void opendoor()
{  
   digitalWrite(Warning,HIGH);
   delay(500);
   digitalWrite(Warning,LOW);
   digitalWrite(Relay,HIGH);
   delay (5000);       // Relay on for 5 sec
   while(state = digitalRead(sensor));
   digitalWrite(Warning,HIGH);
   delay(300);
   digitalWrite(Warning,LOW);
   delay(300);
   digitalWrite(Warning,HIGH);
   delay(300);
   digitalWrite(Warning,LOW);
   delay(300);
   digitalWrite (Relay,LOW); 
}

void setup()
{ 
   Serial.begin(9600);
   mySerial.begin(9600);
   lcd.begin(16, 2);
   pinMode(Relay,OUTPUT);  
  pinMode(Warning,OUTPUT);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(Switch, INPUT_PULLUP);
}
void loop()
{ 

  lcd.print("   Place the   ");
  lcd.setCursor(0, 1);
  lcd.print("    Tag Here    ");
   if(mySerial.available())
   {
      count = 0;
      while(mySerial.available() && count < 12)          
      {
         input[count] = mySerial.read();
         count++;
         delay(5);
      }
      Serial.println(input);  
     flag=0;
     a=0;                       
     while(flag<10 && a==0)
     {
      if(a=check(input,tags[flag]))
        break;
      else
        flag++;
     }
     lcd.clear();
      switch(flag)
      {
        case 0: Serial.println("user1 Access Granted");
                lcd.print("User1");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                 lcd.clear();
                break;
        case 1: Serial.println("user2 Access Granted");
                lcd.print("User2");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                 lcd.clear();
                break;
        case 2: Serial.println("user3 Access Granted");
                lcd.print("User3");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                 lcd.clear();
                break;
        case 3: Serial.println("user4 Access Granted");
                lcd.print("User4");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                 lcd.clear();
                break;
        case 4: Serial.println("user5 Access Granted");
                lcd.print("User5");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                 lcd.clear();
                break;
        case 5: Serial.println("user6 Access Granted");
                lcd.print("User6");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                 lcd.clear();
                break;
        case 6: Serial.println("user7 Access Granted");
                lcd.print("User7");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                lcd.clear();
                break;
        case 7: Serial.println("user8 Access Granted");
                lcd.print("User8");
                lcd.setCursor(0, 1);
                lcd.print("Access Granted");
                opendoor();
                lcd.clear();
                break;
        default:Serial.println("Access Denied");
                lcd.print("  INVALID CARD  ");
                lcd.setCursor(0, 1);
                lcd.print("  Access Denied  ");
                for(int i=0;i<3;i++)
                {
                  tone(Warning, 400);
                  delay(200);
                  noTone(Warning);
                  delay(200);
                }
                 lcd.clear();
      }
  }
  if(!(switch_state = digitalRead(Switch)))
    opendoor();
}
