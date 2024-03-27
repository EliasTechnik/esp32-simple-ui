
#include "uiGraphics.h"
/*
//icon
icon::icon(){
    setDimension(0,0,0,0);
    setVisible(false); 
    bitmap = nullptr;
};

void icon::init(unsigned char* _bitmap, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible){
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
    bitmap = _bitmap;
};

unsigned char* icon::getBitmap(){
    return bitmap;
};

void icon::draw(){
    if(visible){
        display.drawXBM(posX,posY,width,height,bitmap);
    }
};

//interactiveIcon

interactiveIcon::interactiveIcon(){
    icon();
};

void interactiveIcon::init(unsigned char* _bitmap, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true){
    bitmap = _bitmap;
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
};

*/

//uiBox

uiBox::uiBox() : uiElement(){
}

uiBox::uiBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height)
:uiElement(_posX,_posY,_width,_height){};

uiBox::uiBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool _filled, bool isSelectable)
:uiElement(_posX,_posY,_width,_height,isSelectable){
    filled = _filled;
};

uiBox::~uiBox(){
    
}

/*
void uiBox::init(unsigned int _id, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true){
    this->setDimension(_posX, _posY, _width, _height);
    this->visible = isVisible;
    //filled = _filled;
    borderWidth = borderWidth;
}
*/

void uiBox::draw(frameInfo* f){
    Slog("draw2");
    if(/*visible*/true){
        
        if(filled){
            if(f->highlightSelected && selected != SelectionState::notSelected){
                f->display->drawFrame(posX, posY, width, height);
            }else{
                f->display->drawBox(posX, posY, width, height);
            }
            
        }else{
            if(f->highlightSelected && selected != SelectionState::notSelected){
                f->display->drawBox(posX, posY, width, height);
            }else{
                f->display->drawFrame(posX, posY, width, height);
            }
        }
    }
    
    
    //for testing
    
    //f->display->drawBox(posX, posY, width, height);
    //f->display->drawBox(50, 25, 5, 5);
}