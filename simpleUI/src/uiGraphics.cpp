#include "uiGraphics.h"
//icon
icon::icon(){
    setDimension(0,0,0,0);
    setVisible(false); 
    bitmap = nullptr;
};

void icon::init(unsigned char* _bitmap, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible){
    setDimension(_pos_x,_pos_y,_width,_height);
    setVisible(isVisible);
    bitmap = _bitmap;
};

unsigned char* icon::getBitmap(){
    return bitmap;
};

void icon::draw(){
    if(visible){
        display.drawXBM(pos_x,pos_y,width,height,bitmap);
    }
};

//interactiveIcon

interactiveIcon::interactiveIcon(){
    icon();
};

void interactiveIcon::init(unsigned char* _bitmap, unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible){
    bitmap = _bitmap;
    setDimension(_pos_x,_pos_y,_width,_height);
    setVisible(isVisible);
};