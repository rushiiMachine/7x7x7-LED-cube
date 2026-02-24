#include <Arduino.h>
#include "cube.hpp"
#include "Routine.hpp"
#include "routines/AllOn.hpp"
#include "Renderer.hpp"
#include "renderers/StandardRenderer.hpp"
#include "renderers/RawRenderer.hpp"

Routine *currentRoutine = new AllOn();
Renderer *cube = RAW_RENDERER
                     ? dynamic_cast<Renderer *>(new RawRenderer())
                     : dynamic_cast<Renderer *>(new StandardRenderer());

boolean frames[2][CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
boolean (*activeFrame)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

void setupInterrupts() {
    noInterrupts(); // Disable interrupts while setting up
    // Set up an interrupt with timer1
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    // Make interrupt occur at the correct frequency, REFRESH_RATE*CUBE_SIZE
    OCR1A = (16000000 / REFRESH_RATE / 1024 / CUBE_SIZE - 1);
    TCCR1B |= (1 << WGM12);
    // Set to CS10 and CS12 so we have the 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    interrupts(); // Enable interrupts
}

// Called by the configured timer interrupt
ISR(TIMER1_COMPA_vect) {
    cube->renderLayer(activeFrame);
}

/**
 * Get the delta time since the last call of this function in microseconds
 * @return Delta time in microseconds.
 */
unsigned long getTimeSinceLastFrameInMicros() {
    static unsigned long lastTime = 0;
    const auto dt = micros() - lastTime;
    lastTime = micros();
    return dt;
}

void setup() {
    pinMode(52, OUTPUT);
    digitalWrite(52, HIGH);
    for (auto i = 0; i < CUBE_SIZE; ++i) {
        pinMode(i, OUTPUT);
    }

    // currentRoutine->setup(activeFrame);
    // setupInterrupts();
}

void loop() {
    for (auto i = 0; i < CUBE_SIZE; ++i) {
        digitalWrite(i, HIGH);
        delay(100);
        digitalWrite(i, LOW);
    }

    // const auto nextFrame = &frames[0] == activeFrame ? &frames[1] : &frames[0];
    // currentRoutine->update(getTimeSinceLastFrameInMicros(), nextFrame);
    // activeFrame = nextFrame;
}
