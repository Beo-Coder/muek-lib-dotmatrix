// Copyright (c) 2023. Leonhard Baschang
#ifndef UNTITLED5_DOTMATRIX_H
#define UNTITLED5_DOTMATRIX_H

#include "mbed.h"
#include <string>



#define MAX_DISPLAYS 50
#define MAX_TEXT_LENGTH 500

#define NO_OP_ADDRESS 0x00
#define DIGIT_0_ADDRESS 0x01
#define DIGIT_1_ADDRESS 0x02
#define DIGIT_2_ADDRESS 0x03
#define DIGIT_3_ADDRESS 0x04
#define DIGIT_4_ADDRESS 0x05
#define DIGIT_5_ADDRESS 0x06
#define DIGIT_6_ADDRESS 0x07
#define DIGIT_7_ADDRESS 0x08
#define DECODE_MODE_ADDRESS 0x09
#define INTENSITY_ADDRESS 0x0A
#define SCAN_LIMIT_ADDRESS 0x0B
#define SHUTDOWN_MODE_ADDRESS 0x0C
#define DISPLAY_TEST_ADDRESS 0x0F



class DOTMATRIX {
    DigitalOut *cs;
    DigitalOut *din;
    DigitalOut *clk;
    unsigned int displays;
    bool reverseDisplay;

    uint8_t displayData[MAX_DISPLAYS][8]{};
    unsigned int displayDataLetterNumber;
    unsigned int displayDataLetterBit;

    unsigned int idArray[MAX_TEXT_LENGTH]{};
    unsigned int idArraySize{};


private:
    void sendByte(uint8_t address, uint8_t data);

    void addLetter(unsigned int letterId);


public:
    DOTMATRIX(PinName clkPin, PinName dinPin, PinName csPin, unsigned int numberDisplays, bool reverseText);

    void initDisplays();

    void allDisplaysSend(uint8_t address, uint8_t data);

    void setShutdownMode(int displayNumber = -1, bool shutdown = false);

    void setScanLimit(int displayNumber = -1, int scanLimit = 0x07);

    void setDecodeMode(int displayNumber = -1, int decodeMode = 0x00);

    void setIntensity(int displayNumber = -1, unsigned int intensity = 15);

    void setDisplayTest(int displayNumber = -1, bool testMode = false);

    void displayBitPattern(int displayNumber, uint8_t (*pattern)[8]);

    void displayBitPatternAll(uint8_t (*pattern)[MAX_DISPLAYS][8]);

    void createIDArray(string text);

    void loadNextTextBits();

    void shiftText();

    void update();
};

#endif //UNTITLED5_DOTMATRIX_H
