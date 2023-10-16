/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/* Morse code thingy
 * Created by Jakub Dolezal and Vojtech Hejsek
 */

#include "mbed.h"
#include "include/morse.h"
#include "include/board.h"
#include <string>

DigitalOut led(LED1);
bool run;
string message;

void init() {
    message = "sos ";
    run = true;
    led = LED_OFF;
}

void exit() {
    led = LED_OFF;
}

int main()
{
    init();
    
    while (run) {
        blink_morse_refactor(message, led);
    }

    exit();
}
