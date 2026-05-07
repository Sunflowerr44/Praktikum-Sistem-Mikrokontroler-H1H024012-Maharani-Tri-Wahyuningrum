# Dokumentasi Praktikum 4 A

![Percobaan 4A](percobaan4a-1.jpeg)
<video controls src="percobaan4a-1.mp4" title="Percobaan 4A"></video>

## Komponen
1. Arduino Uno R3: Berperan sebagai unit pemroses utama untuk membaca input analog dan menghasilkan sinyal PWM untuk servo.
2. Potensiometer (Analog Input): Digunakan sebagai pembagi tegangan variabel yang nilai ADC-nya dibaca melalui pin A0.
3. Motor Servo SG90 (Output): Bertindak sebagai aktuator yang bergerak sesuai dengan hasil konversi nilai potensiometer.
4. Breadboard & Jumper Wires: Jalur distribusi daya (5V dan GND) serta jalur sinyal data.

## Penjelasan Dokumentasi
1. Input: Kabel dari pin tengah potensiometer terhubung ke pin A0 Arduino.
2. Output: Kabel sinyal servo (biasanya berwarna oranye/kuning) terhubung ke pin 9 (Digital PWM).
3. Power: Seluruh komponen mendapatkan suplai daya 5V yang stabil dari rail breadboard yang terhubung ke pin 5V dan GND Arduino.