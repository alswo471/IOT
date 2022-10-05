// PPID TEST
#include <Wire.h>
   
const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
   
void setup() {
  initMPU6050(); //가속도 자이로 센서 값을 읽음
  Serial.begin(115200);
  Serial.begin(115200);
  calibAccelGyro(); //센서 보정 루틴
  initDT();// 시간 간격에 대한 초기화
  initYPR();
  initMotorSpeed();
}

void loop() {
  readAccelGyro();
  calcDT(); //시간 간격 계산
  calcAccelYPR(); //가속도 센서 처리 루틴
  calcGyroYPR(); //자이로 센서 처리 루틴 --> 가속도 센서의 값을 해석하기 위해 Roll, Pitch, Yaw에 대한 각도 구하는 함수
  calcFilteredYPR(); //상보필터 적용
  // calcYPRtoStdPID();
  calcYPRtoDualPID();
  calcMotorSpeed();
  checkMspPacket();
  updateMotorSpeed();
 
  // static int cnt;
  // cnt++;
  // if(cnt%2==0)
    // SendDataToProcessing(); //Roll, Pitch, Yaw에 대한 각도 정보를 보냄
}
  
//MPU-6050초기화 루틴
void initMPU6050()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}
  
 //가속도 자이로 센서를 읽는 루틴
void readAccelGyro()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}
  
float dt;
float accel_angle_x, accel_angle_y, accel_angle_z;
float gyro_angle_x, gyro_angle_y, gyro_angle_z;
float filtered_angle_x, filtered_angle_y, filtered_angle_z;
float baseAcX, baseAcY, baseAcZ;
float baseGyX, baseGyY, baseGyZ;
extern float roll_output, pitch_output, yaw_output;
extern float motorA_speed, motorB_speed, motorC_speed, motorD_speed;
  
//센서 들의 기본값들의 평균을 내야하는 루틴(센서 보정 루틴)
void calibAccelGyro() 
{
  float sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  float sumGyX = 0, sumGyY = 0, sumGyZ = 0;
  
  //가속도 자이로 센서를 읽어드림
  readAccelGyro();
 
  //읽어드렸으면 이제 읽어드린 값을 토대로 평균값을 구하면 됨
  for(int i=0; i<10; i++)
  {
    readAccelGyro();
    sumAcX += AcX; sumAcY += AcY; sumAcZ += AcZ;
    sumGyX += GyX; sumGyY += GyY; sumGyZ += GyZ;
    delay(100);//0.1초
  }
  //맨 처음 기본 센서 값들을 보여지고 그다음에 평균값을 구하는 함수
  baseAcX = sumAcX / 10;
  baseAcY = sumAcY / 10;
  baseAcZ = sumAcZ / 10;
  
  baseGyX = sumGyX / 10;
  baseGyY = sumGyY / 10;
  baseGyZ = sumGyZ / 10;
}
  
 //프로세싱 스케치로 각도 정보를 보내는 루틴
/* void SendDataToProcessing()
{
  Serial.print(F("DEL:"));
  Serial.print(dt,DEC);
  Serial.print(F("#RPY:"));
  Serial.print(F("#ACC:"));
  Serial.print(accel_angle_y, 2);
  Serial.print(F(","));
  Serial.print(accel_angle_y, 2);
  Serial.print(F(","));
  Serial.print(accel_angle_z, 2);
  Serial.print(F("#GYR:"));
  Serial.print(gyro_angle_x, 2);
  Serial.print(F(","));
  Serial.print(gyro_angle_y, 2);
  Serial.print(F(","));
  Serial.print(gyro_angle_z, 2);
  Serial.print(F("#FIL:"));
  Serial.print(filtered_angle_x, 2);
  Serial.print(F(","));
  Serial.print(filtered_angle_y, 2);
  Serial.print(F(","));
  Serial.print(filtered_angle_z, 2);
  Serial.print(F("#PID:"));
  Serial.print(roll_output, 2);
  Serial.print(F(","));
  Serial.print(pitch_output, 2);
  Serial.print(F(","));
  Serial.println(yaw_output, 2);
  Serial.print(F("#A:"));
  Serial.print(motorA_speed, 2);
  Serial.print(F("#B:"));
  Serial.print(motorB_speed, 2);
  Serial.print(F("#C:"));
  Serial.print(motorC_speed, 2);
  Serial.print(F("#D:"));
  Serial.print(motorD_speed, 2);
  
  delay(10);
} */
 
unsigned long t_now;
unsigned long t_prev;
 
void initDT(){
  t_prev = millis();
}
 
void calcDT(){
  t_now = millis();
  dt = (t_now - t_prev) / 1000.0;
  t_prev = t_now;
}
 
void calcAccelYPR() //가속도 센서 처리 루틴
{
  float accel_x, accel_y, accel_z; //x, y, z 축에 대한 각도 저장 변수
  float accel_xz, accel_yz;
  const float RADIANS_TO_DEGREES = 180 / 3.14159;
 
  accel_x = AcX - baseAcX;
  accel_y = AcY - baseAcY;
  accel_z = AcZ + (16384 - baseAcZ);
 
  accel_yz = sqrt(pow(accel_y, 2) + pow(accel_z, 2));
  accel_angle_y = atan(-accel_x / accel_yz)*RADIANS_TO_DEGREES;
 
  accel_xz = sqrt(pow(accel_x, 2) + pow(accel_z, 2));
  accel_angle_y = atan(accel_y / accel_xz)*RADIANS_TO_DEGREES;
 
  accel_angle_z = 0;
}

float gyro_x, gyro_y, gyro_z;

void calcGyroYPR()
{
  const float GYROXYZ_TO_DEGREES_PER_SEC = 131; // 각속도를 저장하는 변수

  gyro_x = (GyX - baseGyX) / GYROXYZ_TO_DEGREES_PER_SEC;
  gyro_y = (GyY - baseGyY) / GYROXYZ_TO_DEGREES_PER_SEC;
  gyro_z = (GyZ - baseGyZ) / GYROXYZ_TO_DEGREES_PER_SEC;

  gyro_angle_x += gyro_x * dt;
  gyro_angle_y += gyro_y * dt;
  gyro_angle_z += gyro_z * dt;
 /*주석을 하는 이유
  * 이 부분은 자이로 센서 자체적으로 회전각을 구하는 부분,
  * 이제는 PID 제어를 통해 회전각을 구할것이다.
  */
}

void calcFilteredYPR() //상보필터
{
   const float ALPHA = 0.96;
   float tmp_angle_x, tmp_angle_y, tmp_angle_z; //임시 각도

   tmp_angle_x = filtered_angle_x + gyro_x * dt; // 이전 보정 각도 + 현재 자이로 센서를 이용해 얻은 각도(gyro_x * dt)
   tmp_angle_y = filtered_angle_y + gyro_y * dt;
   tmp_angle_z = filtered_angle_z+ gyro_z * dt;

   filtered_angle_x = ALPHA * tmp_angle_x + (1.0 - ALPHA) * accel_angle_x;
   filtered_angle_y = ALPHA * tmp_angle_y + (1.0 - ALPHA) * accel_angle_y;
   filtered_angle_z = tmp_angle_z;
}

//표준 PID 제어기
/* void stdPID(float& setpoint, float& input, float& prev_input, float& kp, float& ki, float& kd, float& iterm, float& output)
{
  float error;
  float dInput;
  float pterm, dterm;

  error = setpoint - input; 
  dInput = input - prev_input;
  prev_input = input;

  pterm = kp * error;
  iterm += ki * error * dt;
  dterm = -kd * (dInput / dt);

  output = pterm + iterm + dterm;
} */

/* float roll_target_angle = 0.0;
float roll_prev_angle = 0.0;
float roll_kp = 0.408;
float roll_ki = 1.02;
float roll_kd = 0.0408;
float roll_iterm;
float roll_output;

float pitch_target_angle = 0.0;
float pitch_prev_angle = 0.0;
float pitch_kp = 0.408;
float pitch_ki = 1.02;
float pitch_kd = 0.0408;
float pitch_iterm;
float pitch_output;

float yaw_target_angle = 0.0;
float yaw_prev_angle = 0.0;
float yaw_kp = 1;
float yaw_ki = 0;
float yaw_kd = 0;
float yaw_iterm;
float yaw_output; */

/* void calcYPRtoStdPID()
{
  stdPID(roll_target_angle, filtered_angle_y, roll_prev_angle, roll_kp, roll_ki, roll_kd, roll_iterm, roll_output);
  stdPID(pitch_target_angle, filtered_angle_x, pitch_target_angle, pitch_kp, pitch_ki, pitch_kd, pitch_iterm, pitch_output);
  stdPID(yaw_target_angle, filtered_angle_z, yaw_target_angle, yaw_kp, yaw_ki, yaw_kd, yaw_iterm, yaw_output);
} */

float base_roll_target_angle;
float base_pitch_target_angle;
float base_yaw_target_angle;

extern float roll_target_angle;
extern float pitch_target_angle;
extern float yaw_target_angle;

void initYPR() {
  for(int i=0; i<10; i++){
    readAccelGyro();
    calcDT();
    calcAccelYPR();
    calcGyroYPR();
    calcFilteredYPR();

    base_roll_target_angle += filtered_angle_y;
    base_pitch_target_angle += filtered_angle_x;
    base_yaw_target_angle += filtered_angle_z;
    delay(100);
    }

    base_roll_target_angle /= 10;
    base_pitch_target_angle /= 10;
    base_yaw_target_angle /= 10;

    roll_target_angle = base_roll_target_angle;
    pitch_target_angle = base_pitch_target_angle;
    yaw_target_angle = base_yaw_target_angle;
  }

  float throttle = 0;
  float motorA_speed, motorB_speed, motorC_speed, motorD_speed;

  void calcMotorSpeed() {
    motorA_speed = (throttle == 0) ? 0: throttle + yaw_output + roll_output + pitch_output + 25;
    motorB_speed = (throttle == 0) ? 0: throttle - yaw_output - roll_output + pitch_output;
    motorC_speed = (throttle == 0) ? 0: throttle + yaw_output - roll_output - pitch_output;
    motorD_speed = (throttle == 0) ? 0: throttle - yaw_output + roll_output - pitch_output + 15;
    
    if(motorA_speed < 0) motorA_speed = 0;
    if(motorA_speed > 255) motorA_speed = 255;
    if(motorB_speed < 0) motorB_speed = 0;
    if(motorB_speed > 255) motorB_speed = 255;
    if(motorC_speed < 0) motorC_speed = 0;
    if(motorC_speed > 255) motorC_speed = 255;
    if(motorD_speed < 0) motorD_speed = 0;
    if(motorD_speed > 255) motorD_speed = 255;
    }

    enum {
      HEAD1, HEAD2, HEAD3, DATASIZE, CMD,
      ROLL, PITCH, YAW, THROTTLE,
      AUX, CRC, PACKETSIZE,
    };
    uint8_t mspPacket[PACKETSIZE];

    void checkMspPacket() {
      static uint32_t cnt;

      if(Seria1.available() > 0) {
        while(Serial.available() > 0) {
          uint8_t mspData = Serial.read();
          if(mspData == '$') cnt = HEAD1;
          else cnt++;

          mspPacket[cnt] = mspData;

          if(cnt == CRC) {
            if(mspPacket[CMD] == 150) {
              throttle = mspPacket[THROTTLE];

             /* float roll_ku = mspPacket[ROLL];
              roll_ku -= 125;
              if(roll_ku < 0) roll_ku = 0;
              roll_ku /= 25;
              roll_kp = roll_ku;

              Serial.print(throttle, 2);
              Serial.print("\t");
              Serial.println(roll_kp, 2); */
            }
          }
        }
      }
    }

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0

int motorA_pin = 6;
int motorB_pin = 10;
int motorC_pin = 9;
int motorD_pin = 5;

void initMotorSpeed() {
  analogWrite(motorA_pin, THROTTLE_MIN);
  analogWrite(motorB_pin, THROTTLE_MIN);
  analogWrite(motorC_pin, THROTTLE_MIN);
  analogWrite(motorD_pin, THROTTLE_MIN); 
}

void updateMotorSpeed() {
  analogWrite(motorA_pin, motorA_speed);
  analogWrite(motorB_pin, motorB_speed);
  analogWrite(motorC_pin, motorC_speed);
  analogWrite(motorD_pin, motorD_speed);
}

void dualPID(
  float target_angle,
  float angle_in,
  float rate_in,
  float stabilize_kp,
  float stabilize_ki,
  float rate_kp,
  float rate_ki,
  float& stabilize_iterm,
  float& rate_iterm,
  float& output) {
    float angle_error;
    float desired_rate;
    float rate_error;
    float stabilize_pterm, rate_pterm;

    angle_error = target_angle - angle_in;

    stabilize_pterm = stabilize_kp * angle_error;
    stabilize_iterm = stabilize_ki * angle_error * dt;

    desired_rate = stabilize_pterm;

    rate_error = desired_rate - rate_in;

    rate_pterm = rate_kp * rate_error;
    rate_iterm += rate_ki * rate_error * dt;

    output = rate_pterm + rate_iterm + stabilize_iterm;
}

float roll_target_angle = 0.0;
float roll_angle_in;
float roll_rate_in;
float roll_stabilize_kp = 1;
float roll_stabilize_ki = 0;
float roll_rate_kp = 1;
float roll_rate_ki = 0;
float roll_stabilize_iterm;
float roll_rate_iterm;
float roll_output;

float pitch_target_angle = 0.0;
float pitch_angle_in;
float pitch_rate_in;
float pitch_stabilize_kp = 1;
float pitch_stabilize_ki = 0;
float pitch_rate_kp = 1;
float pitch_rate_ki = 0;
float pitch_stabilize_iterm;
float pitch_rate_iterm;
float pitch_output;

float yaw_target_angle = 0.0;
float yaw_angle_in;
float yaw_rate_in;
float yaw_stabilize_kp = 1;
float yaw_stabilize_ki = 0;
float yaw_rate_kp = 1;
float yaw_rate_ki = 0;
float yaw_stabilize_iterm;
float yaw_rate_iterm;
float yaw_output;

void calcYPRtoDualPID() {

  roll_angle_in = filtered_angle_y;
  roll_rate_in = gyro_y;
  dualPID(roll_target_angle, roll_angle_in, roll_rate_in, roll_stabilize_kp, roll_stabilize_ki, roll_rate_kp, roll_rate_ki, roll_stabilize_iterm, roll_rate_iterm, roll_output);

  pitch_angle_in = filtered_angle_x;
  pitch_rate_in = gyro_x;
  dualPID(pitch_target_angle, pitch_angle_in, pitch_rate_in, pitch_stabilize_kp, pitch_stabilize_ki, pitch_rate_kp, pitch_rate_ki, pitch_stabilize_iterm, pitch_rate_iterm, pitch_output);

  yaw_angle_in = filtered_angle_z;
  yaw_rate_in = gyro_z;
  dualPID(yaw_target_angle, yaw_angle_in, yaw_rate_in, yaw_stabilize_kp, yaw_stabilize_ki, yaw_rate_kp, yaw_rate_ki, yaw_stabilize_iterm, yaw_rate_iterm, yaw_output);
}
