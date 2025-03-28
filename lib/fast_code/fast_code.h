#pragma once

#include <Arduino.h>

#define ON HIGH);
#define OFF LOW);
#define OPEN HIGH);
#define CLOSE LOW);
#define TURN(x, state) digitalWrite(x, state)

//* If statements
#define IF if( 
#define IS_HIGH ) == HIGH
#define IS_LOW ) == LOW
#define OR_IF } else if (
#define END_CASE }
#define ELSE } else {
#define THEN ) {

//* Others
#define DONE ;
#define AND &&
#define END
#define AND_THEN
#define LASTLY
#define ALSO &&
#define ƒ

//* Builtin Arduino extender
#define WAIT_A_SECOND delay(1000);
#define WAIT_A_MOMENT delay(5000);
#define VOLTAGE_OF digitalRead(
    
//* Things About Pump
#define IS_FULL ) == HIGH
#define IS_NOT_FULL ) != HIGH
