
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
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiBox";
}

uiBox::uiBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height)
:uiElement(_posX,_posY,_width,_height){
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiBox";
};

uiBox::uiBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool _filled, SelectionMode _selectionMode)
:uiElement(_posX,_posY,_width,_height, _selectionMode,true){
    filled = _filled;
    selectionMode = _selectionMode;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiBox";
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

void uiBox::drawThis(frameInfo* f){
    //Slog("draw2");
    bool showSelected = (selected == SelectionState::showAsSelected || selected == SelectionState::Selected);

    if(visible){
        if(filled){
            if(f->highlightSelected && showSelected){
                f->display->drawFrame(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }else{
                f->display->drawBox(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }
            
        }else{
            //not filled
            if(f->highlightSelected && showSelected){
                f->display->drawBox(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }else{
                f->display->drawFrame(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }
        }
    }
}