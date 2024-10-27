#pragma once

#include "uiBasics.h"
#include "uiElement.h"
#include "uiPrebuilds.h"
#include "uiGraphics.h"
#include "uiText.h"

class uiBasicButton: public uiSelectableCollection, public uiText, public uiBox {
    protected:
        Padding padding;
        void drawThis(frameInfo* f) override;
    public:
        uiBasicButton(Dimensions* _dimensions, string _text);
        void receiveFocus(uiElement* sender) override;
};



