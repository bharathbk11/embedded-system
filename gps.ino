#include<SoftwareSerial.h>
   
SoftwareSerial gps(2,3);


int i=0;
int  gps_status=0;
String cordinat="<p>Coordinates:</p>";          
String latitude=""; 
String logitude="";                       
String gpsString="";
char *test="$GPGGA";

void setup() 
{
  Serial.begin(9600);
  gps.begin(9600);
}

void loop() 
{
     get_gps();
     coordinate_display();
     delay(2000);
}


void gps_Function()
{
  gpsString="";
  while(1)
  {
   while (gps.available()>0)                //Serial incoming data from GPS
   {
    char inChar = (char)gps.read();
    gpsString+= inChar;                    //store incoming data from GPS to temporary string str[]
    //Serial.println(gpsString);
    i++;
    if (i < 7)                      
    {
      if(gpsString[i-1] != test[i-1])       //check for right string
      {
        i=0;
        gpsString="";
      }
    }
    if(inChar=='r')
    {
      if(i>65)
      {
        gps_status=1;
        break;
      }
      else
      {
        i=0;
      }
    }
  }
  if(gps_status)
  break;
  }
}

void get_gps()
{
  gps_status=0;
  while(gps_status==0)
  {
    gps_Function();
    int str_lenth=i;
    latitude="";
    logitude="";
    coordinate2dec();
    i=0;
    str_lenth=0;
  }
}

void coordinate_display()
{
  Serial.print("Latitude:");
  Serial.println(latitude);
  Serial.print("Longitude:");
  Serial.println(logitude);
}

void coordinate2dec()
{
  String lat_degree="";
  for(i=18;i<20;i++)          //extract latitude from string
    lat_degree+=gpsString[i];
  String lat_minut="";
  for(i=20;i<28;i++)
    lat_minut+=gpsString[i];
  String long_degree="";
  for(i=30;i<33;i++)          //extract longitude from string
    long_degree+=gpsString[i];
  String long_minut="";
  for(i=33;i<41;i++)
    long_minut+=gpsString[i];
  float minut= lat_minut.toFloat();
  minut=minut/60;
  float degree=lat_degree.toFloat();
  latitude=degree+minut;
  minut= long_minut.toFloat();
  minut=minut/60;
  degree=long_degree.toFloat();
  logitude=degree+minut;
}
