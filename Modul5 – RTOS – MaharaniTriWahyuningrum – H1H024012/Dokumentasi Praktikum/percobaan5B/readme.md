# Percobaan 5B - Komunikasi Task Menggunakan Queue pada FreeRTOS

## Deskripsi Percobaan

Percobaan ini bertujuan untuk memahami mekanisme komunikasi antar task pada sistem embedded menggunakan FreeRTOS. Komunikasi dilakukan menggunakan Queue, yaitu media pertukaran data yang aman antar task.

Pada percobaan ini terdapat dua task utama:

- Task `read_data` bertugas menghasilkan data sensor.
- Task `display` bertugas menerima data dari queue dan menampilkannya pada Serial Monitor.

Selain itu dilakukan modifikasi menggunakan potensiometer dan dua LED sebagai indikator perubahan nilai input secara real-time.


## Komponen yang Digunakan
1 Arduino Uno
2 Breadboard
3 LED Merah
4 LED Hijau
5 Resistor 220Ω
6 Potensiometer
7 Kabel Jumper
8 Kabel USB


## Dokumentasi Rangkaian

![Dokumentasi 1](5B%20(1).jpeg)
![Dokumentasi 2](5B%20(2).jpeg)
<video controls src="5B.mp4" title="Percobaan 5B"></video>

## Hasil Pengamatan
Berdasarkan hasil percobaan:
- Queue berhasil digunakan sebagai media komunikasi antar task.
- Data yang dibaca task pengirim dapat diterima dengan baik oleh task penerima.
- Perubahan posisi potensiometer menghasilkan perubahan kondisi LED.
- LED merah dan LED hijau berfungsi sebagai indikator nilai input yang diterima melalui queue.
- Sistem berjalan secara real-time tanpa mengganggu task lainnya.


## Analisis
Pada FreeRTOS, setiap task berjalan secara independen. Agar data dapat dipertukarkan dengan aman, digunakan mekanisme Queue.
Task pertama membaca nilai dari potensiometer kemudian mengirimkan data tersebut ke queue menggunakan fungsi:
```cpp
xQueueSend()
```
Task kedua menerima data dari queue menggunakan:
```cpp
xQueueReceive()
```
Dengan metode ini tidak terjadi konflik akses data karena FreeRTOS mengatur proses pengiriman dan penerimaan data secara terstruktur.
Ketika nilai potensiometer berubah, data yang dikirim ke queue juga berubah. Task penerima kemudian memproses data tersebut dan mengaktifkan LED yang sesuai dengan kondisi yang telah ditentukan pada program.
Mekanisme queue membuat komunikasi antar task menjadi lebih aman dibandingkan penggunaan variabel global secara langsung.


## Keterangan Video
Video dokumentasi menunjukkan:
- Arduino Uno menjalankan FreeRTOS dengan dua task yang saling berkomunikasi.
- Potensiometer digunakan sebagai input.
- Nilai input dikirim melalui queue.
- LED merah dan LED hijau berubah sesuai data yang diterima.
- Komunikasi task berjalan sesuai dengan spesifikasi percobaan.


## Kesimpulan
Percobaan ini berhasil menunjukkan implementasi komunikasi antar task menggunakan Queue pada FreeRTOS. Data dapat dikirim dan diterima secara aman antar task tanpa menyebabkan konflik akses data. Penggunaan queue sangat penting dalam sistem multitasking karena memungkinkan pertukaran informasi secara terstruktur dan sinkron antar proses yang berjalan secara concurrent.