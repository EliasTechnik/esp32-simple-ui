#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "helper.h"
//#include "uiInteractive.h"

/*
class icon : public uiElement{
    protected:
        unsigned char* bitmap; 
    public:
        icon();
        virtual void init(unsigned char* _bitmap, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
        unsigned char* getBitmap();  
        void draw();    
};

class interactiveIcon: public icon, public uiInteractive{
    protected:
        
    public:
        interactiveIcon();
        virtual void init(unsigned char* _bitmap, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
};

class glyph : public uiElement{
    protected:
        uint16_t code;
    public:
        glyph(uint16_t uni_code, unsigned int _posX, unsigned int _posY, bool isVisible = true);
        void setCode(uint16_t);
        uint16_t getCode();
};

*/

class uiBox: public uiElement{
    protected:
        byte borderWidth = 1;
        bool filled = true;
    public:
        uiBox();
        uiBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height);
        uiBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool _filled, SelectionMode SelectionMode = SelectionMode::notSelectable);
        ~uiBox();
        //virtual void init(unsigned int _id, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
        void draw(frameInfo* f) override;    
};