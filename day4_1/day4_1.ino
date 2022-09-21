const int ledPin = 13; //아두이노 보드의 LED 핀 번호 13
const int interrupPin = 5;
volatile byte buttonState = LOW; // ISR에 사용된 전역 변수는 volatile로 선언 

void setup() {
  pinMode(ledPin, OUTPUT); //LED 핀 출력 설정
  pinMode(interrupPin, INPUT_PULLUP); // 푸시 버튼 입력 설정
  attachInterrupt(digitalPinToInterrupt(interrupPin), blink, FALLING);
}

void loop() {
  
    digitalWrite(ledPin, buttonState); // 13번 핀에 state 변수의 상태 값 반영
    }

  

void blink()
{
  buttonState = !buttonState; // 인터럽트 발생 시 변수 값 반전
  }
