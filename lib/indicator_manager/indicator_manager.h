#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27

//* Instruction Sets
#define CLEAR_CMD 0x01      //* Used for clearing display
#define HOME_CMD 0x02       //* Used for resetting cursor position
#define ENTRY_CMD 0x04      //* Used for setting up cursor or display shift when typing a character
#define DISPLAY_CMD 0x08    //* Used for setting display, cursor, or cursor blink. ON or OFF
#define CURSOR_CMD 0x10     //* Used for moving cursor relative to current cursor position immediately
#define FUNCTION_CMD 0x20   //* 

#define CLEAR_LCD() IndicatorManager::lcd.clear()
#define HOME_LCD() IndicatorManager::lcd.home()

#define LCD_SETUP() Wire.begin();\
                    IndicatorManager::lcd.begin(20, 4);\
                    IndicatorManager::lcd.noCursor();\
                    IndicatorManager::lcd.backlight()

#define LCD_PRINT(text) IndicatorManager::lcd.print(text)

class IndicatorManager {
public:
    static LiquidCrystal_I2C lcd;
};