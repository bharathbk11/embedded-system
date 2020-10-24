#include <ESP8266WiFi.h>
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(13, 15);//d7 and d8

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const char* NAME;
const char* ID;

String Event_Name = "fingerprint";

String Key = "Q9_byudwiygHHSFcjtQzdsOCe9SIns8w2IKho8fQiK";

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
const char *ssid =  "project";    
const char *pass =  "12345678";

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define Relay 4
#define Warning 14
const int sensor = 5;
const int Switch = 12 ;
int state,switch_state;

void opendoor()
{  
   digitalWrite(Warning,HIGH);
   delay(500);
   digitalWrite(Warning,LOW);
   digitalWrite(Relay,HIGH);
   delay (5000);       // Relay on for 5 sec 
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
  if (finger.fingerID == 1) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "BHARATH B K";
    ID = "TT1537";
    if (finger.confidence >= 60) 
    {
      Serial.print("Attendace Marked for ");  
      Serial.println(NAME);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(NAME);
      lcd.setCursor(0,1);
      lcd.print("EID:");
      lcd.print(ID);
      makeIFTTTRequest();
      opendoor();
    }

  }

  if (finger.fingerID == 4 ) 
  {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "SHAFIULLA S";
    ID = "TT1504";
    if (finger.confidence >= 60) 
    {
      Serial.print("Attendace Marked for "); 
      Serial.println(NAME);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(NAME);
      lcd.setCursor(0,1);
      lcd.print("EID:");
      lcd.print(ID);
      makeIFTTTRequest();
      opendoor();
    }      //don't ned to run this at full speed.

  }
  finger.fingerID = 0;
  if(!(switch_state = digitalRead(Switch)))
  {
     opendoor();
  }
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
   digitalWrite (Relay,LOW);
   }  
   lcd.clear();
   lcd.setCursor(0,0);
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
