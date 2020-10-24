const int buzzer = 6; 
const int sensor = 3;

int state; // 0 close - 1 open wwitch

void setup()
{
  pinMode(sensor, INPUT_PULLUP);
}

void loop()
{
  state = digitalRead(sensor);
  
  if (state == HIGH){
    tone(buzzer, 200);
  }
  else{
    noTone(buzzer);
  }
  delay(200);
}
