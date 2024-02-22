#include "uiBasics.h"

//dimmensions
dimensions::dimensions(){
    pos_x=0;
    pos_y=0;
    width=0;
    height=0;
};

void dimensions::init(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height){
    this->setDimension(_pos_x,_pos_y,_width,_height);
}

unsigned int dimensions::getX(){
    return pos_x;
};

unsigned int dimensions::getY(){
    return pos_y;
};

unsigned int dimensions::getWidth(){
    return width;
};

unsigned int dimensions::getHeight(){
    return height;
};

void dimensions::setDimension(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height){
    pos_x=_pos_x;
    pos_y=_pos_y;
    width=_width;
    height=_height;
};
