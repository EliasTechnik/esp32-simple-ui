#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "uiText.h"
#include "uiInteractive.h"


class StaticLabel: public uiElement{
    protected:
        string text;
        UIalign align;
        const uint8_t* font = u8g2_font_5x7_tf;
    public:
        StaticLabel();
        StaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setAlign(UIalign _align);
        UIalign getAlign();
        void draw(frameInfo* f) override;  
        void setText(string _text);
        void setFont(const uint8_t* _font = u8g2_font_5x7_tf);
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

class InteractiveStaticLabel: public StaticLabel, public uiInteractive{
    protected:

    public:
        InteractiveStaticLabel();
        InteractiveStaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        void draw(frameInfo* f) override;  
};
