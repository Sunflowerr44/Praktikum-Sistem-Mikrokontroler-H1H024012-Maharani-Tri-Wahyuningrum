#include <Arduino.h>

// ===================== PIN SETUP =====================
const int potPin = A0;   // pin analog
const int ledPin = 9;    // pin PWM

// ===================== VARIABEL =====================
int nilaiADC = 0;
int pwm = 0;

void setup() {

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // ===================== PEMBACAAN SENSOR =====================
  nilaiADC = analogRead(potPin);

  // ===================== KONVERSI ADC KE PWM =====================
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // ===================== LOGIKA KONDISI =====================
  // LED hanya menyala jika PWM di antara 50 - 200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm); // LED menyala sesuai PWM
  } else {
    analogWrite(ledPin, 0);   // LED mati
  }

  // ===================== MONITORING =====================
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}