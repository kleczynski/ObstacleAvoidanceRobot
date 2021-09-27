#include <Arduino.h>

#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

#define L_SIDE_SENSOR A0
#define R_SIDE_SENSOR A1
#define BUZZER 10

void leftMotor(int V);
void rightMotor(int V);
void stopMotor();

void setup()
{
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  pinMode(L_SIDE_SENSOR, INPUT_PULLUP);
  pinMode(R_SIDE_SENSOR, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0);

  randomSeed(analogRead(5));
}

void loop()
{
  leftMotor(40);
  rightMotor(40);
  int ran = random(5, 20) * 10;

  if (digitalRead(L_SIDE_SENSOR) == LOW && digitalRead(R_SIDE_SENSOR) == LOW)
  {
    leftMotor(-30);
    rightMotor(-30);
    digitalWrite(BUZZER, 1);
    delay(120 + ran);

    leftMotor(-30);
    rightMotor(30);
    digitalWrite(BUZZER, 0);
    delay(200);
  }

  if (digitalRead(L_SIDE_SENSOR) == LOW)
  {
    leftMotor(-40);
    rightMotor(-40);
    digitalWrite(BUZZER, 1);
    delay(200 + ran);

    leftMotor(40);
    rightMotor(-40);
    digitalWrite(BUZZER, 0);
    delay(140 + ran);
  }

  if (digitalRead(R_SIDE_SENSOR) == LOW)
  {
    leftMotor(-40);
    rightMotor(-40);
    digitalWrite(BUZZER, 1);
    delay(160 + ran);

    leftMotor(-40);
    rightMotor(40);
    digitalWrite(BUZZER, 0);
    delay(140 + ran);
  }
}

void leftMotor(int V)
{
  if (V > 0)
  {
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 0);
    analogWrite(L_PWM, V);
  }
  else
  {
    V = abs(V);
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 1);
    analogWrite(L_PWM, V);
  }
}

void rightMotor(int V)
{
  if (V > 0)
  {
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 0);
    analogWrite(R_PWM, V);
  }
  else
  {
    V = abs(V);
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 1);
    analogWrite(R_PWM, V);
  }
}

void stopMotor()
{
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}