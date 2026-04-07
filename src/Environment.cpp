// Nama File : Environment.cpp
// Deskripsi : Implementasi rendering lingkungan, tekstur, dan pencahayaan.
// Tanggal Dibuat : 24 Maret 2026

#include "Environment.h"
#include "Config.h"
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
    glEnable(GL_NORMALIZE);

    GLfloat ambientGlobal[] = {0.20f, 0.20f, 0.20f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientGlobal);
    
    // Senter (Spotlight): Posisinya mengikuti kamera
    GLfloat spotPos[] = { px, py, pz, 1.0f };
    GLfloat spotDir[] = { dx, 0.0f, dz };
    GLfloat spotDiffuse[] = { 0.95f, 0.95f, 0.90f, 1.0f };
    GLfloat spotSpecular[] = { 0.90f, 0.90f, 0.90f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, spotDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spotSpecular);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0f); // Sudut senter sempit agar horor
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 18.0f);
    
    glEnable(GL_LIGHT0);
}

// TODO: Gambar labirin menggunakan primitif (GL_QUADS) dan pasang glTexCoord2f 
void drawMaze() {
    const int mazeRows = 10;
    const int mazeCols = 10;
    const float tileSize = 1.0f;
    const float wallHeight = 1.2f;
    const float xOffset = mazeCols * 0.5f;
    const float zOffset = mazeRows * 0.5f;

    glPushMatrix();

    // Lantai sederhana.
    glDisable(GL_LIGHTING);
    glColor3f(0.15f, 0.17f, 0.20f);
    glBegin(GL_QUADS);
    glVertex3f(-xOffset, 0.0f, -zOffset);
    glVertex3f( xOffset, 0.0f, -zOffset);
    glVertex3f( xOffset, 0.0f,  zOffset);
    glVertex3f(-xOffset, 0.0f,  zOffset);
    glEnd();
    glEnable(GL_LIGHTING);

    for (int r = 0; r < mazeRows; ++r) {
        for (int c = 0; c < mazeCols; ++c) {
            if (maze[r][c] != 1) continue;

            float x = (c + 0.5f) * tileSize - xOffset;
            float z = (r + 0.5f) * tileSize - zOffset;

            glPushMatrix();
            glTranslatef(x, wallHeight * 0.5f, z);
            glScalef(tileSize, wallHeight, tileSize);
            glColor3f(0.40f, 0.42f, 0.46f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }

    glPopMatrix();
}