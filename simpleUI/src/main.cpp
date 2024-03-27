#include <Arduino.h>
#include <U8g2lib.h>

#include "uiInteractive.h"
#include "uiGraphics.h"
#include "uiGroup.h"


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
unsigned long SCREEN_SLEEPTIME=5000;
int AUTOPRESS_SPEED=50;
int AUTOPRESS_DELAY=500;
int DISPLAY_FRAME_DISTANCE=66;
unsigned int DISPLAY_BLINK_DURATION=500; //ms 


enum class ScreenState{off, on};
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

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosCenter();
  u8g2.setFontDirection(0);
}

//UI Globals

frameInfo fi;
uiBox* testBox; 
uiBox* outlineBox;
uiGroup* group;


void setupUI(){

  fi.display = &u8g2;

  group = new uiGroup(3);
  //testBox = new uiBox(0,5,5,118,54);
  //outlineBox = new uiBox(0,0,0,128,64, false);

  group->addElement(
    new uiBox(10,10,20,8,false,true)
  );
  group->addElement(
    new uiBox(10,20,20,8,false,true)
  );
  group->addElement(
    new uiBox(10,30,20,8,false,true)
  );
}


void displayUI(){
  u8g2.clearBuffer();

  if(millis()-last_display_flash < DISPLAY_BLINK_DURATION*2){
    last_display_flash = millis();
    fi.highlightSelected = !fi.highlightSelected;
  }  
  
  //draw functions
  //testBox->draw(&fi);
  //outlineBox->draw(&fi);
  //Serial.println("drawn");
  group->draw(&fi);

  //u8g2.setBitmapMode(1); //for transparancy
  
}

void FlushDisplay(){
  if(next_display_frame<millis()){
    next_display_frame=millis()+DISPLAY_FRAME_DISTANCE;
    if(GLOBAL_SCREEN_STATE==ScreenState::on){
      u8g2.sendBuffer();
    }
  }
}

void screenSwitch(ScreenState state){
  //switches Screem on or off
  if(state == ScreenState::off){
    //switch off
    if(GLOBAL_SCREEN_STATE==ScreenState::on){
      u8g2.clearBuffer();
      u8g2.sendBuffer();
      GLOBAL_SCREEN_STATE=ScreenState::off;
    }
  }
  else{
    //switch on
    if(GLOBAL_SCREEN_STATE==ScreenState::off){
      GLOBAL_SCREEN_STATE=ScreenState::on;
      FlushDisplay();
    }
  }
}

void energyManager(InputAction ia){
  //keeps track of time and manages ScreenTime
  if(ia.executed && !ia.present){
    ia.action=UserAction::none;
  }
  if(ia.action==UserAction::none){
    //check display time
    if(screen_on_timer<=millis()){
      //turn off
      screenSwitch(ScreenState::off);
      Serial.println("Screen off.");
    }
  }
  else{
    //reset display time
    screenSwitch(ScreenState::on);
    screen_on_timer=millis()+SCREEN_SLEEPTIME;
  }
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
  u8g2_prepare();
  //energyManager(UA); //kinda useless

  setupUI();
  //GLOBAL_SCREEN_STATE = ScreenState::on;
}

void loop() {
  //helloWorld();

  
  //u8g2.clearBuffer();
  displayUI();
  //u8g2.drawXBM(0,0,128,64,_bits); 
  //counter=IncValue(counter,1,UserAction::rightButton);
  //counter=IncValue(counter,-1,UserAction::leftButton);
  //itoa(counter,screenBuffer,10);
  //u8g2.drawStr(0,24,screenBuffer);

  
  //final
  energyManager(UA);

  UA.executed = true;

  //for testing
  //GLOBAL_SCREEN_STATE=ScreenState::on;

  
  
  //draw functions
  //testBox->draw(&fi);
  //u8g2.drawBox(10,10,5,5);  
  //u8g2.sendBuffer();

  FlushDisplay();

}

