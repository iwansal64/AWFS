#include <Arduino.h>
#include <torrent_manager.h>
#include <pump_manager.h>
#include <indicator_manager.h>
#include <tests.h>

#ifdef TEST_EXPERIMENTS

void setup() {

}

void loop() {
    
}



#elif defined TEST_COMMUNICATION

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



#elif defined TEST_WATER_FLOW_SENSOR

volatile int pulseCount;   // Counter for the flow sensor pulses
float flowRate;            // Flow rate in L/min
float totalLiters = 0;     // Total water passed in liters
uint64_t oldTime = 0;      // Timer for calculations


void IRAM_ATTR pulseCounter() {
    pulseCount++;  // Increment pulse count
}

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_WATER_FLOW_SENSOR...")
    
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
    Serial.println("TEST_RELAY_FROM_TORRENT_SENSOR...")
}

void loop() {
    Serial.println(TORRENT_SENSOR_THROUGH_RELAY IS_HIGH ? "Water level in torrent is low" : "Water level in torrent is high");
    delay(500);
}



#elif defined TEST_DISPLAY

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1

#define SCREEN_ADDRESS 0x3D

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_DISPLAY...");
    delay(1000);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    Serial.println(F("SSD1306 allocation success!!!"));

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
}

void loop() {
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    display.drawPixel(10, 10, SSD1306_WHITE);

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);
    
    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    display.drawPixel(10, 10, SSD1306_BLACK);

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);
}



#elif defined TEST_SELENOID

void setup() {
    Serial.begin(9600);
    Serial.println("TEST_SELENOID...")
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
    Serial.println("TEST_RUN...")
}

void loop() {
    
}

#endif
