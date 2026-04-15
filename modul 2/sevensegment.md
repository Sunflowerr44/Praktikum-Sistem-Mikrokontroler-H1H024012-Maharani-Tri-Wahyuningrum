# Percobaan 2A - Modifikasi Program Countdown 7-Segment

## Program Seven Segment Display

## Deskripsi
Program ini merupakan modifikasi dari percobaan sebelumnya yang digunakan untuk menampilkan angka pada seven segment display menggunakan mikrokontroler Arduino.

## 💻 Potongan Program yang Dimodifikasi
```cpp
void loop()
{
  // Inisialisasi loop untuk hitung mundur dari indeks 15 hingga 0
  for(int i = 15; i >= 0; i--) 
  {
    displayDigit(i); // Memanggil pola segmen berdasarkan indeks i
    delay(1000);     // Jeda 1 detik agar tampilan dapat terbaca
  }
}
```

## Penjelasan program
Modifikasinya untuk mengubah urutan tampilan Seven-Segment Display dari 0-F menjadi kebalikannya, yaitu F-0.