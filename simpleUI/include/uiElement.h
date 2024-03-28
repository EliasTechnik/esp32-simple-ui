#pragma once
#include "uiBasics.h"
#include "helper.h"

/*uielement is one baseclass for every ui element. It handles attributes common for all ui elements.

uiElements are linked in a tree like structure. Every element can have a parent or a child element.

*/

class uiElement : public dimensions{
    protected:
        bool visible;
        SelectionState selected = SelectionState::notSelected;
        bool selectable;
        FocusState focus = FocusState::parent;
        uiElement* parent = nullptr;
        uiElement* child = nullptr;
        //uiCallback onEnter;
        //uiCallback onLeave;
        uiCallback onInput; //gets called on eny input apart from enter or leave
    public:
        uiElement();
        ~uiElement();
        uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isSelectable = false);
        uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isSelectable, bool isVisible);
        void setVisible(bool isVisible);
        bool getVisible();
        void setSelected(SelectionState isSelected);
        SelectionState getSelected();
        void setSelectable(bool isSelectable);
        bool getSelectable();
        void setParent(uiElement* _parent);
        uiElement* getParent();
        void setChild(uiElement* _child);
        uiElement* getChild();
        virtual void draw(frameInfo* f) = 0; //should be overwritten by every child class which inherrits from uielement
        void react(UserAction UA);
        void receiveFocus(FocusDirection fd);
        FocusState getFocusState();
        void removeFocus(FocusDirection fd);
};