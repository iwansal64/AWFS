#pragma once
#include <Wire.h>

#define LCD_ADDRESS 0x27

#define SEND_BYTE_LCD(binary, write) 
#define SETUP_LCD() Wire.begin();\
                    Wire.beginTransmission(LCD_ADDRESS);\
                    Wire.write();\

                    