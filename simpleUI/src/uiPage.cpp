#include "uiPage.h"

uiPage::uiPage(): uiGroup(){

};

uiPage::~uiPage(){

};

void uiPage::setRoot(uiRoot* _root){
    root = _root;
}


int uiPage::getNextSelectableChildID(){
    int index = selectedChildID;
    index++;
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

void uiPage::receiveFocus(uiRoot* sender){
    //the focus comes from root
    switch(focus){
        case FocusState::parent: {
            focus = FocusState::current;
            int id = getNextSelectableChildID();
            if(id != -1){
                selectedChildID = id;
                uiElement* e = elements.at(selectedChildID);
                e->setSelected(SelectionState::showAsSelected);
            }else{
                //no selectable child
                Slog("no selectable child in uiPage")
                focus = FocusState::parent;
                root->receiveFocus();
            }
            Slog("Page has Focus.");
        break;
        }
        //TODO: Add the above code for the folowing cases. Otherwise the page might select non selectable elements if added afterwards
        case FocusState::current:
            focus = FocusState::child;
            elements.at(selectedChildID)->receiveFocus(this);
        break;
        case FocusState::child:
            elements.at(selectedChildID)->receiveFocus(this);
        break;
    }    
}

void uiPage::react(UserAction ua){
    //a uiPage can have the focus by it self. But it is not selectable.
    Slog("react");
    switch(focus){
        case FocusState::child:
            //we hand it down
            //get the child which has focus

            elements.at(selectedChildID)->react(ua);

            break;
        case FocusState::current:
            //we handle it
            switch (ua){
                case UserAction::backButton:
                    //the focus shifts back to parent
                    Slog("back");
                    if(root != nullptr){
                        focus = FocusState::parent;
                        root->receiveFocus();
                        //onLeave() 
                    }
                    break;
                case UserAction::enterButton:
                    Slog("enter element");
                    //child gets focus
                    if(child != nullptr){
                        focus = FocusState::child;
                        elements.at(selectedChildID)->setSelected(SelectionState::notSelected);
                        elements.at(selectedChildID)->receiveFocus(this);
                        //onLeave() ?   
                    }
                    break;
                case UserAction::leftButton:
                    //previous child gets selected 
                    Slog("next Element");
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
                    Slog("priv Element");
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

void uiPage::removeFocus(uiRoot* remover){
    if(focus != FocusState::child){
        elements.at(selectedChildID)->removeFocus(this);
    }
    if(focus == FocusState::current){
        elements.at(selectedChildID)->setSelected(SelectionState::notSelected);
    }
    focus = FocusState::parent;
}