// 01hellodrone
void setup() {
  Serial1.begin(115200);  // 프로세싱과의 연결을 위해 시리얼을 사용
  Serial.begin(115200);
}

void loop() {
  uint8_t userInput;
  if(Serial1.available() > 0) {
    userInput = Serial1.read();

    Serial.println((char)userInput);
  }
}
