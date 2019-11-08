

#define S3 9
#define S2 10
#define S1 11
#define S0 12


struct finger {
  int fsr;
  int key;
  char fin;

} pinky, ring, mid, poi, thumb;


void setup() {
  // put your setup code here, to run once:
  pinMode(S3, OUTPUT); //S3
  pinMode(S2, OUTPUT); //S2
  pinMode(S1, OUTPUT); //S1
  pinMode(S0, OUTPUT); //S0
thumb.fin='T';
poi.fin='P';
mid.fin='M';
ring.fin='R';
pinky.fin='Y';



  
}

int keyCheck(int aRead){
  int mapped = map(aRead,0,1023,0,446);//446=(90-1)*5+1    90 = 88 + maxvoltage and novoltage----5 = number of divisions between each key
  mapped += 2;
  int i;
  for(i=1;i<88;i++){
    int minV =(i*5)-2;
    int maxV =(i*5)+2;
    if(mapped>=minV&&mapped<=maxV){
      return i;
    }
    
  }
  return 0;
}

void printer(){
  if(thumb.fsr>40){
    Serial.print(thumb.key,DEC);
    Serial.print(thumb.fin);
    Serial.print(" - ");
  }
    if(poi.fsr>40){
    Serial.print(poi.key,DEC);
    Serial.print(poi.fin);
    Serial.print(" - ");
  }
    if(mid.fsr>40){
    Serial.print(mid.key,DEC);
    Serial.print(mid.fin);
    Serial.print(" - ");
  }
    if(ring.fsr>40){
    Serial.print(ring.key,DEC);
    Serial.print(ring.fin);
    Serial.print(" - ");
  }
    if(pinky.fsr>40){
    Serial.print(pinky.key,DEC);
    Serial.print(pinky.fin);
    Serial.print(" - ");
  }
  Serial.print("\n");
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  int t = 0;
  int p = 0;
  int m = 0;
  int r = 0;
  int y = 0;
  for(int i=0;i<5;i++){
    t+=analogRead(1);
    p+=analogRead(2);
    m+=analogRead(3);
    r+=analogRead(4);
    y+=analogRead(5);
  }
  
  thumb.fsr = map(t/5,0,1023,0,100);
  poi.fsr = map(p/5,0,1023,0,100);
  mid.fsr = map(m/5,0,1023,0,100);
  ring.fsr = map(r/5,0,1023,0,100);
  pinky.fsr = map(y/5,0,1023,0,100);
  
  
  int keyRead;
  for (int i = 0; i < 5; i++) {
    int sum = 0;
    switch (i) {
      case 0://15  THUMB
        digitalWrite(S3, HIGH);
        digitalWrite(S1, HIGH);
        digitalWrite(S0, HIGH);

        for(int j=0;j<5;j++){
          keyRead = analogRead(0);
          sum+=keyRead;
        }
        
        thumb.key = keyCheck(sum/5);
        break;
      case 1://12  POINTER
        digitalWrite(S3, HIGH);
        digitalWrite(S2, HIGH);
        digitalWrite(S1, LOW);
        digitalWrite(S0, LOW);

        for(int j=0;j<5;j++){
          keyRead = analogRead(0);
          sum+=keyRead;
        }
        poi.key = keyCheck(sum/5);


        break;
      case 2://8  MIDDLE
        digitalWrite(S3, HIGH);
        digitalWrite(S2, LOW);
        digitalWrite(S1, LOW);
        digitalWrite(S0, LOW);

        for(int j=0;j<5;j++){
          keyRead = analogRead(0);
          sum+=keyRead;
        }
        mid.key = keyCheck(sum/5);

        break;
      case 3://4  RING
        digitalWrite(S3, LOW);
        digitalWrite(S2, HIGH);
        digitalWrite(S1, LOW);
        digitalWrite(S0, LOW);

        for(int j=0;j<5;j++){
          keyRead = analogRead(0);
          sum+=keyRead;
        }
        ring.key = keyCheck(sum/5);


        break;
      case 4://0  PINKY
        digitalWrite(S3, LOW);
        digitalWrite(S2, LOW);
        digitalWrite(S1, LOW);
        digitalWrite(S0, LOW);

        for(int j=0;j<5;j++){
          keyRead = analogRead(0);
          sum+=keyRead;
        }
        pinky.key = keyCheck(sum/5);


        break;
      default:
        //DO NOTHING!!
        break;
    }
  }
  printer();
  

}
