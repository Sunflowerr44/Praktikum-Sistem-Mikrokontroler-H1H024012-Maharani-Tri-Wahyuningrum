# Laporan Praktikum Sistem Mikrokontroler - Percobaan 4B


## Tujuan Praktikum
1. Memahami konsep dasar PWM (Pulse Width Modulation).
2. Mengetahui cara kerja fungsi `analogWrite()` untuk menghasilkan tegangan rata-rata yang bervariasi.
3. Mengatur intensitas cahaya LED berdasarkan input analog.

## Dasar Teori
### Pulse Width Modulation (PWM)
PWM adalah teknik untuk mendapatkan sinyal analog dari sistem digital. Dengan mengatur *Duty Cycle* (rasio waktu sinyal HIGH terhadap periode total), kita bisa mengatur jumlah daya yang dikirim ke komponen seperti LED.


## Alat dan Bahan
- Arduino Uno
- Potensiometer
- LED (Merah)
- Resistor 220 Ohm
- Kabel Jumper & Breadboard

## Kode Program (modul4_percobaan2.ino)
```cpp
#include <Arduino.h>

// ===================== PIN SETUP =====================
const int potPin = A0;   // Pin analog potensiometer
const int ledPin = 9;    // Pin digital PWM (mendukung analogWrite)

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

  // ===================== PEMROSESAN DATA (SCALING) =====================
  // Mengubah rentang 0-1023 (ADC) ke 0-255 (PWM 8-bit)
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // ===================== OUTPUT PWM =====================
  analogWrite(ledPin, pwm); 

  // ===================== MONITORING DATA =====================
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  // ===================== STABILISASI SISTEM =====================
  delay(50); 
}
```

## Pertanyaan Praktikum 4b
1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()! \
Jawab : Karena analogWrite() menghasilkan sinyal PWM yang memanipulasi durasi kondisi HIGH dan LOW pada pin digital dalam satu periode.
2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)? \
Jawab : Nilai ADC memiliki resolusi 10-bit (1024 tingkat), sedangkan PWM pada Arduino Uno memiliki resolusi 8-bit (256 tingkat). Oleh karena itu, terdapat rasio 4:1, di mana nilai ADC perlu dikonversi/dibagi agar sesuai dengan batas maksimal input PWM.
3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. \
Jawab : \
kode yang dimodifikasi : pwm = map(nilaiADC, 0, 1023, 50, 200); \
Dengan memodifikasi fungsi map(), kita membatasi output PWM. Meskipun potensiometer diputar ke posisi minimum, LED tetap menyala redup (nilai 50), dan saat diputar maksimal, LED tidak akan mencapai kecerahan penuh (hanya nilai 200).