#pragma once
#include <Arduino.h>

#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif


inline void slog(String file, int line, String functionname, String message){
  String msg;
  msg = "["+file+":"+line+":<"+functionname+">] "+message;
  Serial.println(msg);
};


#define Slog(message) slog(__FILE__,__LINE__,__FUNCTION_NAME__,message);
