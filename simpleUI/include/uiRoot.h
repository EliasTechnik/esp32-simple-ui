#pragma once
#include "uiBasics.h"
#include "uiPage.h"
#include "uiElement.h"
#include <vector>

/*
The uiRoot is the entry point for the ui. It defines the states at startup and handles inputs
*/

class uiRoot{
    protected:
        frameInfo lastFrameInfo;
        std::vector<uiPage*> pages;
        unsigned int currentPage = 0;
        DisplayConfig config;
        unsigned long nextDisplayFrame = 0;
        unsigned long lastInputTime = 0;
        unsigned long screenOnTime = 0;
        unsigned long lastDisplayFlash = 0;
        ScreenState globalDisplayState = ScreenState::on;
        void init();
        void FlushDisplay(frameInfo* fi);
        void drawUI(frameInfo* fi);
        void screenSwitch(ScreenState state);
        void energyManager();
    public:
        uiRoot();
        uiRoot(DisplayConfig _config);
        ~uiRoot();
        void addPage(uiPage* page);
        bool goToPage(uiPage* page);
        bool goToElement(uiElement* element);
        void display(); //should be called every time in the loop()
        void react(UserAction UA);
        void setConfig(DisplayConfig _config);
        ScreenState getScreenState();
        void wakeUpScreen();
};

