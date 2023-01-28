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
 * *Space* -> *Small Space (4 width)*
 * ( -> (
 * ) -> )
 * . -> .
 * _ -> _
 * - -> -
 *
 * special characters (with % in front (e.g. %A -> Ä)
 * A -> Ä
 * a -> ä
 * .
 * .
 * .
 * ü -> ü
 *
 * *Space* -> *Normal Space (8 width)*
 * 1 -> *one blank vertical line*
 * 2 -> *two blank vertical lines*
 * 3 -> *three blank vertical lines*
 * | -> *one filled vertical line*
 *
 *
 */

//BEGIN OF CONFIG
#define scrollSpeed 50 //Speed of scrolling
#define displays 4 //number of 8x8 displays (max 8 (based on my code (can surely be improved))
#define displayBrightness 5 //0-15

string text = "GDS1 Informatik ist das beste Profilfach der Welt %H% % % ";// text to display
//END OF CONFIG



DigitalOut cs(PC_1);
DigitalOut clk(PC_2);
DigitalOut din(PC_0);

uint16_t shutdownMode = 0x0C01;
uint16_t displayTestMode = 0x0F00;
uint16_t scanLimitMode = 0x0B07;
uint8_t brightnessAddress = 0x0A;

uint64_t writeData[8];
unsigned int countLetter = 0;

unsigned int displayText[500];
unsigned int displayTextSize;


unsigned char lA[] = {0b00110000, 0b01111000, 0b11001100, 0b11001100, 0b11111100, 0b11001100, 0b11001100, 0b00000000,
                      8}; // A
unsigned char lB[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01100110, 0b01100110, 0b11111100, 0b00000000,
                      8}; // B
unsigned char lC[] = {0b00111100, 0b01100110, 0b11000000, 0b11000000, 0b11000000, 0b01100110, 0b00111100, 0b00000000,
                      8}; // C
unsigned char lD[] = {0b11111000, 0b01101100, 0b01100110, 0b01100110, 0b01100110, 0b01101100, 0b11111000, 0b00000000,
                      8}; // D
unsigned char lE[] = {0b11111110, 0b01100010, 0b01101000, 0b01111000, 0b01101000, 0b01100010, 0b11111110, 0b00000000,
                      8}; // E
unsigned char lF[] = {0b11111110, 0b01100010, 0b01101000, 0b01111000, 0b01101000, 0b01100000, 0b11110000, 0b00000000,
                      8}; // F
unsigned char lG[] = {0b00111100, 0b01100110, 0b11000000, 0b11000000, 0b11001110, 0b01100110, 0b00111110, 0b00000000,
                      8}; // G
unsigned char lH[] = {0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b00000000,
                      8}; // H
unsigned char lI[] = {0b01111000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                      8}; // I
unsigned char lJ[] = {0b00011110, 0b00001100, 0b00001100, 0b00001100, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // J
unsigned char lK[] = {0b11110110, 0b01100110, 0b01101100, 0b01111000, 0b01101100, 0b01100110, 0b11110110, 0b00000000,
                      8}; // K
unsigned char lL[] = {0b11110000, 0b01100000, 0b01100000, 0b01100000, 0b01100010, 0b01100110, 0b11111110, 0b00000000,
                      8}; // L
unsigned char lM[] = {0b11000110, 0b11101110, 0b11111110, 0b11111110, 0b11010110, 0b11000110, 0b11000110, 0b00000000,
                      8}; // M
unsigned char lN[] = {0b11000110, 0b11100110, 0b11110110, 0b11011110, 0b11001110, 0b11000110, 0b11000110, 0b00000000,
                      8}; // N
unsigned char lO[] = {0b00111000, 0b01101100, 0b11000110, 0b11000110, 0b11000110, 0b01101100, 0b00111000, 0b00000000,
                      8}; // O
unsigned char lP[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01100000, 0b01100000, 0b11110000, 0b00000000,
                      8}; // P
unsigned char lQ[] = {0b01111000, 0b11001100, 0b11001100, 0b11001100, 0b11011100, 0b01111000, 0b00011100, 0b00000000,
                      8}; // Q
unsigned char lR[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01101100, 0b01100110, 0b11110110, 0b00000000,
                      8}; // R
unsigned char lS[] = {0b01111000, 0b11001100, 0b11100000, 0b01110000, 0b00011100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // S
unsigned char lT[] = {0b11111100, 0b10110100, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                      8}; // T
unsigned char lU[] = {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b00000000,
                      8}; // U
unsigned char lV[] = {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00000000,
                      8}; // V
unsigned char lW[] = {0b11000110, 0b11000110, 0b11000110, 0b11010110, 0b11111110, 0b11101110, 0b11000110, 0b00000000,
                      8}; // W
unsigned char lX[] = {0b11000110, 0b11000110, 0b01101100, 0b00111000, 0b00111000, 0b01101100, 0b11000110, 0b00000000,
                      8}; // X
unsigned char lY[] = {0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                      8}; // Y
unsigned char lZ[] = {0b11111110, 0b11000110, 0b10001100, 0b00011000, 0b00110010, 0b01100110, 0b11111110, 0b00000000,
                      8}; // Z
unsigned char la[] = {0b00000000, 0b00000000, 0b01111000, 0b00001100, 0b01111100, 0b11001100, 0b01110110, 0b00000000,
                      8}; // a
unsigned char lb[] = {0b11100000, 0b01100000, 0b01100000, 0b01111100, 0b01100110, 0b01100110, 0b11011100, 0b00000000,
                      8}; // b
unsigned char lc[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11000000, 0b11001100, 0b01111000, 0b00000000,
                      8}; // c
unsigned char ld[] = {0b00011100, 0b00001100, 0b00001100, 0b01111100, 0b11001100, 0b11001100, 0b01110110, 0b00000000,
                      8}; // d
unsigned char le[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11111100, 0b11000000, 0b01111000, 0b00000000,
                      8}; // e
unsigned char lf[] = {0b00111000, 0b01101100, 0b01100000, 0b11110000, 0b01100000, 0b01100000, 0b11110000, 0b00000000,
                      8}; // f
unsigned char lg[] = {0b00000000, 0b00000000, 0b01110110, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b11111000,
                      8}; // g
unsigned char lh[] = {0b11100000, 0b01100000, 0b01101100, 0b01110110, 0b01100110, 0b01100110, 0b11100110, 0b00000000,
                      8}; // h
unsigned char li[] = {0b00110000, 0b00000000, 0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                      8}; // i
unsigned char lj[] = {0b00001100, 0b00000000, 0b00001100, 0b00001100, 0b00001100, 0b11001100, 0b11001100, 0b01111000,
                      8}; // j
unsigned char lk[] = {0b11100000, 0b01100000, 0b01100110, 0b01101100, 0b01111000, 0b01101100, 0b11100110, 0b00000000,
                      8}; // k
unsigned char ll[] = {0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000, 0b00000000,
                      8}; // l
unsigned char lm[] = {0b00000000, 0b00000000, 0b11001100, 0b11111110, 0b11111110, 0b11010110, 0b11000110, 0b00000000,
                      8}; // m
unsigned char ln[] = {0b00000000, 0b00000000, 0b11111000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b00000000,
                      8}; // n
unsigned char lo[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // o
unsigned char lp[] = {0b00000000, 0b00000000, 0b11011100, 0b01100110, 0b01100110, 0b01111100, 0b01100000, 0b11110000,
                      8}; // p
unsigned char lq[] = {0b00000000, 0b00000000, 0b01110110, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b00011110,
                      8}; // q
unsigned char lr[] = {0b00000000, 0b00000000, 0b10011100, 0b01110110, 0b01100110, 0b01100000, 0b11110000, 0b00000000,
                      8}; // r
unsigned char ls[] = {0b00000000, 0b00000000, 0b01111100, 0b11000000, 0b01111000, 0b00001100, 0b11111000, 0b00000000,
                      8}; // s
unsigned char lt[] = {0b00010000, 0b00110000, 0b01111100, 0b00110000, 0b00110000, 0b00110100, 0b00011000, 0b00000000,
                      8}; // t
unsigned char lu[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01110110, 0b00000000,
                      8}; // u
unsigned char lv[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00000000,
                      8}; // v
unsigned char lw[] = {0b00000000, 0b00000000, 0b11000110, 0b11000110, 0b11010110, 0b11111110, 0b01101100, 0b00000000,
                      8}; // w
unsigned char lx[] = {0b00000000, 0b00000000, 0b11000110, 0b01101100, 0b00111000, 0b01101100, 0b11000110, 0b00000000,
                      8}; // x
unsigned char ly[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b11111000,
                      8}; // y
unsigned char lz[] = {0b00000000, 0b00000000, 0b11111100, 0b10011000, 0b00110000, 0b01100100, 0b11111100, 0b00000000,
                      8}; // z
unsigned char l0[] = {0b01111000, 0b11001100, 0b11011100, 0b11111100, 0b11101100, 0b11001100, 0b01111100, 0b00000000,
                      8}; // 0
unsigned char l1[] = {0b00110000, 0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b11111100, 0b00000000,
                      8}; // 1
unsigned char l2[] = {0b01111000, 0b11001100, 0b00001100, 0b00111000, 0b01100000, 0b11001100, 0b11111100, 0b00000000,
                      8}; // 2
unsigned char l3[] = {0b01111000, 0b11001100, 0b00001100, 0b00111000, 0b00001100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // 3
unsigned char l4[] = {0b00011100, 0b00111100, 0b01101100, 0b11001100, 0b11111110, 0b00001100, 0b00011110, 0b00000000,
                      8}; // 4
unsigned char l5[] = {0b11111100, 0b11000000, 0b11111000, 0b00001100, 0b00001100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // 5
unsigned char l6[] = {0b00111000, 0b01100000, 0b11000000, 0b11111000, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // 6
unsigned char l7[] = {0b11111100, 0b11001100, 0b00001100, 0b00011000, 0b00110000, 0b00110000, 0b00110000, 0b00000000,
                      8}; // 7
unsigned char l8[] = {0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                      8}; // 8
unsigned char l9[] = {0b01111000, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b00011000, 0b01110000, 0b00000000,
                      8}; // 9
unsigned char l_[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
                      8}; // _

unsigned char lBracketO[] = {0b00011000, 0b00110000, 0b01100000, 0b01100000, 0b01100000, 0b00110000, 0b00011000,
                             0b00000000, 8}; // (
unsigned char lBracketC[] = {0b01100000, 0b00110000, 0b00011000, 0b00011000, 0b00011000, 0b00110000, 0b01100000,
                             0b00000000, 8}; // )
unsigned char lDot[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110000, 0b00110000, 0b00000000,
                        8}; // .


unsigned char lUnderscore[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111110,
                               0b01111110, 8};; // _
unsigned char lDash[] = {0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b01111110, 0b00000000, 0b00000000, 0b00000000,
                         8}; // -
unsigned char lHeart[] = {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000,
                          0b00000000, 8}; // <3



unsigned char lAe[] = {0b11000110, 0b00111000, 0b01101100, 0b11000110, 0b11111110, 0b11000110, 0b11000110, 0b00000000,
                       8};
unsigned char lae[] = {0b11001100, 0b00000000, 0b01111000, 0b00001100, 0b01111100, 0b11001100, 0b01111110, 0b00000000,
                       8};
unsigned char lOe[] = {0b11000011, 0b00011000, 0b00111100, 0b01100110, 0b01100110, 0b00111100, 0b00011000, 0b00000000,
                       8};
unsigned char loe[] = {0b00000000, 0b11001100, 0b00000000, 0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                       8};
unsigned char lUe[] = {0b11001100, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00000000,
                       8};
unsigned char lue[] = {0b00000000, 0b11001100, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111110, 0b00000000,
                       8};


unsigned char l_small[] = {0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 4};
unsigned char l_single[] = {0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 1};
unsigned char l_double[] = {0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 2};
unsigned char l_triple[] = {0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 3};
unsigned char lLine[] = {0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 1};


string alphabetSeries = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ()._-";
string specialCharSeries = "AaOoUuH 1|";

unsigned char *Alphabet[] = {lA, lB, lC, lD, lE, lF, lG, lH, lI, lJ, lK, lL, lM, lN, lO, lP, lQ, lR, lS, lT, lU, lV, lW,
                             lX, lY, lZ, la, lb, lc, ld, le, lf, lg, lh, li, lj, lk, ll, lm, ln, lo, lp, lq, lr, ls, lt,
                             lu, lv, lw, lx, ly, lz, l0, l1, l2, l3, l4, l5, l6, l7, l8,
                             l9, l_small, lBracketO, lBracketC, lDot, lUnderscore, lDash, lAe, lae, lOe, loe, lUe, lue,
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




int main() {
    initDisplays();
    createText(text);


    //display first letter of text
    for (int i = 0; i < 8; i++) {
        writeData[i] = (Alphabet[displayText[0]][i]);
    }


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
                    uint16_t outputData = ((j + 1) << (8)) | ((writeData[j] >> (8 * ((displays - 1) - k))) & 0xFF);
                    output(outputData);
                }
                cs = 1;

                //only if displaying 1 letter (no scrolling)
                if (displayTextSize > 1) {
                    writeData[j] = (writeData[j] << 1) | (((Alphabet[displayText[countLetter]][j])
                            >> (Alphabet[displayText[countLetter]][8] - 1 - i)) & 0x01);

                }



            }
            thread_sleep_for(scrollSpeed);
        }


    }


}