#include "uiText.h"

//staticLabel
template <unsigned int capacity>
staticLabel<capacity>::staticLabel(){
    setDimensions();
    setVisible(true);
    align = UIEalign::UIEAleft;
};

template <unsigned int capacity>
void staticLabel<capacity>::init(char _text[capacity], unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible){
    text = _text;
    setDimensions(_pos_x,_pos_y,_width,_height);
    setVisible(isVisible);
};

template <unsigned int capacity>
void staticLabel<capacity>::setAlign(UIEalign _align){
    align = _align;
};

template <unsigned int capacity>
UIEalign staticLabel<capacity>::getAlign(){
    return align;
}

//interactiveStaticLabel
template <unsigned int capacity>
interactiveStaticLabel<capacity>::interactiveStaticLabel(){
    setDimensions();
    align = UIEalign::UIEAleft;
    setVisible(true);
};

template <unsigned int capacity>
void interactiveStaticLabel<capacity>::init(char _text[capacity], unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true){
    text = _text;
    setDimensions(_pos_x,_pos_y,_width,_height);
    setVisible(isVisible);
};