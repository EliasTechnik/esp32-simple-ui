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


Viewport::Viewport(dimensions _dimension){
    dimension = _dimension;
}

int Viewport::convertX(int _x){
    return _x + dimension.getX();
}

int Viewport::convertY(int _y){
    return _y + dimension.getY();
}

int Viewport::convertWidth(int _width){
    if(_width + dimension.getX() > dimension.getWidth()){
        return dimension.getX() + dimension.getWidth();
    }else{
        return _width + dimension.getX();
    }
}

int Viewport::convertHeight(int _height){
     if(_height + dimension.getY() > dimension.getHeight()){
        return dimension.getY() + dimension.getHeight();
    }else{
        return _height + dimension.getY();
    }
}

String SelectionModetoString(SelectionMode selectionMode){
    switch(selectionMode){
        case SelectionMode::selectable: return "selectable";
        case SelectionMode::notSelectable: return "notSelectable";
        case SelectionMode::passthroughSelection: return "passthroughSelection";
        case SelectionMode::forwardSelection: return "forwardSelection";
        default: return "unknown";
    }
}

String FocusModetoString(FocusMode focusMode){
    switch(focusMode){
        case FocusMode::target: return "target";
        case FocusMode::collection: return "collection";
        case FocusMode::passthrough: return "passthrough";
        case FocusMode::passive: return "passive";
        default: return "unknown";
    }
}

String FocusStatetoString(FocusState focusState){
    switch(focusState){
        case FocusState::parent: return "parent";
        case FocusState::current: return "current";
        case FocusState::child: return "child";
        default: return "unknown";
    }
}