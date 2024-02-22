#include "uiElement.h"


//uiElement
uiElement::uiElement(){
    setDimension(0,0,0,0);
    visible = true;
};

void uiElement::init(unsigned int _id, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible){
    this->setDimension(_pos_x,_pos_y,_width,_height);
    visible = isVisible;
};

void uiElement::setVisible(bool isVisible){
    visible = isVisible;
};

bool uiElement::getVisible(){
    return visible;
};

void uiElement::setDisplay(U8G2 _display){
    display = _display;
};

unsigned int uiElement::getId(){
    return id;
}