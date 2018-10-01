#include "Emeny.h"


Emeny::Emeny (const char* filename, float x = 0, float y = 0, float w = 0.5, float h = 0.5,float rate = 0.01) {
    
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
    movingDown = true;
    
    
    xinc = 0.01;
    yinc = rate;
}



void Emeny::jump(){

    
    
    if (movingDown)
        y-=yinc;
    
    
    if ((y-h) < -0.99){
        movingDown = true;
    }
    
}



void Emeny::draw(){
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


bool Emeny::contains(float mx, float my){
    return mx >= x && mx <= x+w && my <= y && my >= y - h;
}

void Emeny::drop(){
    for(int i = 0; i < playerBullets.size(); i++){
    
        playerBullets[i]->drop();
    }
}

void Emeny::shoot(){
    playerBullets.push_back(new bullet("images/compassSmall.png", x+w/3, y-w/2, 0.10, 0.10));
}

void Emeny::bulletdraw(){
    for (int i = 0; i < playerBullets.size();i++){
        playerBullets[i]->draw();
    }
}

bool Emeny::outofB(){
    for (int i = 0; i < playerBullets.size();i++){
        playerBullets[i]->OOB();
    }
    return 0;
}

void Emeny::cleanB(int i){
    playerBullets.erase(playerBullets.begin()+i-1);
}

bool Emeny::bulletcontains(float mx, float my){
    for (int i = 0; i < playerBullets.size();i++){
        if (playerBullets[i]->bulletcontain(mx, my))
            return true;
    }
    return 0;
}
