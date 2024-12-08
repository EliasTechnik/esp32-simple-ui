#include "uiImage.h"


uiXBM::uiXBM(int _x, int _y, int _width, int _height, unsigned char* _img, bool _inverted, bool _transparent){
    posX = _x,
    posY = _y;
    width = _width;
    height = _height;
    img = _img;
    inverted = _inverted;
    transparent = _transparent;
}

void uiXBM::drawXBM(frameInfo* f, uiVisualTransformation vt){
    if(vt.invertedContent){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1);
    }

    f->display->drawXBM(
        f->viewportOffset.convertX(posX),
        f->viewportOffset.convertY(posY), 
        f->viewportOffset.convertWidth(width),
        f->viewportOffset.convertHeight(height),
        img
    );
}

uiXBMContainer::uiXBMContainer(int _x, int _y, int _width, int _height, unsigned char* _img, bool _inverted, bool _transparent):uiXBM(_x, _y, _width, _height, _img, _inverted, _transparent){

}

void uiXBMContainer::drawThis(frameInfo* f){
    drawXBM(f, uiVisualTransformation(false, false));
}