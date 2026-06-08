# Percobaan 6A (External Interrupt)

# Source Code
```cpp
#include <Arduino.h>

// Variabel volatile agar dapat diubah dalam ISR
volatile bool ledState = false;

// ISR: dijalankan saat tombol ditekan
void tombolInterrupt() {
  ledState = !ledState; // Toggle status LED
}

void setup() {

  // Konfigurasi pin 13 sebagai output (LED)
  pinMode(13, OUTPUT);

  // Konfigurasi pin 2 sebagai input pull-up
  pinMode(2, INPUT_PULLUP);

  // Daftarkan interrupt pada pin 2
  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    FALLING
  );
}

void loop() {

  // Menulis status LED sesuai variabel ledState
  digitalWrite(13, ledState);

}
```

---

# Penjelasan Program
## 1. Memanggil Library Arduino
```cpp
#include <Arduino.h>
```
Library utama Arduino yang berisi fungsi-fungsi dasar seperti:

* pinMode()
* digitalWrite()
* attachInterrupt()

## 2. Deklarasi Variabel Global
```cpp
volatile bool ledState = false;
```
Variabel digunakan untuk menyimpan kondisi LED.
Nilai awal:

* false -> LED mati
* true -> LED menyala
Keyword `volatile` digunakan karena variabel ini diakses baik oleh program utama maupun oleh ISR (Interrupt Service Routine).

## 3. Interrupt Service Routine (ISR)
```cpp
void tombolInterrupt() {
  ledState = !ledState;
}
```
Fungsi ini akan dijalankan secara otomatis ketika interrupt terjadi.
Operator `!` digunakan untuk membalik nilai variabel, yang di mana jika nilai awalnya true, maka menjadi false, begitu juga sebaliknya.Akibatnya LED akan berganti status setiap tombol ditekan.

## 4. Fungsi setup()

### Konfigurasi LED
```cpp
pinMode(13, OUTPUT);
```
Pin 13 digunakan sebagai output untuk LED.

### Konfigurasi Push Button
```cpp
pinMode(2, INPUT_PULLUP);
```
Pin 2 digunakan sebagai input dengan resistor pull-up internal Arduino. Yang di mana berarti jika tombol tidak ditekan, maka pin nya HIGH, tapi jika tombol ditekan, maka nilai pin nya akan LOW


### Mendaftarkan Interrupt
```cpp
attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    FALLING
);
```
Keterangan:
* `digitalPinToInterrupt(2)` -> menggunakan interrupt pada pin 2
* `tombolInterrupt` -> fungsi ISR yang dijalankan
* `FALLING` -> interrupt aktif saat sinyal berubah dari HIGH ke LOW

## 5. Fungsi loop()
```cpp
digitalWrite(13, ledState);
```
Program utama hanya menuliskan status LED sesuai nilai variabel `ledState`.
Jika:
* true, maka LED menyala
* false, maka LED mati

# Jawaban Pertanyaan Praktikum
## 1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan interrupt!
Ketika tombol ditekan, tegangan pada pin 2 berubah dari HIGH menjadi LOW karena menggunakan konfigurasi INPUT_PULLUP. Perubahan sinyal tersebut dideteksi oleh interrupt dengan mode FALLING. Arduino kemudian menghentikan sementara program utama dan menjalankan ISR `tombolInterrupt()`. Di dalam ISR, nilai `ledState` dibalik menggunakan operator `!`. Setelah ISR selesai, program kembali ke loop() dan memperbarui kondisi LED sesuai nilai terbaru dari `ledState`.

## 2. Apa fungsi attachInterrupt() pada program tersebut?
Fungsi `attachInterrupt()` digunakan untuk menghubungkan suatu pin interrupt dengan ISR.
Pada program:
```cpp
attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    FALLING
);
```
artinya:
* Pin 2 digunakan sebagai sumber interrupt
* ISR yang dijalankan adalah `tombolInterrupt()`
* Interrupt aktif saat terjadi perubahan HIGH -> LOW

## 3. Mengapa pada ISR tidak disarankan menggunakan delay() dan Serial.print()?
### delay()
Fungsi delay() menghentikan eksekusi program selama waktu tertentu.
Jika digunakan dalam ISR, maka Interrupt lain tidak dapat diproses, sistem menjadi lambat, dan respons real-time terganggu
### Serial.print()
Komunikasi serial membutuhkan interrupt internal.
Saat ISR berjalan, interrupt lain biasanya dinonaktifkan sementara sehingga data serial dapat gagal terkirim dan program dapat hang atau tidak stabil. Karena itu ISR harus dibuat sesingkat mungkin.

## 4. Apa fungsi keyword volatile pada variabel ledState?
Keyword `volatile` memberi tahu compiler bahwa nilai variabel dapat berubah sewaktu-waktu di luar alur normal program. Tanpa volatile, compiler dapat mengoptimasi variabel sehingga perubahan yang dilakukan ISR tidak selalu terbaca oleh program utama. Dengan volatile, Arduino selalu membaca nilai terbaru dari memori.

## 5. Modifikasi Program Menggunakan Mode Interrupt Lain
## A. Mode RISING
### Source Code
```cpp
attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    RISING
);
```
### Cara Kerja
Interrupt aktif saat sinyal berubah: LOW -> HIGH
### Analisis
Karena menggunakan INPUT_PULLUP:
* Tombol ditekan -> LOW
* Tombol dilepas -> HIGH
Interrupt terjadi ketika tombol dilepas.
Akibatnya LED berubah kondisi saat tombol dilepas, bukan saat ditekan.

## B. Mode CHANGE
### Source Code
```cpp
attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    CHANGE
);
```
### Cara Kerja
Interrupt aktif setiap kali terjadi perubahan logika.
```text
HIGH -> LOW
atau
LOW -> HIGH
```
### Analisis
Interrupt terjadi dua kali:
1. Saat tombol ditekan
2. Saat tombol dilepas
Karena LED ditoggle setiap interrupt, LED dapat berubah dua kali dalam satu siklus penekanan tombol sehingga kondisi akhirnya bisa kembali seperti semula.
## C. Mode LOW
### Source Code
```cpp
attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    LOW
);
```
### Cara Kerja
Interrupt aktif selama pin berada pada kondisi LOW.
### Analisis
Saat tombol ditekan dan ditahan:
* Pin tetap LOW
* ISR dipanggil berulang kali
Akibatnya LED dapat berkedip sangat cepat atau berubah kondisi secara terus-menerus selama tombol ditekan. Mode LOW umumnya digunakan untuk kondisi khusus dan jarang dipakai untuk push button sederhana.


# Perbandingan Mode Interrupt
| Mode    | Kondisi Pemicu | LED                            |
| ------- | -------------- | --------------------------------------- |
| FALLING | HIGH -> LOW     | LED berubah saat tombol ditekan         |
| RISING  | LOW -> HIGH     | LED berubah saat tombol dilepas         |
| CHANGE  | HIGH -> LOW     | LED berubah saat ditekan dan dilepas    |
| LOW     | Selama LOW     | LED berubah terus selama tombol ditekan |

# Kesimpulan
External interrupt memungkinkan Arduino merespons penekanan tombol tanpa melakukan polling secara terus-menerus. Pada percobaan ini, LED berhasil dikendalikan menggunakan interrupt pada pin 2 dengan mode FALLING. Penggunaan interrupt membuat sistem lebih responsif dan efisien dibandingkan metode polling karena prosesor hanya menjalankan ISR ketika event benar-benar terjadi.
