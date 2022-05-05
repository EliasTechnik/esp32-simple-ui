#include <simpleUI.h>


//dimmensions
dimensions::dimensions(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height){
    this->setDimension(_pos_x,_pos_y,_width,_height);
};
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

//uielement
uielement::uielement(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible){
    this->setDimension(_pos_x,_pos_y,_width,_height);
    visible = isVisible;
    focus = false;
};
void uielement::setVisible(bool isVisible){
    visible = isVisible;
};
bool uielement::getVisible(){
    return visible;
};
void uielement::setDisplay(U8G2 _display){
    display = _display;
};
void uielement::setName(string _name){
    name = _name;
};
void uielement::setFocus(bool _focus){
    focus = _focus;
};

//icon
icon::icon(unsigned char* _bitmap, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible){
    this->setDimension(_pos_x,_pos_y,_width,_height);
    this->setVisible(isVisible);
};
unsigned char* icon::getBitmap(){
    return bitmap;
}
void icon::draw(){
    display.drawXBM(pos_x,pos_y,width,height,bitmap);
}
