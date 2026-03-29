// Nama File : Entity.cpp
// Deskripsi : Implementasi logika entitas seperti item, hantu, dan status game.
// Tanggal Dibuat : 24 Maret 2026

#include "Entity.h"
#include "Config.h"
#include <math.h>

// TODO: Implementasikan deteksi tabrakan AABB (Axis-Aligned Bounding Box) 
bool checkCollision(float nextX, float nextZ) {
    // Cek apakah koordinat pemain menabrak dinding di map
    return false; 
}

// TODO: Implementasikan AI Hantu yang bergerak menuju (px, pz) 
void updateGhost(float px, float pz) {
    if (!isGhostTriggered) return;
    
    // Ghost gerak perlahan mengejar pemain (Translasi)
}

// TODO: Implementasikan animasi koin berputar (Rotasi) dan interaksi ambil koin 
void updateItems() {
    // glRotatef(angle, 0, 1, 0);
    // Jika jarak koin ke pemain < threshold, score++ dan isActive = false
}