// 03msp_input_period
void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop() {
  static uint32_t t_now, t_prev;
  static uint32_t msp_period;

  if(Serial1.available()) {
    uint8_t mspData = Serial1.read();
    if(mspData == '$') {  // mspData 값이 '$'이면, 즉 메시지의 시작이면,
      t_now = micros();
      msp_period = t_now - t_prev;
      t_prev = t_now;

      Serial.println(msp_period, DEC);
    }
  }
}
