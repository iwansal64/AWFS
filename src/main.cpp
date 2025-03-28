#include <Arduino.h>
#include <torrent_manager.h>
#include <pump_manager.h>
#include <indicator_manager.h>
#include <fast_code.h>

//? Uncomment this to test functions
// #define BUILD

#ifndef BUILD

#include <tests.h>

#else // Below is the main program

void setup() {

    //? CONDITION:  When program first start,
    //- ACTION:     make sure the pump off and the selenoid closed
    TURN_PUMP       OFF     AND_THEN
    TURN_SELENOID   CLOSE
    
}

void loop() {
 
    //? CONDITION:  If the water level is below some point (torrent sensor active) and water in the pump is not full,
    //- ACTION:     make sure to turn off the pump and then fill the pump with water through selenoid
    IF ( ( VOLTAGE_OF TORRENT_SENSOR_THROUGH_RELAY IS_HIGH ) AND ( STATE_OF_PUMP IS_NOT_FILLED ) ) THEN
    
        TURN_PUMP       OFF       AND_THEN
        WAIT_A_MOMENT             LASTLY
        TURN_SELENOID   OPEN
        CHANGE_STATE_OF_PUMP      TO_FILLING
    
    END_CASE
    
    
    //? CONDITION:  If the water in the pump is full (flow sensor active) and currently filling it,
    //- ACTION:     close the selenoid and then turn on the pump
    IF ( ( WATER_IN_PUMP IS_FULL ) AND ( STATE_OF_PUMP IS_FILLING )  ) THEN

        TURN_SELENOID   CLOSE     AND_THEN
        WAIT_A_SECOND             LASTLY
        TURN_PUMP       ON
        CHANGE_STATE_OF_PUMP      TO_FILLED
    
    END_CASE
    

    //? CONDITION:  If the water level is above some point (torrent sensor not active), 
    //- ACTION:     turn off the pump and make sure the selenoid still closed
    IF ( ( VOLTAGE_OF TORRENT_SENSOR_THROUGH_RELAY IS_LOW ) AND ( STATE_OF_PUMP IS_FILLED ) ) THEN

        TURN_PUMP       OFF       AND_THEN
        TURN_SELENOID   CLOSE
        CHANGE_STATE_OF_PUMP      TO_EMPTY

    END_CASE

}


#endif


/*

! Problem: 
! After filling the pump with water and it detected fulled, 
! The selenoid closes and the pump will turned on. 
! But when there's no flow in the water flow sensor,
! there's still a chance that the sensor on the torrent still active
!!> THE STATE OF THE PUMP WILL STILL ON BUT,
!!> THE STATE OF THE SELENOID BE OPENED (cause it detects that the water in pump is not full (because of the water flow sensor) )

? Solution:
? Add VARIABLE to track the state of water level in torrent!
? If the water level from torrent is below some point, the variable turns false
? If the water level from torrent is above some point, the variable turns true
? Thus, We only open the selenoid when the variable is true
? And, We only turn on the pump when the variable is false


*/