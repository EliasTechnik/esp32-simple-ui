#pragma once
#include "uiBasics.h"
#include "uiInteractive.h"


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