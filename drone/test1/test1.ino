void setup() {

}

void loop() {
  analogWrite(6, 4); delay(1000);
  analogWrite(10, 4); delay(1000);
  analogWrite(9, 4); delay(1000);
  analogWrite(5, 4); delay(1000);

  analogWrite(6, 0); delay(1000);
  analogWrite(10, 0); delay(1000);
  analogWrite(9, 0); delay(1000);
  analogWrite(5, 0); delay(1000);
}
