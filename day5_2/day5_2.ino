#include <Servo.h>

int servoPin = 9;
const byte interrupPin = 2;
volatile byte buttonState = 0;

Servo servo;

int angle = 0;

void count() {
  buttonState++;
  if(buttonState == 5)
  buttonState = 0;
  }
  
void setup() {
  servo.attach(servoPin);
  pinMode (interrupPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupPin), count, FALLING);
  Serial.begin(9600);
}

void loop() {
 
  switch(buttonState){
    
    case '0' : angle = 0;
    Serial.println(angle);
    break;
    case '1' :  angle = 45;
    Serial.println(angle);
    break;
    case '2' : angle = 90;
    Serial.println(angle);
    break;
    case '3' : angle = 135;
    Serial.println(angle);
    break; 
    case '4' : angle = 180;
    Serial.println(angle);
    break;

    default : ;
    }
  
  servo.write(angle);
  delay(50);

}
