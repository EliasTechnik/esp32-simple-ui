#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "uiText.h"
#include "uiInteractive.h"

class uiText{
    protected:
        string text;
        UIalign align;
        const uint8_t* font = DEFAULT_UI_FONT;
        void drawText(frameInfo* f, uiVisualTransformation vt, Position p);
    public:
        uiText();
        uiText(string _text);
        uiText(string _text, UIalign _align);
        void setAlign(UIalign _align);
        UIalign getAlign();
        void setText(string _text);
        void setFont(const uint8_t* _font = DEFAULT_UI_FONT);
        Sizing getTextSizing(frameInfo* f); 
};


class uiStaticLabel: public uiElement, public Dimension{
    protected:
        string text;
        UIalign align;
        const uint8_t* font = DEFAULT_UI_FONT;
        void drawThis(frameInfo* f) override;  
    public:
        uiStaticLabel();
        uiStaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setAlign(UIalign _align);
        UIalign getAlign();
        void setText(string _text);
        void setFont(const uint8_t* _font = DEFAULT_UI_FONT);
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

/*
class InteractiveStaticLabel: public uiStaticLabel, public uiInteractive{
    protected:
        void drawThis(frameInfo* f) override;  
    public:
        InteractiveStaticLabel();
        InteractiveStaticLabel(string _text, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible = true);
        
};
*/
