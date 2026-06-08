# Penjelasan Program
## Source Code
```cpp
#include <Arduino.h>

unsigned long previousMillis = 0; // Waktu terakhir LED berubah
const long interval = 1000;       // Interval kedip 1 detik

bool ledState = false;            // Status LED

void setup() {

  // Pin 13 sebagai output
  pinMode(13, OUTPUT);

}

void loop() {

  // Ambil waktu saat ini
  unsigned long currentMillis = millis();

  // Cek apakah interval sudah tercapai
  if (currentMillis - previousMillis >= interval) {

    // Simpan waktu sekarang
    previousMillis = currentMillis;

    // Toggle LED
    ledState = !ledState;

    // Tulis ke LED
    digitalWrite(13, ledState);
  }

}
```

---

# Penjelasan Kode

## Library Arduino
```cpp
#include <Arduino.h>
```
Library utama Arduino yang menyediakan fungsi-fungsi dasar seperti `pinMode()`, `digitalWrite()`, `millis()`

## Variabel Waktu
```cpp
unsigned long previousMillis = 0;
```
Variabel untuk menyimpan waktu terakhir LED berubah kondisi. Nilai awal `0` menunjukkan program baru mulai dijalankan.
```cpp
const long interval = 1000;
```
Menentukan interval waktu kedip LED. Karena nilainya `1000`, maka LED akan berubah kondisi setiap 1000 ms atau 1 detik. Keyword `const` digunakan karena nilai interval tidak akan berubah selama program berjalan.

## Variabel Status LED
```cpp
bool ledState = false;
```
Digunakan untuk menyimpan kondisi LED.
* `false` = LED mati
* `true` = LED menyala

### Konfigurasi Pin
```cpp
pinMode(13, OUTPUT);
```
Mengatur pin 13 sebagai output untuk LED.

## Fungsi loop()
```cpp
void loop() {
```
Fungsi ini akan dijalankan terus-menerus selama Arduino aktif.

### Membaca Waktu Saat Ini
```cpp
unsigned long currentMillis = millis();
```
Fungsi `millis()` mengembalikan jumlah waktu yang telah berlalu sejak Arduino dinyalakan dalam satuan milidetik (ms).
Contoh:
| Waktu Nyala Arduino | Nilai millis() |
| ------------------- | -------------- |
| 1 detik             | 1000           |
| 5 detik             | 5000           |
| 10 detik            | 10000          |
Nilai tersebut disimpan pada variabel `currentMillis`.

### Memeriksa Interval Waktu
```cpp
if (currentMillis - previousMillis >= interval)
```
Program menghitung selisih waktu antara:
* waktu sekarang (`currentMillis`)
* waktu terakhir LED berubah (`previousMillis`)
Jika selisihnya mencapai 1000 ms, maka LED akan diubah kondisinya.

### Menyimpan Waktu Terbaru
```cpp
previousMillis = currentMillis;
```
Setelah interval tercapai, waktu sekarang disimpan sebagai acuan untuk perhitungan berikutnya.

### Mengubah Kondisi LED
```cpp
ledState = !ledState;
```
Melakukan toggle status LED:
* OFF -> ON
* ON -> OFF

### Menampilkan Status LED
```cpp
digitalWrite(13, ledState);
```
Menuliskan nilai `ledState` ke pin 13 sehingga LED berubah sesuai kondisi yang diinginkan.


# Jawaban Pertanyaan Praktikum
## 1. Jelaskan bagaimana fungsi millis() bekerja pada program tersebut!
Fungsi `millis()` digunakan untuk menghitung waktu sejak Arduino mulai menyala. Nilai yang dikembalikan berupa milidetik (ms). Pada program ini, `millis()` digunakan untuk mengetahui kapan LED harus berubah kondisi. Program membandingkan waktu saat ini dengan waktu terakhir LED berubah. Jika selisih waktunya mencapai 1000 ms, LED akan di-toggle. Dengan cara ini LED dapat berkedip setiap 1 detik tanpa menggunakan fungsi `delay()`.

## 2. Apa perbedaan utama antara delay() dan millis()?
| delay()                                         | millis()                                   |
| ----------------------------------------------- | ------------------------------------------ |
| Bersifat blocking                               | Bersifat non-blocking                      |
| Program berhenti sementara                      | Program tetap berjalan                     |
| Tidak dapat menjalankan tugas lain selama delay | Dapat menjalankan beberapa tugas sekaligus |
| Cocok untuk program sederhana                   | Cocok untuk sistem multitasking            |
Contoh:
```cpp
delay(1000);
```
Arduino berhenti selama 1 detik.
Sedangkan:
```cpp
if (millis() - previousMillis >= 1000)
```
Arduino tetap menjalankan program sambil menunggu waktu mencapai 1 detik.

## 3. Mengapa metode millis() disebut non-blocking?
Metode `millis()` disebut non-blocking karena tidak menghentikan jalannya program. Selama menunggu interval waktu tercapai, Arduino tetap dapat:
* Membaca sensor
* Menangani tombol
* Mengirim data serial
* Menjalankan proses lainnya

Program hanya melakukan pengecekan waktu tanpa menghentikan eksekusi. Karena itu metode ini sangat cocok digunakan pada sistem embedded yang membutuhkan beberapa tugas berjalan secara bersamaan.

## 4. Modifikasi Program
### Spesifikasi
* LED 1 berkedip setiap 1 detik
* LED 2 berkedip setiap 500 ms
* Tidak menggunakan delay()
## Source Code Modifikasi
```cpp
#include <Arduino.h>

// LED 1
unsigned long previousMillis1 = 0;
const long interval1 = 1000;
bool ledState1 = false;

// LED 2
unsigned long previousMillis2 = 0;
const long interval2 = 500;
bool ledState2 = false;

void setup() {

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {

  unsigned long currentMillis = millis();

  // LED 1 setiap 1 detik
  if (currentMillis - previousMillis1 >= interval1) {

    previousMillis1 = currentMillis;

    ledState1 = !ledState1;

    digitalWrite(13, ledState1);
  }

  // LED 2 setiap 500 ms
  if (currentMillis - previousMillis2 >= interval2) {

    previousMillis2 = currentMillis;

    ledState2 = !ledState2;

    digitalWrite(12, ledState2);
  }

}
```

---

# Program Modifikasi
## Variabel LED 1
```cpp
unsigned long previousMillis1 = 0;
const long interval1 = 1000;
bool ledState1 = false;
```
Digunakan untuk mengatur LED pertama yang berkedip setiap 1 detik.

## Variabel LED 2
```cpp
unsigned long previousMillis2 = 0;
const long interval2 = 500;
bool ledState2 = false;
```
Digunakan untuk mengatur LED kedua yang berkedip setiap 500 ms.

## Setup
```cpp
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
```
Pin 13 digunakan untuk LED pertama. Pin 12 digunakan untuk LED kedua.
## Timer LED Pertama
```cpp
if (currentMillis - previousMillis1 >= interval1)
```
Ini untuk mengecek apakah sudah berlalu 1000 ms sejak perubahan terakhir LED pertama.
## Timer LED Kedua
```cpp
if (currentMillis - previousMillis2 >= interval2)
```
Ini untuk mengecek apakah sudah berlalu 500 ms sejak perubahan terakhir LED kedua.
## Hasil Program
LED pertama akan berkedip setiap 1 detik.
LED kedua akan berkedip setiap 500 ms.
Kedua LED dapat berjalan bersamaan tanpa saling mengganggu karena menggunakan metode `millis()` yang bersifat non-blocking.

# Kesimpulan
Percobaan ini menunjukkan bahwa fungsi `millis()` dapat digunakan sebagai timer untuk mengatur waktu tanpa menghentikan jalannya program. Dibandingkan `delay()`, metode `millis()` lebih efisien karena memungkinkan beberapa tugas berjalan secara bersamaan. Dengan memanfaatkan beberapa variabel timer, lebih dari satu LED dapat dikendalikan dengan interval berbeda tanpa menggunakan delay().
