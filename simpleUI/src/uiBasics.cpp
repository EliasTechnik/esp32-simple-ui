#include "uiBasics.h"

//dimmensions
dimensions::dimensions(){
    posX=0;
    posY=0;
    width=0;
    height=0;
};

dimensions::dimensions(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height){
    this->setDimension(_posX,_posY,_width,_height);
}

dimensions::~dimensions(){

};

unsigned int dimensions::getX(){
    return posX;
};

unsigned int dimensions::getY(){
    return posY;
};

unsigned int dimensions::getWidth(){
    return width;
};

unsigned int dimensions::getHeight(){
    return height;
};

void dimensions::setDimension(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height){
    posX=_posX;
    posY=_posY;
    width=_width;
    height=_height;
};

void dimensions::setPosX(unsigned int _posX){
    posX=_posX;
};

void dimensions::setPosY(unsigned int _posY){
    posY=_posY;
};

void dimensions::setWidth(unsigned int _width){
    width=_width;
};

void dimensions::setHeight(unsigned int _height){
    height=_height;
};