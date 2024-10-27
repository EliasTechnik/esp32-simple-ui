#include "uiButtons.h"

uiBasicButton::uiBasicButton(Dimensions* _dimensions, string _text){
    visible = true;
    id = "uiBasicButton";
    selectionMode = SelectionMode::selectable;
    focusMode = FocusMode::collection;
    padding = Padding();
}

void uiBasicButton::receiveFocus(uiElement* sender){

}


void uiBasicButton::drawThis(frameInfo* f){
    switch(selected){
        case SelectionState::notSelected:
            drawBox(
                f,
                new uiVisualTransformation(true,true),
                new Dimensions getTextSizing(f).toDimensions(this)
            )

        break;
        default:

    }
}