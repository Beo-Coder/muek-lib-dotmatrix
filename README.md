# DOTMATRIX
## MBED libary for MAX7219 driven 8x8 LED dot matrixes

# Features
- Multiple display support
- Scrolling text
- Comes with built-in bit patterns
- Custom bit pattern display
- Each display individually controllable
- Full control over every display

# Usage
## Quick usage
#### Initialize matrix:

`DOTMATRIX matrix(<clkPin>, <dinPin>, <csPin>, <number of displays>, <reverse displays>);`
- **matrix**: name of choice.
- **clkPin**: pin on which the clk pin of the first display is connected. Must be a SPI sclk (e.g. `PB_13`)
- **dinPin**: pin on which the din pin of the first display is connected. Must be a SPI mosi (e.g. `PB_15`)
- **csPin**: pin on which the cs pin of the first display is connected (e.g. `PC_1`)
- **number of displays**: number of displays connected in series (e.g. `4`)
- **reverse displays**: whether the displays are mounted upside down (e.g. `false`)


#### Initialize displays:

`matrix.initDisplays();`


#### Set scrolling text:

`matrix.createIDArray(<text>);`
-	**text**: Text that will be displayed 


#### Update scrolling text:

`matrix.update();`


## Advanced usage
#### Set shutdown mode:
`matrix.setShutdownMode(<displayNumber>, <shutdown>);`

- **displayNumber**: number of display (`-1` for all displays)
- **shutdown**: `true`or `false`


#### Set scan limit:
`matrix.setScanLimit(<displayNumber>, <scanLimit>);`

- **displayNumber**: number of display (`-1` for all displays)
- **scanLimit**: how many lines are dispalyed (`0` -> 1 line, `7` -> all 8 lines)


#### Set decode mode:
`matrix.setDecodeMode(<displayNumber> ,<decodeMode>);`

- **displayNumber**: number of display (`-1` for all displays)
- **decodeMode**: how many lines are dispalyed (`0` -> 1 line, `7` -> all 8 lines)

#### Set display brightness:
`matrix.setIntensity(<displayNumber>, <intensity>);`

- **displayNumber**: number of display (`-1` for all displays)
- **intensity**: brightness of display (from `0`to `15`)

#### Set display test:
`matrix.setDisplayTest(<displayNumber>, <testMode>);`

- **displayNumber**: number of display (`-1` for all displays)
- **testMode**: `true`or `false`

#### Set bit pattern for singe display:
`matrix.displayBitPattern(<displayNumber>, <pattern>);`

- **displayNumber**: number of display
- **pattern**: address of uint8_t array with 8 elemnts (e.g. `&letterA`)

#### Set bit pattern for all displays:
`matrix.displayBitPatternAll(<pattern>);`

- **pattern**: address of two dimesional uint8_t array with 8 elemnts per display (e.g. `&textABC`)

#### Load next bits of text
`matrix.loadNextTextBits();`

#### Shift Text 1 bit to the left
`matrix.shiftText();`

#### Send raw data to display
`matrix.sendByte(<address>, <data>);`

- **address**: address of register (see MAX7219 datasheet)
- **data**: data to load in the register (see MAX7219 datasheet)


## Usage of text input
Decode table (input -> output (on display))

#### Normal characters
A -> A  
B -> B  
...  
y -> y  
z -> z  

0 -> 0  
...  
9 -> 9  

*space* -> *small space (4 dot wide)*  
( -> (  
) -> )  
. -> .  
, -> ,  
_ -> _  
\- -> -  
? -> ?  
! -> !  

#### Special character (with `%` in front (e.g. `%A` -> Ä))
A -> Ä  
a -> ä  
...  
ü -> ü  

*space* -> *space (8 dot wide)*  
1 -> *one blank vertical line*  
2 -> *two blank vertical lines*  
3 -> *three blank vertical lines*  
| -> *one filled vertical line*  

H -> *Heart symbol*  



## Example
### Basic scrolling text example
```c++
main(){
  DOTMATRIX matrix(PC_2, PC_0, PC_1, 4, false);
  matrix.initDisplays();
  matrix.createIDArray("Hello World!% % % %");
  while(true){
    matrix.update();
    thread_sleep_for(40);
  }
}
```

## Limitations
* By default only support up to 50 displays (can be changed in DOTMATRIX.h)
* By default maximum text length is 500 characters (can be changed in DOTMATRIX.h)