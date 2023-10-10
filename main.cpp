/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <string>

#define IS_NI
#ifdef IS_NI
    #define LED_ON false
    #define LED_OFF true
#else
    #define LED_ON true
    #define LED_OFF false
#endif

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define DOT 250ms
#define DASH 3*DOT
#define PAUSE 3*DOT
#define WORD_PAUSE 7*DOT
#define NEWLINE_PAUSE 21*DOT

void init(){
    
}
void exit(){

}

static const string morse[36]= {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};

void blink_morse(string str, DigitalOut led){

    for(int i=0; i<str.size(); i++){
        int j=((int)str.at(i))-97;
        if(j>=0 || j<=35){
            string seq=morse[j];
            for(int k=0;k<seq.size();k++){
                switch(seq.at(k)){
                    case '.': led = LED_ON; ThisThread::sleep_for(DOT); led = LED_OFF; break;
                    case '-': led = LED_ON; ThisThread::sleep_for(DASH); led = LED_OFF; break;
                    default: led = LED_OFF; ThisThread::sleep_for(DOT); led = LED_OFF; break;
                }
            }
            ThisThread::sleep_for(PAUSE);
        }else{
            switch(str.at(i)){
                case '\n': led = LED_OFF; ThisThread::sleep_for(NEWLINE_PAUSE); led = LED_OFF; break;
                case ' ': led = LED_OFF; ThisThread::sleep_for(WORD_PAUSE); led = LED_OFF; break;
                default : break;
            }
        }
    }
}



int main()
{
    // Initialise the digital pin LED1 as an output
    init();
    DigitalOut led(LED1);
    bool run = true;
    
    led=LED_OFF;

    while (run) {
        blink_morse("sos ", led);
    }

    exit();
}
