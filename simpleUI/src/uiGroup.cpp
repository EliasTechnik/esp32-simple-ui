#include "uiGroup.h"

uiGroup::uiGroup():uiBaseElement(){
    selectionMode = SelectionMode::selectable;
    focusMode = FocusMode::target;
    //elements = new dList<uiElement>(2);
};

uiGroup::uiGroup(unsigned int expectedElements):uiBaseElement(){
    selectionMode = SelectionMode::selectable;
    focusMode = FocusMode::target;
    //elements = new dList<uiElement>(expectedElements);
    //elements = vector<uiElement>(expectedElements,nullptr);
}

uiGroup::uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height): uiBaseElement(_posX, _posY, width, height, SelectionMode::selectable){
    //elements = new dList<uiElement>(2);
}

uiGroup::uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible): uiBaseElement(_posX, _posY, width, height, SelectionMode::selectable, isVisible){
    //elements = new dList<uiElement>(2);
}

uiGroup::uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, unsigned int expectedElements, bool isVisible): uiElement(_posX, _posY, width, height, SelectionMode::selectable, isVisible){
    //elements = new dList<uiElement>(expectedElements);
}

uiGroup::~uiGroup(){
    //delete elements; //free up memory
    //TODO: delete elements
}

void uiGroup::addElement(uiElement* _element){
    //elements->addItem(*_element);
    _element->setParent(this);
    elements.push_back(_element);

}

void uiGroup::draw(frameInfo* f){
    //f->display->drawCircle(0,0,5);

    for (uiElement* e : elements){
        //Slog("draw");
        e->draw(f);
    }
}

void uiGroup::react(UserAction UA){
    int id = -2;
    switch(focus){
        case FocusState::child:{
            //we hand it down
            //get the child which has focus
            Slog("group: push react to child")
            elements.at(selectedChildID)->react(UA);

            break;
        }
        case FocusState::current:{
            //we handle it
            switch (UA){
                case UserAction::backButton:{
                    //the focus shifts back to parent
                    if(parent != nullptr){
                        focus = FocusState::parent;
                        elements.at(selectedChildID)->setSelected(SelectionState::notSelected);
                        parent->receiveFocus(this);
                        //onLeave() 
                    }
                    break;
                }
                case UserAction::enterButton:{
                    //child gets focus
                    Slog("group: push focus to child")
                    focus = FocusState::child;
                    elements.at(selectedChildID)->setSelected(SelectionState::notSelected); //remove selection. this is now the problem of the child
                    elements.at(selectedChildID)->receiveFocus(this);
                    //onLeave() ?   
                    
                    break;
                }
                case UserAction::leftButton:{
                    //previous child gets selected 
                    Slog("group: sel priv child")
                    id = getPriviousSelectableChildID();

                    if(id == -1){
                        Slog("err: No selectable child found.")
                    }else{
                        //remove selection from old child
                        elements.at(selectedChildID)->setSelected(SelectionState::notSelected);
                        selectedChildID = id;
                        elements.at(selectedChildID)->setSelected(SelectionState::showAsSelected);
                    }
                    
                    break;
                }
                case UserAction::rightButton:{
                    //next child gets selected 
                    Slog("group: sel next child")
                    id = getNextSelectableChildID();

                    if(id == -1){
                        Slog("err: No selectable child found.")
                    }else{
                        //remove selection from old child
                        elements.at(selectedChildID)->setSelected(SelectionState::notSelected);
                        selectedChildID = id;
                        elements.at(selectedChildID)->setSelected(SelectionState::showAsSelected);
                    }
                    break;
                }
                default:{
                    if(onInput.CB != nullptr)
                        onInput.CB;
                    break;
                }
            }
            break;
        }
        default:{
            //this should not happen
            Slog("err: reacted but Parent has focus!");
            break;
        }
    }
}

void uiGroup::removeFocus(uiElement* remover){
    if(remover == parent){
        if(focus != FocusState::current){
            elements.at(selectedChildID)->removeFocus(this);
        }
        focus = FocusState::parent;
    }
}


int uiGroup::getNextSelectableChildID(){
    int index = selectedChildID;
    index++;
    if(index>=elements.size()){
            index = 0;
    }
    uiElement* e;
    do{
        e = elements.at(index);
        if(e != nullptr){
            if(e->getSelectable()){
                return index;
            }else{
                index++;
            }
        }else{
            index++;
        }
        if(index>=elements.size()){
            index = 0;
        }
    }while(index != selectedChildID);

    return -1;
}

int uiGroup::getPriviousSelectableChildID(){
    int index = selectedChildID;
    index--;
    if(index<0){
        index = elements.size()-1;
    }
    uiElement* e;
    do{
        e = elements.at(index);
        if(e != nullptr){
            if(e->getSelectable()){
                return index;
            }else{
                index--;
            }
        }else{
            index--;
        }
        if(index<0){
            index = elements.size()-1;
        }
    }while(index != selectedChildID);

    return -1;
}