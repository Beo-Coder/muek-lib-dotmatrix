#include "DOTMATRIX.h"

DOTMATRIX::DOTMATRIX(PinName clkPin, PinName dinPin, PinName csPin, unsigned int numberDisplays, bool reverseText) {
    clk = new DigitalOut(clkPin);
    cs = new DigitalOut(csPin);
    din = new DigitalOut(dinPin);

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
    uint16_t sendData = (address << 8) | data;
    for (int i = 0; i < 16; i++) {
        din->write((sendData >> (15 - i)) & 1);
        clk->write(1);
        clk->write(0);
    }
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
