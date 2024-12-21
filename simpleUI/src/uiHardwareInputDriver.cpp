#include "uiHardwareInputDriver.h"

//HardwareButton

uiHardwareButton::uiHardwareButton(){
    action = UserAction::none;
    //lastPress = 0;
    //lastRelease= 0;
    floatingValue = true;
    lastReadValue = floatingValue;
    state = ButtonStates::up;
    autopressDelay = DEFAULT_AUTOPRESS_DELAY;
    triggerAutopressAfter = 0;
    triggerAutopressActionAfter = 0;
    requestSatisfied = true;
}

uiHardwareButton::uiHardwareButton(uint8_t _pin, UserAction _action, unsigned long _autopressSpeed, unsigned long _autopressDelay, bool _expectedFloatingValue){
    pin = _pin;
    action = _action;
    //lastPress = 0;
    //lastRelease= 0;
    floatingValue = _expectedFloatingValue;
    lastReadValue = floatingValue;
    state = ButtonStates::up;
    autopressSpeed = _autopressSpeed;
    autopressDelay = _autopressDelay;
    triggerAutopressAfter = 0;
    triggerAutopressActionAfter = 0;
    requestSatisfied = true;
}

void uiHardwareButton::trigger(){
    //check previous state
    bool v=digitalRead(pin);
    if(lastReadValue==!floatingValue && v==floatingValue){
        //released
        state=ButtonStates::up;
        requestSatisfied=true; 
    }
    if(lastReadValue==floatingValue && v==!floatingValue){
        //pressed
        state=ButtonStates::down;
        requestSatisfied=false;
        /*
        UA.action=UserAction::backButton;
        UA.present=true; 
        UA.executed=false;
        */
        triggerAutopressAfter=millis()+autopressDelay;
    }
    lastReadValue=v;
}

ButtonStates uiHardwareButton::getState(){
    return state;
}

UserAction uiHardwareButton::getAction(){
    return action;
}

bool uiHardwareButton::isAutopressing(){
    if(triggerAutopressAfter<millis() && state == ButtonStates::down){
        if(triggerAutopressAfter<millis()){
            return true;
        }{
            return false;
        }
    }else{
        return false;
    }
}

void uiHardwareButton::satisfyAutopressRequest(){
    triggerAutopressActionAfter = millis()+autopressSpeed;
}

bool uiHardwareButton::isSatisfied(){
    return requestSatisfied;
}

void uiHardwareButton::satisfyRequest(){
    requestSatisfied = true;
}


//uiHardwareInputDriver
uiHardwareInputDriver::uiHardwareInputDriver(uiRoot* _uiRoot){
    root = _uiRoot;
}

void uiHardwareInputDriver::addInput(uiHardwareButton* input){
    inputs.push_back(input);
}

void uiHardwareInputDriver::run(){
    for(uiHardwareButton* input : inputs){
        if(!input->isSatisfied()){
            root->react(input->getAction());
            input->satisfyRequest();
        }
        if(input->isAutopressing()){
            root->react(input->getAction());
            input->satisfyAutopressRequest();
        }
    }
}
