/*
    main.cpp  -  Abyssal Maze Showcase  (Yu Ming Jie)

    MODE:
      [1] Wall    - close-up dinding + spotlight
      [2] Floor   - close-up lantai (// jika tidak perlu)
      [3] Torch   - obor/lilin close-up, kamera berputar
      [4] Maze Perspektif  - FPS, spotlight + obor + shadow
      [5] Maze Ortografik  - top-down, maze shape terlihat jelas

    Kontrol mode 4:
      W/S  maju/mundur
      A/D  putar kiri/kanan
      ESC  keluar

    Compile Windows:
      g++ main.cpp Environment.cpp Config.cpp -lfreeglut -lglu32 -lopengl32 -o maze.exe
    Compile Linux:
      g++ main.cpp Environment.cpp Config.cpp -lGL -lGLU -lglut -lm -o maze
*/

#include <GL/glut.h>
#include <cmath>
#include "Config.h"
#include "Camera.h"
#include "Environment.h"

/* Semua fungsi, extern variabel sudah ada di Environment.h */

/* ------------------------------------------------------------------ */
/*  State                                                              */
/* ------------------------------------------------------------------ */
static int   g_mode     = 4;
static float g_lastTime = 0.0f;
static bool  g_keyW = false;
static bool  g_keyA = false;
static bool  g_keyS = false;
static bool  g_keyD = false;
static bool  g_mouseReady = false;
static int   g_prevMouseX = 0;

static bool canMoveTo(float nx, float nz)
{
    const float tile = 2.0f;
    const float radius = 0.25f;
    const float p[4][2] = {
        {nx - radius, nz - radius},
        {nx + radius, nz - radius},
        {nx - radius, nz + radius},
        {nx + radius, nz + radius}
    };

    for (int i = 0; i < 4; ++i) {
        int col = (int)floorf(p[i][0] / tile);
        int row = (int)floorf(p[i][1] / tile);
        if (row < 0 || row >= MAZE_HEIGHT || col < 0 || col >= MAZE_WIDTH) {
            return false;
        }
        if (mazeMatrix[row][col] == 1) {
            return false;
        }
    }
    return true;
}

/* ------------------------------------------------------------------ */
/*  HUD                                                                */
/* ------------------------------------------------------------------ */
static void drawHUD(float px, float py, const char* str)
{
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    if (h==0) h=1;

    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D);
    glDisable(GL_FOG);      glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0,w,0,h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();

    glColor3f(0.95f,0.82f,0.12f);
    glRasterPos2f(px,py);
    while(*str){ glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(int)(*str)); ++str; }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING);
}

/* ------------------------------------------------------------------ */
/*  Proyeksi                                                           */
/* ------------------------------------------------------------------ */
static void setPerspective()
{
    int w=glutGet(GLUT_WINDOW_WIDTH), h=glutGet(GLUT_WINDOW_HEIGHT);
    if(h==0) h=1;
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(65.0f,(float)w/(float)h,0.1f,120.0f);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

static void setOrtho(float scale)
{
    int w=glutGet(GLUT_WINDOW_WIDTH), h=glutGet(GLUT_WINDOW_HEIGHT);
    if(h==0) h=1;
    float asp=(float)w/(float)h;
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(-scale*asp, scale*asp, -scale, scale, -80.0f, 80.0f);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

/* ==================================================================
   MODE 1  -  Wall close-up
   ================================================================== */
static void showWall()
{
    setPerspective();
    camX=1.0f; camY=1.3f; camZ=3.2f;
    lookX=1.0f; lookY=1.3f; lookZ=0.0f;
    gluLookAt(camX,camY,camZ, lookX,lookY,lookZ, 0,1,0);

    setupFlashlight();

    GLfloat amb[]={0.35f,0.22f,0.18f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);

    /* Gambar dinding manual 4 sisi untuk showcase */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_texWall);
    glColor3f(1,1,1);

    float x0=0,x1=2,y0=0,y1=2.5f,z0=0,z1=2;
    glBegin(GL_QUADS);
    /* Front */
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);glVertex3f(x0,y0,z1); glTexCoord2f(1,0);glVertex3f(x1,y0,z1);
    glTexCoord2f(1,1);glVertex3f(x1,y1,z1); glTexCoord2f(0,1);glVertex3f(x0,y1,z1);
    /* Back */
    glNormal3f(0,0,-1);
    glTexCoord2f(0,0);glVertex3f(x1,y0,z0); glTexCoord2f(1,0);glVertex3f(x0,y0,z0);
    glTexCoord2f(1,1);glVertex3f(x0,y1,z0); glTexCoord2f(0,1);glVertex3f(x1,y1,z0);
    /* Left */
    glNormal3f(-1,0,0);
    glTexCoord2f(0,0);glVertex3f(x0,y0,z0); glTexCoord2f(1,0);glVertex3f(x0,y0,z1);
    glTexCoord2f(1,1);glVertex3f(x0,y1,z1); glTexCoord2f(0,1);glVertex3f(x0,y1,z0);
    /* Right */
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);glVertex3f(x1,y0,z1); glTexCoord2f(1,0);glVertex3f(x1,y0,z0);
    glTexCoord2f(1,1);glVertex3f(x1,y1,z0); glTexCoord2f(0,1);glVertex3f(x1,y1,z1);
    /* Top */
    glNormal3f(0,1,0);
    glTexCoord2f(0,0);glVertex3f(x0,y1,z0); glTexCoord2f(1,0);glVertex3f(x1,y1,z0);
    glTexCoord2f(1,1);glVertex3f(x1,y1,z1); glTexCoord2f(0,1);glVertex3f(x0,y1,z1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    drawTexturedFloor(-0.5f,-0.5f,3.0f);

    /* Obor showcase - tanpa extern, render langsung */
    GLfloat ambDark[]={0.06f,0.04f,0.05f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambDark);

    int wh=glutGet(GLUT_WINDOW_HEIGHT);
    drawHUD(12,(float)(wh-28),"MODE 1: Textured Wall   [1-5] ganti mode");
    drawHUD(12,14,"Bata Han Dynasty + Noda Darah + Goresan Jimat (GL_LIGHT0 spotlight)");
}

/* ==================================================================
   MODE 2  -  Floor close-up
   Comment out case 2 di display() jika tidak diperlukan
   ================================================================== */
static void showFloor()
{
    setPerspective();
    camX=3.0f; camY=4.5f; camZ=6.5f;
    lookX=3.0f; lookY=0.0f; lookZ=2.5f;
    gluLookAt(camX,camY,camZ, lookX,lookY,lookZ, 0,1,0);
    setupFlashlight();

    GLfloat amb[]={0.28f,0.18f,0.16f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);

    int r,c;
    for(r=0;r<3;r++) for(c=0;c<3;c++)
        drawTexturedFloor((float)c*2,(float)r*2,2.0f);

    /* Tiga obor rendah menerangi lantai - pakai light langsung */
    glEnable(GL_LIGHT1);
    GLfloat p1[]={1.0f,0.5f,1.0f,1.0f};
    GLfloat d1[]={1.0f,0.4f,0.05f,1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,p1); glLightfv(GL_LIGHT1,GL_DIFFUSE,d1);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,180);
    glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.15f);

    glEnable(GL_LIGHT2);
    GLfloat p2[]={3.0f,0.5f,3.0f,1.0f};
    glLightfv(GL_LIGHT2,GL_POSITION,p2); glLightfv(GL_LIGHT2,GL_DIFFUSE,d1);
    glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,180);
    glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,0.15f);

    GLfloat ambDark[]={0.06f,0.04f,0.05f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambDark);

    int wh=glutGet(GLUT_WINDOW_HEIGHT);
    drawHUD(12,(float)(wh-28),"MODE 2: Textured Floor   [1-5] ganti mode");
    drawHUD(12,14,"Ubin Batu Hitam + Bercak Darah + Kertas Jimat Kuning");
}

/* ==================================================================
   MODE 3  -  Torch/Obor close-up
   Kamera berputar, hanya cahaya obor (spotlight off)
   ================================================================== */
static void showTorch()
{
    setPerspective();
    float angle=g_time*0.5f;
    float cx=1.5f+cosf(angle)*2.8f;
    float cz=1.5f+sinf(angle)*2.8f;
    camX=cx; camY=1.9f; camZ=cz;
    lookX=1.5f; lookY=1.4f; lookZ=1.5f;
    gluLookAt(camX,camY,camZ, lookX,lookY,lookZ, 0,1,0);

    /* Matikan spotlight, hanya cahaya obor */
    glDisable(GL_LIGHT0);
    GLfloat ambDark[]={0.02f,0.01f,0.01f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambDark);

    /* Lantai + dinding konteks */
    int r2,c2;
    for(r2=0;r2<2;r2++) for(c2=0;c2<2;c2++)
        drawTexturedFloor((float)c2*2,(float)r2*2,2.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_texWall);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);glVertex3f(0,0,4); glTexCoord2f(2,0);glVertex3f(4,0,4);
    glTexCoord2f(2,1);glVertex3f(4,3,4); glTexCoord2f(0,1);glVertex3f(0,3,4);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);glVertex3f(0,0,4); glTexCoord2f(1,0);glVertex3f(0,0,0);
    glTexCoord2f(1,1);glVertex3f(0,3,0); glTexCoord2f(0,1);glVertex3f(0,3,4);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /* Satu obor di tengah */
    drawTorch(1.5f,0.0f,1.5f,0);

    /* Shadow sederhana di bawah obor */
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    float f=0.5f+0.5f*sinf(g_time*3.8f);
    glColor4f(0,0,0,0.4f*f);
    glBegin(GL_QUADS);
    glVertex3f(0.9f,0.01f,0.9f); glVertex3f(2.1f,0.01f,0.9f);
    glVertex3f(2.1f,0.01f,2.1f); glVertex3f(0.9f,0.01f,2.1f);
    glEnd();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

    GLfloat ambReset[]={0.06f,0.04f,0.05f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambReset);

    int wh=glutGet(GLUT_WINDOW_HEIGHT);
    drawHUD(12,(float)(wh-28),"MODE 3: Torch (Obor/Lilin)   [1-5] ganti mode");
    drawHUD(12,14,"GL_LIGHT1 point light flicker + shadow quad di lantai");
}

/* ==================================================================
   MODE 4  -  Maze Perspektif FPS
   Spotlight aktif, fog, obor berkedip, shadow
   ================================================================== */
static void showMazePerspective()
{
    setPerspective();

    camX = playerCam.x;
    camY = playerCam.y;
    camZ = playerCam.z;
    lookX = playerCam.x + cosf(playerCam.angle);
    lookY = playerCam.y;
    lookZ = playerCam.z + sinf(playerCam.angle);
    playerCam.apply();

    /* Spotlight SETELAH gluLookAt */
    setupFlashlight();
    setupFog();
    renderEnvironment();

    int wh=glutGet(GLUT_WINDOW_HEIGHT);
    drawHUD(12,(float)(wh-28),
        "POV PLAYABLE: W/A/S/D bergerak, mouse lihat sekitar, ESC keluar");
    drawHUD(12,14,
        "GL_LIGHT0 spotlight + GL_LIGHT1-6 obor flicker + shadow lantai");
}

/* ==================================================================
   MODE 5  -  Maze Ortografik Top-Down
   Kamera vertikal dari atas, seluruh struktur maze terlihat 1:1
   Dinding kubus 5-sisi ? atap dinding terlihat dari atas
   ================================================================== */
static void showMazeOrtho()
{
    float S  = 2.0f;
    float MW = (float)MAZE_WIDTH *S;
    float MH = (float)MAZE_HEIGHT*S;
    float scale = (MW>MH?MW:MH)*0.56f;

    setOrtho(scale);

    float cx=MW*0.5f, cz=MH*0.5f;
    camX=cx; camY=40.0f; camZ=cz;
    lookX=cx; lookY=0.0f; lookZ=cz;
    /* up = (0,0,-1): "atas" layar = arah negatif Z dunia */
    gluLookAt(camX,camY,camZ, lookX,lookY,lookZ, 0,0,-1);

    glDisable(GL_FOG);

    /* Ambient terang: semua atap dinding terlihat */
    GLfloat ambBright[]={0.70f,0.50f,0.42f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambBright);

    /* Spotlight dari atas sebagai directional fill */
    setupFlashlight();

    renderEnvironment();

    GLfloat ambDark[]={0.06f,0.04f,0.05f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambDark);

    int wh=glutGet(GLUT_WINDOW_HEIGHT);
    drawHUD(12,(float)(wh-28),
        "MODE 5: Maze Ortografik Top-Down   [1-5] ganti mode");
    drawHUD(12,14,
        "Proyeksi Ortografik: dinding = gelap, jalan = terang, bentuk maze 1:1");
}

/* ================================================================== */
static void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    showMazePerspective();
    glutSwapBuffers();
}

static void reshape(int w,int h)
{ if(h==0)h=1; glViewport(0,0,w,h); }

static void idle()
{
    float now=(float)glutGet(GLUT_ELAPSED_TIME)/1000.0f;
    float dt = now-g_lastTime;
    if (dt < 0.0f) dt = 0.0f;
    if (dt > 0.1f) dt = 0.1f;
    g_time   += dt;
    g_lastTime = now;

    float speed = PLAYER_SPEED * 6.0f * dt;
    float fx = cosf(playerCam.angle);
    float fz = sinf(playerCam.angle);
    float rx = -fz;
    float rz = fx;

    float mvX = 0.0f;
    float mvZ = 0.0f;
    if (g_keyW) { mvX += fx; mvZ += fz; }
    if (g_keyS) { mvX -= fx; mvZ -= fz; }
    if (g_keyA) { mvX -= rx; mvZ -= rz; }
    if (g_keyD) { mvX += rx; mvZ += rz; }

    if (mvX != 0.0f || mvZ != 0.0f) {
        float len = sqrtf(mvX*mvX + mvZ*mvZ);
        mvX /= len; mvZ /= len;

        float nx = playerCam.x + mvX * speed;
        float nz = playerCam.z + mvZ * speed;

        if (canMoveTo(nx, playerCam.z)) playerCam.x = nx;
        if (canMoveTo(playerCam.x, nz)) playerCam.z = nz;
    }

    glutPostRedisplay();
}

static void keyboard(unsigned char key,int mx,int my)
{
    (void)mx;(void)my;
    switch(key){
        case 'w':case 'W':g_keyW=true;break;
        case 'a':case 'A':g_keyA=true;break;
        case 's':case 'S':g_keyS=true;break;
        case 'd':case 'D':g_keyD=true;break;
        case 27:exit(0);break;
        default:break;
    }
}

static void keyboardUp(unsigned char key,int mx,int my)
{
    (void)mx;(void)my;
    switch(key){
        case 'w':case 'W':g_keyW=false;break;
        case 'a':case 'A':g_keyA=false;break;
        case 's':case 'S':g_keyS=false;break;
        case 'd':case 'D':g_keyD=false;break;
        default:break;
    }
}

static void mouseMove(int x, int y)
{
    (void)y;
    if (!g_mouseReady) {
        g_prevMouseX = x;
        g_mouseReady = true;
        return;
    }

    int dx = x - g_prevMouseX;
    g_prevMouseX = x;
    playerCam.angle += (float)dx * 0.0045f;
}

int main(int argc,char** argv)
{
    playerCam.x = 3.0f;
    playerCam.y = 1.6f;
    playerCam.z = 3.0f;
    playerCam.angle = 3.9269907f;
    playerCam.bobbingTimer = 0.0f;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(1024,640);
    glutCreateWindow("Ghost Dimension POV");
    initEnvironment();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMove);
    glutMainLoop();
    return 0;
}
