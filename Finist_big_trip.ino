#define ENA 3     // Вывод управления скоростью вращения мотора №1
#define ENB 9     // Вывод управления скоростью вращения мотора №2
#define IN1 4     // Вывод управления направлением вращения мотора №1
#define IN2 5     // Вывод управления направлением вращения мотора №1
#define IN3 6     // Вывод управления направлением вращения мотора №2
#define IN4 7     // Вывод управления направлением вращения мотора №2
#define LINEL A6  //Левый датчик линии
#define LINER A5  //Левый датчик линии
#define POT A4    //Потенциометр

#define POWERL 93
#define POWERR 93

long prevtime;  //время после предыдущего поворота
int timeDrive;  //время проезда в одну сторону. Регламентируется потенциометром
bool BoolLineL, BoolLineR, BoolLineLPrev;

void setup() {
  //Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LINEL, INPUT);
  pinMode(LINER, INPUT);
  pinMode(POT, INPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  prevtime = millis();
}

void driveForward() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, POWERR);
  analogWrite(ENB, POWERL);
}

void Left() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, POWERR-10);
  analogWrite(ENB, POWERL-10);
}

void Right() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, POWERR-10);
  analogWrite(ENB, POWERL-10);
}

void LinesUpdate() {
  BoolLineLPrev = BoolLineL;
  if (analogRead(LINEL) >= 350) BoolLineL = true;  //===Left pin===
  if (analogRead(LINER) >= 500) BoolLineR = true;  //===Right pin===
  if (analogRead(LINEL) < 350) BoolLineL = false;
  if (analogRead(LINER) < 500) BoolLineR = false;
  /*
  Serial.print("Left: "); Serial.print(analogRead(LINEL));
  Serial.print(" BLeft: "); Serial.print(BoolLineL);
  Serial.print(" Right: "); Serial.print(analogRead(LINER));
  Serial.print(" BRight: "); Serial.println(BoolLineR);
  */
}

void NeedTurn() {
  while (BoolLineL == 1 or BoolLineR == 1) {
    if (BoolLineL == 1 and BoolLineR == 0) {
      Left();
    }
    if (BoolLineL == 0 and BoolLineR == 1) {
      Right();
    }
    if (BoolLineL == 1 and BoolLineR == 1) {
      driveForward();
    }
    LinesUpdate();
  }
}

void loop() {
  timeDrive = map(analogRead(POT), 0, 1023, 1500, 4000);
  LinesUpdate();

  if (millis() - prevtime < timeDrive) {  //движение робота вперёд на протяжении времени, регламентируемом потенциометром
    driveForward();
    NeedTurn();
  } else {
    NeedTurn();
    while (not(BoolLineLPrev == 1 and BoolLineL == 0)) {
      Left();
      LinesUpdate();
    }
    driveForward();
    prevtime = millis();  //робот проехал полный цикл. Обновляется
  }
}
