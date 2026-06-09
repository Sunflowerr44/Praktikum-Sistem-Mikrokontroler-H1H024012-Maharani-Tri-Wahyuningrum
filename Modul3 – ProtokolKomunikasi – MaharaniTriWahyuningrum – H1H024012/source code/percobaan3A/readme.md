# Percobaan 3A - Mengontrol LED Menggunakan Serial Monitor

## Source Code
```cpp
#include <Arduino.h>

const int PIN_LED = 12;

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      digitalWrite(PIN_LED, HIGH);
      Serial.println("LED ON");
    }
    else if (data == '0') {
      digitalWrite(PIN_LED, LOW);
      Serial.println("LED OFF");
    }
    else if (data != '\n' && data != '\r') {
      Serial.println("Perintah tidak dikenal");
    }
  }
}
```


# Penjelasan Kode

### Import Library
```cpp
#include <Arduino.h>
```
Menggunakan library utama Arduino yang menyediakan fungsi dasar seperti `pinMode()`, `digitalWrite()`, `Serial.begin()`, dan lain-lain.

### Deklarasi Pin LED
```cpp
const int PIN_LED = 12;
```
Ini untuk mendefinisikan pin digital 12 sebagai pin yang terhubung ke LED.

### Fungsi setup()
```cpp
void setup() {
```
Fungsi yang hanya dijalankan satu kali saat Arduino pertama kali dinyalakan atau di-reset.
```cpp
Serial.begin(9600);
```
Menginisialisasi komunikasi serial dengan baud rate 9600 bps.
```cpp
Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED");
```
Menampilkan instruksi pada Serial Monitor.
```cpp
pinMode(PIN_LED, OUTPUT);
```
Mengatur pin 12 sebagai output.

### Fungsi loop()
```cpp
void loop() {
```
Fungsi yang dijalankan secara berulang selama Arduino aktif.
```cpp
if (Serial.available() > 0)
```
Memeriksa apakah terdapat data yang masuk dari Serial Monitor.
```cpp
char data = Serial.read();
```
Membaca satu karakter yang dikirim pengguna.

### Menyalakan LED
```cpp
if (data == '1')
```
Memeriksa apakah karakter yang diterima adalah '1'.
```cpp
digitalWrite(PIN_LED, HIGH);
```
Memberikan logika HIGH pada pin 12 sehingga LED menyala.
```cpp
Serial.println("LED ON");
```
Menampilkan status LED pada Serial Monitor.

### Mematikan LED
```cpp
else if (data == '0')
```
Memeriksa apakah karakter yang diterima adalah '0'.
```cpp
digitalWrite(PIN_LED, LOW);
```
Memberikan logika LOW pada pin 12 sehingga LED mati.
```cpp
Serial.println("LED OFF");
```
Menampilkan status LED pada Serial Monitor.

### Input Tidak Dikenal
```cpp
else if (data != '\n' && data != '\r')
```
Memastikan karakter yang dibaca bukan karakter Enter.
```cpp
Serial.println("Perintah tidak dikenal");
```
Menampilkan pesan kesalahan jika input selain '0' dan '1'.

# Jawaban Pertanyaan
## 1. Jelaskan proses dari input keyboard hingga LED menyala/mati!
Proses dimulai ketika pengguna mengetik karakter pada Serial Monitor dan menekan tombol Enter. Data tersebut dikirim dari komputer ke Arduino melalui komunikasi serial menggunakan kabel USB. Arduino memeriksa apakah ada data yang masuk menggunakan `Serial.available()`. Jika terdapat data, Arduino membacanya menggunakan `Serial.read()`.
Apabila karakter yang diterima adalah `'1'`, Arduino menjalankan fungsi `digitalWrite(PIN_LED, HIGH)` sehingga pin 12 menghasilkan tegangan sekitar 5V dan LED menyala. Sebaliknya, jika karakter yang diterima adalah `'0'`, Arduino menjalankan `digitalWrite(PIN_LED, LOW)` sehingga tegangan pada pin menjadi 0V dan LED mati.
## 2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
Fungsi:
```cpp
Serial.available()
```
digunakan untuk memeriksa apakah terdapat data yang tersedia pada buffer serial sebelum dilakukan pembacaan.
Jika kondisi ini dihilangkan:
```cpp
char data = Serial.read();
```
akan tetap dieksekusi meskipun tidak ada data yang masuk. Akibatnya Arduino dapat membaca nilai kosong (`-1`) yang kemudian menghasilkan perilaku tidak diinginkan, seperti munculnya pesan error berulang atau pembacaan data yang tidak valid. Oleh karena itu, `Serial.available()` digunakan untuk memastikan bahwa data benar-benar tersedia sebelum dibaca.
## 3. Modifikasi Program Agar LED Berkedip Saat Menerima Input '2'
### Program Modifikasi
```cpp
#include <Arduino.h>

const int PIN_LED = 12;

int modeLED = 0; //Menyimpan mode operasi LED (0=OFF ; 1=ON ; 2=BLINK)
unsigned long previousMillis = 0; //Menyimpan waktu terakhir LED berubah keadaan.
const long interval = 500; //Interval kedip LED sebesar 500 ms.
bool ledState = LOW; //Menyimpan kondisi LED saat ini.

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);

  Serial.println("1 = ON");
  Serial.println("0 = OFF");
  Serial.println("2 = BLINK");
}

void loop() {

  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      modeLED = 1;
      digitalWrite(PIN_LED, HIGH);
      Serial.println("LED ON");
    }

    else if (data == '0') {
      modeLED = 0;
      digitalWrite(PIN_LED, LOW);
      Serial.println("LED OFF");
    }

    else if (data == '2') {
      modeLED = 2; //Diaktifkan ketika pengguna mengirim karakter 2.
      Serial.println("LED BLINK");
    }
  }

  if (modeLED == 2) {
    unsigned long currentMillis = millis(); //Membaca waktu sejak Arduino dinyalakan.

    if (currentMillis - previousMillis >= interval) { //Memeriksa apakah waktu interval telah tercapai.
      previousMillis = currentMillis;

      ledState = !ledState; //Membalik status LED dari ON menjadi OFF atau sebaliknya.
      digitalWrite(PIN_LED, ledState); //Mengubah kondisi LED sesuai nilai `ledState`.
    }
  }
}
```
## 4. Program Menggunakan delay() atau millis()? Jelaskan Pengaruhnya terhadap Sistem
Program modifikasi menggunakan millis() bukan delay().

### Jika Menggunakan delay()
```cpp
delay(500);
```
Arduino akan berhenti menjalankan program selama 500 ms. Selama waktu tersebut Arduino tidak dapat membaca input serial baru sehingga respons sistem menjadi lambat.
### Jika Menggunakan millis()
Arduino tetap dapat menjalankan tugas lain sambil menghitung waktu kedipan LED. Sistem menjadi lebih responsif karena input baru dari Serial Monitor dapat langsung diproses tanpa harus menunggu proses kedipan selesai.
### Kesimpulan
Penggunaan `millis()` lebih baik dibandingkan `delay()` pada sistem yang memerlukan multitasking sederhana atau respons real-time karena tidak menghambat eksekusi program utama.