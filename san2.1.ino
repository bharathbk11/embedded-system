#define echoPin 3 
#define trigPin 2
#define motor 4 
#define sv 5
#define buz 6 
#define light 12
long duration; 
int distance; 


void setup() 
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(motor, OUTPUT);
   pinMode(sv, OUTPUT); 
  pinMode(buz, OUTPUT); 
  pinMode(light, OUTPUT); 
  Serial.begin(9600); 
  for(int i=0;i<50;i++)
    getdistance(); 
  digitalWrite(motor,LOW);
  digitalWrite(buz,LOW);
}
void loop() 
{
  for(int i=0;i<50;i++)
    getdistance();
  if(distance<16)
  {
    digitalWrite(motor,HIGH);
    digitalWrite(sv,HIGH);
    digitalWrite(light,HIGH);
    digitalWrite(buz,HIGH);
    delay(2000);
    digitalWrite(motor,LOW);
    digitalWrite(sv,LOW);
    digitalWrite(buz,LOW);
    digitalWrite(light,LOW);
    delay(1000);
  }
}
void getdistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("distance=");
  Serial.println(distance);
}
