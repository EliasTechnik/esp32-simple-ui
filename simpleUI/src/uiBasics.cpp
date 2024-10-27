#include "uiBasics.h"

//dimmensions
Dimensions::Dimensions(){
    posX=0;
    posY=0;
    width=0;
    height=0;
};

Dimensions::Dimensions(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height){
    this->setDimension(_posX,_posY,_width,_height);
}

Dimensions::~Dimensions(){

};

unsigned int Dimensions::getX(){
    return posX;
};

unsigned int Dimensions::getY(){
    return posY;
};

unsigned int Dimensions::getWidth(){
    return width;
};

unsigned int Dimensions::getHeight(){
    return height;
};

void Dimensions::setDimension(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height){
    posX=_posX;
    posY=_posY;
    width=_width;
    height=_height;
};

void Dimensions::setPosX(unsigned int _posX){
    posX=_posX;
};

void Dimensions::setPosY(unsigned int _posY){
    posY=_posY;
};

void Dimensions::setWidth(unsigned int _width){
    width=_width;
};

void Dimensions::setHeight(unsigned int _height){
    height=_height;
};


Viewport::Viewport(Dimensions _dimension){
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

Sizing::Sizing(){
    width = 0;
    height = 0;
};

Sizing::Sizing(unsigned int _width, int _height){
    width = _width;
    height = _height;
}

Dimensions Sizing::toDimensions(Dimensions* d){
    Dimensions dim;
    dim.setPosX(d->getX());
    dim.setPosY(d->getY());
    dim.setWidth(width);
    dim.setHeight(height);
    return dim;
}

uiVisualTransformation::uiVisualTransformation(){
    invertedBackground = false;
    invertedContent = false;
}

uiVisualTransformation::uiVisualTransformation(bool _invertedContent, bool _invertedBackground){
    invertedBackground = _invertedBackground;
    invertedContent = _invertedContent;
}