#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "uiInteractive.h"


class icon : public uiElement{
    protected:
        unsigned char* bitmap; 
    public:
        icon();
        virtual void init(unsigned char* _bitmap, unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
        unsigned char* getBitmap();  
        void draw();    
};

class interactiveIcon: public icon, public uiInteractive{
    protected:
        
    public:
        interactiveIcon();
        virtual void init(unsigned char* _bitmap, unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
};

class glyph : public uiElement{
    protected:
        uint16_t code;
    public:
        glyph(uint16_t uni_code, unsigned int _pos_x, unsigned int _pos_y, bool isVisible = true);
        void setCode(uint16_t);
        uint16_t getCode();
};