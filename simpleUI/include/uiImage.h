#pragma once
#include "uiBasics.h"
#include "helper.h"
#include "uiPrebuilds.h"

/*

uiImage.h provides all classes to handle bitmaps.
They alone are usless but can be inherited when building uiElements.

*/

/*
TODO:
    - implement inverted
    - implement transparent
*/

class uiXBM: public FixedSizing, public Position{
    protected:
        bool inverted = false;
        bool transparent = false;
        unsigned char* img = nullptr;
        void drawXBM(frameInfo* f, uiVisualTransformation vt);
    public:
        uiXBM(int _x, int _y, int _width, int _height, unsigned char* _img = nullptr, bool _inverted = false, bool _transparent = false);
};


class uiXBMContainer: public uiXBM, public uiCollection{
    protected:
        void drawThis(frameInfo* f) override;
    public:
        uiXBMContainer(int _x, int _y, int _width, int _height, unsigned char* _img = nullptr, bool _inverted = false, bool _transparent = false);
};