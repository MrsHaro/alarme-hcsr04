#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8

int led_pins[] = {13, 7, 6, 5, 4};
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  lcd.begin(); // Initialisation de l'écran LCD I2C
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  Serial.begin(9600);
}

float recup_distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.034) / 2;
  return distance;
}

void loop() {
  float distance = recup_distance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(0, 1);
  lcd.print("                "); // Effacer la ligne
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm.");

  for (int i = 0; i < 5; i++) {
    digitalWrite(led_pins[i], LOW);
  }
  digitalWrite(BUZZER_PIN, LOW);

  if (distance <= 200) {digitalWrite(led_pins[0], HIGH);}
  if (distance <= 150) {digitalWrite(led_pins[1], HIGH);}
  if (distance <= 100) {digitalWrite(led_pins[2], HIGH);}
  if (distance <= 50) {digitalWrite(led_pins[3], HIGH);}
  if (distance <= 25) {
    digitalWrite(led_pins[4], HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }

  delay(100);
}