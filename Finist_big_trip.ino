#define ENA 9 // Вывод управления скоростью вращения мотора №1
#define ENB 3 // Вывод управления скоростью вращения мотора №2
#define IN1 7 // Вывод управления направлением вращения мотора №1
#define IN2 6 // Вывод управления направлением вращения мотора №1
#define IN3 5 // Вывод управления направлением вращения мотора №2
#define IN4 4 // Вывод управления направлением вращения мотора №2
#define LINEL A6 //Левый датчик линии
#define LINER A5 //Левый датчик линии
#define POT A4 //Потенциометр
long prevtime = millis();
int timeDrive, powerL, powerR;
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
}

void driveForward() {
  if (BoolLineL) powerL = 67;
  if (BoolLineR) powerR = 67;
  if (BoolLineR == 0 and BoolLineL == 0) {
    powerL = 100;
    powerR = 100;
  }

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, powerL);
  analogWrite(ENB, powerR);
}

void driveBackward() {
  if (BoolLineL) powerR = 75;
  if (BoolLineR) powerL = 75;
  if (BoolLineR == 0 and BoolLineL == 0) {
    powerL = 100;
    powerR = 100;
  }

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, powerL);
  analogWrite(ENB, powerR);
}
void loop() {
  timeDrive = map(analogRead(POT), 0, 1023, 2000, 5000);
  Serial.print("Left: "); Serial.print(timeDrive);
  Serial.print(" BLeft: "); Serial.print(BoolLineL);
  Serial.print(" Right: "); Serial.print(prevtime);
  Serial.print(" BRight: "); Serial.print(BoolLineR);
  if (analogRead(LINEL) >= 400) BoolLineL = true;  //===Left pin===
  if (analogRead(LINER) >= 600) BoolLineR = true;   //===Right pin=== 
  if (analogRead(LINEL) < 400) BoolLineL = false;
  if (analogRead(LINER) < 600) BoolLineR = false;

  if (millis() - prevtime < timeDrive ) { //движение робота вперёд на протяжении времени, регламентируемом потенциометром
    driveForward();
    Serial.println("FORWARD");
  } else if (millis() - prevtime < timeDrive * 2) { //движение робота назад на протяжении времени, регламентируемом потенциометром
    driveBackward();
    Serial.println("BACKWARD");
  } else {
    prevtime = millis(); //робот проехал полный цикл. Обновляется
    Serial.println("UPDATE");
  }

}
