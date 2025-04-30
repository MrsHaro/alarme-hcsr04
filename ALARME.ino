#include <Wire.h>
#include <LiquidCrystal.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int led_pins[] = {13, 7, 6};

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  Serial.begin(9600);
  lcd.begin(16, 2);  // Initialisation de l'écran LCD
  lcd.print("Distance: ");
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

  if (distance <= 300) {digitalWrite(led_pins[0], HIGH);}
  if (distance <= 150) {digitalWrite(led_pins[1], HIGH);}
  if (distance <= 75) {
    digitalWrite(led_pins[2], HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }

  delay(100);
}
