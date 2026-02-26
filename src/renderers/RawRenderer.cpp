#include "renderers/RawRenderer.hpp"

// IO port bitmasks for the column pins
/** Digital pins D22, D23, D24, D25, D26, D27, D28, D29 */
#define PORTA_MASK (_BV(PA0)|_BV(PA1)|_BV(PA2)|_BV(PA3)|_BV(PA4)|_BV(PA5)|_BV(PA6)|_BV(PA7))
/** Digital pins D10, D11, D12, D13 */
#define PORTB_MASK (_BV(PB4)|_BV(PB5)|_BV(PB6)|_BV(PB7))
/** Digital pins D37, D36, D35, D34, D33, D32, D31, D30 */
#define PORTC_MASK (_BV(PC0)|_BV(PC1)|_BV(PC2)|_BV(PC3)|_BV(PC4)|_BV(PC5)|_BV(PC6)|_BV(PC7))
/** Digital pins D21, D20, D19, D18, D38 */
#define PORTD_MASK (_BV(PD0)|_BV(PD1)|_BV(PD2)|_BV(PD3)|_BV(PD7))
/** Digital pins D0, D1, D2, D3, D5 */
#define PORTE_MASK (_BV(PE0)|_BV(PE1)|_BV(PE3)|_BV(PE4)|_BV(PE5))
/** Digital pins D41, D40, D39, D4 */
#define PORTG_MASK (_BV(PG0)|_BV(PG1)|_BV(PG2)|_BV(PG5))
/** Digital pins D17, D16, D6, D7, D8, D9 */
#define PORTH_MASK (_BV(PH0)|_BV(PH1)|_BV(PH3)|_BV(PH4)|_BV(PH5)|_BV(PH6))
/** Digital pins D15, D14 */
#define PORTJ_MASK (_BV(PJ0)|_BV(PJ1))
/** Digital pins D48, D47, D46, D45, D44, D43, D42 */
#define PORTL_MASK (_BV(PL1)|_BV(PL2)|_BV(PL3)|_BV(PL4)|_BV(PL5)|_BV(PL6)|_BV(PL7))

// IO port bitmasks for layer pins
/** Digital pins D54, D55, D56, D57, D58, D59, D60 */
#define PORTF_MASK (_BV(PF0)|_BV(PF1)|_BV(PF2)|_BV(PF3)|_BV(PF4)|_BV(PF5)|_BV(PF6))

void RawRenderer::setup() {
    static_assert(CUBE_SIZE == 7, "RawRenderer is only configured for 7x7x7 cubes");

    auto interrupts = SREG;
    noInterrupts();

    // Turn off all layers (A0 to A6 aka. D54 to D60)
    PORTF &= ~PORTF_MASK;

    // Configure all layer pins to output (A0 to A6 aka. D54 to D60)
    DDRF |= PORTF_MASK;

    // Turn off all columns (D0 to D48)
    PORTA &= ~PORTA_MASK;
    PORTB &= ~PORTB_MASK;
    PORTC &= ~PORTC_MASK;
    PORTD &= ~PORTD_MASK;
    PORTE &= ~PORTE_MASK;
    PORTG &= ~PORTG_MASK;
    PORTH &= ~PORTH_MASK;
    PORTJ &= ~PORTJ_MASK;
    PORTL &= ~PORTL_MASK;

    // Configure all column pins to output (D0 to D48)
    DDRA |= PORTA_MASK;
    DDRB |= PORTB_MASK;
    DDRC |= PORTC_MASK;
    DDRD |= PORTD_MASK;
    DDRE |= PORTE_MASK;
    DDRG |= PORTG_MASK;
    DDRH |= PORTH_MASK;
    DDRJ |= PORTJ_MASK;
    DDRL |= PORTL_MASK;

    SREG = interrupts; // Restore interrupts
}

void RawRenderer::renderLayer(const boolean (*model)[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE]) {
    auto interrupts = SREG;
    noInterrupts();

    // Turn off all layers (A0 to A6 aka. D54 to D60)
    PORTF &= ~PORTF_MASK;

    // Enable/disable all columns

    // 6  D42, D43, D44, D45, D46, D47, D48
    // 5  D35, D36, D37, D38, D39, D40, D41
    // 4  D28, D29, D30, D31, D32, D33, D34
    // 3  D21, D22, D23, D24, D25, D26, D27     ^ y-axis
    // 2  D14, D15, D16, D17, D18, D19, D20     > x-axis
    // 1  D7,  D8,  D9,  D10, D11, D12, D13
    // 0  D0,  D1,  D2,  D3,  D4,  D5,  D6
    //    0    1    2    3    4    5    6

#define PIN(x, y, bit) ((*model[x][y][currentLayer]) << bit)

    PORTA = PIN(1, 3, PA0) | // D22
            PIN(2, 3, PA1) | // D23
            PIN(3, 3, PA2) | // D24
            PIN(4, 3, PA3) | // D25
            PIN(5, 3, PA4) | // D26
            PIN(6, 3, PA5) | // D27
            PIN(0, 4, PA6) | // D28
            PIN(1, 4, PA7); // D29
    PORTB = (PORTB & ~PORTB_MASK) |
            PIN(3, 1, PB4) | // D10
            PIN(4, 1, PB5) | // D11
            PIN(5, 1, PB6) | // D12
            PIN(6, 1, PB7); // D13
    PORTC = PIN(2, 5, PC0) | // D37
            PIN(1, 5, PC1) | // D36
            PIN(0, 5, PC2) | // D35
            PIN(6, 4, PC3) | // D34
            PIN(5, 4, PC4) | // D33
            PIN(4, 4, PC5) | // D32
            PIN(3, 4, PC6) | // D31
            PIN(2, 4, PC7); // D30
    PORTD = (PORTD & ~PORTD_MASK) |
            PIN(0, 3, PD0) | // D21
            PIN(6, 2, PD1) | // D20
            PIN(5, 2, PD2) | // D19
            PIN(4, 2, PD3) | // D18
            PIN(3, 5, PD7); // D38
    PORTE = (PORTE & ~PORTE_MASK) |
            PIN(0, 0, PE0) | // D0
            PIN(1, 0, PE1) | // D1
            PIN(2, 0, PE3) | // D2
            PIN(3, 0, PE4) | // D3
            PIN(5, 0, PE5); // D5
    PORTG = (PORTG & ~PORTG_MASK) |
            PIN(6, 5, PG0) | // D41
            PIN(5, 5, PG1) | // D40
            PIN(4, 5, PG2) | // D39
            PIN(0, 4, PG5); // D4
    PORTH = (PORTH & ~PORTH_MASK) |
            PIN(3, 2, PH0) | // D17
            PIN(2, 2, PH1) | // D16
            PIN(6, 0, PH3) | // D6
            PIN(0, 1, PH4) | // D7
            PIN(1, 1, PH5) | // D8
            PIN(2, 1, PH6); // D9
    PORTJ = (PORTJ & ~PORTJ_MASK) |
            PIN(1, 2, PJ0) | // D15
            PIN(0, 2, PJ1); // D14
    PORTL = (PORTL & ~PORTL_MASK) |
            PIN(6, 6, PL1) | // D48
            PIN(5, 6, PL2) | // D47
            PIN(4, 6, PL3) | // D46
            PIN(3, 6, PL4) | // D45
            PIN(2, 6, PL5) | // D44
            PIN(1, 6, PL6) | // D43
            PIN(0, 6, PL7); // D42

    // Turn on current layer (one of A0 to A6 aka. D54 to D60)
    PORTF = _BV(currentLayer);

    // Advance layer for the next render
    currentLayer = (currentLayer + 1) % CUBE_SIZE;

    SREG = interrupts; // Restore interrupts
}
