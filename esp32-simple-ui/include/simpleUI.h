#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

class dimensions{
    protected:
        unsigned int pos_x;
        unsigned int pos_y;
        unsigned int width;
        unsigned int height;
    public:
        dimensions(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _hight);
        unsigned int getX();
        unsigned int getY();
        unsigned int getWidth();
        unsigned int getHeight();
};

class uielement : dimensions{
    protected:
        bool visible;
        U8G2 display;
    public:
        uielement(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _hight, bool isVisible = true);
        void setVisible(bool isVisible);
        bool getVisible();
        void setDisplay(U8G2 _display);
        void draw(); //should be overwritten by every child class which inherrits from uielement
};

class icon : uielement{
    private:
        unsigned char* bitmap; 
    public:
        icon(unsigned char* _bitmap, unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _hight, bool isVisible = true);
        unsigned char* getBitmap();
        
};

class uipage{
    private:

    public:    
};

class ui{
    private:
        unsigned int x;
        unsigned int y;
        unsigned int pagecount; //counts the number of available ui pages

    public:
        void init(U8G2 display, unsigned int _x, unsigned int _y, unsigned int _pagecount);
};