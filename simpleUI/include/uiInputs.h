#pragma once

#include "uiBasics.h"
#include "uiElement.h"
#include "uiPrebuilds.h"
#include "uiText.h"
#include "uiGraphics.h"

class uiIntValueInput: public uiText, public uiBox, public uiFrame, public uiSelectableCollection{
    protected:
        Padding padding = UI_DEFAULT_PADDING_2a;
        Position position;
        int maxValue = 100; //inclusive
        int minValue = 0; //inclusive
        int value = 42;
        bool keepMaxWidth = true;
        void drawThis(frameInfo* f) override;
        int getLongestValue();
        uiNotifyCallback onChange = nullptr;
    public:
        uiIntValueInput(Position _position, int _value, int _max, int _min, uiNotifyCallback _onChange, Padding _padding = UI_DEFAULT_PADDING_2a);
        void setKeepMaxWidth(bool keep); //if set to true (default) the input doesnt shrink when displaying lower numbers than _max.
        int getValue();
        int setValue(int _value); //will set the value if it is within range. If its out of range the min/max value will be used. 
        int increaseBy(int a, bool allowRollover = true);
        int decreaseBy(int a, bool allowRollover = true);
        void react(UserAction UA) override;
};