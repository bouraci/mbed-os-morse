#ifndef MORSE_H
#define MORSE_H

#include "mbed.h"
#include <string>

#define BLINK_DOT 250ms
#define BLINK_DASH 3 * BLINK_DOT
#define BLINK_PAUSE 3 * BLINK_DOT
#define BLINK_WORD_PAUSE 7 * BLINK_DOT
#define BLINK_NEWLINE_PAUSE 21 * BLINK_DOT

void toggle_led(DigitalOut& led, bool on, int duration);

void blink_morse_refactor(string& str, DigitalOut led);

void blink_morse(string str, DigitalOut led);

#endif