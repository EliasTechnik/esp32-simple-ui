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

class Position{
    protected:
        unsigned int posX;
        unsigned int posY;
    public:
        Position();
        ~Position();
        Position(unsigned int _posX, unsigned int _posY);
        unsigned int getX();
        unsigned int getY();
        void setPosition(unsigned int _posX = 0, unsigned int _posY = 0);
        void setPosX(unsigned int _posX = 0);
        void setPosY(unsigned int _posY = 0);
};



class Sizing{
    protected:
        int width;
        int height;
    public:
        Sizing();
        ~Sizing();
        Sizing(int _width, int _height);
        int getWidth();
        int getHeight();
        void setSizing(int _width = 0, int _height = 0);
        void setWidth(int _width = 0);
        void setHeight(int _height = 0);
};


struct Padding{
    unsigned int top = 1;
    unsigned int start = 1;
    unsigned int end = 1;
    unsigned int bottom = 1;
};




struct Viewport{
    Sizing sizing;
    Viewport();
    Viewport(Sizing _sizing);
    int convertX(int _x);
    int convertY(int _y);
    int convertWidth(int _width);
    int convertHeight(int _height);
};

const Viewport DEFAULT_OFFSET = Viewport(Sizing(128,64));
const Viewport ZERO_OFFSET_128_X_65 = Viewport(Sizing(128,65));

/*Information about the current frame. Every draw method gets this info. */

struct frameInfo{
    bool highlightSelected = false;
    Viewport viewportOffset = DEFAULT_OFFSET;
    U8G2* display = nullptr;
};


enum class FocusState{
    parent, //the partent element or above has focus
    current, //this element has focus
    child   //on of our childs has focus
};

String FocusStatetoString(FocusState focusState);

enum class FocusMode{
    target, //can receive focus and is selectable
    collection, //can receive focus but ends the focus tree. All of its childs will show selected.
    passthrough, //can receive focus but will passthrough to its child
    passive //can not receive focus
};

String FocusModetoString(FocusMode focusMode);


enum class SelectionMode{
    selectable, //this component can be selected
    passthroughSelection, //this component cant be selected but will forward its selection to its childs
    forwardSelection, //this component can be selected and will forward its selection state to its childs
    notSelectable //this component is not selectable
};

String SelectionModetoString(SelectionMode selectionMode);

enum class uiClassHirachyType{
    element,
    page,
    root
};

enum class SelectionState{notSelected, showAsSelected, Selected};

enum class FocusDirection{fromParent,fromChild,fromUperNeighbour,fromLowerNeighbour};

enum class UserAction{none, generalButton, backButton, leftButton, rightButton, enterButton};

enum class ScreenState{off, on};

struct InputAction{
  UserAction action=UserAction::none;
  bool executed=false;
  bool present=false;
};

struct uiCallback{
    void (*CB)(void * context, void *trigger, UIEventType event_type);
    void * CBcontext;
};

struct DisplayConfig{
    unsigned long screenSleepTime = 20000;
    int frameDistance = 16;//66;
    int flashHalfCycle = 250;
    bool useSleep = true;
    U8G2* display = nullptr;
    Viewport viewportOffset = ZERO_OFFSET_128_X_65;
};

struct uiVisualTransformation{
    bool invertedContent = false;
    bool invertedBackground = false;
    uiVisualTransformation();
    uiVisualTransformation(bool _invertedContent, bool _invertedBackground);
};