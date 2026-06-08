# Penjelasan Program

## Library yang Digunakan
```cpp
#include <Arduino_FreeRTOS.h>
```
Library FreeRTOS digunakan untuk mengaktifkan fitur Real-Time Operating System pada Arduino sehingga beberapa task dapat dijalankan secara concurrent menggunakan scheduler.

## Deklarasi Task
```cpp
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void Taskprint( void *pvParameters );
```
Ketiga baris tersebut merupakan deklarasi fungsi task yang akan dijalankan oleh FreeRTOS.
- `TaskBlink1()` : Mengendalikan LED pada pin 8.
- `TaskBlink2()` : Mengendalikan LED pada pin 7.
- `Taskprint()` : Menampilkan nilai counter pada Serial Monitor.

## Fungsi setup()
```cpp
void setup() {
  Serial.begin(9600);
```
Mengaktifkan komunikasi serial dengan baud rate 9600 bps.

### Membuat Task Pertama
```cpp
xTaskCreate(
  TaskBlink1,
  "task1",
  128,
  NULL,
  1,
  NULL );

xTaskCreate(
  TaskBlink2,
  "task2",
  128,
  NULL,
  1,
  NULL );

xTaskCreate(
  Taskprint,
  "task3",
  128,
  NULL,
  1,
  NULL );
```
Parameter yang digunakan:
| Parameter | Keterangan |
|------------|------------|
| TaskBlink1 | Fungsi task yang dijalankan |
| "task1" | Nama task |
| 128 | Ukuran stack task |
| NULL | Tidak menggunakan parameter |
| 1 | Prioritas task |
| NULL | Tidak menggunakan task handle |

Task pertama bertugas mengendalikan LED pada pin 8.
Task kedua bertugas mengendalikan LED pada pin 7.
Task ketiga bertugas mencetak nilai counter ke Serial Monitor.

### Menjalankan Scheduler
```cpp
vTaskStartScheduler();
```
Scheduler FreeRTOS mulai bekerja dan mengatur pergantian eksekusi antar task. Setelah scheduler aktif, seluruh task akan berjalan sesuai jadwal yang telah ditentukan.


## Task 1 : LED Pin 8

```cpp
void TaskBlink1(void *pvParameters)
{
  pinMode(8, OUTPUT);
```
Mengatur pin 8 sebagai output.

```cpp
Serial.println("Task1");
```
Menampilkan teks "Task1" pada Serial Monitor.

```cpp
digitalWrite(8, HIGH);
```
Menyalakan LED.

```cpp
vTaskDelay(200 / portTICK_PERIOD_MS);
```
Menunggu selama 200 ms.

```cpp
digitalWrite(8, LOW);
```
Mematikan LED.

```cpp
vTaskDelay(200 / portTICK_PERIOD_MS);
```
Menunggu kembali selama 200 ms sebelum mengulangi proses.


## Task 2 : LED Pin 7

```cpp
void TaskBlink2(void *pvParameters)
```
Task ini bekerja sama seperti Task 1, namun menggunakan pin 7.

```cpp
digitalWrite(7, HIGH);
vTaskDelay(300 / portTICK_PERIOD_MS);
digitalWrite(7, LOW);
vTaskDelay(300 / portTICK_PERIOD_MS);
```
LED berkedip dengan periode 300 ms sehingga kecepatannya berbeda dengan LED pada Task 1.


## Task 3 : Counter

```cpp
void Taskprint(void *pvParameters)
{
  int counter = 0;
```
Variabel counter digunakan untuk menghitung jumlah iterasi task.

```cpp
counter++;
```
Nilai counter bertambah satu setiap siklus.

```cpp
Serial.println(counter);
```
Menampilkan nilai counter pada Serial Monitor.

```cpp
vTaskDelay(500 / portTICK_PERIOD_MS);
```
Task menunggu selama 500 ms sebelum menghitung kembali.

# Hasil Program
Program menjalankan tiga task secara concurrent:
1. LED pada pin 8 berkedip setiap 200 ms.
2. LED pada pin 7 berkedip setiap 300 ms.
3. Counter pada Serial Monitor bertambah setiap 500 ms.
Ketiga task dijalankan dan diatur oleh scheduler FreeRTOS sehingga dapat berjalan secara bersamaan dari sudut pandang pengguna.


# Jawaban Pertanyaan Praktikum 5A

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Ketiga task terlihat berjalan secara bersamaan, namun sebenarnya dijalankan secara bergantian oleh scheduler FreeRTOS menggunakan teknik multitasking.
Scheduler memberikan waktu eksekusi kepada setiap task berdasarkan prioritas dan status task. Ketika suatu task menjalankan fungsi `vTaskDelay()`, task tersebut masuk ke keadaan blocked sehingga scheduler dapat memberikan CPU kepada task lain yang siap dijalankan.
Karena proses pergantian task berlangsung sangat cepat, pengguna melihat ketiga task berjalan secara bersamaan.

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!
Langkah-langkah menambahkan task keempat:
Membuat fungsi task baru
```cpp
void Task4(void *pvParameters)
{
  while(1)
  {
    Serial.println("Task4");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```
Menambahkan xTaskCreate pada setup()
```cpp
xTaskCreate(
  Task4,
  "task4",
  128,
  NULL,
  1,
  NULL );
```

Upload ulang program
Setelah ditambahkan, scheduler akan mengatur empat task secara otomatis.


## 3. Modifikasi program menggunakan potensiometer untuk mengontrol kecepatan LED. Bagaimana hasilnya?
Potensiometer dapat dihubungkan ke pin analog Arduino, misalnya A0. Nilai ADC yang dibaca akan digunakan untuk menentukan nilai delay LED.
Contoh:
```cpp
int nilaiPot = analogRead(A0);

int delayLED = map(nilaiPot, 0, 1023, 100, 1000);
```
Ketika potensiometer diputar:
- Nilai ADC meningkat atau menurun.
- Nilai delay LED berubah.
- Kecepatan kedipan LED ikut berubah.
Hasil percobaan menunjukkan bahwa semakin besar nilai potensiometer maka periode delay semakin besar sehingga LED berkedip lebih lambat. Sebaliknya, semakin kecil nilai potensiometer maka LED berkedip lebih cepat.