const int buttonPin = 5; // 푸시 버튼의 핀 번호 5
const int ledPin = 13; //아두이노 보드의 LED 핀 번호 13

int buttonState = 0; // 입력 핀의 상태 값을 저장하는 변수

void setup() {
  pinMode(ledPin, OUTPUT); //LED 핀 출력 설정
  pinMode(buttonPin, INPUT); // 푸시 버튼 입력 설정

}

void loop() {
  buttonState = digitalRead(buttonPin); // 2번 핀 입력 상태 값 저장

  if(buttonState == HIGH){ //buttonState 변수가 HIGH(1)이면
    //즉, 푸시 버튼이 눌렸다면,
    digitalWrite(ledPin, HIGH); // LED 켜짐 
    }
  

}
