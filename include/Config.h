// Nama File : Config.h
// Deskripsi : Konstanta konfigurasi aplikasi dan deklarasi status game global.
// Tanggal Dibuat : 24 Maret 2026

#ifndef CONFIG_H
#define CONFIG_H

// Screen Settings
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Game States
extern bool isGameOver;
extern bool isGameWin;
extern bool hasKey;
extern int score;
extern bool isGhostTriggered;

// TODO: Tambahkan konstanta untuk kecepatan gerak dan sensitivitas mouse
// TODO: Tambahkan threshold jarak untuk trigger munculnya hantu

// Map Data
extern int maze[10][10];

// Backward-compatible aliases used by rendering modules.
const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 10;
#define mazeMatrix maze

// Constants (Bisa langsung di header karena 'const')
const float PLAYER_SPEED = 0.1f;
const float GHOST_SPEED = 0.05f;

#endif