

void setup() {
 Serial.begin(9600);
  }

  void loop(){
    
char ch;
if(Serial.available()){
  ch = Serial.read();
  Serial.println(ch);
}
delay(100);
    }

    
     

     
