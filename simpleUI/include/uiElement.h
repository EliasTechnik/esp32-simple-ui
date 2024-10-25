#pragma once
#include "uiBasics.h"
#include "helper.h"

/*uielement is one baseclass for every ui element. It handles attributes common for all ui elements.

uiElements are linked in a tree like structure. Every element can have a parent or a child element.

*/


class uiBaseElement : public dimensions{
    protected:
        bool visible = true;
        String id = "";
        SelectionState selected = SelectionState::notSelected;
        SelectionMode selectionMode = SelectionMode::notSelectable;
        FocusMode focusMode = FocusMode::passive;
        FocusState focus = FocusState::parent;
        uiElement* parent = nullptr;
        uiElement* child = nullptr;
        //uiCallback onEnter;
        //uiCallback onLeave;
        uiCallback onInput; //gets called on any input apart from enter or leave
    public:
        uiBaseElement();
        ~uiBaseElement();
        uiBaseElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode = SelectionMode::notSelectable);
        uiBaseElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode, bool isVisible);
        void setVisible(bool isVisible);
        bool getVisible();
        void setSelected(SelectionState isSelected);
        SelectionState getSelected();
        void setSelectionMode(SelectionMode _selectionMode);
        SelectionMode getSelectionMode();
        bool getSelectable();
        void setFocusMode(FocusMode _mode);
        FocusMode getFocusMode();
        virtual void setParent(uiElement* _parent);
        virtual uiElement* getParent();
        virtual void setChild(uiElement* _child);
        virtual uiElement* getChild();
        virtual void draw(frameInfo* f) = 0; //should be overwritten by every child class which inherrits from uielement
        virtual void react(UserAction UA);
        virtual void receiveFocus(uiElement* sender);
        FocusState getFocusState();
        virtual void removeFocus(uiElement* remover);
        void setID(String _id);
};


class uiElement : public uiBaseElement{
    protected:
        
    public:
        uiElement();
        ~uiElement();
        uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode = SelectionMode::notSelectable);
        uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode, bool isVisible);
        virtual void draw(frameInfo* f) = 0; //should be overwritten by every child class which inherrits from uielement
        void react(UserAction UA) override;
        void removeFocus(uiElement* remover) override;
        void receiveFocus(uiElement* sender) override;
        void setParent(uiElement* _parent);
        uiElement* getParent();
        void setChild(uiElement* _child);
        uiElement* getChild();
};