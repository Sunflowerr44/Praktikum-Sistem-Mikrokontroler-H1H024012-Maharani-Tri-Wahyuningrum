# Laporan Praktikum Sistem Embedded - Percobaan 4A
**Nama:** Maharani Tri Wahyuningrum  
**NIM:** 12  
**Instansi:** Universitas Jenderal Soedirman

## Tujuan Praktikum
1. Mampu mengetahui fungsi `analogRead()`.
2. Mampu mengaplikasikan ADC pada Arduino Uno untuk mengendalikan aktuator.
3. Mengonversi nilai analog dari potensiometer menjadi sudut pergerakan Motor Servo.

## Dasar Teori
### Analog to Digital Converter (ADC)
ADC adalah fitur yang mengubah sinyal analog (tegangan kontinu) menjadi data digital (angka diskrit). Arduino Uno memiliki ADC 10-bit, yang berarti tegangan 0-5V akan dikonversi menjadi rentang angka 0 hingga 1023.


## Alat dan Bahan
- Arduino Uno
- Potensiometer (10k Ohm)
- Motor Servo (SG90)
- Kabel Jumper & Breadboard

## Kode Program (modul4_percobaan1.ino)
```cpp
#include <Servo.h> 

Servo myservo; 

// ===================== PIN SETUP =====================
const int potensioPin = A0;   // Pin analog input dari potensiometer
const int servoPin = 9;      // Pin digital PWM untuk servo

// ===================== VARIABEL =====================
int pos = 0; // Variabel untuk menyimpan posisi sudut servo
int val = 0; // Variabel untuk menyimpan nilai mentah ADC

void setup() {
  myservo.attach(servoPin);  // Menghubungkan servo ke pin 9
  Serial.begin(9600);        // Baud rate 9600
}

void loop() {
  // ===================== PEMBACAAN ADC =====================
  val = analogRead(potensioPin); // Membaca nilai (0-1023)

  // ===================== KONVERSI DATA =====================
  // Mengubah rentang 0-1023 menjadi 0-180 derajat
  pos = map(val, 0, 1023, 0, 180);

  // ===================== OUTPUT SERVO =====================
  myservo.write(pos); // Menggerakkan servo

  // ===================== MONITORING DATA =====================
  Serial.print("ADC Potensio: ");
  Serial.print(val); 
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); 

  // ===================== STABILISASI =====================
  delay(15); // Delay standar untuk pergerakan servo
}

##Pertanyaan Percobaan 4A
1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
Jawab : 
2. Mengapa diperlukan fungsi map() dalam program tersebut?
3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023.