// Copyright (c) 2023. Leonhard Baschang
#include "DOTMATRIX.h"

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
                         0b01111110, 8}; // _
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
string specialCharSeries = "AaOoUuH 123|";

uint8_t *Alphabet[] = {lA, lB, lC, lD, lE, lF, lG, lH, lI, lJ, lK, lL, lM, lN, lO, lP, lQ, lR, lS, lT, lU, lV, lW,
                       lX, lY, lZ, la, lb, lc, ld, le, lf, lg, lh, li, lj, lk, ll, lm, ln, lo, lp, lq, lr, ls, lt,
                       lu, lv, lw, lx, ly, lz, l0, l1, l2, l3, l4, l5, l6, l7, l8,
                       l9, l_small, lBracketO, lBracketC, lDot, lComma, lUnderscore, lDash, lQuestionMark,
                       lExclamationMark, lAe, lae, lOe, loe, lUe,
                       lue,
                       lHeart, l_, l_single, l_double, l_triple, lLine};


DOTMATRIX::DOTMATRIX(PinName clkPin, PinName dinPin, PinName csPin, unsigned int numberDisplays, bool reverseText) {
    cs = new DigitalOut(csPin);
    spi= new SPI(dinPin, NC, clkPin);

    displays = numberDisplays;
    reverseDisplay = reverseText;


    displayDataLetterNumber = 0;
    displayDataLetterBit = 0;


}



uint8_t reverseByte(uint8_t byte) {
    byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
    byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
    byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
    return byte;
}


void DOTMATRIX::sendByte(uint8_t address, uint8_t data) {
    spi->write(address);
    spi->write(data);
}


void DOTMATRIX::allDisplaysSend(uint8_t address, uint8_t data) {
    cs->write(0);
    for (unsigned int i = 0; i < displays; i++) {
        sendByte(address, data);
    }
    cs->write(1);
}

void DOTMATRIX::setShutdownMode(int displayNumber, bool shutdown) {
    uint8_t shutdownData;
    if (shutdown) {
        shutdownData = 0x00;
    } else {
        shutdownData = 0x01;
    }
    if (displayNumber == -1) {
        allDisplaysSend(SHUTDOWN_MODE_ADDRESS, shutdownData);
    } else {
        cs->write(0);
        for (int i = 0; i <= displayNumber; i++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        sendByte(SHUTDOWN_MODE_ADDRESS, shutdownData);
        for (unsigned int j = displayNumber + 1; j < displays; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        cs->write(1);
    }
}

void DOTMATRIX::setScanLimit(int displayNumber, int scanLimit) {
    if (displayNumber == -1) {
        allDisplaysSend(SCAN_LIMIT_ADDRESS, scanLimit);
    } else {
        cs->write(0);
        for (int i = 0; i <= displayNumber; i++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        sendByte(SCAN_LIMIT_ADDRESS, scanLimit);
        for (unsigned int j = displayNumber + 1; j < displays; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        cs->write(1);
    }
}

void DOTMATRIX::setDecodeMode(int displayNumber, int decodeMode) {
    if (displayNumber == -1) {
        allDisplaysSend(DECODE_MODE_ADDRESS, decodeMode);
    } else {
        cs->write(0);
        for (int i = 0; i <= displayNumber; i++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        sendByte(DECODE_MODE_ADDRESS, decodeMode);
        for (unsigned int j = displayNumber + 1; j < displays; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        cs->write(1);
    }
}

void DOTMATRIX::setIntensity(int displayNumber, unsigned int intensity) {
    if (intensity > 15) {
        intensity = 15;
    }
    if (displayNumber == -1) {
        allDisplaysSend(INTENSITY_ADDRESS, intensity);
    } else {
        cs->write(0);
        for (int i = 0; i <= displayNumber; i++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        sendByte(INTENSITY_ADDRESS, intensity);
        for (unsigned int j = displayNumber + 1; j < displays; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        cs->write(1);
    }
}

void DOTMATRIX::setDisplayTest(int displayNumber, bool testMode) {
    uint8_t testModeData;
    if (testMode) {
        testModeData = 0x01;
    } else {
        testModeData = 0x00;
    }
    if (displayNumber == -1) {
        allDisplaysSend(DISPLAY_TEST_ADDRESS, testModeData);
    } else {
        cs->write(0);
        for (int i = 0; i <= displayNumber; i++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        sendByte(DISPLAY_TEST_ADDRESS, testModeData);
        for (unsigned int j = displayNumber + 1; j < displays; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        cs->write(1);
    }
}

void DOTMATRIX::displayBitPattern(int displayNumber, uint8_t (*pattern)[8]) {

    for (int i = 0; i < 8; i++) {
        cs->write(0);
        for (int j = 0; j <= displayNumber; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }

        sendByte(i + 1, (*pattern)[i]);
        for (unsigned int j = displayNumber + 1; j < displays; j++) {
            sendByte(NO_OP_ADDRESS, 0x00);
        }
        cs->write(1);
    }


}

void DOTMATRIX::displayBitPatternAll(uint8_t (*pattern)[MAX_DISPLAYS][8]) {
    for (int i = 0; i < 8; i++) {
        cs->write(0);
        for (unsigned int j = 0; j < displays; j++) {
            sendByte(i + 1, (*pattern)[j][i]);
        }
        cs->write(1);
    }

}

void DOTMATRIX::addLetter(unsigned int letterId) {
    idArray[idArraySize] = letterId;
    idArraySize++;
}

void DOTMATRIX::createIDArray(string text) {
    for (unsigned int i = 0; i < text.size(); i++) {
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

void DOTMATRIX::loadNextTextBits() {
    if (reverseDisplay) {
        for (int j = 0; j < 8; j++) {
            displayData[displays - 1][j] = (displayData[displays - 1][j] << 1) |
                                           ((Alphabet[idArray[displayDataLetterNumber]][j]
                                                   >> (Alphabet[idArray[displayDataLetterNumber]][8] -
                                                       displayDataLetterBit - 1)) & 0x01);
        }
    } else {
        for (int j = 0; j < 8; j++) {
            displayData[0][j] = (displayData[0][j] >> 1) |
                                ((reverseByte(Alphabet[idArray[displayDataLetterNumber]][7 - j])
                                        << (Alphabet[idArray[displayDataLetterNumber]][8] - displayDataLetterBit - 1)) &
                                 0x80);
        }
    }

    displayDataLetterBit++;
    if (displayDataLetterBit >= Alphabet[idArray[displayDataLetterNumber]][8]) {
        displayDataLetterNumber++;
        displayDataLetterBit = 0;
    }

}

void DOTMATRIX::shiftText() {
    if (reverseDisplay) {
        for (unsigned int i = 0; i < displays - 1; i++) {
            for (int j = 0; j < 8; j++) {
                displayData[i][j] = (displayData[i][j] << 1) | ((displayData[i + 1][j] & 0x80) >> 7);
            }
        }
        loadNextTextBits();

    } else {
        for (unsigned int i = displays - 1; i > 0; i--) {
            for (int j = 0; j < 8; j++) {
                displayData[i][j] = (displayData[i][j] >> 1) | ((displayData[i - 1][j] & 0x01) << 7);
            }
        }
        loadNextTextBits();
    }


}

void DOTMATRIX::update() {
    shiftText();
    displayBitPatternAll(&displayData);

    if (displayDataLetterNumber >= idArraySize) {
        displayDataLetterNumber = 0;
        displayDataLetterBit = 0;

    }
}

void DOTMATRIX::initDisplays(){
    setShutdownMode();
    setDisplayTest();
    setDecodeMode();
    setScanLimit();
    setIntensity();
}
