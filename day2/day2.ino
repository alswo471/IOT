

void setup() {
  pinMode(13, OUTPUT);
 Serial.begin(9600);
  }

  void loop(){
    
  char ch;
  if(Serial.available()){
  ch = Serial.read();
   }
  if(ch == 'A' || ch == 'a') {
   shortex();
    longex();
    }

    if(ch == 'B' || ch == 'b') {
  
    longex();
     shortex();
      shortex();
       shortex();
    }


    if(ch == 'C' || ch == 'c') {
   longex();
      shortex();
     longex();
     shortex();
    }

    if(ch == 'D' || ch == 'd') {
  longex();
      shortex();
     shortex();
    }

    if(ch == 'E' || ch == 'e') {
  shortex();
    }

 if(ch == 'F' || ch == 'f') {
  shortex();
    shortex();
    longex();
    shortex();
    }

   if(ch == 'F' || ch == 'f') {
  shortex();
    shortex();
    longex();
    shortex();
    }

    if(ch == 'G' || ch == 'g') {
 
    longex();
    longex();
    shortex();
    }

    if(ch == 'H' || ch == 'h') {
  shortex();
    shortex();
    shortex();
    shortex();
    }

    if(ch == 'I' || ch == 'i') {
  shortex();
   shortex();
   
    }

    if(ch == 'J' || ch == 'j') {

    shortex();
    longex();
    longex();
    longex();
    }

    if(ch == 'K' || ch == 'k') {
 
    longex();
    shortex();
    longex();
    }

    if(ch == 'L' || ch == 'l') {
  shortex();
  longex();
    shortex();
    shortex();
    }

    if(ch == 'M' || ch == 'm') {
  
    longex();
    longex();
    }

    if(ch == 'N' || ch == 'n') {
  
    longex();
    shortex();
    }

    if(ch == 'O' || ch == 'o') {
  
    longex();
   longex();
   longex();
    }

   if(ch == 'P' || ch == 'p') {
  shortex();
    longex();
   longex();
   shortex();
    }

    if(ch == 'Q' || ch == 'q') {
  
    longex();
   longex();
   shortex();
   longex();
   
    }

    if(ch == 'R' || ch == 'r') {
  
    shortex();
   longex();
   shortex(); 
    }
     
delay(100);
    }


  void shortex() {
        digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
        }

        void longex() {
        digitalWrite(13, HIGH);
    delay(700);
    digitalWrite(13, LOW);
    delay(700);
        }
        
    

     
      

      


      

    
     

     
