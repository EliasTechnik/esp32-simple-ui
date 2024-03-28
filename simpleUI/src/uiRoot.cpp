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
    pages.push_back(page);
    if(pages.size() == 1){
        pages[0]->receiveFocus(FocusDirection::fromParent);
        pages[0]->setSelected(SelectionState::Selected); //do we need this?
    }
}

void uiRoot::display(){ 
    energyManager(); //takes care of about the sleep

    frameInfo fi;
    fi.display = config.display;
    
    fi.display->clearBuffer();

    if(millis()-lastDisplayFlash >= config.flashHalfCycle){
        lastDisplayFlash = millis();
        fi.highlightSelected = !fi.highlightSelected;
    }  

    lastFrameInfo = fi;

    FlushDisplay(&fi);
}

bool uiRoot::goToPage(uiPage* page){
    //todo
}

bool uiRoot::goToElement(uiElement* element){
    //todo
}

void uiRoot::react(UserAction UA){
    //reset display time
    screenSwitch(ScreenState::on);
    screenOnTime=millis()+ config.screenSleepTime;


    if(pages[currentPage]->getFocusState()==FocusState::parent){
        switch (UA){
        case UserAction::leftButton:
            if(currentPage == 0){
                currentPage = pages.size()-1;
            }else{
                currentPage--;
            }
            break;
        case UserAction::rightButton:
            if(currentPage == pages.size()-1){
                currentPage = 0;
            }else{
                currentPage++;
            }
            break;
        case UserAction::enterButton:

            //remove selection from old child
            pages[currentPage]->removeFocus(FocusDirection::fromChild);

            if(currentPage == pages.size()-1){
                currentPage = 0;
            }else{
                currentPage++;
            }

            pages[currentPage]->receiveFocus(FocusDirection::fromParent);
            break;
        default:
            pages[currentPage]->react(UA);
            break;
        }
    }else{
        pages[currentPage]->react(UA);
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
}

void uiRoot::FlushDisplay(frameInfo* fi){
  if(nextDisplayFrame<millis()){
    nextDisplayFrame=millis()+config.frameDistance;

    drawUI(fi);

    if(globalDisplayState==ScreenState::on){
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