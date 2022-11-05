#include <simpleUI.h>


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


//uiInteractive
uiInteractive::uiInteractive(){
    tabPosition.horizontalTabId = 0;
    tabPosition.verticalTabId = 0;
    CBonEvent.CBcontext = nullptr;
    CBonEvent.CB = nullptr;
};

void uiInteractive::setCB(uiCallback _CBonEvent){
    CBonEvent = _CBonEvent;
}

void uiInteractive::triggerUIaction(UIEventType triggerType){
    if(CBonEvent.CBcontext != nullptr){
        CBonEvent.CB(CBonEvent.CBcontext, this, triggerType);
    }
};

void uiInteractive::setFocus(bool _focus){
    focus = _focus;
};


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

void interactiveIcon::init(unsigned char* _bitmap, unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true){
    bitmap = _bitmap;
    setDimension(_pos_x,_pos_y,_width,_height);
    setVisible(isVisible);
};






