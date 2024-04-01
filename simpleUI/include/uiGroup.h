#pragma once
#include "uiBasics.h"
#include "uiElement.h"
#include "dList.h"
#include <vector>

/*
A uiGroup is a group of uiElements. Elements which are part of the group get drawn fro back to front (in the order they where added).
A uiGroup supports also navigation between elements.

A uiGroup can have the focus by it self. But it is not selectable. Instead it choses sets the first selectable child as selected but reacts to UA until one child is in focus
*/

class uiGroup: public uiElement{
    protected:
        std::vector<uiElement*> elements;
        unsigned int selectedChildID = 0;
    public:
        uiGroup();
        uiGroup(unsigned int expectedElements); //if the number of elements is known this constructor can save memory and prevent fragmentation
        uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height);
        uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible);
        uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, unsigned int expectedElements, bool isVisible);
        ~uiGroup();
        void addElement(uiElement* _element);
        void draw(frameInfo* f) override;
        void react(UserAction UA);
        void removeFocus(uiElement* remover);
        void receiveFocus(uiElement* sender);
};