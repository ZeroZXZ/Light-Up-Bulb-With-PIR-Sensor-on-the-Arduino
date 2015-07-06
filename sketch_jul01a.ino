int sensorVCC=10, sensorGND=13, sensorREAD=12;
int relayPIN=11;

void setup(){
  pinMode(sensorVCC, OUTPUT);
  digitalWrite(sensorVCC, HIGH);
  
  pinMode(sensorGND, OUTPUT);
  digitalWrite(sensorGND, LOW);
  
  pinMode(sensorREAD, INPUT);
  pinMode(relayPIN, OUTPUT);
  digitalWrite(relayPIN, HIGH);
  
  Serial.begin(9600);
}

void loop(){
  static const int timing=15000;//10000 = 10segs
  static int counting=0;
  static unsigned short int last_time;
  unsigned short int current_time = millis();
  
  int x = digitalRead(sensorREAD);
  if(x == HIGH){
    counting=timing;
  }
  else{
    if(last_time > current_time)//fix for millis() rollover
      last_time = current_time;
    
    if(current_time - last_time > 10){ //delay sem usar função delay()
      last_time = current_time;
      if(counting>0)
        counting-=10;
    }
  }

  if(counting>0)
    digitalWrite(relayPIN, LOW);//liga
  else
    digitalWrite(relayPIN, HIGH);//desliga
}
  
