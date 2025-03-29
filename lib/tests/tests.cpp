#include <Arduino.h>
#include <torrent_manager.h>
#include <pump_manager.h>
#include <indicator_manager.h>
#include <tests.h>

// #define TEST_COMMUNICATION
// #define TEST_WATER_FLOW_SENSOR
// #define TEST_RELAY_FROM_TORRENT_SENSOR
#define TEST_DISPLAY
// #define TEST_SELENOID
// #define TEST_RUN
// #define TEST_EXPERIMENTS

#ifdef TEST_EXPERIMENTS

void setup() {

}

void loop() {
    
}



#elif defined TEST_COMMUNICATION /// ✅ TESTED!

uint8_t counter = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_COMMUNICATION...")
}

void loop() {
    counter++;
    Serial.println("TEST_"+counter.toString());
    delay(500*((counter % 5) + 1));
}



#elif defined TEST_WATER_FLOW_SENSOR /// ✅ TESTED!

volatile int pulseCount;   // Counter for the flow sensor pulses
float flowRate;            // Flow rate in L/min
float totalLiters = 0;     // Total water passed in liters
uint64_t oldTime = 0;      // Timer for calculations


void IRAM_ATTR pulseCounter() {
    pulseCount++;  // Increment pulse count
}

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_WATER_FLOW_SENSOR...");
    
    pinMode(WATER_FLOW_SENSOR, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR), pulseCounter, FALLING);
}

void loop() {
    if (millis() - oldTime > 1000) {  // Calculate every second
        detachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR)); // Disable interrupt while calculating
        
        // Conversion formula: (Pulse Frequency / 7.5) = Flow rate in L/min (for YF-S201)
        flowRate = (pulseCount / 6.6);  

        // Calculate total water volume
        float liters = (flowRate / 60.0); // Convert L/min to L/sec
        totalLiters += liters; // Accumulate total liters

        Serial.print("[Flow Rate: ");
        Serial.print(flowRate);
        Serial.print(" L/min]\t");

        Serial.print("[Total Volume: ");
        Serial.print(totalLiters);
        Serial.println(" L]");

        pulseCount = 0;     // Reset pulse counter
        oldTime = millis(); // Reset timer

        attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR), pulseCounter, FALLING); // Re-enable interrupt
    }
}



#elif defined TEST_RELAY_FROM_TORRENT_SENSOR

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_RELAY_FROM_TORRENT_SENSOR...");
}

void loop() {
    Serial.println(TORRENT_SENSOR_THROUGH_RELAY IS_HIGH ? "Water level in torrent is low" : "Water level in torrent is high");
    delay(500);
}



#elif defined TEST_DISPLAY

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_DISPLAY...");
}

void loop() {
    delay(2000); // Pause for 2 seconds
}



#elif defined TEST_SELENOID

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_SELENOID...");
}

void loop() {
    TURN_SELENOID OPEN
    WAIT_A_SECOND
    TURN_SELENOID CLOSE
    WAIT_A_SECOND
}



#elif defined TEST_RUN

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_RUN...");
}

void loop() {
    
}

#endif
