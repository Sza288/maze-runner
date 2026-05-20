# 🎮 The Silent Labyrinth - GTI 2026

**The Silent Labyrinth** adalah sebuah proyek game _survival horror_ berbasis _First-Person_ yang dikembangkan menggunakan **OpenGL** dan library **GLUT**. Proyek ini dikerjakan secara berkelompok untuk memenuhi tugas besar praktikum Grafika dan Teknik Interaktif (GTI) Informatika 2025/2026.

## 📝 Deskripsi Umum

Pemain akan terjebak di dalam sebuah labirin kuno yang gelap. Tujuan utama pemain adalah mengumpulkan koin untuk mendapatkan skor tertinggi, menemukan kunci yang tersembunyi, dan mencapai pintu keluar. Namun, pemain tidak sendirian; sebuah entitas akan mulai mengejar setelah pemain bergerak menjauh dari titik awal. Keberhasilan pemain ditentukan oleh kemampuan navigasi di bawah penerangan terbatas dan kecepatan menyelesaikan misi sebelum tertangkap atau waktu habis.

---

## ⚙️ Mekanisme Game

Game ini dirancang dengan alur permainan (_gameplay loop_) sebagai berikut:

### 1. Kondisi Awal (Start Condition)

- Pemain memulai permainan di titik _spawn_ yang aman di dalam labirin.
- Pemain dilengkapi dengan senter (tanpa baterai/penerangan permanen) untuk membantu penglihatan di area gelap.

### 2. Mekanisme Eksplorasi & Interaksi

- **Pergerakan:** Pemain bergerak menggunakan sudut pandang mata (_eye level_) dengan kontrol keyboard.
- **Koin & Skor:** Koin tersebar di lorong labirin; mengambil koin akan menambah skor akhir pemain.
- **Kunci & Pintu:** Pemain wajib menemukan item "Kunci" untuk dapat berinteraksi dengan pintu keluar yang terkunci.
- **Penerangan:** Selain senter pemain, terdapat obor statis di beberapa titik dinding untuk memberikan pencahayaan tambahan.

### 3. Entitas Musuh (Ghost AI)

- **Trigger:** Entitas hantu akan muncul secara otomatis setelah pemain menempuh jarak tertentu dari titik awal.
- **Perilaku:** Hantu akan mengejar posisi pemain secara terus-menerus. Entitas direncanakan menggunakan model 3D kompleks (atau _billboard_ sebagai alternatif efisiensi waktu).

### 4. Kondisi Akhir (Win/Lose Condition)

- **Menang (Win):** Pemain berhasil menemukan kunci dan mencapai pintu keluar.
- **Kalah (Lose):** Pemain berhasil ditangkap oleh hantu atau durasi waktu permainan habis.

---

## 🛠️ Implementasi Teknis (Kebutuhan Tugas)

Proyek ini mengimplementasikan unsur grafika komputer yang disyaratkan dalam spesifikasi tugas besar:

- **Primitif Drawing:** Digunakan untuk membangun aset dasar seperti dinding, lantai, dan objek item.
- **Translasi & Rotasi:** Diaplikasikan pada pergerakan pemain (kamera), rotasi koin yang berputar, serta pergerakan hantu.
- **Proyeksi & Animasi:** Menggunakan proyeksi perspektif untuk dunia 3D dan ortografis untuk HUD/UI, serta animasi _flickering_ cahaya obor.
- **Kamera, Depth, & Lighting:** Implementasi kamera _First-Person_ menggunakan `gluLookAt`, pengaktifan `GL_DEPTH_TEST`, serta penggunaan _Spotlight_ (senter) dan _Point Light_ (obor).
- **Tekstur & Bayangan:** Penerapan _texture mapping_ pada dinding (batu/lumut) dan lantai, serta implementasi bayangan sederhana untuk kedalaman visual.
- **Interaksi Antar Objek:** Sistem deteksi tabrakan (_collision detection_) antara pemain dengan dinding, serta trigger pengambilan koin dan kunci.

---

## 📂 Struktur Proyek

Proyek diatur dalam struktur folder berikut untuk memudahkan pengerjaan paralel:

- `/assets`: Menyimpan file gambar tekstur (.bmp/.png).
- `/include`: File header (.h) untuk modul Kamera, Environment, dan Entity.
- `/src`: Source code utama (.cpp) termasuk `main.cpp` sebagai _entry point_.

---

## 📺 Format Luaran & Pengumpulan

Sesuai dengan ketentuan praktikum, hasil akhir proyek mencakup:

1. **Source Code:** Diunggah ke repositori GitHub tim.
2. **Video Presentasi:** Demonstrasi game di YouTube dengan format judul: `GTI [Nama Lab] [Judul Project] 2026`.
3. **Laporan Resmi:** Dokumen penyelesaian menggunakan format baku asisten praktikum yang melampirkan link GitHub dan YouTube.
