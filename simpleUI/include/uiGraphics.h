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

class uiBox{
    protected:
        unsigned int borderWidth = 1;
        bool filled = true;
        void drawBox(frameInfo* f, uiVisualTransformation* vt, Dimensions* d);
    public:
        uiBox();
        uiBox(bool _filled);
        uiBox(unsigned int _borderWidth);
        void setBorderWidth(unsigned int _borderWidth);
        void setFilled(bool _filled);
};

class uiInteractiveBox: public uiElement{
    protected:
        byte borderWidth = 1;
        bool filled = true;
        void drawThis(frameInfo* f) override; 
    public:
        uiInteractiveBox();
        uiInteractiveBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height);
        uiInteractiveBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool _filled, SelectionMode SelectionMode = SelectionMode::notSelectable);
        ~uiInteractiveBox();
        //virtual void init(unsigned int _id, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
};