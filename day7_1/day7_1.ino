int redPin = 11;
int greenPin = 12;
int bluePin = 9;

void RGB(int r, int g, int b);

void setup() {
 Serial.begin(9600);
}

void loop() {
int rvalue = analogRead(A0);
int gvalue = analogRead(A3);
Serial.println(gvalue);
delay(15);
int bvalue = analogRead(A2);

int R = map(rvalue, 0 , 1023 , 0 , 255);
int G = map(gvalue, 0 , 1023 , 0 , 255);
int B = map(bvalue, 0 , 1023 , 0 , 255);

RGB(R, G, B);

delay(15);
}

void RGB(int r, int g, int b){
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  
  }
