
#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>

#include "TexRect.h"

class bullet {

    // float xVel; // Velocity of bullet in X-Direction

    float yVel; // Velocity of bullet in Y-Direction
    float speed; // set speed of bullet in direction it's going
//    float xPos; // position of bullet in the X-Direction
//    float yPos; // position of bullet in the Y-Direction
    bool fFire; // determine if bullet is from MC or Enemy
    bool contact; // Check if the bullet has come in contact with the enemy/MC (based on the value of friendlyFire)
    bool rising;

    float x;
    float y;
    float w;
    float h;

    bool fire;

    GLuint texture_id;






    // Speed will represent distance it will travel in one second (1000 milliseconds)
    // friendlyFire will determine if bullet will interact with MC or Enemy
public:
    bullet (const char*, float, float, float, float);
    void setFire();
    void stopFire();

    void bulletMov (float, float, float, float, bool);
    void draw();
    void advance();
    bool OOB();
//bullet for emeny
    void drop();
    
    void velocity();
    
    bool bullety();
    
    void cleanbullet();
    
    bool bulletcontain(float,float);
    
    float getx();
    float gety();


};

#endif

