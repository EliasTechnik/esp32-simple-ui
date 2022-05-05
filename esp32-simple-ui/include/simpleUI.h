#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <string>

using namespace std; //to use string

enum UIEaligne{UIEAcenter,UIEAleft,UIEAright,UIEAtop,UIEAbottom};

class dimensions{
    protected:
        unsigned int pos_x;
        unsigned int pos_y;
        unsigned int width;
        unsigned int height;
    public:
        dimensions(unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0);
        unsigned int getX();
        unsigned int getY();
        unsigned int getWidth();
        unsigned int getHeight();
        void setDimension(unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0);
};

class uielement : public dimensions{
    protected:
        bool visible;
        U8G2 display;
        string name;
        bool focus; //true if element has focus (flash inverted)
    public:
        uielement(unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
        void setVisible(bool isVisible);
        bool getVisible();
        void setDisplay(U8G2 _display);
        void setName(string _name);
        void setFocus(bool _focus = true);
        virtual void draw(); //should be overwritten by every child class which inherrits from uielement
};

class icon : public uielement{
    protected:
        unsigned char* bitmap; 
    public:
        icon(unsigned char* _bitmap, unsigned int _pos_x = 0, unsigned int _pos_y = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true);
        unsigned char* getBitmap();  
        void draw();    
};

class label : public uielement{
    protected:
        string text;
        UIEaligne aligne;
    public:
        label(string _text, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setText(string _text);
        void setAligne(UIEaligne _aligne);
        UIEaligne getAligne();
        string getText();
        //TODO: setFont, setSize, setColor, setUnderline, setItallic, setBold
};

class uipage{
    protected:
        uielement* elist; //dynamic array  
        string name;
        unsigned int ecount; 
    public:    
        uipage(string _name); //constructor
        ~uipage(); //destructor
        void drawPage();
        unsigned int addUIElement(uielement _e);
        uielement getUIElement(int index);
        uielement getUIElement(string name);
};

class ui{
    protected:
        unsigned int x;
        unsigned int y;
        unsigned int pagecount; //counts the number of available ui pages
        unsigned int pagepos;
        uipage* pagelist;
    public:
        ui(U8G2 display, unsigned int _x, unsigned int _y, unsigned int _pagecount);
        ~ui();
        unsigned int addPage(uipage page);
        uipage getPage(unsigned int index);
        uipage getPage(string name);
        void displayPage(string name);
        void displayPage(unsigned int index);
        void updateUI(); //updates the display, should be called several times a second (30x for 30 FPS)
};