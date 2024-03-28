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

            elements[childIDwithPreFocus]->react(UA);

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
                        elements[childIDwithPreFocus]->receiveFocus(FocusDirection::fromParent);
                        //onLeave() ?   
                    }
                    break;
                case UserAction::leftButton:
                    //previous child gets selected 

                    //remove selection from old child
                    elements[childIDwithPreFocus]->setSelected(SelectionState::notSelected);

                    if(childIDwithPreFocus == 0){
                        childIDwithPreFocus = elements.size()-1;
                    }else{
                        childIDwithPreFocus--;
                    }

                    elements[childIDwithPreFocus]->setSelected(SelectionState::showAsSelected);
                    break;
                case UserAction::rightButton:
                    //next child gets selected 

                    //remove selection from old child
                    elements[childIDwithPreFocus]->setSelected(SelectionState::notSelected);

                    if(childIDwithPreFocus == elements.size()-1){
                        childIDwithPreFocus = 0;
                    }else{
                        childIDwithPreFocus++;
                    }

                    elements[childIDwithPreFocus]->setSelected(SelectionState::showAsSelected);
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