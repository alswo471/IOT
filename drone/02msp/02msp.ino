// 02msp_input
void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop() {
  if(Serial1.available()) {
    uint8_t mspData = Serial1.read();
    Serial.print((char)mspData);
    Serial.print('\t');
    Serial.println(mspData, DEC);
  }
}
