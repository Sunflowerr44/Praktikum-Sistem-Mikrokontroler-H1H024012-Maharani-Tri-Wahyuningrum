# Percobaan 3B - Pembacaan ADC Menggunakan Potensiometer dan LCD I2C

## Source Code
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Ganti alamat jika perlu (0x27 / 0x20)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  // Mapping ke bar (0-16)
  int panjangBar = map(nilai, 0, 1023, 0, 16);

  // Tampilkan ke Serial
  Serial.print("Nilai ADC : ");
  Serial.println(nilai);

  // Baris 1: nilai ADC
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(nilai);
  lcd.print("    ");

  // Baris 2: bar
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}
```

---

# Penjelasan Kode

## Library yang Digunakan
```cpp
#include <Wire.h> //Library untuk komunikasi I2C antara Arduino dan LCD.
#include <LiquidCrystal_I2C.h> //Library untuk mengendalikan LCD yang menggunakan modul I2C.
#include <Arduino.h> //Library utama Arduino yang berisi fungsi-fungsi dasar seperti analogRead(), pinMode(), dan Serial.
```
## Inisialisasi LCD
```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2); //Mendefinisikan LCD I2C dengan alamat `0x27`, jumlah kolom 16, dan jumlah baris 2.
```
## Deklarasi Pin Potensiometer
```cpp
const int pinPot = A0; //Menentukan pin analog A0 sebagai input pembacaan potensiometer.
```
## Fungsi setup()
```cpp
Serial.begin(9600); //Menginisialisasi komunikasi serial dengan baud rate 9600 bps.
lcd.init(); //Menginisialisasi LCD I2C.
lcd.backlight(); //Mengaktifkan lampu latar LCD.
```
## Fungsi loop()
```cpp
int nilai = analogRead(pinPot); //Membaca nilai ADC dari potensiometer. Rentang potensiometer 0-1023.
int panjangBar = map(nilai, 0, 1023, 0, 16); //Mengubah nilai ADC menjadi panjang indikator bar pada LCD dengan rentang 0–16 karakter.
Serial.print("Nilai ADC : "); //Menampilkan nilai ADC pada Serial Monitor.
Serial.println(nilai); //Menampilkan nilai ADC pada Serial Monitor.
lcd.setCursor(0, 0); //Menempatkan kursor pada kolom 0 baris 0 LCD.
lcd.print("ADC: ");
lcd.print(nilai); //Menampilkan nilai ADC pada baris pertama LCD.
lcd.setCursor(0, 1); //Memindahkan kursor ke baris kedua LCD.
for (int i = 0; i < 16; i++) //Melakukan perulangan sebanyak 16 kali sesuai jumlah kolom LCD.
lcd.print((char)255);  //Menampilkan karakter blok penuh sebagai indikator level ADC.
delay(200);
```

# Jawaban Pertanyaan
## 1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!
Komunikasi I2C (Inter Integrated Circuit) menggunakan dua jalur utama yaitu SDA (Serial Data) dan SCL (Serial Clock). Pada rangkaian ini Arduino berperan sebagai master dan LCD I2C berperan sebagai slave.
Proses komunikasi dimulai ketika Arduino mengirimkan alamat perangkat LCD melalui jalur SDA. Setelah alamat dikenali, Arduino mengirimkan data yang ingin ditampilkan pada LCD. Jalur SCL digunakan sebagai sinyal clock untuk menyinkronkan proses pengiriman data. Modul I2C pada LCD menerima data tersebut dan menampilkannya pada layar LCD.
Keuntungan penggunaan I2C adalah hanya membutuhkan empat kabel yaitu VCC, GND, SDA, dan SCL sehingga penggunaan pin Arduino menjadi lebih efisien.
## 2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!
Potensiometer memiliki tiga terminal:
- Pin kiri terhubung ke VCC (5V)
- Pin tengah terhubung ke pin analog A0
- Pin kanan terhubung ke GND
Pin tengah harus tetap terhubung ke A0 karena berfungsi sebagai output tegangan variabel.
Jika pin kiri dan pin kanan ditukar, rangkaian tetap dapat bekerja dengan normal. Namun arah perubahan nilai ADC menjadi terbalik.
Sebelum ditukar:
- Diputar ke kiri → ADC mendekati 0
- Diputar ke kanan → ADC mendekati 1023
Setelah ditukar:
- Diputar ke kiri → ADC mendekati 1023
- Diputar ke kanan → ADC mendekati 0
## 3. Modifikasi Program Menggunakan UART dan I2C Sebagai Output
### Program Modifikasi
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0; //Membaca nilai ADC dari potensiometer.

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {
  int adc = analogRead(pinPot);
  float volt = adc * 5.0 / 1023.0; //Mengubah nilai ADC menjadi tegangan.
  int persen = adc * 100 / 1023; //Mengubah nilai ADC menjadi persentase.
  int level = map(adc, 0, 1023, 0, 16); //Mengubah nilai ADC menjadi panjang indikator level pada LCD.

  Serial.print("ADC: "); //Menampilkan nilai ADC, tegangan, dan persentase pada Serial Monitor.
  Serial.print(adc);

  Serial.print(" Volt: ");
  Serial.print(volt, 2);

  Serial.print(" V Persen: ");
  Serial.print(persen);

  Serial.println("%");

  lcd.setCursor(0, 0); //Menampilkan data ADC dan persentase pada baris pertama LCD.
  lcd.print("ADC:");
  lcd.print(adc);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("% ");

  lcd.setCursor(0, 1); //Menampilkan indikator level pada baris kedua LCD.

  for (int i = 0; i < 16; i++) {
    if (i < level)
      lcd.write(255);
    else
      lcd.print(" ");
  }

  delay(200);
}
```

Untuk hasil dokumentasi, dilihat di folder dokumentasi praktikum percobaan 3B modifikasi