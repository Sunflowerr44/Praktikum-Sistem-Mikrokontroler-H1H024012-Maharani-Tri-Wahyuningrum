# Percobaan 5A - Multitasking dengan FreeRTOS


Percobaan ini bertujuan untuk memahami konsep multitasking pada sistem embedded menggunakan FreeRTOS di Arduino Uno. Pada percobaan ini dijalankan beberapa task secara bersamaan menggunakan fungsi `xTaskCreate()`, yaitu:
- Task 1 mengendalikan LED Merah.
- Task 2 mengendalikan LED Hijau.
- Task 3 menampilkan nilai counter pada Serial Monitor.
Setiap task memiliki periode eksekusi yang berbeda sehingga scheduler FreeRTOS akan mengatur pembagian waktu eksekusi secara otomatis.


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
![Dokumentasi 1](5A%20(1).jpeg)
![Dokumentasi 2](5A%20(2).jpeg)


## Hasil Pengamatan
Berdasarkan hasil percobaan:
- Perpindahan kondisi LED terjadi secara otomatis tanpa menggunakan fungsi `loop()`.
- Scheduler FreeRTOS berhasil menjalankan beberapa task
- Sistem menunjukkan konsep multitasking dimana beberapa task dapat berjalan dalam satu mikrokontroler secara terjadwal.
- Arduino Uno berhasil menjalankan FreeRTOS.
- LED merah dan LED hijau berkedip sesuai task masing-masing.

## Analisis
Pada Arduino biasa, seluruh program dijalankan secara berurutan di dalam fungsi `loop()`. Namun pada FreeRTOS, setiap pekerjaan dipisahkan menjadi task yang independen.
Scheduler FreeRTOS akan memberikan waktu eksekusi (time slice) kepada setiap task berdasarkan prioritas dan waktu delay yang ditentukan menggunakan `vTaskDelay()`. Oleh karena itu LED merah, LED hijau, dan counter dapat berjalan secara bersamaan dari sudut pandang pengguna.
Meskipun terlihat berjalan bersamaan, sebenarnya prosesor mengeksekusi task secara bergantian dengan sangat cepat sehingga tercipta efek multitasking.


## Kesimpulan
Percobaan ini berhasil menunjukkan implementasi multitasking menggunakan FreeRTOS pada Arduino Uno. Beberapa task dapat dijalankan melalui mekanisme scheduler sehingga LED dan proses pencetakan data pada Serial Monitor dapat bekerja secara bersamaan tanpa saling mengganggu.