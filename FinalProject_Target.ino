/* 20191205 이민영 */
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void(* resetFunc) (void) = 0; // 프로그램 다시 시작하기 위한 함수

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int state = 0; // 버튼 상태

int score = 0;
int timer = 30;

int redTact = 1; // 빨강 택트 스위치
int blueTact = 11; // 파랑 택트 스위치

int trig = 6; // 초음파센서 출력핀
int echo = 7; // 초음파센서 입력핀

void setup() {
  // 서보모터
  servo.attach(2); // 서보모터 시그널 핀번호
  servo.write(180);

  // 택트 스위치
  pinMode(redTact, INPUT_PULLUP);
  pinMode(blueTact, INPUT_PULLUP);

  //초음파 센서
  pinMode(trig, OUTPUT); // 초음파센서 출력
  pinMode(echo, INPUT); // 초음파센서 입력

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCORE: 0");
  lcd.setCursor(0, 1);
  lcd.print("TIMER: 0");
}

void loop() {
  set();

  sing();
  targetHit();
  ifEnd();
  countdown();

  // 다시 시작
  if(reset() == 1)
    resetFunc();
  // 프로그램 종료
  if(reset() == -1){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("The End");
    
    exit(0);
  }
}

// 거리 측정
float distance() {
  float distance = -1;
  float duration;
  
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = ((float) (340*duration)/10000)/2;
  
  Serial.println(distance);

  return distance;
}

// 타겟 명중 시
void targetHit(){
    // 거리가 15cm 이내로 들어오면 서보모터 작동
  if(distance() < 15.0){
    Score();
    servo.write(180);
  }
  else
    servo.write(90);
}

void set() {  
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("SCORE: ");
  lcd.setCursor(10, 0);
  lcd.print(score);
  lcd.setCursor(0, 1); 
  lcd.print("TIME: ");
  lcd.setCursor(10, 1);
  lcd.print(timer);
}

int reset(){
    // state를 1로 세팅
    if(digitalRead(redTact) == LOW) state = 1;
    // state를 -1로 세팅
    if(digitalRead(blueTact) == LOW)  state = -1;
    
    return state;  
}

//  점수 측정
void Score(){
    score += random(100);
}

// 카운트다운
void countdown() {
  timer--;
  delay(1000);
}


// 끝나면
void ifEnd() {
  if(timer == 0){
    lcd.clear();
    lcd.print("Score: ");
    lcd.setCursor(10, 0);
    lcd.print(score);
    delay(3000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Replay?");
    lcd.setCursor(0, 1);
    lcd.print("Yes:Red No: Blue"); 
    
    reset();
    }
}

// ========= 노래 =========

int BuzzerPin = 5;

#define A 220 // 3음계 라
#define B 246 // 3음계 시
#define C 261 // 도
#define D 293 // 레
#define E 329 // 미
#define F 349 // 파
#define G 391 // 솔
#define A1 440 // 4음계 라
#define C5 523 // 5음계 도

#define b1 500 // 한 박자
#define b2 250 // 반 박자
#define b3 125 // 1/4 박자
#define b4 1000 // 두 박자

// 일루와 부분
void Tone1(){  
  tone(BuzzerPin, A, b2);
  delay(b2);
  tone(BuzzerPin, A, b1);
  delay(b1);
  tone(BuzzerPin, C, b2);
  delay(b2);
  tone(BuzzerPin, C, b1);
  delay(b1);
  tone(BuzzerPin, D, b2);
  delay(b2);
  tone(BuzzerPin, D, b1);
  delay(b1);
  tone(BuzzerPin, E, b2);
  delay(b2);
  tone(BuzzerPin, E, b1);
  delay(b1);
  tone(BuzzerPin, G, b2);
  delay(b2);
  tone(BuzzerPin, G, b1);
  delay(b1);
  tone(BuzzerPin, E, b2);
  delay(b2);
  tone(BuzzerPin, E, b1);
  delay(b1);
}

void Tone2(){
  // 폰은 저리 치워~착한 척은 그만둬
  tone(BuzzerPin, E, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4/6);
  delay(b4/6);
  tone(BuzzerPin, G, b4/6);
  delay(b4/6);
  tone(BuzzerPin, G, b4);
  delay(b1);
  tone(BuzzerPin, D, b4/6);
  delay(b4/6);
  tone(BuzzerPin, C, b4/6);
  delay(b4/6);
  tone(BuzzerPin, D, b4/6);
  delay(b4/6);
  tone(BuzzerPin, C, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4);
  delay(b1);
  
  tone(BuzzerPin, C, b4/6);
  delay(b4/6);
  tone(BuzzerPin, A, b4/6);
  delay(b4/6);
  tone(BuzzerPin, C, b4/6);
  delay(b4/6);
  tone(BuzzerPin, A, b4/6);
  delay(b4/6);
  tone(BuzzerPin, C, b4/6);
  delay(b4/6);
  tone(BuzzerPin, D, b4/4);
  delay(b4/6);
  tone(BuzzerPin, B, b1);
  delay(b1);
}

// 붐 까까꿍~몸을 맡겨
void Tone3(){
  tone(BuzzerPin, A, b2/2);
  delay(b4/4);
  tone(BuzzerPin, C5, b3);
  delay(b3);
  tone(BuzzerPin, C5, b4/6);
  delay(b4/6);
  tone(BuzzerPin, A1, b4/6);
  delay(b2);
  tone(BuzzerPin, A1, b3);
  delay(b3);
  tone(BuzzerPin, A1, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4/6);
  delay(b1);
  
  tone(BuzzerPin, G, b3);
  delay(b3);
  tone(BuzzerPin, G, b4/6);
  delay(b4/6);
  tone(BuzzerPin, D, b4/6);
  delay(b2);
  tone(BuzzerPin, D, b4/6);
  delay(b4/6);
  tone(BuzzerPin, D, b4/6);
  delay(b4/6);
  tone(BuzzerPin, F, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b1/2);
  delay(b1/2);
}

// 뻔뻔하게 놀아 라라라
void Tone4(){
  delay(b4/6);
  tone(BuzzerPin, A, b4/4);
  delay(b4/4);
  tone(BuzzerPin, A, b4/4);
  delay(b4/4);
  tone(BuzzerPin, B, b4/4);
  delay(b4/4);
  tone(BuzzerPin, C, b4/4);
  delay(b4/4);
  tone(BuzzerPin, D, b4/4);
  delay(b2);
  tone(BuzzerPin, E, b1);
  delay(b1); 

  tone(BuzzerPin, A, b4/4);
  delay(b2);
  tone(BuzzerPin, A, b4/6);
  delay(2*b2);
  tone(BuzzerPin, A, b4/4);
  delay(b1);
}

// 시간 제한 끝났음을 알리는 알림음
void finish(){
  tone(BuzzerPin, C, b4/6);
  delay(b4/6);
  tone(BuzzerPin, D, b4/6);
  delay(b4/6);
  tone(BuzzerPin, E, b4/6);
  delay(b4/6);
}

// 노래 실행 함수
void sing() {
  if(timer==0)  
    finish();
    
  for(int i=0; i<2; i++){
    Tone1();
    delay(1000);
  }
  
  Tone2();
  delay(1000);
  Tone2();
  delay(1000);
  
  Tone3();
  
  Tone4();
}
