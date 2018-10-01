
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
class Emeny {
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
    
    
    Emeny (const char*, float, float, float, float,float);
    // TexRect (const char*, int, int, float, float,float, float);
    
    void draw();
    
    bool contains(float, float);
    
    void moveUp(float rate=0.01);
    void moveDown(float rate=0.01);
    void moveLeft(float rate=0.01);
    void moveRight(float rate=0.01);
    
    void jump();
    
    bool rising;
    bool movingDown;
    
    float xinc;
    float yinc;
    //for bullet
    std::vector<bullet*> playerBullets;
    void drop();
    void shoot();
    void bulletdraw();
    void speed();
    bool outofB();
    void cleanB(int i);
    bool bulletcontains(float,float);
};

