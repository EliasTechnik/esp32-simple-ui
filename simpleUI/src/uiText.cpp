
#include "uiText.h"

//uiText

uiText::uiText(){
    text = "";
    align = UIalign::UIAleft;
}

uiText::uiText(string _text){
    text = _text;
    align = UIalign::UIAleft;
}

uiText::uiText(string _text, UIalign _align){
    text = "";
    align = _align;
}

void uiText::setAlign(UIalign _align){
    align = _align;
};

UIalign uiText::getAlign(){
    return align;
}

void uiText::setFont(const uint8_t* _font){
    font = _font;
}

void uiText::setText(string _text){
    text = _text;
}

void uiText::drawText(frameInfo* f, uiVisualTransformation vt, Position p){
    f->display->setFont(font);
    int height = f->display->getAscent();
    f->display->setFontMode(1); //https://github.com/olikraus/u8g2/wiki/u8g2reference#setdrawcolor
    if(vt.invertedContent){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1);
    }
    f->display->setFontPosBaseline();
    f->display->drawStr(f->viewportOffset.convertX(p.getX()),f->viewportOffset.convertY(p.getY()+height), text.c_str());
}

Sizing uiText::getTextSizing(frameInfo* f){
    f->display->setFont(font);
    Sizing s = Sizing(f->display->getStrWidth(text.c_str()),(f->display->getAscent())-(f->display->getDescent()));
    return s;
}





//staticLabel

uiStaticLabel::uiStaticLabel(){
    //setDimension();
    setVisible(true);
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiStaticLabel";
    align = UIalign::UIAleft;
};


uiStaticLabel::uiStaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible): 
    uiElement(SelectionMode::notSelectable, isVisible)
{
    posX = _posX;
    posY = _posY;
    width = _width;
    height = _height;

    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiStaticLabel";
    text = _text;
    align = UIalign::UIAleft;
};


void uiStaticLabel::setAlign(UIalign _align){
    align = _align;
};

UIalign uiStaticLabel::getAlign(){
    return align;
}

void uiStaticLabel::setFont(const uint8_t* _font){
    font = _font;
}

void uiStaticLabel::setText(string _text){
    text = _text;
}

void uiStaticLabel::drawThis(frameInfo* f){
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

/*
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
*/
