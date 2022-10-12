#include <Servo.h>

int lepPin = 11;
int servoPin = 9;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  
}

void loop() {
  
  int value = analogRead(A0);
  int bright = map(value, 0, 1023, 0, 255); 
  Serial.print("Input value : ");
  Serial.println(value);
  Serial.print("comput value : ");
  Serial.println(bright);
  analogWrite(lepPin, bright);

  analogWrite(servoPin, value);  
  delay(1000); 
  
}
