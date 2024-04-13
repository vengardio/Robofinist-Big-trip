#define ENA 3 // Вывод управления скоростью вращения мотора №1
#define ENB 9 // Вывод управления скоростью вращения мотора №2
#define IN1 4 // Вывод управления направлением вращения мотора №1
#define IN2 5 // Вывод управления направлением вращения мотора №1
#define IN3 6 // Вывод управления направлением вращения мотора №2
#define IN4 7 // Вывод управления направлением вращения мотора №2
#define LINEL A6 //Левый датчик линии
#define LINER A5 //Левый датчик линии
#define POT A4 //Потенциометр
long prevtime = millis();
int timeDrive, powerL, powerR, RotSpeedR, RotSpeedL;
bool BoolLineL, BoolLineR;


void setup() {
  Serial.begin(9600);
  // Установка всех управляющих пинов в режим выхода
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LINEL, INPUT);
  pinMode(LINER, INPUT);
  pinMode(POT, INPUT);
  // Команда остановки двум моторам
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  prevtime = millis();
  powerL = 85;
  powerR = 80;
  RotSpeedR = 80;
  RotSpeedL = 85;
}

void driveForward() { //g
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, powerR);
  analogWrite(ENB, powerL);
}

void driveBackward() { 
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, powerR);
  analogWrite(ENB, powerL);
}

void forwardLeft() { 
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  analogWrite(ENA, RotSpeedR + 15);
  analogWrite(ENB, RotSpeedL);
}

void forwardRight() { 
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, 0);
  analogWrite(ENB, RotSpeedL);
}
void backwardLeft() { 
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  analogWrite(ENA, RotSpeedR);
  analogWrite(ENB, 0);
}
void backwardRight() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, 0);
  analogWrite(ENB, RotSpeedL);
}

void loop() {
  timeDrive = map(analogRead(POT), 0, 1023, 2000, 5000);
  Serial.print("BoolL: "); Serial.print(BoolLineL);
  Serial.print("BoolR: "); Serial.println(BoolLineR);
  if (analogRead(LINEL) >= 400) BoolLineL = true;  //===Left pin===
  if (analogRead(LINER) >= 600) BoolLineR = true;   //===Right pin=== 
  if (analogRead(LINEL) < 400) BoolLineL = false;
  if (analogRead(LINER) < 600) BoolLineR = false;

  if (millis() - prevtime < timeDrive ) { //движение робота вперёд на протяжении времени, регламентируемом потенциометром
    driveForward();
    if (BoolLineL == 1 and BoolLineR == 0) {
      forwardLeft();
    }
    if (BoolLineR== 1 and BoolLineL == 0) {
      forwardRight();
    }
  } else if (millis() - prevtime < timeDrive * 2) { //движение робота назад на протяжении времени, регламентируемом потенциометром
    driveBackward();
    if (BoolLineR == 1 and BoolLineL == 0) {
      backwardRight();
    }
    if (BoolLineL == 1 and BoolLineR == 0) {
      backwardLeft();
    }
  } else {
    prevtime = millis(); //робот проехал полный цикл. Обновляется
  }
}
