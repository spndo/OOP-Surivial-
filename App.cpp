#include<iostream>
#include <string>
#include "App.h"

static App* singleton;
static badGuys* pt;

int WindowHeight = 600;
int WindowWidth = 600;
int score = 0;


void app_timer(int value){
    
    if (singleton->game_over){
        singleton->gameOver->advance();
    }
    if (!(pt->explosions.empty())){
        for (int i = 0; i < pt->explosions.size(); i++){
            pt->explosions[i]->advance();
            if (pt->explosions[i]->frameNumber == 11){
                pt->explosions[i]->stop();
            }
        }
    }
    pt->explosion->advance();
    
    
    if (singleton->moving){
        singleton->mc->advance();
        pt ->falling();
        pt ->bulletshoot();
        
        //)
        
        if (pt->contain(singleton->mc->x, singleton->mc->y) || pt->bulletcotaincheck(singleton->mc->x, singleton->mc->y)){
            singleton->moving = false;
            singleton->game_over = true;
            singleton->mc->shooting = false;
            singleton->gameOver->animate();
        }
        if (pt->contain(singleton->mc->getbulletx(), singleton->mc->getbullety())){
            int b = pt->whatContain(singleton->mc->getbulletx(), singleton->mc->getbullety());
            pt->deleteBad(b);
            //TODO INCREMENT SCORE
            score += 100;
            
        }
//
//        while (!singleton->game_over && score > 200) {
//            pt->r += 10%30;
//        }
        
    }
    
    if (singleton->up) {
        singleton->mc->moveUp(0.02);
    }
    if (singleton->down) {
        singleton->mc->moveDown(0.04);
    }
    if (singleton->left) {
        singleton->mc->moveLeft(0.04);
    }
    if (singleton->right) {
        singleton->mc->moveRight(0.04);
    }
    
    //    if (!(pt->explosions.empty())){
    //        singleton->redraw();
    //        glutTimerFunc(100, app_timer, value);
    //    }
    if (singleton->game_over){
        singleton->redraw();
        glutTimerFunc(100, app_timer, value);
    }
    else {
        if (singleton->up || singleton->down || singleton->left || singleton->right || singleton->moving && !singleton->game_over){
            singleton->redraw();
            glutTimerFunc(16, app_timer, value);
        }
    }
}


void App::PrintText(int x, int y, string String){
    //(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
    {glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    pt = new badGuys();
    singleton = this;
    mx = 0.0;
    my = 0.0;
    
    int score = 0;
    
    background = new TexRect("images/background.png", -1, 1, 2, 2);
    mc = new Reimu("images/reimu.png", -0.1, -0.6, 0.15, 0.22);
    gameOver = new AnimatedRect("images/game_over.png", 7, 1, -1.0, 0.8, 2, 1.2);
    
    
    up = down = left = right = false;
    
    moving = false;
    game_over = false;
    
    app_timer(1);
    
}

void App::specialKeyPress(int key){
    if (!game_over){
        if (key == 100){
            left = true;
        }
        if (key == 101){
            up = true;
        }
        if (key == 102){
            right = true;
        }
        if (key == 103){
            down = true;
        }
        //        if (key == ' '){
        //            singleton->mc->shoot();
        //        }
        //        if (key == ' '){
        ////            myBullet->setFire();
        ////            redraw();
        //    }
        //    move(1);
    }
    
}

void App::specialKeyUp(int key) {
    if (key == 100) {
        left = false;
    }
    if (key == 101) {
        up = false;
    }
    if (key == 102) {
        right = false;
    }
    if (key == 103) {
        down = false;
    }
}

void App::draw() {
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 1.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    background->draw();
    singleton ->mc->bulletdraw();
    
    pt -> drawbullet();
    pt ->draw();
    mc->draw();

    if(moving){
        PrintText(410, 500, "Score:");
        PrintText(500, 500, to_string(score));
    }
    
    if(game_over){
        PrintText(410, 500, "Score:");
        PrintText(500, 500, to_string(score));
    }
    
    
    gameOver->draw();
    
    
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
}

void App::idle(){
    
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        
        delete singleton;
        delete pt;
        delete gameOver;
        delete background;
        delete mc;
        exit(0);
    }
    
    if (key == ' '){
        singleton->mc->shoot();
    }
    
    if (key == 's') {
        moving = true;
        app_timer(1);
    }
        

    
    //    if (key = 'r'){
    //        game_over = false;
    //        gameOver->stop();
    //        moving = true;
    //        mc->draw();
    //        pt->draw();
    //    }
    
    
}
