#include <Arduino.h>
#include <avr/sleep.h>
#include "cube.hpp"
#include "wiring.hpp"
#include "Routine.hpp"
#include "routines/AllOn.hpp"
#include "routines/Test.hpp"
#include "routines/Fade.hpp"
#include "routines/Rain.hpp"
#include "routines/Snake.hpp"
#include "routines/Ripple.hpp"
#include "Renderer.hpp"
#include "renderers/StandardRenderer.hpp"
#include "renderers/RawRenderer.hpp"

constexpr size_t FRAME_COUNT = 2;
boolean frames[FRAME_COUNT][CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
volatile size_t frameActiveIdx = 0;

Renderer *renderer = RAW_RENDERER
                         ? dynamic_cast<Renderer *>(new RawRenderer())
                         : dynamic_cast<Renderer *>(new StandardRenderer());


using RoutineFactory = Routine* (*)();

RoutineFactory routineFactories[] = {
    []() -> Routine * { return new AllOn(); },
    []() -> Routine * { return new Test(); },
    []() -> Routine * { return new Fade(); },
    []() -> Routine * { return new Rain(); },
    []() -> Routine * { return new Snake(); },
    []() -> Routine * { return new Ripple(); },
};
size_t currentRoutineIdx = 0;
Routine *currentRoutine = routineFactories[currentRoutineIdx]();

/**
 * Disables the interrupt timer for rendering the cube.
 */
void teardownRenderingTimer() {
    TIMSK1 &= ~(_BV(OCIE1A)); // Disable timer interrupt
}

/**
* Configure the interrupt timer for rendering the cube LEDs.
*/
void setupRenderingTimer() {
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
 * The callback for the timer interrupt configured in @link setupRenderingTimer@endlink.
 */
ISR(TIMER1_COMPA_vect) {
    renderer->renderLayer(&frames[frameActiveIdx]);
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

void setupFrames() {
    memset(frames, false, sizeof(frames));

    for (auto &frame: frames) {
        currentRoutine->setup(&frame);
    }
}

void nextRoutine() {
    constexpr auto routineCount = sizeof(routineFactories) / sizeof(routineFactories[0]);
    currentRoutineIdx = (currentRoutineIdx + 1) % routineCount;
    currentRoutine = routineFactories[currentRoutineIdx]();

    setupFrames();
}

void wakeUp() {
    detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
    sleep_disable();

    setupRenderingTimer();
}

void startSleep() {
    teardownRenderingTimer();
    renderer->setup(); // Turn off cube

    // Wait for button to be released
    while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10); // Wait 10ms
    }

    noInterrupts();
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeUp, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    interrupts();
    sleep_cpu();
}

void checkButton() {
    constexpr auto BUTTON_DEBOUNCE_MS = 250; // 250ms
    constexpr auto BUTTON_SLEEP_MS = 2 * 1000; // 2s

    static unsigned long buttonPressedMs = 0;
    static unsigned long buttonReleasedMs = 0;

    const auto pressed = digitalRead(BUTTON_PIN) == LOW;

    if (pressed
        && buttonPressedMs == 0 // New press
        && millis() - buttonReleasedMs > BUTTON_DEBOUNCE_MS // Throttle new presses
    ) {
        buttonPressedMs = millis();
        nextRoutine();
    } else if (buttonPressedMs > 0 // Was pressed
               && !pressed // No longer pressed
    ) {
        buttonPressedMs = 0;
        buttonReleasedMs = millis();
    } else if (pressed // Is currently pressed
               && buttonPressedMs > 0 // Was pressed
               && millis() - buttonPressedMs >= BUTTON_SLEEP_MS // Was pressed for long time
    ) {
        buttonPressedMs = 0;
        buttonReleasedMs = millis();
        startSleep();
    }
}

void setup() {
    randomSeed(analogRead(SEED_PIN));
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    renderer->setup();
    setupFrames();
    setupRenderingTimer();
}

void loop() {
    checkButton();

    if (currentRoutine->useFrameBuffering) {
        const auto frameNextIdx = (frameActiveIdx + 1) % FRAME_COUNT;
        currentRoutine->update(&frames[frameNextIdx], getTimeSinceLastFrameInMicros());
        frameActiveIdx = frameNextIdx;
    } else {
        currentRoutine->update(&frames[frameActiveIdx], getTimeSinceLastFrameInMicros());
    }
}
