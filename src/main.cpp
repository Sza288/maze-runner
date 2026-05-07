// Nama File : main.cpp
// Deskripsi : Titik masuk aplikasi dan loop utama rendering game.
// Tanggal Dibuat : 24 Maret 2026

#include <GL/glut.h>
#include "../include/Config.h"
#include "../include/Camera.h"
#include "../include/Environment.h"
#include "../include/Entity.h"

// Inisialisasi Objek Global
Camera playerCam = {0.0f, 1.7f, 5.0f, 0.0f, 0.0f};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GTI A1 Maze Runner 2026"); 
    glLoadIdentity();

    playerCam.apply();
    setupLighting(); // Render Lighting 
    
    drawMaze();      // Render Lingkungan
    updateItems();   // Render Koin & Kunci
    
    // TODO: Render HUD di sini menggunakan Proyeksi Ortografis
    
    glutSwapBuffers();
}

void timer(int v) {
    // TODO: Update semua logika game (Bobbing, Ghost AI, Collision) setiap frame
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // TODO: Setup window dan panggil fungsi init dari modul lain
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}