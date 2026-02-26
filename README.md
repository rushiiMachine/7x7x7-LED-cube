# 7³ LED Cube

Firmware for a 7x7x7 LED cube powered by an Arduino MEGA 2560.

## Building & Flashing

1. [Install PlatformIO](https://docs.platformio.org/en/latest/core/installation/index.html)
2. Clone this repository
3. Connect a compatible microcontroller such as:
    - Arduino Mega 2560 Rev3
    - ELEGOO MEGA R3 Board ATmega 2560
4. Run one of these commands in the cloned repository:

```shell
# For Arduino Mega 2560 Rev3
$ platformio run -e ATmega2560 --target upload

# For ELEGOO MEGA R3 Board ATmega 2560
$ platformio run -e ELEGOO_ATmega2560 --target upload
```

### Fast Renderer

To use the (experimental) fast renderer that utilizes raw IO port writes, set
this environment variable prior to running the flashing command:

```shell
$ export PLATFORMIO_BUILD_FLAGS="-DRAW_RENDERER=true"
```

Alternatively, modify the appropriate configuration value in [`./include/cube.hpp`](./include/cube.hpp).

## Wiring

Each column is wired through a transistor to one of the digital pins, D0 to D48
in the following configuration when looking from the top-down:

```
6  D42, D43, D44, D45, D46, D47, D48
5  D35, D36, D37, D38, D39, D40, D41
4  D28, D29, D30, D31, D32, D33, D34
3  D21, D22, D23, D24, D25, D26, D27     ^ y-axis
2  D14, D15, D16, D17, D18, D19, D20     > x-axis
1  D7,  D8,  D9,  D10, D11, D12, D13
0  D0,  D1,  D2,  D3,  D4,  D5,  D6
   0    1    2    3    4    5    6
```

Note that the origin (0,0) can be placed at any corner of the cube but by convention,
it is better to place the origin in the bottom left corner when facing the cube head-on.
Any control buttons ideally should be visible to you.

Each layer ground (7 total) is wired through a separate transistor to the digital/analog pins
A0 to A6 aka., D54 to D60. Layer 0 should be wired to D54, Layer 1 to D55 and so on.

[//]: # (TODO: button wiring)
