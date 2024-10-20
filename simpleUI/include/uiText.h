

#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "uiText.h"
#include "uiInteractive.h"


class StaticLabel: public uiElement{
    protected:
        string text;
        UIalign align;
    public:
        StaticLabel();
        virtual void init(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setAlign(UIalign _align);
        UIalign getAlign();
        void draw(frameInfo* f) override;  
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

class InteractiveStaticLabel: public StaticLabel, public uiInteractive{
    protected:

    public:
        InteractiveStaticLabel();
        virtual void init(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        void draw(frameInfo* f) override;  
};
