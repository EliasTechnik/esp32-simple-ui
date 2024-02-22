#pragma once
#include "uiBasics.h"

/*uielement is one baseclass for every ui element. It handles attributes commen for all ui elements*/

class uiElement : public dimensions{
    protected:
        bool visible;
        U8G2 display;
        unsigned int id;
    public:
        uiElement();
        virtual void init(unsigned int _id, unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
        void setVisible(bool isVisible);
        bool getVisible();
        void setDisplay(U8G2 _display);
        unsigned int getId();
        virtual void draw(); //should be overwritten by every child class which inherrits from uielement
};