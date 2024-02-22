#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "uiText.h"
#include "uiInteractive.h"

template <unsigned int capacity> 
class staticLabel: public uiElement{
    protected:
        char text[capacity];
        UIEalign align;
    public:
        staticLabel();
        virtual void init(char _text[capacity], unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setAlign(UIEalign _align);
        UIEalign getAlign();
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

template <unsigned int capacity> 
class interactiveStaticLabel : public staticLabel, public uiInteractive{
    protected:

    public:
        interactiveStaticLabel();
        virtual void init(char _text[capacity], unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
};