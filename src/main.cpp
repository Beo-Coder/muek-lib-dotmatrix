// Copyright (c) 2023. Leonhard Baschang
// https://github.com/LeoCoder-Maker/muehk-8x8_LED_Dot_Matrix_ScrollText.git
#include "mbed.h"
#include "DOTMATRIX.h"

//BEGIN OF CONFIG
unsigned int scrollSpeed = 40;//Speed of scrolling
const unsigned int displays = 26;//number of 8x8 displays
unsigned int displayBrightness = 5;//0-15
bool reverseDisplay = false;

string inputText = "GDS1 Informatik ist das beste Profilfach der Schule %H% % % % % ";// text to display
//END OF CONFIG


int main() {

    DOTMATRIX matrix(PC_2, PC_0, PC_1, displays, reverseDisplay);
    matrix.initDisplays();
    matrix.setIntensity(-1, displayBrightness);
    matrix.createIDArray(inputText);

    while (true) {
        matrix.update();
        thread_sleep_for(scrollSpeed);
    }


}
