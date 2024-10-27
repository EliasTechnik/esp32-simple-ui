#include "uiBasics.h"


//Position
Position::Position(){
    posX=0;
    posY=0;
};

Position::Position(unsigned int _posX, unsigned int _posY){
    this->setPosition(_posX,_posY);
}

Position::~Position(){

};

unsigned int Position::getX(){
    return posX;
};

unsigned int Position::getY(){
    return posY;
};

void Position::setPosition(unsigned int _posX, unsigned int _posY){
    posX=_posX;
    posY=_posY;
};


void Position::setX(unsigned int _posX){
    posX=_posX;
};

void Position::setY(unsigned int _posY){
    posY=_posY;
};

//Sizing
Sizing::Sizing(){
    width=0;
    height=0;
};

Sizing::Sizing(int _width, int _height){
    this->setSizing(_width,_height);
}

Sizing::~Sizing(){

};

int Sizing::getWidth(){
    return width;
};

int Sizing::getHeight(){
    return height;
};

void Sizing::setSizing(int _width, int _height){
    width=_width;
    height=_height;
};


void Sizing::setWidth(int _width){
    width=_width;
};

void Sizing::setHeight(int _height){
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


uiVisualTransformation::uiVisualTransformation(){
    invertedBackground = false;
    invertedContent = false;
}

uiVisualTransformation::uiVisualTransformation(bool _invertedContent, bool _invertedBackground){
    invertedBackground = _invertedBackground;
    invertedContent = _invertedContent;
}