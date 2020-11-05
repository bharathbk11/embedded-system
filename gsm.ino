#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(9600);

Serial.println("Calling through GSM Modem");

// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
delay(2000);
//mySerial.println("ATD8088446427;"); // ATD81290255XX; -- watch out here for semicolon at the end!!

//Serial.println("Called ATD81290255XX");
SendMessage();
}

void loop() // run over and over
{
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918088446427\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
