// Copyright (c) 2023. Leonhard Baschang

#include "mbed.h"

/*
 * Script that displays a text on 8x8 led dot matrix with MAX7219 interface
 * Speed, number of displays and brightness of displays can be set
 * Max number of characters is 500 (could be increased, but would not be so smart)
 *
 *
 * Input (in variable "text") -> Output (on display)
 * A -> A
 * B -> B
 * .
 * .
 * .
 * y -> y
 * z -> z
 * 0 -> 0
 * .
 * .
 * .
 * 9 -> 9
 * *space* -> *Small space (4 width)*
 * ( -> (
 * ) -> )
 * . -> .
 * , -> ,
 * _ -> _
 * - -> -
 * ? -> ?
 * ! -> !
 *
 * special characters (with % in front (e.g. %A -> Ä)
 * A -> Ä
 * a -> ä
 * .
 * .
 * .
 * ü -> ü
 *
 * *space* -> *Normal space (8 width)*
 * 1 -> *one blank vertical line*
 * 2 -> *two blank vertical lines*
 * 3 -> *three blank vertical lines*
 * | -> *one filled vertical line*
 *
 *
 * How to add characters?
 *
 * 1. Declare character as uint8_t array with specific name (bitcode must consists of  8 elements, 9th element is the length of the char (max 8))
 * 2. Append the character that will represent the char to either alphabetSeries or specialCharsSeries (Call with % iin front of character in inputText)
 * 3. Append the char name to Alphabet (If in specialCharsSeries, at the End. If in alphabetSeries, before the first specialCharsSeries character and after the last alphabetSeries character)
 * 4. Add it to inputText
 *
 */

//BEGIN OF CONFIG
unsigned int scrollSpeed = 50;//Speed of scrolling
const unsigned int displays = 4;//number of 8x8 displays
unsigned int displayBrightness = 5;//0-15
bool scrollEnable = true;
bool reverseDisplay = false;

string inputText = "GDS1 Informatik ist das beste Profilfach der Schule!% % % ";// text to display
//END OF CONFIG



DigitalOut cs(PC_1);
DigitalOut clk(PC_2);
DigitalOut din(PC_0);

uint16_t shutdownMode = 0x0C01;
uint16_t displayTestMode = 0x0F00;
uint16_t scanLimitMode = 0x0B07;
uint8_t brightnessAddress = 0x0A;

uint8_t writeData[displays][8];
unsigned int countLetter = 0;

unsigned int displayText[500];
unsigned int displayTextSize;


uint8_t lA[] = {0b00110000, 0b01111000, 0b11001100, 0b11001100, 0b11111100, 0b11001100, 0b11001100, 0b00000000,
                8}; // A
uint8_t lB[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01100110, 0b01100110, 0b11111100, 0b00000000,
                8}; // B
uint8_t lC[] = {0b00111100, 0b01100110, 0b11000000, 0b11000000, 0b11000000, 0b01100110, 0b00111100, 0b00000000,
                8}; // C
uint8_t lD[] = {0b11111000, 0b01101100, 0b01100110, 0b01100110, 0b01100110, 0b01101100, 0b11111000, 0b00000000,
                8}; // D
uint8_t lE[] = {0b11111110, 0b01100010, 0b01101000, 0b01111000, 0b01101000, 0b01100010, 0b11111110, 0b00000000,
                8}; // E
uint8_t lF[] = {0b11111110, 0b01100010, 0b01101000, 0b01111000, 0b01101000, 0b01100000, 0b11110000, 0b00000000,
                8}; // F
uint8_t lG[] = {0b00111100, 0b01100110, 0b11000000, 0b11000000, 0b11001110, 0b01100110, 0b00111110, 0b00000000,
                8}; // G
uint8_t lH[] = {0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b00000000,
                8}; // H
uint8_t lI[] = {0b01111000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                8}; // I
uint8_t lJ[] = {0b00011110, 0b00001100, 0b00001100, 0b00001100, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                8}; // J
uint8_t lK[] = {0b11110110, 0b01100110, 0b01101100, 0b01111000, 0b01101100, 0b01100110, 0b11110110, 0b00000000,
                8}; // K
uint8_t lL[] = {0b11110000, 0b01100000, 0b01100000, 0b01100000, 0b01100010, 0b01100110, 0b11111110, 0b00000000,
                8}; // L
uint8_t lM[] = {0b11000110, 0b11101110, 0b11111110, 0b11111110, 0b11010110, 0b11000110, 0b11000110, 0b00000000,
                8}; // M
uint8_t lN[] = {0b11000110, 0b11100110, 0b11110110, 0b11011110, 0b11001110, 0b11000110, 0b11000110, 0b00000000,
                8}; // N
uint8_t lO[] = {0b00111000, 0b01101100, 0b11000110, 0b11000110, 0b11000110, 0b01101100, 0b00111000, 0b00000000,
                8}; // O
uint8_t lP[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01100000, 0b01100000, 0b11110000, 0b00000000,
                8}; // P
uint8_t lQ[] = {0b01111000, 0b11001100, 0b11001100, 0b11001100, 0b11011100, 0b01111000, 0b00011100, 0b00000000,
                8}; // Q
uint8_t lR[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01101100, 0b01100110, 0b11110110, 0b00000000,
                8}; // R
uint8_t lS[] = {0b01111000, 0b11001100, 0b11100000, 0b01110000, 0b00011100, 0b11001100, 0b01111000, 0b00000000,
                8}; // S
uint8_t lT[] = {0b11111100, 0b10110100, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                8}; // T
uint8_t lU[] = {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b00000000,
                8}; // U
uint8_t lV[] = {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00000000,
                8}; // V
uint8_t lW[] = {0b11000110, 0b11000110, 0b11000110, 0b11010110, 0b11111110, 0b11101110, 0b11000110, 0b00000000,
                8}; // W
uint8_t lX[] = {0b11000110, 0b11000110, 0b01101100, 0b00111000, 0b00111000, 0b01101100, 0b11000110, 0b00000000,
                8}; // X
uint8_t lY[] = {0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                8}; // Y
uint8_t lZ[] = {0b11111110, 0b11000110, 0b10001100, 0b00011000, 0b00110010, 0b01100110, 0b11111110, 0b00000000,
                8}; // Z
uint8_t la[] = {0b00000000, 0b00000000, 0b01111000, 0b00001100, 0b01111100, 0b11001100, 0b01110110, 0b00000000,
                8}; // a
uint8_t lb[] = {0b11100000, 0b01100000, 0b01100000, 0b01111100, 0b01100110, 0b01100110, 0b11011100, 0b00000000,
                8}; // b
uint8_t lc[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11000000, 0b11001100, 0b01111000, 0b00000000,
                8}; // c
uint8_t ld[] = {0b00011100, 0b00001100, 0b00001100, 0b01111100, 0b11001100, 0b11001100, 0b01110110, 0b00000000,
                8}; // d
uint8_t le[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11111100, 0b11000000, 0b01111000, 0b00000000,
                8}; // e
uint8_t lf[] = {0b00111000, 0b01101100, 0b01100000, 0b11110000, 0b01100000, 0b01100000, 0b11110000, 0b00000000,
                8}; // f
uint8_t lg[] = {0b00000000, 0b00000000, 0b01110110, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b11111000,
                8}; // g
uint8_t lh[] = {0b11100000, 0b01100000, 0b01101100, 0b01110110, 0b01100110, 0b01100110, 0b11100110, 0b00000000,
                8}; // h
uint8_t li[] = {0b00110000, 0b00000000, 0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                8}; // i
uint8_t lj[] = {0b00001100, 0b00000000, 0b00001100, 0b00001100, 0b00001100, 0b11001100, 0b11001100, 0b01111000,
                8}; // j
uint8_t lk[] = {0b11100000, 0b01100000, 0b01100110, 0b01101100, 0b01111000, 0b01101100, 0b11100110, 0b00000000,
                8}; // k
uint8_t ll[] = {0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                8}; // l
uint8_t lm[] = {0b00000000, 0b00000000, 0b11001100, 0b11111110, 0b11111110, 0b11010110, 0b11000110, 0b00000000,
                8}; // m
uint8_t ln[] = {0b00000000, 0b00000000, 0b11111000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b00000000,
                8}; // n
uint8_t lo[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                8}; // o
uint8_t lp[] = {0b00000000, 0b00000000, 0b11011100, 0b01100110, 0b01100110, 0b01111100, 0b01100000, 0b11110000,
                8}; // p
uint8_t lq[] = {0b00000000, 0b00000000, 0b01110110, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b00011110,
                8}; // q
uint8_t lr[] = {0b00000000, 0b00000000, 0b10011100, 0b01110110, 0b01100110, 0b01100000, 0b11110000, 0b00000000,
                8}; // r
uint8_t ls[] = {0b00000000, 0b00000000, 0b01111100, 0b11000000, 0b01111000, 0b00001100, 0b11111000, 0b00000000,
                8}; // s
uint8_t lt[] = {0b00010000, 0b00110000, 0b01111100, 0b00110000, 0b00110000, 0b00110100, 0b00011000, 0b00000000,
                8}; // t
uint8_t lu[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01110110, 0b00000000,
                8}; // u
uint8_t lv[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00000000,
                8}; // v
uint8_t lw[] = {0b00000000, 0b00000000, 0b11000110, 0b11000110, 0b11010110, 0b11111110, 0b01101100, 0b00000000,
                8}; // w
uint8_t lx[] = {0b00000000, 0b00000000, 0b11000110, 0b01101100, 0b00111000, 0b01101100, 0b11000110, 0b00000000,
                8}; // x
uint8_t ly[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b11111000,
                8}; // y
uint8_t lz[] = {0b00000000, 0b00000000, 0b11111100, 0b10011000, 0b00110000, 0b01100100, 0b11111100, 0b00000000,
                8}; // z
uint8_t l0[] = {0b01111000, 0b11001100, 0b11011100, 0b11111100, 0b11101100, 0b11001100, 0b01111100, 0b00000000,
                8}; // 0
uint8_t l1[] = {0b00110000, 0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b11111100, 0b00000000,
                8}; // 1
uint8_t l2[] = {0b01111000, 0b11001100, 0b00001100, 0b00111000, 0b01100000, 0b11001100, 0b11111100, 0b00000000,
                8}; // 2
uint8_t l3[] = {0b01111000, 0b11001100, 0b00001100, 0b00111000, 0b00001100, 0b11001100, 0b01111000, 0b00000000,
                8}; // 3
uint8_t l4[] = {0b00011100, 0b00111100, 0b01101100, 0b11001100, 0b11111110, 0b00001100, 0b00011110, 0b00000000,
                8}; // 4
uint8_t l5[] = {0b11111100, 0b11000000, 0b11111000, 0b00001100, 0b00001100, 0b11001100, 0b01111000, 0b00000000,
                8}; // 5
uint8_t l6[] = {0b00111000, 0b01100000, 0b11000000, 0b11111000, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                8}; // 6
uint8_t l7[] = {0b11111100, 0b11001100, 0b00001100, 0b00011000, 0b00110000, 0b00110000, 0b00110000, 0b00000000,
                8}; // 7
uint8_t l8[] = {0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                8}; // 8
uint8_t l9[] = {0b01111000, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b00011000, 0b01110000, 0b00000000,
                8}; // 9
uint8_t l_[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
                8}; // _

uint8_t lBracketO[] = {0b00011000, 0b00110000, 0b01100000, 0b01100000, 0b01100000, 0b00110000, 0b00011000,
                       0b00000000, 8}; // (
uint8_t lBracketC[] = {0b01100000, 0b00110000, 0b00011000, 0b00011000, 0b00011000, 0b00110000, 0b01100000,
                       0b00000000, 8}; // )
uint8_t lDot[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110000, 0b00110000, 0b00000000,
                  8}; // .
uint8_t lComma[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110000, 0b00110000, 0b01100000,
                    8}; // ,
uint8_t lQuestionMark[] = {0b01111000, 0b11001100, 0b00001100, 0b00011000, 0b00110000, 0b00000000, 0b00110000,
                           0b00000000, 8}; // ,
uint8_t lExclamationMark[] = {0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00000000, 0b00011000,
                              0b00000000, 8};

uint8_t lUnderscore[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111110,
                         0b01111110, 8};; // _
uint8_t lDash[] = {0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b01111110, 0b00000000, 0b00000000, 0b00000000,
                   8}; // -
uint8_t lHeart[] = {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000,
                    0b00000000, 8}; // <3



uint8_t lAe[] = {0b11000110, 0b00111000, 0b01101100, 0b11000110, 0b11111110, 0b11000110, 0b11000110, 0b00000000,
                 8};
uint8_t lae[] = {0b11001100, 0b00000000, 0b01111000, 0b00001100, 0b01111100, 0b11001100, 0b01111110, 0b00000000,
                 8};
uint8_t lOe[] = {0b11000011, 0b00011000, 0b00111100, 0b01100110, 0b01100110, 0b00111100, 0b00011000, 0b00000000,
                 8};
uint8_t loe[] = {0b00000000, 0b11001100, 0b00000000, 0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                 8};
uint8_t lUe[] = {0b11001100, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                 8};
uint8_t lue[] = {0b00000000, 0b11001100, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111110, 0b00000000,
                 8};


uint8_t l_small[] = {0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 4};
uint8_t l_single[] = {0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 1};
uint8_t l_double[] = {0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 2};
uint8_t l_triple[] = {0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 3};
uint8_t lLine[] = {0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 1};


string alphabetSeries = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ().,_-?!";
string specialCharSeries = "AaOoUuH 1|";

uint8_t *Alphabet[] = {lA, lB, lC, lD, lE, lF, lG, lH, lI, lJ, lK, lL, lM, lN, lO, lP, lQ, lR, lS, lT, lU, lV, lW,
                       lX, lY, lZ, la, lb, lc, ld, le, lf, lg, lh, li, lj, lk, ll, lm, ln, lo, lp, lq, lr, ls, lt,
                       lu, lv, lw, lx, ly, lz, l0, l1, l2, l3, l4, l5, l6, l7, l8,
                       l9, l_small, lBracketO, lBracketC, lDot, lComma, lUnderscore, lDash, lQuestionMark,
                       lExclamationMark, lAe, lae, lOe, loe, lUe,
                       lue,
                       lHeart, l_, l_single, l_double, l_triple, lLine};


void output(uint16_t data) {
    for (int i = 0; i < 16; i++) {
        din = (data >> (15 - i)) & 1;
        clk = 1;
        clk = 0;
    }

}


void addLetter(unsigned int letterId) {
    displayText[displayTextSize] = letterId;
    displayTextSize++;
}

void createText(string text) {
    for (int i = 0; i < text.size(); i++) {
        char letter = text[i];
        unsigned int letterId;
        if (letter == '%') {
            letter = text[i + 1];
            letterId = specialCharSeries.find(letter);
            i = i + 1;
            if (letterId == string::npos) { continue; }
            letterId = letterId + alphabetSeries.size();
            addLetter(letterId);
        } else {
            letterId = alphabetSeries.find(letter);
            if (letterId == string::npos) { continue; }
            addLetter(letterId);
        }
    }
}

void initDisplays() {
    cs = 0;
    for (int i = 0; i < displays; i++) {
        output(shutdownMode);
    }
    cs = 1;
    cs = 0;
    for (int i = 0; i < displays; i++) {
        output(displayTestMode);
    }
    cs = 1;
    cs = 0;
    for (int i = 0; i < displays; i++) {
        output(scanLimitMode);
    }
    cs = 1;
    cs = 0;
    for (int i = 0; i < displays; i++) {
        output(brightnessAddress << 8 | displayBrightness);
    }
    cs = 1;


}

uint8_t reverseByte(uint8_t byte) {
    byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
    byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
    byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
    return byte;
}

int main() {
    initDisplays();
    createText(inputText);


    //display first letter of text
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < displays; j++) {
            if (reverseDisplay) {
                writeData[j][i] = reverseByte(Alphabet[displayText[displays - 1 - j]][7 - i]);
            } else {
                writeData[j][i] = (Alphabet[displayText[j]][i]);
            }


        }

    }
    countLetter = displays - 1;


    while (true) {
        //increase letter count every 8 bits shifted
        countLetter++;

        //reset letter counter if max is reached
        if (countLetter >= displayTextSize) {
            countLetter = 0;
        }



        //load next char if current char is fully latched in
        for (int i = 0; i < Alphabet[displayText[countLetter]][8]; i++) {

            //output all 8 data packets per display
            for (int j = 0; j < 8; j++) {
                cs = 0;
                for (int k = 0; k < displays; k++) {
                    uint16_t outputData = ((j + 1) << (8)) | ((writeData[k][j]) & 0xFF);
                    output(outputData);
                }
                cs = 1;

                if (scrollEnable && !reverseDisplay) {
                    //Load next bit from previous Module
                    for (int k = 0; k < displays - 1; k++) {
                        writeData[k][j] = (writeData[k][j] << 1) | ((writeData[k + 1][j] & 0x80) >> 7);
                    }
                    //Load next bit from array
                    writeData[displays - 1][j] = (writeData[displays - 1][j] << 1) |
                                                 (((Alphabet[displayText[countLetter]][j])
                                                         >> (Alphabet[displayText[countLetter]][8] - 1 - i)) & 0x01);
                } else if (scrollEnable && reverseDisplay) {
                    //Load next bit from previous Module
                    for (int k = 0; k < displays - 1; k++) {
                        writeData[displays - 1 - k][j] = (writeData[displays - 1 - k][j] >> 1) |
                                                         ((writeData[displays - 1 - k - 1][j] & 0x01) << 7);
                    }
                    //Load next bit from array
                    writeData[0][j] = (writeData[0][j] >> 1) | ((reverseByte(Alphabet[displayText[countLetter]][7 - j])
                            << (Alphabet[displayText[countLetter]][8] - 1 - i)) & 0x80);

                }


            }
            thread_sleep_for(scrollSpeed);
        }


    }


}