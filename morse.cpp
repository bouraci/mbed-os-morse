#include <string>
#include <unordered_map>
#include "mbed.h"
#include "include/morse.h"
#include "include/board.h"

using namespace std;

static const unordered_map<char, string> morse_dict = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
    {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
    {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"},
    {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
    {'8', "---.."}, {'9', "----."}
};

void toggle_led(DigitalOut& led, bool on, chrono::milliseconds duration) {
    led = on ? LED_ON : LED_OFF;
    ThisThread::sleep_for(duration);
}

void blink_morse_refactor(string& str, DigitalOut led) {
    for (char c : str) {
        if (morse_dict.find(c) != morse_dict.end()) {
            const string& seq = morse_dict.at(c);

            for (char m : seq) {
                toggle_led(led, true, m == '.' ? BLINK_DOT : BLINK_DASH);
                toggle_led(led, false, BLINK_PAUSE);
            }
        } else {
            switch (c) {
                case '\n':
                    toggle_led(led, false, BLINK_NEWLINE_PAUSE);
                    break;
                case ' ':
                    toggle_led(led, false, BLINK_WORD_PAUSE);
                    break;
                default:
                    break;
            }
        }
    }
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
                    case '.': led = LED_ON; ThisThread::sleep_for(BLINK_DOT); led = LED_OFF; break;
                    case '-': led = LED_ON; ThisThread::sleep_for(BLINK_DASH); led = LED_OFF; break;
                    default: led = LED_OFF; ThisThread::sleep_for(BLINK_DOT); led = LED_OFF; break;
                }
            }
            ThisThread::sleep_for(BLINK_PAUSE);
        }else{
            switch(str.at(i)){
                case '\n': led = LED_OFF; ThisThread::sleep_for(BLINK_NEWLINE_PAUSE); led = LED_OFF; break;
                case ' ': led = LED_OFF; ThisThread::sleep_for(BLINK_WORD_PAUSE); led = LED_OFF; break;
                default : break;
            }
        }
    }
}