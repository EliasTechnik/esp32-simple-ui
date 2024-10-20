#pragma once
#include "uiBasics.h"
#include "uiGroup.h"
#include "uiRoot.h"


/*
A UI-Page is like a uiGroup but it covers the whole screen and only draws it child elements 
*/

class uiRoot;

class uiPage: public uiGroup{
    protected:
        uiRoot* root;
        int getNextSelectableChildID();
    public:    
        uiPage(); //constructor
        ~uiPage(); //destructor
        void setRoot(uiRoot* _root);
        //void receiveFocus(uiElement* sender);
        void receiveFocus(uiRoot* sender);
        void removeFocus(uiRoot* remover);
        void react(UserAction ua);
};



