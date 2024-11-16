#include <Arduino.h>
#include <U8g2lib.h>

#include "uiText.h"
#include "uiInteractive.h"
#include "uiGraphics.h"
#include "uiBasics.h"
#include "uiPage.h"
#include "uiRoot.h"
#include "uiPrebuilds.h"
#include "uiButtons.h"
#include "uiInputs.h"


//Pin Config
#define BACK_BUTTON 32 
#define LEFT_BUTTON 33
#define RIGHT_BUTTON 25
#define ENTER_BUTTON 26
#define ENC_CS 5

#define SD_CS 17
#define SD_CLK 14
#define SD_MISO 27 //pull up needed
#define SD_MOSI 13

//Config
unsigned long SCREEN_SLEEPTIME=20000;
int AUTOPRESS_SPEED=50;
int AUTOPRESS_DELAY=500;
int DISPLAY_FRAME_DISTANCE=66;
unsigned int DISPLAY_BLINK_DURATION=150; //ms (one half of the blink cycle)



enum class ButtonStates{down,up,};


struct Button{
  uint8_t pin;
  UserAction defaultAction = UserAction::none;
  unsigned long lastpress = 0;
  unsigned long lastrelease= 0;
  bool laststate = 1;
  ButtonStates state = ButtonStates::up;
};

//Globals
Button b_back;
Button b_left;
Button b_right;
Button b_enter;
InputAction UA; //global variable for current user action
unsigned long autopress=0;
unsigned long screen_on_timer=0;
unsigned long next_autopress=0;
unsigned long next_display_frame=0;
int counter=0;
char screenBuffer [50];
ScreenState GLOBAL_SCREEN_STATE=ScreenState::on;
unsigned long last_display_flash=0;


using namespace std;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);//OLED Display

void helloWorld(){
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);
};


//ISR's
void IRAM_ATTR b_back_ISR(){
  //check previos state
  bool v=digitalRead(b_back.pin);
  if(b_back.laststate==false && v==true){
     //released
     b_back.state=ButtonStates::up;
     UA.present=false; 
  }
  if(b_back.laststate==true && v==false){
    //pressed
    b_back.state=ButtonStates::down;
    UA.action=UserAction::backButton;
    UA.present=true; 
    UA.executed=false;
    autopress=millis()+AUTOPRESS_DELAY;
  }
  b_back.laststate=v;
}
void IRAM_ATTR b_left_ISR(){
  //check previos state
  bool v=digitalRead(b_left.pin);
  if(b_left.laststate==false && v==true){
     //released
     b_left.state=ButtonStates::up;
     UA.present=false; 
  }
  if(b_left.laststate==true && v==false){
    //pressed
    b_left.state=ButtonStates::down;
    UA.action=UserAction::leftButton;
    UA.present=true; 
    UA.executed=false;
    autopress=millis()+AUTOPRESS_DELAY;
  }
  b_left.laststate=v;
}
void IRAM_ATTR b_right_ISR(){
  //check previos state
  bool v=digitalRead(b_right.pin);
  if(b_right.laststate==false && v==true){
     //released
     b_right.state=ButtonStates::up;
     UA.present=false; 
  }
  if(b_right.laststate==true && v==false){
    //pressed
    b_right.state=ButtonStates::down;
    UA.action=UserAction::rightButton;
    UA.present=true; 
    UA.executed=false;
    autopress=millis()+AUTOPRESS_DELAY;
  }
  b_right.laststate=v;
}
void IRAM_ATTR b_enter_ISR(){
  //check previos state
  bool v=digitalRead(b_enter.pin);
  if(b_enter.laststate==false && v==true){
     //released
     b_enter.state=ButtonStates::up;
     UA.present=false; 
  }
  if(b_enter.laststate==true && v==false){
    //pressed
    b_enter.state=ButtonStates::down;
    UA.action=UserAction::enterButton;
    UA.present=true; 
    UA.executed=false;
    autopress=millis()+AUTOPRESS_DELAY;
  }
  b_enter.laststate=v;
}

//uiCallbackFuctions

void cbButton1(void * sender, UIEventType event_type){
  Slog("CB_Button 1!")
}
void cbButton2(void * sender, UIEventType event_type){
  Slog("CB_Button 2!")
}
void cbButton3(void * sender, UIEventType event_type){
  Slog("CB_Button 3!")
}

void cbValueChange(void * sender){
  Slog("the value changed to:")
}




int value1 = 128;



//UI Globals

frameInfo fi;
uiRoot* display; 

uiSelectGroup* setupEditTest(){
  uiSelectGroup* editTest = new uiSelectGroup();

  //add editable Text
  editTest->addChild(
    new uiIntValueInput(
      Position(10,10),0,-10,10,&cbValueChange
    )
  );

  return editTest;
}

void setupUI(){

  //create a new config
  DisplayConfig config;

  //set the output device
  config.display = &u8g2;
  //change the viewport offset
  config.viewportOffset = DEFAULT_OFFSET;

  //create a new ui root object. This is the start of the UI Tree
  display = new uiRoot(config);

  //create a new page
  //page1 = new uiPage();
  //page2 = new uiPage();

  uiSelectGroup* mainPage = new uiSelectGroup();
  mainPage->setID("mainPage");
  uiSelectGroup* secPage = new uiSelectGroup();
  secPage->setID("secPage");

  //testBox = new uiBox(0,5,5,118,54);
  //outlineBox = new uiBox(0,0,0,128,64, false);

  //add some ui elements to the Page
  uiPassiveLabel * label = new uiPassiveLabel("Input Mode",Position(25,0));
  label->setID("label");
  mainPage->addChild(
    label
  );

/*
  uiBasicButton * box1 = new uiBasicButton(0,0,128,64,false,SelectionMode::notSelectable);
  box1->setID("box1");
  mainPage->addChild(
    box1
  );
  */

  uiBasicButton * bt1 = new uiBasicButton(Position(10,10),"Aoptg1()",&cbButton1);
  bt1->setID("opt1");
  mainPage->addChild(
    bt1,true
  );
  uiBasicButton * bt2 = new uiBasicButton(Position(10,25),"Aopt2g.....ium()",&cbButton2);
  bt2->setID("opt2");
  mainPage->addChild(
    bt2,true
  );
  
  uiBasicButton * bt3 = new uiBasicButton(Position(10,40),"Aopt2g()",&cbButton3);
  bt3->setID("opt3");
  mainPage->addChild(
    bt3,true
  );

  secPage->addChild(
    new uiPassiveLabel("Test",Position(32,0))
  );
  /*
  secPage->addChild(
    new uiBasicButton(Position(10,20), "Button")
  );
  */



  Slog("Setup6");

  uiPage* page1 = new uiPage(mainPage);
  page1->setID("page1");
  uiPage* page2 = new uiPage(secPage);
  page2->setID("page2");


  display->addPage(new uiPage(setupEditTest()));
  display->addPage(page1);
  display->addPage(page2);

  Slog(page1->getConfig());
  Slog(page2->getConfig());
  Slog(mainPage->getConfig());
  Slog(secPage->getConfig());

  Slog("Setup end");
}


void setup() {
  b_back.pin=BACK_BUTTON;
  b_left.pin=LEFT_BUTTON;
  b_right.pin=RIGHT_BUTTON;
  b_enter.pin=ENTER_BUTTON;
  pinMode(b_back.pin, INPUT_PULLUP);
  pinMode(b_left.pin, INPUT_PULLUP);
  pinMode(b_right.pin, INPUT_PULLUP);
  pinMode(b_enter.pin, INPUT_PULLUP);
  attachInterrupt(b_back.pin, b_back_ISR, CHANGE);
  attachInterrupt(b_left.pin, b_left_ISR, CHANGE);
  attachInterrupt(b_right.pin, b_right_ISR, CHANGE);
  attachInterrupt(b_enter.pin, b_enter_ISR, CHANGE);

  Serial.begin(115200);

  u8g2.begin();

  setupUI();

}

void loop() {
  
  if(!UA.executed){
    display->react(UA.action); //this needs to be done differently. react() should take the InputAction and return it!
    UA.executed = true;
  }
  

  display->display();
  
  
  
  
  
  
  /*
  u8g2.setFont(u8g2_font_helvR08_tr);
  string s = "Cage";
  int w = u8g2.getStrWidth(s.c_str());      // returns w = 24
  int h = u8g2.getAscent()-u8g2.getDescent();
  int x = 5;
  int y = 11;
  u8g2.setFontPosBaseline();
  u8g2.firstPage();
  do
  {
    u8g2.drawStr(x, y, s.c_str());
    u8g2.drawFrame(x-1,y-u8g2.getAscent()-1, w+2, h+2);
  } while( u8g2.nextPage() );
  */


}

