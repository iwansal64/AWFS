#pragma once

#include <fast_code.h>

#define SELENOID            12
#define PUMP                13
#define WATER_FLOW_SENSOR   15

#define TURN_SELENOID   digitalWrite(SELENOID, 
#define TURN_PUMP       digitalWrite(PUMP, 

#define WATER_IN_PUMP               digitalRead(WATER_FLOW_SENSOR
#define STATE_OF_PUMP               PumpManager::get_state_of_pump()
#define SET_STATE_OF_PUMP_TO(val)   PumpManager::set_state_of_pump(val);
#define IS_FILLED                   == 2
#define IS_FILLING                  == 1
#define IS_NOT_FILLED               == 0

#define CHANGE_STATE_OF_PUMP    PumpManager::state_of_pump = 
#define TO_FILLED               2;
#define TO_FILLING              1;
#define TO_EMPTY                0;

class PumpManager {
public:
    static uint8_t get_state_of_pump();
    static void set_state_of_pump(uint8_t value);

    PumpManager() = delete;

private:
    static uint8_t state_of_pump;
};
