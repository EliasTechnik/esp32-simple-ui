#pragma once
#include "uiBasics.h"
#include "uiElement.h"

struct uiCallback{
    void (*CB)(void * context, void *trigger, UIEventType event_type);
    void * CBcontext;
};

/*uiInteractiveElement is the baseclass for all interactive UI-Elements*/
class uiInteractive{
    protected:
        tabPos tabPosition;
        bool focus; //true if element has focus (display inverted)
        uiCallback CBonEvent; 
    public:
        uiInteractive();
        void setCB(uiCallback _CBonEvent);
        void triggerUIaction(UIEventType triggerType);
        void setFocus(bool _focus = true);
};