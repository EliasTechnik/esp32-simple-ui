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

enum UIEaligne{UIEAcenter,UIEAleft,UIEAright,UIEAtop,UIEAbottom};

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

struct uiCallback{
    void (*CB)(void * context, uiElement *trigger, UIEventType event_type);
    void * CBcontext;
};

/*uiInteractiveElement is the baseclass for all interactive UI-Elements*/
class uiInteractive{
    protected:
        tabPos tabPosition;
        bool focus; //true if element has focus (display inverted)
        uiCallback CBonEvent; 
    public:
        void triggerUIaction(UIEventType triggerType);
        void setFocus(bool _focus = true);
};

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

template <unsigned int capacity> 
class staticLabel : public uielement{
    protected:
        char text[capacity];
        UIEaligne aligne;
    public:
        staticLabel();
        virtual void init(char _text[capacity], unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setText(char _text[capacity]);
        void setAligne(UIEaligne _aligne);
        UIEaligne getAligne();
        char* getText();
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

template <unsigned int capacity> 
class interactiveStaticLabel : public staticLabel , public uiInteractive{
    protected:

    public:
        interactiveStaticLabel();
        virtual void init(char _text[capacity], unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
};

class glyph : public uiElement{
    protected:
        uint16_t code;
    public:
        glyph(uint16_t uni_code, unsigned int _pos_x, unsigned int _pos_y, bool isVisible = true);
        void setCode(uint16_t);
        uint16_t getCode();
};

/*A UI-Page owns a set of ui elements.
The Element-ID are given by the page*/

class uipage{
    protected:
        uiElement* elist; //dynamic array of non interactive Elements 
        uiInteractive* ilist; //dynamic array of interactive Elements
        unsigned int pageID;
        unsigned int ecount; 
        unsigned int icount;
        uipagegroup childgroup; //stores a potential childgroup behind that page (has no function but can be used to make menu building and navigation easyer)
    public:    
        uipage(); //constructor
        ~uipage(); //destructor
        void init(unsigned int _pageID);
        void drawPage();
        unsigned int addUIElement(uiElement _e);
        unsigned int addUIInteractive(uiInteractive _i);
        uiElement getUIElement(unsigned int index);
        uiInteractive getUIinteractive(unsigned int index);
        void setChildgroup(uipagegroup _childgroup);
        uipagegroup getChildgroup();
};

/*Groups UI-Pages together*/

class uipagegroup{
    protected:
        unsigned int pagecount; //counts the number of available ui pages
        unsigned int pagepos;
        uipage* pagelist;
    public:
        uipagegroup(U8G2 display, unsigned int _pagecount);
        ~uipagegroup();
        unsigned int addPage(uipage page);
        uipage getPage(unsigned int index);
        uipage getPage(string name);
        void displayPage(string name);
        void displayPage(unsigned int index);
        void updateUI(); //updates the display, should be called several times a second (30x for 30 FPS)
};