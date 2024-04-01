#include "uiPage.h"

uiPage::uiPage(): uiGroup(){

};

uiPage::~uiPage(){

};

void uiPage::setRoot(uiRoot* _root){
    root = _root;
}


void uiPage::receiveFocus(uiRoot* sender){
    //the focus comes from root
    switch(focus){
        case FocusState::parent:
            focus = FocusState::current;
            Slog("Page has Focus.")
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