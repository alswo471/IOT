#include <Servo.h>

int servoPin = 9;
int piezo = 5;

Servo servo;

char InputNo[4] = {};
char password[4] = {'1', '2', '3', '4'};
int index = 0;
int failNo = 0;

void setup() {
  servo.attach(servoPin);
  pinMode (piezo, OUTPUT);
  Serial.begin(9600);
  servo.write(0);
}

void loop() {
  i:
  if(Serial.available()){
    char ch = Serial.read();

    if(ch >= '0' && ch <= '9'){
      InputNo[index] = ch;
      index++;
      // Serial.print("Input_index : ");
      // Serial.println(index);
      }
    }

    if(index == 4)
    goto j;
    else
    goto i;

    j:

    index = 0;
    while(index < 4) {
      if(InputNo[index] != password[index])
      break;
      
      index++;
      }

      //Serial.print("comp_index : ");
      //Serial.println(index);

      if(index == 4){
        servo.write(90);
        index = 0;
        failNo = 0;
        goto i;
        }

        else{
          Serial.println("Wrong Number!!!");
          Serial.println("Try again");
          failNo++;
          index = 0;

          if(failNo == 3){
            for(int i = 0; i < 5; i++){
              delay(500);
              }
              failNo = 0;
            }
          else
          goto i;
          }
}
