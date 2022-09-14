int piezo = 9;

int DO = 262;
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

void loop() {
  tone(piezo, Do, 250);
  delay(250);
   tone(piezo, Re, 250);
  delay(250);
   tone(piezo, Mi, 250);
  delay(250);
   tone(piezo, Fa, 250);
  delay(250);
   tone(piezo, Sol, 250);
  delay(250);
   tone(piezo, Ra, 250);
  delay(250);
   tone(piezo, Si, 250);
  delay(250);
   tone(piezo, Do2, 250);
  delay(250);
} 


  
