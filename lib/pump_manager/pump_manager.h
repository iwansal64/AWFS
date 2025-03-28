#pragma once

#include <fast_code.h>

#define SELENOID_PIN 12
#define PUMP_PIN 13
#define WATER_FLOW_SENSOR 9

#define TURN_SELENOID  digitalWrite(SELENOID_PIN, 
#define TURN_PUMP digitalWrite(PUMP_PIN, 

#define WATER_IN_PUMP digitalRead(WATER_FLOW_SENSOR
#define STATE_OF_PUMP PumpManager::state_of_pump
#define IS_FILLED == 2
#define IS_FILLING == 1
#define IS_NOT_FILLED == 0

#define CHANGE_STATE_OF_PUMP PumpManager::state_of_pump = 
#define TO_FILLED 2;
#define TO_FILLING 1;
#define TO_EMPTY 0;

class PumpManager {
public:
    static uint8_t state_of_pump;

    PumpManager() = delete;
};
