#include "uiElement.h"

//uiElement
uiElement::uiElement() : dimensions(){
    visible = true;
};

uiElement::~uiElement(){
};

uiElement::uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible) : dimensions(_posX, _posY, _width, _height){
    visible = isVisible;
};

uiElement::uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isSelectable, bool isVisible) : dimensions(_posX, _posY, _width, _height){
    visible = isVisible;
    selectable = isSelectable;
};

void uiElement::setVisible(bool isVisible){
    visible = isVisible;
};

bool uiElement::getVisible(){
    return visible;
};

void uiElement::setSelected(SelectionState isSelected){
    selected = isSelected;
};

bool uiElement::getSelectable(){
    return selectable;
};

void uiElement::setSelectable(bool isSelectable){
    selectable = isSelectable;
};

SelectionState uiElement::getSelected(){
    return selected;
};

void uiElement::setParent(uiElement* _parent){
    parent = _parent;
};

uiElement* uiElement::getParent(){
    return parent;
};

void uiElement::setChild(uiElement* _child){
    child = _child;
};

uiElement* uiElement::getChild(){
    return child;
};

//void uiElement::draw(frameInfo *f){};

void uiElement::react(UserAction UA){
    switch(focus){
        case FocusState::child:
            //we hand it down
            if(child != nullptr){
                child->react(UA);
            }else{
                Slog("Error: FocusState is child but no child exists!");
            }
            break;
        case FocusState::current:
            //we handle it
            switch (UA){
                case UserAction::backButton:
                    //the focus shifts back to parent
                    if(parent != nullptr){
                        focus = FocusState::parent;
                        parent->receiveFocus(FocusDirection::fromChild);
                        //onLeave()
                    }
                    break;
                case UserAction::enterButton:
                    //child gets focus
                    if(child != nullptr){
                        focus = FocusState::child;
                        child->receiveFocus(FocusDirection::fromParent);
                        //onLeave() ?
                    }
                    break;
                default:
                    if(onInput.CB != nullptr)
                        onInput.CB;
                    break;
            }
            break;
        default:
            //this should not happen
            Slog("Error: reacted but Parent has focus!");
            break;
    }
};

void uiElement::receiveFocus(FocusDirection fd){
    //check if we even get the focus (if this element is selectable)
    if(selectable){
        focus = FocusState::current;
    }else{
        switch(fd){
            case FocusDirection::fromChild:
                parent->receiveFocus(fd);
            break;
            case FocusDirection::fromParent:
                child->receiveFocus(fd);
            break;
            default:
                //neighbours can only exist on the same plane. If we get the focus from one neighbour we might want to give it to our childs.
                child->receiveFocus(FocusDirection::fromParent);
        }
    }
    
};

FocusState uiElement::getFocusState(){
    return focus;
}

void uiElement::removeFocus(FocusDirection fd){
    //check if we even get the focus (if this element is selectable)
        switch(fd){
            case FocusDirection::fromChild:
                focus = FocusState::child; //unlikely
            break;
            case FocusDirection::fromParent:
                focus = FocusState::parent;
            break;
            default:
                //nothing
                Slog("removed focus in unknown direction!");
        }
    }
    