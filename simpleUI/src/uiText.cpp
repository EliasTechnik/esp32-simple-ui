
#include "uiText.h"

//staticLabel

StaticLabel::StaticLabel(){
    setDimension();
    setVisible(true);
    align = UIalign::UIAleft;
};


void StaticLabel::init(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible){
    text = _text;
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
};


void StaticLabel::setAlign(UIalign _align){
    align = _align;
};

UIalign StaticLabel::getAlign(){
    return align;
}

void StaticLabel::draw(frameInfo* f){
    //Slog("draw2");
    bool showSelected = (!(selected == SelectionState::notSelected)) | (selectable && (focus == FocusState::current));

    if(visible){
        f->display->drawStr(posX, posY, text.c_str)


        if(filled){
            if(f->highlightSelected && showSelected){
                f->display->drawFrame(posX, posY, width, height);
            }else{
                f->display->drawBox(posX, posY, width, height);
            }
            
        }else{
            if(f->highlightSelected && showSelected){
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

//interactiveStaticLabel

InteractiveStaticLabel::InteractiveStaticLabel(){
    setDimension();
    align = UIalign::UIAleft;
    setVisible(true);
};

void InteractiveStaticLabel::init(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true){
    text = _text;
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
};
