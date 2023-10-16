#ifndef BOARD_H
#define BOARD_H

#define IS_NI
#ifdef IS_NI
    #define LED_ON false
    #define LED_OFF true
#else
    #define LED_ON true
    #define LED_OFF false
#endif

#endif