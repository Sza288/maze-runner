// Nama File : main.cpp
// Deskripsi : Titik masuk aplikasi dan loop utama rendering game.
// Tanggal Dibuat : 24 Maret 2026

#include <GL/glut.h>
#include "Config.h"
#include "Camera.h"
#include "Environment.h"
#include "Entity.h"

// Inisialisasi Objek Global
Camera playerCam = {0.0f, 1.7f, 5.0f, 0.0f, 0.0f};

static void setupScene() {
    glClearColor(0.03f, 0.03f, 0.06f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void reshape(int w, int h) {
    if (h <= 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    playerCam.apply();
    setupLighting(); // Render Lighting 
    
    drawMaze();      // Render Lingkungan
    updateItems();   // Render Koin & Kunci
    drawHUD();
    
    glutSwapBuffers();
}

void timer(int v) {
    // TODO: Update semua logika game (Bobbing, Ghost AI, Collision) setiap frame
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(80, 50);
    glutCreateWindow("GTI A1 Maze Runner 2026");

    setupScene();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}