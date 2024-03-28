#pragma once
#include "uiBasics.h"
#include "uiGroup.h"


/*
A UI-Page is like a uiGroup but it covers the whole screen and only draws it child elements 
*/

class uiPage: public uiGroup{
    protected:
        
    public:    
        uiPage(); //constructor
        ~uiPage(); //destructor
};



