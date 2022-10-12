int redPin = 11;
int greenPin = 5;
int bluePin = 9;

void RGB(int r, int g, int b);

void setup() {
 randomSeed(analogRead(0));
}

void loop() {
int r = random(256);
int g = random(256);
int b = random(256);
analogWrite(redPin, r);
analogWrite(greenPin, g);
analogWrite(bluePin, b);
delay(10);
}
