#include <pump_manager.h>

uint8_t PumpManager::state_of_pump;

uint8_t PumpManager::get_state_of_pump() {
    return state_of_pump;
}

void PumpManager::set_state_of_pump(uint8_t value) {
    state_of_pump = value;
}