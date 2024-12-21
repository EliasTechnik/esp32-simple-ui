#pragma once

#include "uiBasics.h"
#include "uiRoot.h"
#include <vector>

#define DEFAULT_AUTOPRESS_DELAY 500
#define DEFAULT_AUTOPRESS_SPEED 5

/*
The code in here handles user input from hardware devices like buttons.

*/

enum class ButtonStates{down,up,};

class uiHardwareButton{
    private:
        uint8_t pin;
        UserAction action = UserAction::none;
        //unsigned long lastPress = 0;
        //unsigned long lastRelease= 0;
        unsigned long triggerAutopressAfter = 0;
        unsigned long triggerAutopressActionAfter = 0;
        unsigned long autopressDelay = DEFAULT_AUTOPRESS_DELAY;
        unsigned long autopressSpeed = DEFAULT_AUTOPRESS_SPEED;
        bool lastReadValue = true; 
        bool floatingValue; //the expected value when the button is not pressed
        ButtonStates state = ButtonStates::up;
        bool requestSatisfied = false;
    public:
        uiHardwareButton();
        uiHardwareButton(uint8_t _pin, UserAction _action, unsigned long _autopressSpeed = DEFAULT_AUTOPRESS_SPEED, unsigned long _autopressDelay = DEFAULT_AUTOPRESS_DELAY, bool _expectedFloatingValue = true);
        void trigger(); //this function should be called in an ISR it updates the values of the HardwarButton Object but does not run long. 
        ButtonStates getState();
        UserAction getAction();
        bool isSatisfied();
        bool isAutopressing();
        void satisfyRequest();
        void satisfyAutopressRequest();
};


class uiHardwareInputDriver{
    protected:
        std::vector<uiHardwareButton*> inputs;
        uiRoot* root;
    public:
        uiHardwareInputDriver(uiRoot* _uiRoot);
        void addInput(uiHardwareButton* input);
        void run(); //this has to be called frequently in order to process inputs correctly 

};