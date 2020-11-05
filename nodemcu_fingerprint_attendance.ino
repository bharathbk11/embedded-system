#include <ESP8266WiFi.h>
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(13, 15);//d7 and d8

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const char* NAME;
const char* ID;

String Event_Name = "fingerprint";

String Key = "f6lReL_xNyCES_gwjKTIWA9wRqzFil-wZb2TUmZibVX";

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
const char *ssid =  "tharanga 2.4";    
const char *pass =  "tt02072019";

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define Relay 12          //D6
#define Warning 14
const int sensor = 5;     //D1
const int Switch = 4 ;    //D2
int state,switch_state;
int doorstatus=0;

void opendoor()
{  
   digitalWrite(Warning,HIGH);
   delay(500);
   digitalWrite(Warning,LOW);
   digitalWrite(Relay,LOW);
   delay (5000);       // Relay on for 5 sec 
   doorstatus=1;
}

void update_data()
{
      Serial.print("Attendace Marked for "); 
      Serial.println(NAME);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(NAME);
      lcd.setCursor(0,1);
      lcd.print("EID:");
      lcd.print(ID);
      opendoor();
      makeIFTTTRequest();  
}

void setup()
{ 
  Wire.begin(2,0);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  
  pinMode(Relay,OUTPUT);  
  pinMode(Warning,OUTPUT);
  pinMode(Switch, INPUT_PULLUP);
  pinMode(sensor, INPUT_PULLUP);
  digitalWrite(Relay,HIGH);
  Serial.begin(115200);
  mySerial.begin(115200);
  while (!Serial);  
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) 
  {
    Serial.println("Found fingerprint sensor!");
  } 
  else 
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) 
    {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); 
  Serial.print(finger.templateCount); 
  Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  
  //Serial.print("Connecting to: ");
  //Serial.print(ssid);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to: ");
  lcd.setCursor(0,1);
  lcd.print(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    lcd.print(".");
  }
      Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi connected");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()                     
{
  getFingerprintIDez();
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 1) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "BHARATH B K";
    ID = "TT1537";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 2 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "MOHITH N";
    ID = "TT1534";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 3) 
    {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "ROHITH T C";
    ID = "TT1501";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 4 ) 
    {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "SHAFIULLA S";
    ID = "TT1504";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 5) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "BHANUPRIYA A V";
    ID = "TT1505";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 6 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "LAVANYA G N";
    ID = "TT1519";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 7) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "SOWMYA S L";
    ID = "TT1523";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
 /**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 8 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "LIKITH H P";
    ID = "TT1530";
  if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 9 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "KAVITHA N";
    ID = "TT1534";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 10) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "KIRAN B R";
    ID = "TT1535";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 11 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "VIDYALAKSHMI T S";
    ID = "TT1536";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 12) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "KAVANA G";
    ID = "TT1538";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 13 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "MADHUSHREE R";
    ID = "TT1539";
  if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 14) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "SACHINKUMAR KITTUR";
    ID = "TT1540";
if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 15 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "RANGANATH C T";
    ID = "TT1541";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 16) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "MANJUNATH T N";
    ID = "TT15342";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 17 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "MONIKA T M";
    ID = "TT1543";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 18) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "RAMYA T N";
    ID = "TT1544";
  if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 19 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "LAVANYA G";
    ID = "TT1547";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 20) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "PUSHPA S";
    ID = "TT1548";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 21 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "K V PRUTHVI REDDY";
    ID = "TT1549";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
    if (finger.fingerID == 22) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "SAHANA B";
    ID = "TT1552";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 23 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "MANUJA S";
    ID = "TT1553";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/  
    if (finger.fingerID == 24) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "ARUN KUMAR P";
    ID = "TT1554";
    if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 25 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "CHANDRASHEKAR S";
    ID = "TT1555";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/  
    if (finger.fingerID == 26) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "ARSHITHA P KOTTUR";
    ID = "TT1556";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 27 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "DARSHAN T R";
    ID = "TT1558";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/ 
 if (finger.fingerID == 28) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "REKHASHREE L";
    ID = "TT1560";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
  if (finger.fingerID == 29) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "SHREYA B K";
    ID = "TT1561";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/
if (finger.fingerID == 30) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "CHETAN M";
    ID = "TT1551";
   if (finger.confidence >= 60) 
    {
      update_data();
    }
  }
/**********************************************************************************************************************8*****************************************/

  finger.fingerID = 0;
  if(!(switch_state = digitalRead(Switch)))
  {
     opendoor();
  }
  if(doorstatus==1)
  {
  state = digitalRead(sensor);
   if(state==LOW)
   {
    digitalWrite(Warning,HIGH);
    delay(300);
    digitalWrite(Warning,LOW);
    delay(300);
    digitalWrite(Warning,HIGH);
    delay(300);
    digitalWrite(Warning,LOW);
    delay(300);
    digitalWrite (Relay,HIGH);
    doorstatus=0;
   }  
  }
  
  
   lcd.clear();
   lcd.setCursor(0,0);
   //lcd.println(doorstatus);
   lcd.print(" Attendace Mgmt ");
   lcd.setCursor(0,1);
   lcd.print("     system     ");
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() 
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  return finger.fingerID;
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() 
{
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) 
  {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) 
  {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);

  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") + NAME + "\",\"value2\":\"" + ID + "\"}";
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) 
  {
    delay(100);
  }
  if (!!!client.available()) 
  {
    Serial.println("No response...");
  }
  while (client.available()) 
  {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}
