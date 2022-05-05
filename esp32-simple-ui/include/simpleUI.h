#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <string>

using namespace std; //to use string

class dimensions{
    protected:
        unsigned int pos_x;
        unsigned int pos_y;
        unsigned int width;
        unsigned int height;
    public:
        dimensions(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height);
        unsigned int getX();
        unsigned int getY();
        unsigned int getWidth();
        unsigned int getHeight();
};

class uielement : dimensions{
    protected:
        bool visible;
        U8G2 display;
        string name;
    public:
        uielement(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
        void setVisible(bool isVisible);
        bool getVisible();
        void setDisplay(U8G2 _display);
        void setName(string _name);
        void draw(); //should be overwritten by every child class which inherrits from uielement
};

class icon : uielement{
    private:
        unsigned char* bitmap; 
    public:
        icon(unsigned char* _bitmap, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);
        unsigned char* getBitmap();      
};

class label : uielement{
    private:
        string text;
    public:
        label(string _text, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true);

};

class uipage{
    private:
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
    private:
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
};