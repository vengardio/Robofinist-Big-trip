#define ENA 9 // Вывод управления скоростью вращения мотора №1
#define ENB 3 // Вывод управления скоростью вращения мотора №2
#define IN1 7 // Вывод управления направлением вращения мотора №1
#define IN2 6 // Вывод управления направлением вращения мотора №1
#define IN3 5 // Вывод управления направлением вращения мотора №2
#define IN4 4 // Вывод управления направлением вращения мотора №2
#define LINEL A5 //Левый датчик линии
#define LINER A6 //Левый датчик линии
#define POT A7 //Потенциометр
int powerL, powerR;
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
}

void loop() {
  if (analogRead(LINEL) >= 1013) BoolLineL = true;  //===Left pin===
  if (analogRead(LINER) >= 999) BoolLineR = true;   //===Right pin=== 
  if (analogRead(LINEL) < 1009) BoolLineL = false;
  if (analogRead(LINER) < 993) BoolLineR = false;

  powerL = 120;
  powerR = 120;

  Serial.print("powerL: "); Serial.print(powerL);
  Serial.print("powerR: "); Serial.print(powerR);
  Serial.print("LineL: "); Serial.print(analogRead(LINEL));
  Serial.print("BoolLineL: "); Serial.print(BoolLineL);
  Serial.print("LineR: "); Serial.print(analogRead(LINER));
  Serial.print("BoolLineR: "); Serial.print(BoolLineR);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, powerL);
  analogWrite(ENB, powerR);
}
