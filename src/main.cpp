#include <Arduino.h>
#include "cube.hpp"
#include "Routine.hpp"
#include "routines/AllOn.hpp"
#include "routines/Fade.hpp"
#include "Renderer.hpp"
#include "renderers/StandardRenderer.hpp"
#include "renderers/RawRenderer.hpp"

boolean frames[2][CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
size_t frameActiveIdx = 0;

Renderer *cube = RAW_RENDERER
                     ? dynamic_cast<Renderer *>(new RawRenderer())
                     : dynamic_cast<Renderer *>(new StandardRenderer());


using RoutineFactory = Routine* (*)();

RoutineFactory routineFactories[] = {
    []() -> Routine * { return new AllOn(); },
    []() -> Routine * { return new Fade(); },
};
size_t currentRoutineIdx = 0;
Routine *currentRoutine = routineFactories[currentRoutineIdx]();

/**
* Configure the interrupt timer for controlling the cube pins.
*/
void setupInterrupts() {
    noInterrupts(); // Disable interrupts while setting up

    // Clear timer configuration
    TCCR1A = 0;
    TCCR1B = 0;

    // Reset timer to 0
    TCNT1 = 0;

    // Set interrupt frequency with a 1024 prescaler, REFRESH_RATE*CUBE_SIZE
    OCR1A = F_CPU / 1024 / REFRESH_RATE / CUBE_SIZE - 1;
    // Set timer to CTC mode (Clear Timer on Compare Match)
    TCCR1B |= _BV(WGM12);
    // Set timer prescaler to tick only once every 1024 CPU cycles
    TCCR1B |= _BV(CS12) | _BV(CS10);

    TIMSK1 |= _BV(OCIE1A); // Enable timer interrupt
    interrupts(); // Enable interrupts
}

/**
 * The handler for the timer interrupt configured in @link setupInterrupts@endlink.
 */
ISR(TIMER1_COMPA_vect) {
    cube->renderLayer(&frames[frameActiveIdx]);
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

void nextRoutine() {
    constexpr auto routineCount = sizeof(routineFactories) / sizeof(routineFactories[0]);
    currentRoutineIdx = (currentRoutineIdx + 1) % routineCount;
    currentRoutine = routineFactories[currentRoutineIdx]();
    currentRoutine->setup(&frames[frameActiveIdx]);
}

void setup() {
    randomSeed(analogRead(UNUSED_ANALOG_PIN));
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    currentRoutine->setup(&frames[frameActiveIdx]);
    setupInterrupts();
}

void loop() {
    static auto buttonPressed = false;
    if (!buttonPressed && digitalRead(BUTTON_PIN) == LOW) {
        buttonPressed = true;
        nextRoutine();
    } else {
        buttonPressed = false;
    }

    const auto frameNextIdx = (frameActiveIdx + 1) % (sizeof(frames) / sizeof(frames[0]));
    currentRoutine->update(&frames[frameNextIdx], getTimeSinceLastFrameInMicros());
    frameActiveIdx = frameNextIdx;
}
