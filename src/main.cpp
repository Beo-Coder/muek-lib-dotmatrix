// Copyright (c) 2023. Leonhard Baschang
// https://github.com/LeoCoder-Maker/muehk-8x8_LED_Dot_Matrix_ScrollText.git
#include "mbed.h"
#include "DOTMATRIX.h"

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
unsigned int scrollSpeed = 40;//Speed of scrolling
const unsigned int displays = 26;//number of 8x8 displays
unsigned int displayBrightness = 5;//0-15
bool reverseDisplay = false;

string inputText = "GDS1 Informatik ist das beste Profilfach der Schule %H% % % % % ";// text to display
//END OF CONFIG






int main() {

    DOTMATRIX matrix(PC_2, PC_0, PC_1, displays, reverseDisplay);
    matrix.setShutdownMode();
    matrix.setDisplayTest();
    matrix.setDecodeMode();
    matrix.setScanLimit();
    matrix.setIntensity(-1,displayBrightness);
    matrix.createIDArray(inputText);

    while(true){
        matrix.update();
        thread_sleep_for(scrollSpeed);
    }







}
