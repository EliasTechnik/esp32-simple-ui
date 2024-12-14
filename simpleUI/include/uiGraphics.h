#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "helper.h"

/*

uiGraphics.h provides all classes to draw basic geometric shapes. 
They can be used when building uiElements. 
The uiElement has to inherit the class it wants to use

*/

/*

TODO Canvas!

*/

//mother object 
class uiGraphic{
    protected:

    public:
        uiGraphic();
        virtual void drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d); 
};

class uiGraphicElement{
    protected:
        Dimension gInfo;
        uiGraphic* gElement;
    public:
        uiGraphicElement();
        uiGraphicElement(uiGraphic* element, Dimension d);
        void draw(frameInfo* f, uiVisualTransformation vt);
        //todo set and change gInfo
};

class uiGraphicCanvas{
    protected:
        std::vector<uiGraphicElement*> elements;
    public:
        uiGraphicCanvas();
        void addElement(uiGraphicElement*)
}


class uiBox: public uiGraphic{
    protected:
        void drawBox(frameInfo* f, uiVisualTransformation vt, Dimension d);
    public:
        uiBox();
        void drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d) override;
};

class uiFrame: public uiGraphic{
    protected:
        unsigned int borderWidth = 1;
        void drawFrame(frameInfo* f, uiVisualTransformation vt, Dimension d);
    public:
        uiFrame();
        uiFrame(unsigned int _borderWidth);
        void setBorderWidth(unsigned int _borderWidth);
        void drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d) override;
};

class uiCircle: public uiGraphic{
    protected:
        unsigned int borderWidth = 1;
        void drawCircle(frameInfo* f, uiVisualTransformation vt, Position center, unsigned int r);
    public:
        uiCircle();
        uiCircle(unsigned int _borderWidth);
        void setBorderWidth(unsigned int _borderWidth);
        void drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d) override;
};

class uiFilledCircle: public uiGraphic{
    protected:
        void drawFilledCircle(frameInfo* f, uiVisualTransformation vt, Position center, unsigned int r);
    public:
        uiFilledCircle();
        void drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d) override;
};

class uiLine: public uiGraphic{
    protected:
        unsigned int borderWidth = 1;
        void drawLine(frameInfo* f, uiVisualTransformation vt, Position pos1, Position pos2);
    public:
        uiLine();
        uiLine(unsigned int _borderWidth);
        void setBorderWidth(unsigned int _borderWidth);
        void drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d) override;
};

