// Nama File : Environment.cpp
// Deskripsi : Implementasi rendering lingkungan, tekstur, dan pencahayaan.
// Tanggal Dibuat : 24 Maret 2026

#include "Environment.h"
#include <GL/glut.h>

// TODO: Gunakan glTexImage2D atau library SOIL/stb_image untuk memuat gambar tekstur 
void loadTextures() {
    // 1. Generate texture ID
    // 2. Bind texture
    // 3. Set parameter (Repeat/Linear)
}

// TODO: Implementasikan Lighting (GL_LIGHT0 untuk Senter, GL_LIGHT1 dst untuk Obor) 
void setupLighting() {
    // Placeholder sampai data kamera dihubungkan ke modul ini.
    float px = 0.0f, py = 1.7f, pz = 5.0f;
    float dx = 0.0f, dz = -1.0f;
    glEnable(GL_LIGHTING);
    
    // Senter (Spotlight): Posisinya mengikuti kamera
    GLfloat spotPos[] = { px, py, pz, 1.0f };
    GLfloat spotDir[] = { dx, 0.0f, dz };
    glLightfv(GL_LIGHT0, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0f); // Sudut senter sempit agar horor
    
    glEnable(GL_LIGHT0);
}

// TODO: Gambar labirin menggunakan primitif (GL_QUADS) dan pasang glTexCoord2f 
void drawMaze() {
    // Loop melalui array maze di Config.h
    // Jika array[i][j] == 1, gambar cube/dinding
}