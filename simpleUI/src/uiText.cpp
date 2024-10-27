
#include "uiText.h"

//staticLabel

StaticLabel::StaticLabel(){
    setDimension();
    setVisible(true);
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiStaticLabel";
    align = UIalign::UIAleft;
};


StaticLabel::StaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible): 
    uiElement(_posX, _posY, _width, _height, SelectionMode::notSelectable, isVisible)
{
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiStaticLabel";
    text = _text;
    align = UIalign::UIAleft;
};


void StaticLabel::setAlign(UIalign _align){
    align = _align;
};

UIalign StaticLabel::getAlign(){
    return align;
}

void StaticLabel::setFont(const uint8_t* _font){
    font = _font;
}

void StaticLabel::setText(string _text){
    text = _text;
}

void StaticLabel::drawThis(frameInfo* f){
    //Slog("draw2");
    bool showSelected = (selected == SelectionState::showAsSelected || selected == SelectionState::Selected);

    if(visible){
        f->display->setFont(font);
        int height = f->display->getMaxCharHeight();
        f->display->drawStr(f->viewportOffset.convertX(posX),f->viewportOffset.convertY(posY+height), text.c_str());
        /*

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
        */
    }
}

//interactiveStaticLabel

InteractiveStaticLabel::InteractiveStaticLabel(){
    setDimension();
    align = UIalign::UIAleft;
    setVisible(true);
};

InteractiveStaticLabel::InteractiveStaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible){
    text = _text;
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
};
