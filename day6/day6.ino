#include <Servo.h>

int servoPin = 9;
int piezo = 5;

Servo servo;

void setup() {
  servo.attach(servoPin);
  pinMode (piezo, OUTPUT);
  Serial.begin(9600);
  servo.write(0);

}

void loop() {
  if(Serial.available()){
    char ch = Serial.read();
    if(ch == 10 || ch == 13) {}
    else if(ch == '1')
    servo.write(90);
    else{
      for(int i = 0; i < 5; i++){
        tone(piezo, 1000, 500);
        delay(500);
        }
      }
    }

}
