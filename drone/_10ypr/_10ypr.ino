void setup() {
  initMPU6050();
  Serial.begin(115200);
  calibAccelGyro();
}

float baseAcX, baseAcY, baseAcZ;
float baseGyx, BaseGyY, baseGyZ;

void calibAccelGyro() {
  float sumAcX = 0, sumAcY =0, sumAcZ = 0;
  float sumGyX = 0, sumGyY = 0, sumGyZ = 0;

  readAccelGyro();

  for(int i =0; i<10; i++){
    readAccelGyro();
    sum                       x v 
    }
  
}
