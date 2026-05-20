## Layout Labirin:

```c++
int maze[10][10] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 2, 0, 0, 2, 1},
{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
{1, 2, 1, 0, 0, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 2, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 0, 1, 1, 1, 3, 1},
{1, 2, 0, 1, 0, 0, 0, 1, 1, 1},
{1, 0, 0, 0, 0, 2, 0, 0, 4, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
```

Berikut adalah definisi nilai untuk matriks tersebut yang merepresentasikan layout labirin:

- **1**: Dinding (Objek statis dengan tekstur).
- **0**: Jalan/Lantai kosong (Tempat pemain berjalan).
- **2**: Koin (Objek interaksi untuk menambah skor).
- **3**: Kunci (Item wajib untuk membuka pintu keluar).
- **4**: Pintu Keluar/Finish (Kondisi menang/Win Condition).

---

## TODO LIST:

### **Camera.cpp**

1. Implementasi `gluLookAt` untuk _set up_ posisi mata pemain di tingkat ketinggian mata (_eye level_).
2. _Set up_ input keyboard (WASD) untuk pergerakan maju, mundur, dan menyamping (Translasi).
3. Implementasi kontrol _mouse_ untuk merotasi sudut pandang pemain secara _real-time_ (Rotasi).
4. Implementasi efek _head bobbing_ (animasi naik-turun kamera) saat pemain sedang bergerak.
5. Implementasi _switch_ proyeksi dari perspektif ke ortografis untuk merender HUD seperti teks skor dan sisa waktu.

### **Environment.cpp**

1. Implementasi fungsi `drawMaze` yang membaca matriks dari `Config.cpp` untuk menggambar dinding menggunakan primitif.
2. Implementasi _texture mapping_ pada seluruh permukaan dinding dan lantai agar terlihat realistis.
3. _Set up_ pencahayaan senter pemain menggunakan `GL_LIGHT0` dengan tipe _Spotlight_.
4. _Set up_ pencahayaan obor di beberapa titik dinding menggunakan _Point Light_ (`GL_LIGHT1` dst) dengan efek api berkedip.
5. Aktivasi `GL_DEPTH_TEST` dan implementasi bayangan sederhana (_shadows_) untuk menciptakan efek kedalaman.

### **Entity.cpp**

1. Implementasi model 3D koin dan kunci menggunakan objek primitif dasar.
2. Implementasi animasi rotasi terus-menerus pada koin dan kunci agar menarik perhatian pemain.
3. Implementasi sistem deteksi tabrakan (_collision detection_) agar pemain tidak menembus dinding labirin.
4. Implementasi interaksi pengambilan item (koin/kunci) yang akan memperbarui variabel skor di `Config.cpp`.
5. Implementasi pergerakan entitas hantu yang mengejar pemain dan memicu kondisi kalah (_Lose Condition_) jika tertangkap.
