# Laporan Praktikum Sistem Mikrokontroler - Percobaan 4A

## Alat dan Bahan
- Arduino Uno
- Potensiometer
- Motor Servo
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
```

## Pertanyaan Percobaan 4A
1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini? \
Jawab : berfungsi untuk membaca tegangan input analog dari pin A0 yang dihasilkan oleh potensiometer dan mengubahnya menjadi nilai digital.
2. Mengapa diperlukan fungsi map() dalam program tersebut? \
Jawab : Karena rentang input ADC (0-1023) tidak sama dengan rentang input sudut servo (0-180). Fungsi map() melakukan penskalaan agar nilai potensio yang terbaca dapat diterjemahkan ke dalam derajat sudut servo.
3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. \
Jawab : Untuk membatasi gerak servo, baris kode mapping diubah menjadi:
pos = map(val, 0, 1023, 30, 150);
Karena dengan ini, meskipun potensiometer diputar maksimal, servo hanya akan bergerak di area tengah (30 hingga 150 derajat) untuk menghindari beban berlebih pada engsel mekanik atau sesuai kebutuhan sistem.