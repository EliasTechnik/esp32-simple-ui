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

enum UIalign{UIAcenter,UIAleft,UIAright,UIAtop,UIAbottom};

enum UIEventType{UIET_recvFocus, UIET_lostFocus, UIET_onEnter, UIET_onExit};

struct tabPos{
    byte horizontalTabId=0;
    byte verticalTabId=0;
};


/*Every UI Element has dimensions defined as rectangle. posX and posY define the upper left corner of that element.*/

class dimensions{
    protected:
        unsigned int posX;
        unsigned int posY;
        unsigned int width;
        unsigned int height;
    public:
        dimensions();
        ~dimensions();
        dimensions(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height);
        unsigned int getX();
        unsigned int getY();
        unsigned int getWidth();
        unsigned int getHeight();
        void setDimension(unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0);
        void setPosX(unsigned int _posX = 0);
        void setPosY(unsigned int _posY = 0);
        void setWidth(unsigned int _width = 0);
        void setHeight(unsigned int _height = 0);
};


/*Information about the current frame. Every draw method gets this info. */

struct frameInfo{
    bool highlightSelected = false;
    U8G2* display = nullptr;
};

enum class FocusState{parent, current, child};

enum class SelectionState{notSelected, showAsSelected, Selected};

enum class FocusDirection{fromParent,fromChild,fromUperNeighbour,fromLowerNeighbour};

enum class UserAction{none, generalButton, backButton, leftButton, rightButton, enterButton};

struct InputAction{
  UserAction action=UserAction::none;
  bool executed=false;
  bool present=false;
};

struct uiCallback{
    void (*CB)(void * context, void *trigger, UIEventType event_type);
    void * CBcontext;
};