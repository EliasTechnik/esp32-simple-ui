#include "uiGroup.h"

uiGroup::uiGroup():uiElement(){
    //elements = new dList<uiElement>(2);
};

uiGroup::uiGroup(unsigned int expectedElements):uiElement(){
    //elements = new dList<uiElement>(expectedElements);
    //elements = vector<uiElement>(expectedElements,nullptr);
}

uiGroup::uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height): uiElement(_posX, _posY, width, height, false){
    //elements = new dList<uiElement>(2);
}

uiGroup::uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible): uiElement(_posX, _posY, width, height, false, isVisible){
    //elements = new dList<uiElement>(2);
}

uiGroup::uiGroup(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, unsigned int expectedElements, bool isVisible): uiElement(_posX, _posY, width, height, false, isVisible){
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
    //a uiGroup can not have the focus by it self. It is also not selectable.
    switch(focus){
        case FocusState::child:
            //we hand it down
            //get the child which has focus

            elements.at(selectedChildID)->react(UA);

            break;
        case FocusState::current:
            //we handle it
            switch (UA){
                case UserAction::backButton:
                    //the focus shifts back to parent
                    if(parent != nullptr){
                        focus = FocusState::parent;
                        elements.at(selectedChildID)->setSelected(SelectionState::notSelected);
                        parent->receiveFocus(this);
                        //onLeave() 
                    }
                    break;
                case UserAction::enterButton:
                    //child gets focus
                    
                    focus = FocusState::child;
                    elements.at(selectedChildID)->receiveFocus(this);
                    //onLeave() ?   
                    
                    break;
                case UserAction::leftButton:
                    //previous child gets selected 

                    //remove selection from old child
                    elements.at(selectedChildID)->setSelected(SelectionState::notSelected);

                    if(selectedChildID == 0){
                        selectedChildID = elements.size()-1;
                    }else{
                        selectedChildID--;
                    }

                    elements.at(selectedChildID)->setSelected(SelectionState::showAsSelected);
                    break;
                case UserAction::rightButton:
                    //next child gets selected 

                    //remove selection from old child
                    elements.at(selectedChildID)->setSelected(SelectionState::notSelected);

                    if(selectedChildID == elements.size()-1){
                        selectedChildID = 0;
                    }else{
                        selectedChildID++;
                    }

                    elements.at(selectedChildID)->setSelected(SelectionState::showAsSelected);
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
}

void uiGroup::removeFocus(uiElement* remover){
    if(remover == parent){
        if(focus != FocusState::current){
            elements.at(selectedChildID)->removeFocus(this);
        }
        focus = FocusState::parent;
    }
}

void uiGroup::receiveFocus(uiElement* sender){
    //the focus comes from parent
    switch(focus){
        case FocusState::parent:
            focus = FocusState::current;
            Slog("Group has Focus.")
        break;
        case FocusState::current:
            focus = FocusState::child;
            elements.at(selectedChildID)->receiveFocus(this);
        break;
        case FocusState::child:
            elements.at(selectedChildID)->receiveFocus(this);
        break;
    }
}