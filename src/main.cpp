#include "mbed.h"


#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

#define a 26
#define b 27
#define c 28
#define d 29
#define e 30
#define f 31
#define g 32
#define h 33
#define i 34
#define j 35
#define k 36
#define l 37
#define m 38
#define n 39
#define o 40
#define p 41
#define q 42
#define r 43
#define s 44
#define t 45
#define u 46
#define v 47
#define w 48
#define x 49
#define y 50
#define z 51

#define n0 52
#define n1 53
#define n2 54
#define n3 55
#define n4 56
#define n5 57
#define n6 58
#define n7 59
#define n8 60
#define n9 61

#define _ 62
#define _BracketO 63
#define _BracketC 64
#define _Dot 65
#define _Underscore 66
#define _Dash 67
#define _Heart 68

#define scrollSpeed 100 //100 is good
int displayText[] = {G, D, S, n1, _, I, n, f, o, r, m, a, t, i, k, _, i, s, t, _, c, o, o, l, _,
                     _}; // text to display as array
//int displayText[] = {_Underscore, _Dash};
//int displayText[] = {_Heart};

DigitalOut cs(PC_1);
DigitalOut clk(PC_2);
DigitalOut din(PC_0);

uint16_t shutdown = 0x0C01;
uint16_t displayTest = 0x0F00;
uint16_t scanLimit = 0x0B07;


unsigned char lA[] = {0b00110000, 0b01111000, 0b11001100, 0b11001100, 0b11111100, 0b11001100, 0b11001100,
                      0b00000000}; // A
unsigned char lB[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01100110, 0b01100110, 0b11111100,
                      0b00000000}; // B
unsigned char lC[] = {0b00111100, 0b01100110, 0b11000000, 0b11000000, 0b11000000, 0b01100110, 0b00111100,
                      0b00000000}; // C
unsigned char lD[] = {0b11111000, 0b01101100, 0b01100110, 0b01100110, 0b01100110, 0b01101100, 0b11111000,
                      0b00000000}; // D
unsigned char lE[] = {0b11111110, 0b01100010, 0b01101000, 0b01111000, 0b01101000, 0b01100010, 0b11111110,
                      0b00000000}; // E
unsigned char lF[] = {0b11111110, 0b01100010, 0b01101000, 0b01111000, 0b01101000, 0b01100000, 0b11110000,
                      0b00000000}; // F
unsigned char lG[] = {0b00111100, 0b01100110, 0b11000000, 0b11000000, 0b11001110, 0b01100110, 0b00111110,
                      0b00000000}; // G
unsigned char lH[] = {0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11001100, 0b11001100, 0b11001100,
                      0b00000000}; // H
unsigned char lI[] = {0b01111000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000,
                      0b00000000}; // I
unsigned char lJ[] = {0b00011110, 0b00001100, 0b00001100, 0b00001100, 0b11001100, 0b11001100, 0b01111000,
                      0b00000000}; // J
unsigned char lK[] = {0b11110110, 0b01100110, 0b01101100, 0b01111000, 0b01101100, 0b01100110, 0b11110110,
                      0b00000000}; // K
unsigned char lL[] = {0b11110000, 0b01100000, 0b01100000, 0b01100000, 0b01100010, 0b01100110, 0b11111110,
                      0b00000000}; // L
unsigned char lM[] = {0b11000110, 0b11101110, 0b11111110, 0b11111110, 0b11010110, 0b11000110, 0b11000110,
                      0b00000000}; // M
unsigned char lN[] = {0b11000110, 0b11100110, 0b11110110, 0b11011110, 0b11001110, 0b11000110, 0b11000110,
                      0b00000000}; // N
unsigned char lO[] = {0b00111000, 0b01101100, 0b11000110, 0b11000110, 0b11000110, 0b01101100, 0b00111000,
                      0b00000000}; // O
unsigned char lP[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01100000, 0b01100000, 0b11110000,
                      0b00000000}; // P
unsigned char lQ[] = {0b01111000, 0b11001100, 0b11001100, 0b11001100, 0b11011100, 0b01111000, 0b00011100,
                      0b00000000}; // Q
unsigned char lR[] = {0b11111100, 0b01100110, 0b01100110, 0b01111100, 0b01101100, 0b01100110, 0b11110110,
                      0b00000000}; // R
unsigned char lS[] = {0b01111000, 0b11001100, 0b11100000, 0b01110000, 0b00011100, 0b11001100, 0b01111000,
                      0b00000000}; // S
unsigned char lT[] = {0b11111100, 0b10110100, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000,
                      0b00000000}; // T
unsigned char lU[] = {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111100,
                      0b00000000}; // U
unsigned char lV[] = {0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000,
                      0b00000000}; // V
unsigned char lW[] = {0b11000110, 0b11000110, 0b11000110, 0b11010110, 0b11111110, 0b11101110, 0b11000110,
                      0b00000000}; // W
unsigned char lX[] = {0b11000110, 0b11000110, 0b01101100, 0b00111000, 0b00111000, 0b01101100, 0b11000110,
                      0b00000000}; // X
unsigned char lY[] = {0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000, 0b00110000, 0b01111000,
                      0b00000000}; // Y
unsigned char lZ[] = {0b11111110, 0b11000110, 0b10001100, 0b00011000, 0b00110010, 0b01100110, 0b11111110,
                      0b00000000}; // Z
unsigned char la[] = {0b00000000, 0b00000000, 0b01111000, 0b00001100, 0b01111100, 0b11001100, 0b01110110,
                      0b00000000}; // a
unsigned char lb[] = {0b11100000, 0b01100000, 0b01100000, 0b01111100, 0b01100110, 0b01100110, 0b11011100,
                      0b00000000}; // b
unsigned char lc[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11000000, 0b11001100, 0b01111000,
                      0b00000000}; // c
unsigned char ld[] = {0b00011100, 0b00001100, 0b00001100, 0b01111100, 0b11001100, 0b11001100, 0b01110110,
                      0b00000000}; // d
unsigned char le[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11111100, 0b11000000, 0b01111000,
                      0b00000000}; // e
unsigned char lf[] = {0b00111000, 0b01101100, 0b01100000, 0b11110000, 0b01100000, 0b01100000, 0b11110000,
                      0b00000000}; // f
unsigned char lg[] = {0b00000000, 0b00000000, 0b01110110, 0b11001100, 0b11001100, 0b01111100, 0b00001100,
                      0b11111000}; // g
unsigned char lh[] = {0b11100000, 0b01100000, 0b01101100, 0b01110110, 0b01100110, 0b01100110, 0b11100110,
                      0b00000000}; // h
unsigned char li[] = {0b00110000, 0b00000000, 0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000,
                      0b00000000}; // i
unsigned char lj[] = {0b00001100, 0b00000000, 0b00001100, 0b00001100, 0b00001100, 0b11001100, 0b11001100,
                      0b01111000}; // j
unsigned char lk[] = {0b11100000, 0b01100000, 0b01100110, 0b01101100, 0b01111000, 0b01101100, 0b11100110,
                      0b00000000}; // k
unsigned char ll[] = {0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b01111000,
                      0b00000000}; // l
unsigned char lm[] = {0b00000000, 0b00000000, 0b11001100, 0b11111110, 0b11111110, 0b11010110, 0b11000110,
                      0b00000000}; // m
unsigned char ln[] = {0b00000000, 0b00000000, 0b11111000, 0b11001100, 0b11001100, 0b11001100, 0b11001100,
                      0b00000000}; // n
unsigned char lo[] = {0b00000000, 0b00000000, 0b01111000, 0b11001100, 0b11001100, 0b11001100, 0b01111000,
                      0b00000000}; // o
unsigned char lp[] = {0b00000000, 0b00000000, 0b11011100, 0b01100110, 0b01100110, 0b01111100, 0b01100000,
                      0b11110000}; // p
unsigned char lq[] = {0b00000000, 0b00000000, 0b01110110, 0b11001100, 0b11001100, 0b01111100, 0b00001100,
                      0b00011110}; // q
unsigned char lr[] = {0b00000000, 0b00000000, 0b10011100, 0b01110110, 0b01100110, 0b01100000, 0b11110000,
                      0b00000000}; // r
unsigned char ls[] = {0b00000000, 0b00000000, 0b01111100, 0b11000000, 0b01111000, 0b00001100, 0b11111000,
                      0b00000000}; // s
unsigned char lt[] = {0b00010000, 0b00110000, 0b01111100, 0b00110000, 0b00110000, 0b00110100, 0b00011000,
                      0b00000000}; // t
unsigned char lu[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b01110110,
                      0b00000000}; // u
unsigned char lv[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111000, 0b00110000,
                      0b00000000}; // v
unsigned char lw[] = {0b00000000, 0b00000000, 0b11000110, 0b11000110, 0b11010110, 0b11111110, 0b01101100,
                      0b00000000}; // w
unsigned char lx[] = {0b00000000, 0b00000000, 0b11000110, 0b01101100, 0b00111000, 0b01101100, 0b11000110,
                      0b00000000}; // x
unsigned char ly[] = {0b00000000, 0b00000000, 0b11001100, 0b11001100, 0b11001100, 0b01111100, 0b00001100,
                      0b11111000}; // y
unsigned char lz[] = {0b00000000, 0b00000000, 0b11111100, 0b10011000, 0b00110000, 0b01100100, 0b11111100,
                      0b00000000}; // z
unsigned char l0[] = {0b01111000, 0b11001100, 0b11011100, 0b11111100, 0b11101100, 0b11001100, 0b01111100,
                      0b00000000}; // 0
unsigned char l1[] = {0b00110000, 0b01110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b11111100,
                      0b00000000}; // 1
unsigned char l2[] = {0b01111000, 0b11001100, 0b00001100, 0b00111000, 0b01100000, 0b11001100, 0b11111100,
                      0b00000000}; // 2
unsigned char l3[] = {0b01111000, 0b11001100, 0b00001100, 0b00111000, 0b00001100, 0b11001100, 0b01111000,
                      0b00000000}; // 3
unsigned char l4[] = {0b00011100, 0b00111100, 0b01101100, 0b11001100, 0b11111110, 0b00001100, 0b00011110,
                      0b00000000}; // 4
unsigned char l5[] = {0b11111100, 0b11000000, 0b11111000, 0b00001100, 0b00001100, 0b11001100, 0b01111000,
                      0b00000000}; // 5
unsigned char l6[] = {0b00111000, 0b01100000, 0b11000000, 0b11111000, 0b11001100, 0b11001100, 0b01111000,
                      0b00000000}; // 6
unsigned char l7[] = {0b11111100, 0b11001100, 0b00001100, 0b00011000, 0b00110000, 0b00110000, 0b00110000,
                      0b00000000}; // 7
unsigned char l8[] = {0b01111000, 0b11001100, 0b11001100, 0b01111000, 0b11001100, 0b11001100, 0b01111000,
                      0b00000000}; // 8
unsigned char l9[] = {0b01111000, 0b11001100, 0b11001100, 0b01111100, 0b00001100, 0b00011000, 0b01110000,
                      0b00000000}; // 9
unsigned char l_[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
                      0b00000000}; // _

unsigned char lBracketO[] = {0b00011000, 0b00110000, 0b01100000, 0b01100000, 0b01100000, 0b00110000, 0b00011000,
                             0b00000000}; // (
unsigned char lBracketC[] = {0b01100000, 0b00110000, 0b00011000, 0b00011000, 0b00011000, 0b00110000, 0b01100000,
                             0b00000000}; // )
unsigned char lDot[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110000, 0b00110000,
                        0b00000000}; // .


unsigned char lUnderscore[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111110,
                               0b01111110};; // _
unsigned char lDash[] = {0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b01111110, 0b00000000, 0b00000000,
                         0b00000000}; // -
unsigned char lHeart[] = {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000,
                          0b00000000}; // <3





unsigned char *Alphabet[] = {lA, lB, lC, lD, lE, lF, lG, lH, lI, lJ, lK, lL, lM, lN, lO, lP, lQ, lR, lS, lT, lU, lV, lW,
                             lX, lY, lZ, la, lb, lc, ld, le, lf, lg, lh, li, lj, lk, ll, lm, ln, lo, lp, lq, lr, ls, lt,
                             lu, lv, lw, lx, ly, lz, l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l_, lBracketO,
                             lBracketC, lDot, lUnderscore, lDash, lHeart};


int writeData[16];
int countLetter = 0;


void output(uint16_t data) {
    cs = 0;
    for (int ii = 0; ii < 16; ii++) {
        din = (data >> (15 - ii)) & 1;
        clk = 1;
        clk = 0;
    }
    cs = 1;

}


int main() {

    output(shutdown);
    output(displayTest);
    output(scanLimit);


    for (int jj = 0; jj < 8; jj++) {
        writeData[jj] = Alphabet[displayText[0]][jj];
    }
    countLetter++;


    while (true) {
        if (countLetter >= sizeof(displayText) / sizeof(displayText[0])) {
            countLetter = 0;
        }


        for (int jj = 0; jj < 8; jj++) {

            for (int ii = 0; ii < 8;
                 ii++) {

                uint16_t writeData2 = ((ii + 1) << 8) | (writeData[ii] & 0xFF);
                output(writeData2);

                if (sizeof(displayText) / sizeof(displayText[0]) > 1) {
                    writeData[ii] =
                            (writeData[ii] << 1) | (((Alphabet[displayText[countLetter]][ii]) >> (8 - jj)) & 0x01);
                }


            }
            thread_sleep_for(scrollSpeed);


        }
        countLetter++;


    }


}