#include "uiRoot.h"

uiRoot::uiRoot(){

};

uiRoot::uiRoot(DisplayConfig _config){
    config = _config;
    init();
};

uiRoot::~uiRoot(){

}

void uiRoot::addPage(uiPage* page){
    Slog("addPage");
    pages.push_back(page);
    page->setRoot(this);

    if(pages.size() == 1){
        uiPage* e = pages.front();

        if(e == nullptr){
            Slog("nullptr");
        }
        e->receiveFocus(this);
    }
    
}

void uiRoot::display(){ 
    energyManager(); //takes care of about the sleep

    //Slog("display");

    frameInfo fi;
    fi = lastFrameInfo;
    
    fi.display->clearBuffer();

    FlushDisplay(&fi);
    //Slog("display end");
}

bool uiRoot::goToPage(uiPage* page){
    //todo
}

bool uiRoot::goToElement(uiElement* element){
    //todo
}

void uiRoot::react(UserAction UA){
    Slog("react");
    //reset display time
    screenOnTime=millis()+ config.screenSleepTime;
    if(globalDisplayState == ScreenState::off){
        screenSwitch(ScreenState::on);
    }else{
        if(this->focus == FocusState::current){
            switch (UA){
                case UserAction::leftButton:
                    Slog("left");
                    if(currentPage == 0){
                        currentPage = pages.size()-1;
                    }else{
                        currentPage--;
                    }
                    break;
                case UserAction::rightButton:
                    Slog("right");
                    if(currentPage == pages.size()-1){
                        currentPage = 0;
                    }else{
                        currentPage++;
                    }
                    break;
                case UserAction::enterButton:
                    Slog("enter");
                    //remove selection from old child
                    pages.at(currentPage)->removeFocus(this);
                    Slog("removeFocus");
                    if(currentPage == pages.size()-1){
                        currentPage = 0;
                    }else{
                        currentPage++;
                    }

                    focus = FocusState::child;

                    Slog("receiveFocus");
                    pages.at(currentPage)->receiveFocus(this);
                    break;
                default:
                    //pages[currentPage]->react(UA);
                    //do nothing!
                    Slog("unknown action");
                    break;
            }
        }
        else{
            pages.at(currentPage)->react(UA);
        }
    }
}

void uiRoot::setConfig(DisplayConfig _config){
    config = _config;
    init();
}

void uiRoot::init(){
    config.display->begin();
    config.display->setFont(u8g2_font_6x10_tf);
    config.display->setFontRefHeightExtendedText();
    config.display->setDrawColor(1);
    config.display->setFontPosCenter();
    config.display->setFontDirection(0);

    lastFrameInfo.display = config.display;
}

void uiRoot::FlushDisplay(frameInfo* fi){
  if(nextDisplayFrame<millis()){
    nextDisplayFrame=millis()+config.frameDistance;
    if(globalDisplayState==ScreenState::on){

        if(millis()-lastDisplayFlash >= config.flashHalfCycle){
            lastDisplayFlash = millis();
            fi->highlightSelected = !lastFrameInfo.highlightSelected;
        }  

        lastFrameInfo = *fi;

        drawUI(fi);
      config.display->sendBuffer();
    }
  }
}

void uiRoot::drawUI(frameInfo* fi){
    pages[currentPage]->draw(fi);
}

ScreenState uiRoot::getScreenState(){
    return globalDisplayState;
}

void uiRoot::wakeUpScreen(){
    screenSwitch(ScreenState::on);
    lastInputTime = millis();
}

void uiRoot::screenSwitch(ScreenState state){
  //switches Screen on or off
  if(state == ScreenState::off){
    //switch off
    if(globalDisplayState==ScreenState::on){
      config.display->clearBuffer();
      config.display->sendBuffer();
      globalDisplayState=ScreenState::off;
    }
  }
  else{
    //switch on
    if(globalDisplayState==ScreenState::off){
      globalDisplayState=ScreenState::on;
      FlushDisplay(&lastFrameInfo);
    }
  }
}

void uiRoot::energyManager(){
    //keeps track of time and manages ScreenTime
  
    //check display time
    if(screenOnTime<=millis() && config.useSleep){
    //turn off
    screenSwitch(ScreenState::off);
    }
}

void uiRoot::receiveFocus(){
    if(pages.size()>1){
        focus = FocusState::current;
    }else{
        //reject focus
        focus = FocusState::child;
        pages.at(currentPage)->receiveFocus(this);
    }
    
}