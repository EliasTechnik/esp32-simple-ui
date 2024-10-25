#include "uiElement.h"

//uiBaseElement
uiBaseElement::uiBaseElement() : dimensions(){
    visible = true;
};

uiBaseElement::~uiBaseElement(){
};

uiBaseElement::uiBaseElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode) : dimensions(_posX, _posY, _width, _height){
    selectionMode = _selectionMode;
};

uiBaseElement::uiBaseElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode, bool isVisible) : dimensions(_posX, _posY, _width, _height){
    visible = isVisible;
    selectionMode = _selectionMode;
};

void uiBaseElement::setVisible(bool isVisible){
    visible = isVisible;
};

bool uiBaseElement::getVisible(){
    return visible;
};

void uiBaseElement::setSelected(SelectionState isSelected){
    switch(selectionMode){
        case SelectionMode::selectable:
            selected = isSelected;
        break;
        case SelectionMode::passthroughSelection:
            if(child != nullptr){
                child->setSelected(isSelected);
            }
        break;
        case SelectionMode::forwardSelection:
            selected = isSelected;
            if(child != nullptr){
                child->setSelected(isSelected);
            }
        break;
        case SelectionMode::notSelectable:
            selected = SelectionState::notSelected;
        break;
    }

    selected = isSelected;
};

bool uiBaseElement::getSelectable(){
    if(selectionMode == SelectionMode::notSelectable){
        Slog("notSelectable")
        return false;
    }else{
        Slog("selectable")
        return true;
    }
};

void uiBaseElement::setSelectionMode(SelectionMode _selectionMode){
    selectionMode = _selectionMode;
};

SelectionState uiBaseElement::getSelected(){
    return selected;
};

FocusState uiBaseElement::getFocusState(){
    return focus;
}

void uiBaseElement::setFocusMode(FocusMode _mode){
    focusMode = _mode;
}

FocusMode uiBaseElement::getFocusMode(){
    return focusMode;
}

SelectionMode uiBaseElement::getSelectionMode(){
    return selectionMode;
}

void uiBaseElement::setID(String _id){
    id = _id;
}

/*
#################################################################
        uiElement
################################################################
*/

//uiElement
uiElement::uiElement() : uiBaseElement(){
    visible = true;
};

uiElement::~uiElement(){
};

uiElement::uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode):
 uiBaseElement(_posX, _posY, _width, _height){
    selectionMode = _selectionMode;
};

uiElement::uiElement(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, SelectionMode _selectionMode, bool isVisible):
 uiBaseElement(_posX, _posY, _width, _height){
    visible = isVisible;
    selectionMode = _selectionMode;
};

void uiElement::react(UserAction UA){
    S_log("react",id);
    switch(focus){
        case FocusState::child:
            //we hand it down
            if(child != nullptr){
                S_log("hand down",id);
                child->react(UA);
            }else{
                Slog("err: FocusState is child but no child exists!");
            }
            break;
        case FocusState::current:
            //we handle it
            S_log("i have to react",id);
            switch (UA){
                case UserAction::backButton:
                    //the focus shifts back to parent
                    if(parent != nullptr){
                        focus = FocusState::parent;
                        if(parent != nullptr){
                            parent->receiveFocus(this);
                        }else{
                            Slog("err: element is orphan!");
                        }
                        
                        //onLeave()
                    }
                    break;
                case UserAction::enterButton:
                    //child gets focus
                    if(child != nullptr){
                        focus = FocusState::child;
                        child->receiveFocus(this);
                        //onLeave() ?
                    }else{
                        //onEnter()
                    }
                    break;
                default:
                    if(onInput.CB != nullptr){
                         onInput.CB;
                    }
                    break;
            }
            break;
        default:
            //this should not happen
            Slog("err: reacted but Parent has focus!");
            break;
    }
};

void uiElement::receiveFocus(uiElement* sender){
    S_log("received focus",id)
    //check the focus mode
    switch(focusMode){
        case FocusMode::target:
            //check the direction
            switch(focus){
                case FocusState::child:
                    Slog("has focus, came from child")
                    focus = FocusState::current;
                    child = sender;
                    break;
                case FocusState::current:
                    //this should not happen
                    Slog("err: Received focus but already had it.")
                    break;
                case FocusState::parent:
                     Slog("has focus, came from parent")
                     focus = FocusState::current;
                     parent = sender;
                     break;
            }
            break;
        case FocusMode::passthrough:
            //check the direction
            switch(focus){
                case FocusState::child:
                    focus = FocusState::parent;
                    parent->receiveFocus(this);
                    child = sender;
                    break;
                case FocusState::current:
                    //this should not happen
                    Slog("err: Received focus but already had it. Passthrough enabled but direction unknown. Defaulting to parent")
                    parent->receiveFocus(this);
                    break;
                case FocusState::parent:
                    if(child != nullptr){
                        focus = FocusState::child;
                        child->receiveFocus(this);
                        parent = sender;
                    }else{
                        focus = FocusState::parent;
                        parent = sender;
                        parent->receiveFocus(this);
                    }
                    break;
                }
            break;
        case FocusMode::passive:
            Slog("err: Received focus but this element is passive.")
            parent = sender;
            parent->receiveFocus(this);
            break;
    }    
};


void uiElement::removeFocus(uiElement* remover){
    if(remover == parent){
        if(focus != FocusState::current){
            if(child != nullptr){
                child->removeFocus(this);
            }
        }
        focus = FocusState::parent;
    }
    //the child can not remove the focus!
}

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