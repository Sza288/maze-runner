// Nama File : Camera.cpp
// Deskripsi : Implementasi fungsi kamera dan pengaturan tampilan pemain.
// Tanggal Dibuat : 24 Maret 2026

#include "Camera.h"
#include "Config.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

static void drawText2D(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* p = text; *p != '\0'; ++p) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
    }
}

void Camera::update() {
    static int lastTimeMs = -1;
    static float lastX = 0.0f;
    static float lastZ = 0.0f;

    const int nowMs = glutGet(GLUT_ELAPSED_TIME);
    if (lastTimeMs < 0) {
        lastTimeMs = nowMs;
        lastX = x;
        lastZ = z;
        return;
    }

    float deltaSec = (nowMs - lastTimeMs) / 1000.0f;
    if (deltaSec < 0.0f) deltaSec = 0.0f;
    if (deltaSec > 0.1f) deltaSec = 0.1f;

    const float dx = x - lastX;
    const float dz = z - lastZ;
    const float movement = sqrt(dx * dx + dz * dz);
    const bool isMoving = movement > 0.0001f;

    if (isMoving) {
        bobbingTimer += (6.0f + movement * 35.0f) * deltaSec;
    } else {
        bobbingTimer *= 0.92f;
        if (fabs(bobbingTimer) < 0.001f) {
            bobbingTimer = 0.0f;
        }
    }

    const float twoPi = 6.2831853f;
    while (angle > twoPi) angle -= twoPi;
    while (angle < 0.0f) angle += twoPi;

    lastX = x;
    lastZ = z;
    lastTimeMs = nowMs;
}

// Gunakan gluLookAt() untuk mengatur sudut pandang mata pemain.
void Camera::apply() {
    update();

    const float bobbingOffset = sin(bobbingTimer) * 0.05f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        x, y + bobbingOffset, z,
        x + cos(angle), y + bobbingOffset, z + sin(angle),
        0.0f, 1.0f, 0.0f
    );
}

// Switch ke proyeksi ortografis untuk menampilkan HUD.
void drawHUD() {
    char scoreText[64];
    char stateText[64];

    sprintf(scoreText, "Score: %d", score);
    sprintf(stateText, "Key: %s  Ghost: %s",
            hasKey ? "YES" : "NO",
            isGhostTriggered ? "ACTIVE" : "IDLE");

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText2D(16.0f, WINDOW_HEIGHT - 24.0f, scoreText);
    drawText2D(16.0f, WINDOW_HEIGHT - 44.0f, stateText);

    if (isGameOver || isGameWin) {
        const char* msg = isGameWin ? "YOU ESCAPED!" : "GAME OVER";
        glColor3f(1.0f, 0.2f, 0.2f);
        drawText2D((WINDOW_WIDTH * 0.5f) - 70.0f, WINDOW_HEIGHT * 0.5f, msg);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}