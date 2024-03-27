
/*
#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "uiText.h"
#include "uiInteractive.h"


class staticLabel: public uiElement{
    protected:
        string text;
        UIEalign align;
    public:
        staticLabel();
        virtual void init(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setAlign(UIEalign _align);
        UIEalign getAlign();
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

class interactiveStaticLabel: public staticLabel, public uiInteractive{
    protected:

    public:
        interactiveStaticLabel();
        virtual void init(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
};
*/