
#include "bullet.h"

//void bullet::bulletMov (float yVel, float speed, float xPos, float yPos, bool fFire) {
//
//    this->yVel = yVel;
//    this->speed = speed;
//    this->xPos = xPos;
//    this->yPos = yPos;
//    this->fFire = fFire;
//
//}

bullet::bullet (const char* filename, float x = 0, float y = 0, float w = 0.5, float h = 0.5) {

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    texture_id = SOIL_load_OGL_texture (
                                        filename,
                                        SOIL_LOAD_AUTO,
                                        SOIL_CREATE_NEW_ID,
                                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                                        );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    //speed = 0.01;
    speed = 0.03;

    fire = false;

    //    rising = false;
    //    movingLeft = true;

    //    xinc = 0.01;
    //    yinc = 0.01;
}

void bullet::advance(){
//    speed += .004;

    y += speed;
}

bool bullet::OOB() {//out of bounds
  if (x <= 1.0 && x >= -1.0) {
    if (y <= 1.0 && y >= -1.0) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

//enemy
void bullet::drop(){
    y -= speed;
}


void bullet::draw(){
    //if (fire) {
        glBindTexture( GL_TEXTURE_2D, texture_id );
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_QUADS);
        glColor4f(1, 1, 1, 1);
        glTexCoord2f(0, 0);
        glVertex2f(x, y - h);

        glTexCoord2f(0, 1);
        glVertex2f(x, y);

        glTexCoord2f(1, 1);
        glVertex2f(x+w, y);

        glTexCoord2f(1, 0);
        glVertex2f(x+w, y - h);

        glEnd();

        glDisable(GL_TEXTURE_2D);

//}
}

void bullet::setFire() {
    fire = true;
}

void bullet::stopFire() {
    fire = false;
}

bool bullet::bullety(){
    if (y < -1.2){
        return true;
    }
    return false;
}

bool bullet::bulletcontain(float mx,float my){
    return mx >= x && mx <= x+w && my <= y && my >= y - h;
}


float bullet::getx(){
    return x;
}

float bullet::gety(){
    return y;
}

