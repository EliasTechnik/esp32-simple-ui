#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <string>

/*
void (*CBonMessage)(void * context, WSMessage msg);
void * CBcontext;

*/

/*
ideas:
    - uiPages store only a (fixed) list of pointers to elements and interactiveElements. 
    - every ui pice has to be declared permanently (global) at compile time, thus getting placed on the stack
    - user manipulates the ui only by using the previous declared objets

*/
using namespace std; //to use string

enum UIEalign{UIEAcenter,UIEAleft,UIEAright,UIEAtop,UIEAbottom};

enum UIEventType{UIET_recvFocus, UIET_lostFocus, UIET_onEnter, UIET_onExit};

struct tabPos{
    byte horizontalTabId=0;
    byte verticalTabId=0;
};


/*Every UI Element has dimensions defined as rectangle. pos_x and pos_y define the upper left corner of that element.*/

class dimensions{
    protected:
        unsigned int pos_x;
        unsigned int pos_y;
        unsigned int width;
        unsigned int height;
    public:
        dimensions();
        virtual void init(unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0);
        unsigned int getX();
        unsigned int getY();
        unsigned int getWidth();
        unsigned int getHeight();
        void setDimension(unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0);
};