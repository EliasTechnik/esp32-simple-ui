#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "helper.h"

/*

uiGraphics.h provides all classed to draw basic geometric shapes. They can be used when building uiElements. The uiElement has to inherit the class it wants to use

*/


class uiBox{
    protected:
        void drawBox(frameInfo* f, uiVisualTransformation vt, Dimension d);
    public:
        uiBox();
};

class uiFrame{
    protected:
        unsigned int borderWidth = 1;
        void drawFrame(frameInfo* f, uiVisualTransformation vt, Dimension d);
    public:
        uiFrame();
        uiFrame(unsigned int _borderWidth);
        void setBorderWidth(unsigned int _borderWidth);
};

class uiCircle{
    protected:
        unsigned int borderWidth = 1;
        void drawCircle(frameInfo* f, uiVisualTransformation vt, Dimension d);
    public:
        uiCircle();
        uiCircle(unsigned int _borderWidth);
        void setBorderWidth(unsigned int _borderWidth);
};

class uiFilledCircle{
    protected:
        void drawFilledCircle(frameInfo* f, uiVisualTransformation vt, Dimension d);
    public:
        uiFilledCircle();
        uiFilledCircle();
};

