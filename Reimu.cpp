#include "Reimu.h"


Reimu::Reimu (const char* filename, float x = 0, float y = 0, float w = 0.5, float h = 0.5) {

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

    rising = false;
    movingLeft = true;
    
    shooting = true;

    xinc = 0.01;
    yinc = 0.01;
}



void Reimu::moveUp(float rate){
    y += rate;
    if (y > 0.99) {
        y = 0.99;
    }
}
void Reimu::moveDown(float rate){
    y -= rate;
    if (y - h < -0.99) {
        y = -0.99 + h;
    }
}
void Reimu::moveLeft(float rate){
    x -= rate;
    if (x < -0.99){
        x = -0.99;
    }
}
void Reimu::moveRight(float rate){
    x += rate;
    if (x + w > 0.99){
        x = 0.99 - w;
    }
}

void Reimu::shoot(){
    if (shooting) {
        playerBullets.push_back(new bullet("images/bullet.png", x+w/8, y, 0.10, 0.10));
    }
}
    
void Reimu::advance(){
    for(int i = 0; i < playerBullets.size(); i++){
//        playerBullets[i]->setSpeed(speed);

        if (playerBullets[i]->OOB() == false) {
            //delete function for bullet
            playerBullets.erase(playerBullets.begin()+i-1);
        }
        else {
            playerBullets[i]->advance();
        }

    }
}


void Reimu::draw(){
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
}


bool Reimu::contains(float mx, float my){
    return mx >= x && mx <= x+w && my <= y && my >= y - h;
}

void Reimu::bulletdraw(){
    for(int i = 0; i < playerBullets.size(); i++){
        playerBullets[i]->draw();
    }
}

float Reimu::getbulletx(){
    float position = 0;
    for (int i = 0; i < playerBullets.size();i++){
        position = playerBullets[i]->getx();
    }
    return position;
}

float Reimu::getbullety(){
    float position = 0;
    for (int i = 0; i < playerBullets.size();i++){
        position = playerBullets[i]->gety();
    }
    return position;
}
