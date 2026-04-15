# Percobaan 2B - Modifikasi Program Counter dengan Push Button

## Program Counter Increment & Decrement menggunakan Push Button

## Deskripsi
Program ini merupakan modifikasi dari percobaan sebelumnya yang memungkinkan pengguna untuk menambah dan mengurangi nilai counter secara manual menggunakan dua push-button. Nilai ditampilkan pada seven segment display dengan rentang 0 sampai 15 (heksadesimal 0–F).

## Potongan Program yang Dimodifikasi

```cpp
void loop()
{
  bool upState = digitalRead(btnUp);      // Baca tombol tambah
  bool downState = digitalRead(btnDown);  // Baca tombol kurang

  // Logika Increment (Deteksi Tepi Jatuh)
  if (lastUpState == HIGH && upState == LOW) 
  {
    counter++;                            // Tambah nilai
    if(counter > 15) counter = 0;         // Batas atas (reset ke 0)
    displayDigit(counter);                // Perbarui tampilan
    delay(200);                           // Debouncing sederhana
  }
  
  // Logika Decrement (Deteksi Tepi Jatuh)
  if (lastDownState == HIGH && downState == LOW) 
  {
    counter--;                            // Kurangi nilai
    if(counter < 0) counter = 15;         // Batas bawah (lompat ke F)
    displayDigit(counter);                // Perbarui tampilan
    delay(200);                           // Debouncing sederhana
  }
  
  lastUpState = upState;                  
  lastDownState = downState;
}
```