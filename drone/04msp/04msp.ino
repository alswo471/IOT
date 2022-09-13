// 04msp_input_time
void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop() {
  static uint32_t t_head1, t_crc;
  static uint32_t msp_time;
  static uint32_t cnt;

  if(Serial1.available()) {
    uint8_t mspData = Serial1.read();
    if(mspData == '$') {
      t_head1 = micros();
      cnt = 0;
    } else cnt++;

    if(cnt == 10) {
      t_crc = micros();
      msp_time = t_crc - t_head1;

      Serial.println(msp_time, DEC);
    }
  }
}
