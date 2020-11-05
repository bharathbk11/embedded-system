#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "h2TvmyE1AwHo18Ofhf7xXhXsDHonCG__";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "tharanga 2.4";
char pass[] = "tt02072019";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
