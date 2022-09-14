int piezo = 9;

int D = 262;
int R = 294;
int M = 330;
int F = 349;
int So = 392;
int Ra = 440;
int S = 494;
int D2 = 523;

int dotDelay = 200;

void setup() {
  pinMode(piezo, OUTPUT);
}


 


int A[]={D,D,D,D,D,M,So,So,M,D,So,So,So,M,So,So,M,D,D,D,So,So,M,D,So,So,So,So,So,M,D,So,So,So, So,So,M,D,So,So,So,Ra,So,D,So,D,So,M,R,D},i;

void loop() {
   for(i=0;i<=43;i++)
  {
    tone(9,A[i]);
    delay(500); 
  }


} 


  
