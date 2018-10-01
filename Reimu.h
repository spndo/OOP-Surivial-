#ifndef Reimu_h
#define Reimu_h

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

#include "bullet.h"
#include <vector>

class Reimu {
public:
    float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    GLuint texture_if;
    int rows;
    int cols;
    
    int curr_row;
    int curr_col;
    
    bool complete;
    
    float firerate;

    Reimu (const char*, float, float, float, float);
    // Reimu (const char*, int, int, float, float,float, float);
    
    void draw();
    
    bool contains(float, float);
    
    void moveUp(float rate=0.01);
    void moveDown(float rate=0.01);
    void moveLeft(float rate=0.01);
    void moveRight(float rate=0.01);
    
    
    std::vector<bullet*> playerBullets;
    void shoot();
    void jump();
    void advance();
    
    bool rising;
    bool movingLeft;
    
    bool shooting;
   
    float xinc;
    float yinc;
    
    void bulletdraw();
    void reset();
    
    float getbulletx();
    float getbullety();
    
};

#endif
