#pragma once
#include <Wire.h>

#define LCD_ADDRESS 0x27

//* Instruction Sets
#define CLEAR_CMD 0x01      //* Used for clearing display
#define HOME_CMD 0x02       //* Used for resetting cursor position
#define ENTRY_CMD 0x04      //* Used for setting up cursor or display shift when typing a character
#define DISPLAY_CMD 0x08    //* Used for setting display, cursor, or cursor blink. ON or OFF
#define CURSOR_CMD 0x10     //* Used for moving cursor relative to current cursor position immediately
#define FUNCTION_CMD 0x20   //* 

#define PRINT_BINARY(binary)    for(int i = 7; i >= 0; i--) { Serial.print(((binary >> i) & 1) ? "1" : "0"); }\
                                Serial.println();

#define SEND_BYTE_I2C_LCD(binary, data)     Wire.begin();                        /* Memulai komunikasi      */\
                                            Wire.beginTransmission(LCD_ADDRESS); /* Set Alamat Komunikasi   */\
                                            Wire.write((binary | 0x08) & ~0x04 | (data ? 0x01 : 0x00)); /* Set the data            */\
                                            Serial.println("-----------");\
                                            PRINT_BINARY((binary | 0x08))\
                                            PRINT_BINARY(~0x04)\
                                            PRINT_BINARY((0b00101000) & (0b11111011))\
                                            PRINT_BINARY((binary | 0x08) & ~0x04 | (data ? 0x01 : 0x00))\
                                            delayMicroseconds(50);\
                                            Wire.write((binary | 0x08) |  0x04 | (data ? 0x01 : 0x00)); /* Enable                  */\
                                            PRINT_BINARY((binary | 0x08) |  0x04 | (data ? 0x01 : 0x00))\
                                            delayMicroseconds(50);\
                                            Wire.write((binary | 0x08) & ~0x04 | (data ? 0x01 : 0x00)); /* Back to normal          */\
                                            delayMicroseconds(50);\
                                            Wire.endTransmission();              /* Stop komunikasi         */\
                                            delayMicroseconds(50);\

#define CLEAR_LCD() SEND_BYTE_I2C_LCD(CLEAR_CMD, false)
#define HOME_LCD() SEND_BYTE_I2C_LCD(HOME_CMD, false)

#define FORCE_4_BIT_MODE()  SEND_BYTE_I2C_LCD(0b00110000, false)\
                            SEND_BYTE_I2C_LCD(0b00110000, false)\
                            SEND_BYTE_I2C_LCD(0b00110000, false)\
                            SEND_BYTE_I2C_LCD(0b00100000, false)

#define LCD_SETUP() SEND_BYTE_I2C_LCD(0b00101100, false)

#define SEND_COMMAND_LCD(binary, data)  SEND_BYTE_I2C_LCD((binary << 0) & 0xF0, data)\
                                        SEND_BYTE_I2C_LCD((binary << 4) & 0xF0, data)

#define LCD_PRINT_CHAR(character) SEND_COMMAND_LCD(character, true)
#define LCD_PRINT(text) for(char character : text) { LCD_PRINT_CHAR(character) }