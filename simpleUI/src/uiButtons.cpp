#include "uiButtons.h"

uiBasicButton::uiBasicButton(Position _position, string _text, uiEventCallback _onRcvFocus, Padding _padding){
    visible = true;
    id = "uiBasicButton";
    selectionMode = SelectionMode::selectable;
    focusMode = FocusMode::collection;
    padding = _padding;
    position = _position;
    text = _text;
    onRcvFocus = _onRcvFocus;
}

void uiBasicButton::receiveFocus(uiElement* sender){
    S_log("bounce focus",id)
    sender->receiveFocus(this);
    onRcvFocus(this, UIEventType::UIET_onBounce);
}


void uiBasicButton::drawThis(frameInfo* f){
    //S_log("draw",id);
    switch(selected){
        case SelectionState::notSelected:
            //S_log("draw not selected",id)
            drawFrame(
                f,
                uiVisualTransformation(false,false),
                padding.getOuter(Dimension(position, getTextSizing(f)))
            );
            
            drawText(
                f,
                uiVisualTransformation(false,false),
                position
            );

        break;
        default:
            //S_log("draw selected",id);
            if(f->highlightSelected){
                drawBox(
                    f,
                    uiVisualTransformation(false,false),
                    padding.getOuter(Dimension(position, getTextSizing(f)))
                );
                drawText(
                    f,
                    uiVisualTransformation(true,true),
                    position
                );
            }else{
                drawFrame(
                    f,
                    uiVisualTransformation(false,false),
                    padding.getOuter(Dimension(position, getTextSizing(f)))
                );
                drawText(
                    f,
                    uiVisualTransformation(false,false),
                    position
                );
            }
            

    }
}

/*
##########################################################
                    uiFixedButton
##########################################################
*/

uiFixedButton::uiFixedButton(Dimension _dimension, string _text, Padding _padding){
    visible = true;
    id = "uiFixedButton";
    selectionMode = SelectionMode::selectable;
    focusMode = FocusMode::collection;
    padding = _padding;
    dimension = _dimension;
    text = _text;
}

void uiFixedButton::receiveFocus(uiElement* sender){

}


void uiFixedButton::drawThis(frameInfo* f){
    //S_log("drawFixed",id);
    switch(selected){
        case SelectionState::notSelected:
            //S_log("draw not selected",id)
            drawFrame(
                f,
                uiVisualTransformation(false,false),
                dimension
            );
            drawText(
                f,
                uiVisualTransformation(false,false),
                dimension.getPosition()
            );

        break;
        default:
            //S_log("draw selected",id);
            if(f->highlightSelected){
                drawBox(
                    f,
                    uiVisualTransformation(false,false),
                    dimension
                );
                drawText(
                    f,
                    uiVisualTransformation(true,true),
                    dimension.getPosition()
                );
            }else{
                drawFrame(
                    f,
                    uiVisualTransformation(false,false),
                    dimension
                );
                drawText(
                    f,
                    uiVisualTransformation(false,false),
                    dimension.getPosition()
                );
            }
            

    }
}