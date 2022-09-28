#include <Servo.h>

int servoPin = 9;

Servo servo;

int angle = 0;

void setup() {
  servo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
 if(Serial.available()){
  char ch = Serial.read();

  switch(ch){
    case '0' : angle = 0;
    break;
    case '1' :  angle = 45;
    break;
    case '2' : angle = 90;
    break;
    case '3' : angle = 135;
    break; 
    case '4' : angle = 180;
    break;

    case 10 : 
    case 13 : break;
    default : Serial.println("Wrong Input!!!");
    }
  } 
  servo.write(angle);
  delay(50);

}
