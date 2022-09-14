int piezo = 9;

int Do = 262;
int Re = 294;
int Mi = 330;
int Fa = 349;
int Sol = 392;
int Ra = 440;
int Si = 494;
int Do2 = 523;

int dotDelay = 200;

void setup() {
  pinMode(piezo, OUTPUT);
}

int A[25]={Mi,Re,Do,Re,Mi,Mi,Mi,Re,Re,Re,Mi,Mi,Mi,Mi,Re,Do,Re,Mi,Mi,Mi,Re,Re,Mi,Re,Do},i;

void loop() {
   for(i=0;i<=24;i++)
  {
    tone(9,A[i]);
    delay(500); 
  }


} 


  
