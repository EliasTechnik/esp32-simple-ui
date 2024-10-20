#include <Arduino.h>
#include <U8g2lib.h>

#include "uiText.h"
#include "uiInteractive.h"
#include "uiGraphics.h"
#include "uiGroup.h"
#include "uiBasics.h"
#include "uiRoot.h"


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
  UserAction defaultAction = UserAction::generalButton;
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


//UI Globals

frameInfo fi;
uiRoot* display; 
uiBox* testBox; 
uiBox* outlineBox;
uiPage* page;


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
  page = new uiPage();

  //testBox = new uiBox(0,5,5,118,54);
  //outlineBox = new uiBox(0,0,0,128,64, false);

  //add some ui elements to the Page
  page->addElement(
    new StaticLabel("Input Mode",32,0,128,32)
  );

  page->addElement(
    new uiBox(0,0,128,64,false,false)
  );

  page->addElement(
    new uiBox(10,10,80,8,false,false)
  );
  page->addElement(
    new uiBox(10,20,80,8,false,true)
  );
  page->addElement(
    new uiBox(10,30,80,8,false,false)
  );

  Slog("Setup6");

  display->addPage(page);
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


}

