int FloatSensor1a = 8;
int FloatSensor1b = 9;
int FloatSensor2a = 10;
int FloatSensor2b = 11;

int txpin1 = 6;
int txpin2 = 7;

int valvepin1 = 5;
int valvepin2 = 4;

int level1a,level1b,valve1=0 ;
int level2a,level2b,valve2=0 ;

int i=0,j=0;

void setup() 
{
  Serial.begin(9600);
 
  pinMode(FloatSensor1a, INPUT_PULLUP);
  pinMode(FloatSensor1b, INPUT_PULLUP);
  pinMode(FloatSensor2a, INPUT_PULLUP); 
  pinMode(FloatSensor2b, INPUT_PULLUP); 
  pinMode(txpin1, OUTPUT);
  pinMode(txpin2, OUTPUT);
  pinMode(valvepin1, OUTPUT);
  pinMode(valvepin2, OUTPUT);
}

void loop() 
{
 valvecontrol();
}

void valvecontrol()
{
  level1a = digitalRead(FloatSensor1a);
  level1b = digitalRead(FloatSensor1b);
  level2a = digitalRead(FloatSensor2a);
  level2b = digitalRead(FloatSensor2b);
  
  if(level1a==LOW)
   valve1=1;
  if(level1b==HIGH)
    valve1=0;
    
  if(valve1)
  {
    digitalWrite(valvepin1,HIGH);
    digitalWrite(txpin1,HIGH);
    if(i==0)
    {
      Serial.println("Valve1 Open");
      i=1;
    }
  }
   else
  {
    digitalWrite(valvepin1,LOW);
    digitalWrite(txpin1,LOW);
    if(i==1)
    {
      Serial.println("Valve1 closed");
      i=0;
    }
  }

   if(level2a==LOW)
   valve2=1;
  if(level2b==HIGH)
    valve2=0;
    
  if(valve2)
  {
    digitalWrite(valvepin2,HIGH);
    digitalWrite(txpin2,HIGH);
    if(j==0)
    {
      Serial.println("Valve2 Open");
      j=1;
    }
  }
   else
  {
    digitalWrite(valvepin2,LOW);
    digitalWrite(txpin2,LOW);
    if(j==1)
    {
      Serial.println("Valve2 closed");
      j=0;
    }
    
  }
}
