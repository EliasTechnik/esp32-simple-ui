#include "uiInputs.h"

/*
##########################################################
                    uiIntValueInput
##########################################################
*/



uiIntValueInput::uiIntValueInput(Position _position, int _value, int _max, int _min, uiNotifyCallback _onChange, Padding _padding){
    visible = true;
    id = "uiIntValueInput";
    selectionMode = SelectionMode::selectable;
    focusMode = FocusMode::collection;
    padding = _padding;
    position = _position;
    if(_max >= _min){
        maxValue = _max;
        minValue = _min;
    }else{
        maxValue = _min;
        minValue = _max;
    }
    this->setValue(_value);
    
    onChange = _onChange;
    this->setTextType(number);
    this->setText(to_string(value));
}

int uiIntValueInput::getLongestValue(){
    if(minValue < 0 && maxValue < 0){
        return minValue; //the lowest number is probably the longest
    }
    if(minValue > 0 && maxValue > 0){
        return maxValue; //the highest number si probably the longest
    }
    if(minValue < 0 && maxValue > 0){
        int a = abs(minValue);
        if(maxValue < a){
            return minValue;
        }else{
            return maxValue*-1;
        }
    }
}


int uiIntValueInput::getValue(){
    return value;
}

int uiIntValueInput::setValue(int _value){
    if(minValue <= _value <= maxValue){
        value = _value;
    }else{
        if(_value>maxValue){
            value = maxValue;
        }else{
            value = minValue;
        }
    }
    return value;
}

int uiIntValueInput::increaseBy(int a, bool allowRollover){
    if(allowRollover){
        //TODO
        
    }else{
        //TODO
    }
}

int uiIntValueInput::decreaseBy(int a, bool allowRollover){
    if(allowRollover){
        //TODO
        
    }else{
        //TODO
    }
}



void uiIntValueInput::drawThis(frameInfo* f){
    //S_log("draw",id);
    Sizing s;
    if(keepMaxWidth){
        s = getTextSizing(f,to_string(getLongestValue()));
    }else{
        s = getTextSizing(f);
    }
    switch(selected){
        case SelectionState::notSelected:
            //S_log("draw not selected",id)
            drawFrame(
                f,
                uiVisualTransformation(false,false),
                padding.getOuter(Dimension(position, s))
            );
            
            drawText(
                f,
                uiVisualTransformation(false,false),
                position
            );

        break;
        default:
            //S_log("draw selected",id);
            if(focus == FocusState::current){
                drawBox(
                    f,
                    uiVisualTransformation(false,false),
                    padding.getOuter(Dimension(position, s))
                );
                drawText(
                    f,
                    uiVisualTransformation(true,true),
                    position
                );
            }else{
                if(f->highlightSelected){
                    drawBox(
                        f,
                        uiVisualTransformation(false,false),
                        padding.getOuter(Dimension(position, s))
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
                        padding.getOuter(Dimension(position, s))
                    );
                    drawText(
                        f,
                        uiVisualTransformation(false,false),
                        position
                    );
                }
            }
            
    }
}

void uiIntValueInput::react(UserAction UA){
    S_log("react",id);
    int cid = -2;
    switch(focus){
        case FocusState::current:
            //we handle it
            S_log("i have to react",id);
            switch (UA){
                case UserAction::backButton:
                    S_log("back pressed",id);
                    //the focus shifts back to parent
                    if(parent != nullptr){
                        focus = FocusState::parent;
                         S_log("back to parent",id);
                        selectFocusReceiverMethod(parent);
                    }else{
                            Slog("err: element is orphan! (has no parent)");
                        }
                    break;
                case UserAction::leftButton:{
                    //increase
                    if(value<maxValue){
                        value++;
                    }else{
                        value = minValue;
                    }
                    this->setText(to_string(value));
                    SaveCallback(onChange,onChange(this));
                    break;
                }
                case UserAction::rightButton:{
                    //decrese
                    if(value>minValue){
                        value--;
                    }else{
                        value = maxValue;
                    }
                    this->setText(to_string(value));
                    SaveCallback(onChange,onChange(this));
                    break;
                }
                default:
                    S_log("default",id);
                    SaveCallback(onUnassignedInput,onUnassignedInput(this,getUIEventTypeFromUserAction(UA)));
                    break;
            }
            break;
        default:
            //this should not happen
            S_log("err: reacted but Parent has focus!",id)
            break;
    };
};