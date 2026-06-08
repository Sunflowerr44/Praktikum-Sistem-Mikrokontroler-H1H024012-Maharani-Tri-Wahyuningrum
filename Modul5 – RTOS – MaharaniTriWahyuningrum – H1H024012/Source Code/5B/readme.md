# Penjelasan Program

## Library yang Digunakan
```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
```
Library `Arduino_FreeRTOS.h` digunakan untuk menjalankan sistem operasi FreeRTOS pada Arduino.
Library `queue.h` digunakan untuk menyediakan fitur Queue sebagai media komunikasi antar task.


## Struktur Data
```cpp
struct readings{
  int temp;
  int h;
};
```
Struktur `readings` digunakan untuk menyimpan dua data:
- `temp` : nilai suhu
- `h` : nilai kelembapan
Data ini nantinya akan dikirim melalui queue dari task pengirim ke task penerima.


## Deklarasi Queue
```cpp
QueueHandle_t my_queue;
```
Variabel `my_queue` digunakan sebagai handle atau penunjuk queue yang akan dipakai oleh kedua task.


### Membuat Queue
```cpp
my_queue = xQueueCreate(1, sizeof(struct readings));
```
Queue dibuat dengan spesifikasi:
- Kapasitas queue = 1 data
- Tipe data = `struct readings`
Artinya queue hanya dapat menyimpan satu data pembacaan pada satu waktu.


### Membuat Task Pengirim Data
```cpp
xTaskCreate(
  read_data,
  "read sensors",
  128,
  NULL,
  0,
  NULL
);
```
Task ini bertugas membaca data sensor dan mengirimkannya ke queue.


### Membuat Task Penerima Data
```cpp
xTaskCreate(
  display,
  "display",
  128,
  NULL,
  0,
  NULL
);
```
Task ini bertugas menerima data dari queue dan menampilkannya ke Serial Monitor.


## Fungsi loop()
```cpp
void loop() {}
```
Pada FreeRTOS fungsi `loop()` tidak digunakan karena seluruh pekerjaan sudah ditangani oleh task-task yang dibuat menggunakan `xTaskCreate()`.


## Task Pembaca Data
```cpp
void read_data(void *pvParameters)
{
```
Task ini berfungsi sebagai pengirim data.

### Membuat Variabel Data
```cpp
struct readings x;
```
Variabel `x` digunakan untuk menyimpan data yang akan dikirim.


### Mengisi Nilai Data
```cpp
x.temp = 54;
x.h = 30;
```
Data suhu dan kelembapan diisi secara statis.
- Suhu = 54
- Kelembapan = 30


### Mengirim Data ke Queue
```cpp
xQueueSend(my_queue,&x,portMAX_DELAY);
```
Parameter:

| Parameter | Fungsi |
|------------|---------|
| my_queue | Queue tujuan |
| &x | Data yang dikirim |
| portMAX_DELAY | Menunggu hingga queue tersedia |


### Delay Task
```cpp
vTaskDelay(100);
```
Task berhenti sementara selama 100 tick sebelum mengirim data berikutnya.


## Task Penampil Data
```cpp
void display(void *pvParameters)
{
```
Task ini bertugas menerima data dari queue.


### Membuat Variabel Penampung
```cpp
struct readings x;
```
Variabel digunakan untuk menerima data dari queue.


### Menerima Data dari Queue
```cpp
if(xQueueReceive(my_queue,&x,portMAX_DELAY) == pdPASS)
```
Task menunggu hingga terdapat data pada queue.
Jika data berhasil diterima maka program akan menampilkan nilainya.


### Menampilkan Data
```cpp
Serial.print("temp = ");
Serial.println(x.temp);
Serial.print("humidity = ");
Serial.println(x.h);
```
Output Serial Monitor:
```text
temp = 54
humidity = 30
```


# Hasil Program
Program berhasil menunjukkan komunikasi antar task menggunakan Queue.
Task `read_data` mengirimkan data suhu dan kelembapan ke queue, sedangkan task `display` menerima data tersebut dan menampilkannya pada Serial Monitor.
Dengan Queue, data dapat dipertukarkan secara aman tanpa konflik akses antar task.


# Jawaban Pertanyaan Praktikum 5B
## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Kedua task terlihat berjalan secara bersamaan, tetapi sebenarnya dijalankan secara bergantian oleh scheduler FreeRTOS.
Mekanismenya adalah:
1. Task `read_data` mengirim data ke queue.
2. Setelah mengirim data, task masuk ke kondisi delay.
3. Scheduler kemudian menjalankan task `display`.
4. Task `display` membaca data dari queue dan menampilkan hasilnya.
5. Setelah selesai, scheduler kembali menjalankan task lain yang siap dieksekusi.
Pergantian task berlangsung sangat cepat sehingga terlihat seperti berjalan bersamaan.

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
Program ini tidak berpotensi mengalami race condition karena komunikasi data dilakukan menggunakan Queue.
Queue pada FreeRTOS memiliki mekanisme sinkronisasi internal yang menjamin:
- Data tidak dibaca saat sedang ditulis.
- Data tidak ditulis saat queue penuh.
- Data tidak hilang akibat akses bersamaan.
Jika program menggunakan variabel global biasa tanpa Queue atau Semaphore, maka race condition dapat terjadi ketika dua task mengakses data yang sama secara bersamaan.
Dengan penggunaan Queue, akses data menjadi lebih aman dan terkontrol.

## 3. Modifikasilah program menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?

![Dokumentasi Percobaan 5B](5B_ModifikasiDHT.png)

```cpp
x.temp = dht.readTemperature();
x.h = dht.readHumidity();
```
Task `read_data` membaca data langsung dari sensor DHT kemudian mengirimkannya ke queue.
Task `display` menerima data tersebut dan menampilkan hasil pembacaan secara real-time pada Serial Monitor.
Hasil percobaan menunjukkan bahwa nilai suhu dan kelembapan berubah secara dinamis mengikuti kondisi lingkungan sekitar.
Penggunaan Queue memungkinkan data sensor dikirim dan diterima dengan aman antar task tanpa mengganggu proses multitasking yang sedang berjalan.
