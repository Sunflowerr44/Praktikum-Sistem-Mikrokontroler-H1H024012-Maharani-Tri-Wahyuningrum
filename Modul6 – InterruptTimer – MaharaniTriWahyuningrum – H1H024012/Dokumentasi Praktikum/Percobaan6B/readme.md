# Modul 6B - Timer Menggunakan millis()

## Deskripsi

Percobaan 6B bertujuan untuk mengimplementasikan timer pada Arduino Uno menggunakan fungsi `millis()` tanpa menggunakan fungsi `delay()`. Pada percobaan ini LED dikendalikan agar berubah kondisi setiap 1 detik dengan memanfaatkan perhitungan waktu yang berjalan secara terus-menerus.

## Dokumentasi Percobaan

### Kondisi LED Mati

![LED Mati](6B(1).jpeg)

### Kondisi LED Menyala

![LED Menyala](6B(2).jpeg)

### Video Percobaan
<video controls src="6B.mp4" title="Percobaan 6B"></video>

## Analisis Hasil

Berdasarkan hasil percobaan, LED berhasil berubah kondisi secara berkala setiap 1 detik. Pada saat program dijalankan, Arduino menghitung waktu menggunakan fungsi `millis()`. Ketika selisih waktu antara `currentMillis` dan `previousMillis` mencapai 1000 ms, status LED diubah dari ON menjadi OFF atau sebaliknya.

Pada dokumentasi terlihat bahwa LED merah menyala pada satu kondisi dan mati pada kondisi berikutnya. Hal ini menunjukkan bahwa mekanisme timer bekerja sesuai dengan interval yang telah ditentukan.

Berbeda dengan penggunaan `delay()`, metode `millis()` tidak menghentikan eksekusi program sehingga sistem tetap dapat menjalankan proses lain secara bersamaan. Oleh karena itu metode ini disebut sebagai teknik non-blocking dan lebih cocok digunakan pada sistem embedded yang membutuhkan multitasking sederhana.

## Source Code

```cpp
#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 1000;

bool ledState = false;

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    ledState = !ledState;

    digitalWrite(13, ledState);
  }
}
```

## Penjelasan Program
- `previousMillis` digunakan untuk menyimpan waktu terakhir perubahan LED.
- `interval` bernilai 1000 ms atau 1 detik.
- `millis()` digunakan untuk membaca waktu sejak Arduino dinyalakan.
- Program memeriksa apakah selisih waktu sudah mencapai 1000 ms.
- Jika sudah, status LED dibalik (toggle) menggunakan operator `!`.
- LED kemudian diperbarui menggunakan `digitalWrite()`.

## Kesimpulan

Percobaan berhasil menunjukkan penggunaan timer berbasis `millis()` untuk mengendalikan LED tanpa menggunakan `delay()`. LED dapat berkedip setiap 1 detik sesuai spesifikasi praktikum, serta membuktikan bahwa metode non-blocking memungkinkan program tetap berjalan secara responsif selama proses timing berlangsung.