#ifndef CustomGraphics_h
#define CustomGraphics_h
 
#define LINE_DEBUG println("line : ",__LINE__);

// #define SPI_HW ((SPI_TypeDef *)0x40013000)
// #define SPI_HW 0x40013000//((SPI_TypeDef *)0x40015000)// 0x40015000 //SPI5//((SPI_TypeDef *) SPI1_BASE) 
#define SPI_HW SPI5

#define SPI_SETTINGS 40000000//8000000
#include <SPI.h>

#define TAB_WIDTH 8//max size that is going to be done

// I STOLE THIS FROM TFT_eSPI *MAKING THIS KNOWN OUT THERE*
// Default color definitions
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */
#define BLOOD_IS_THE_LAW 1 
// 1. Helper macros to turn whatever is in WOKWI_SIM into a "string"
#define STRINGIZE_INTERNAL(x) #x
#define STRINGIZE(x) STRINGIZE_INTERNAL(x)
#define sizeofarray(x) (sizeof(x)/sizeof(x[0]))

//define MIN macro if necessary
#ifndef MIN
    #define MIN(a,b) (a<b?a:b)
#endif

//define MAX macro if hasn't already been done
#ifndef MAX
    #define MAX(a,b) (a>b?a:b)
#endif

#define clearArray(arr, ...) \
for(unsigned int __pAgD67o5 = 0; __pAgD67o5 < sizeofarray(arr); __pAgD67o5++)\
{\
    arr[__pAgD67o5] = __VA_ARGS__;\
}
#define ISLETTER(x)  ((('a' <= x && x <= 'z')||('A' <= x && x <= 'Z'))?(true):(false))
#define ERR_POS -256

// // 2. A simple C++11 constexpr function to compare strings at compile-time
// constexpr bool strings_equal(char const* a, char const* b) {
//     return *a == *b && (*a == '\0' || strings_equal(a + 1, b + 1));
// }

// // 3. The check
// // This will throw a compiler error if SOMETHING is anything else.
// static_assert(!strings_equal(STRINGIZE(WOKWI_SIM), "[0 or 1]"), "haha very funny. you did  \"#define WOKWI_SIM [0 or 1]\" ... but seriously, do something like '#define WOKWI_SIM 1'\n\n\n");

// Are we running Wokwi simulation? (automatically checks based on the current board (if its a mega its wokwiSIM))
#ifndef WOKWI_SIM
  #if defined(__AVR_ATmega2560__) || defined(ARDUINO_AVR_MEGA2560)
    #define WOKWI_SIM 1
  #elif defined(ARDUINO_GIGA)
    #define WOKWI_SIM 0
  #else
    #warning "ERROR, if you don't have a GIGA or a MEGA board, this library most likely wont work, if you want to try anyways do '#define WOKWI_SIM [0 or 1]' just before including the library"
  #endif
#endif

#if WOKWI_SIM
    #define SPI_BUS SPI

    #if defined(EMULATE_SCREEN)
        //detailed explaination : 
        //go read the explaination a couple lines before this one that explains why the arduino mega cannot have a screen buffer (if your intrested)
        //the screen emulation needs a screen buffer, without it we cannot print the state of the screen in the serial monitor, thats why we can't emulate the screen
        //the only way your going to see is with a screen connected to it
        #warning "IMPORTANT, SCREEN EMULATION ON ARDUINO MEGA CANNOT BE DONE DUE TO INSUFICIENT MEMORY, STRONGLY SUGGESTED THAT YOU GET RID OF THE \"#define EMULATE_SCREEN\" LINE"
    #endif

    #if !defined(INVERT_DRAWING_ORDER)
        //detailed explaination : 
        //the arduino GIGA which is more powerful, also has more memory, because of this, I decided that it would be better to have a screen buffer
        //a screen buffer is something to store the screen, imagine storing the screen you are watching, all in memory, every color of every pixel in memory, thats a screen buffer
        //for optimisation reasons, I decided it would be better to draw front to back, meaning to draw the stuff in front before, meaning they hide everything you do afterwards, this can only be achieved with a screen buffer
        //except the arduino MEGA does not have enough memory to store that giant screen buffer, so on arduino mega we take the shortcut and directly display on the screen, this is slower, but its better than not displaying in the first place so deal with it
        #warning "IMPORTANT, ARDUINO MEGA CANNOT DRAW FRONT TO BACK BECAUSE IT HAS NO SCREEN BUFFER, STRONGLY SUGGESTED THAT YOU INVERT DRAWING ORDER WITH \"#define INVERT_DRAWING_ORDER\""
    #endif
#else
    #include "SDRAM.h"

    //no longer needed  
    // #define SPI_BUS SPI1
    #define SPI_BUS println("YOU FORGOT TO GET RID OF THE SPI_BUS AT LINE ",__LINE__);SPI1

    //buffer instead : 
    // Point directly to SDRAM base + offset to avoid conflicts

    #define SCREEN_BUFFER_SIZE SCREEN_WIDTH*2*SCREEN_HEIGHT
    /*inline*/ uint8_t* screenBuffer = nullptr;
    //we don't need to waste sapce if we don't need the drawn pixel buffer
    #if !defined(INVERT_DRAWING_ORDER)
        /*inline*/ uint8_t  drawnPixel[(240 * 320) / 8];
    #endif

    // Hardware pointer to SPI5 (the actual peripheral pins 11,12,13 use)
    #define SPI5_HW ((SPI_TypeDef *)SPI5_BASE)
#endif

/*inline*/ void resetDrawnPixel()
{
    //drawnPixel doesn't exist when inverting the drawing order
    #if !defined(INVERT_DRAWING_ORDER)
        #if WOKWI_SIM
            #error add this line before #include <AwesomeUI.h> or #include <CustomGraphics.h>: '#define INVERT_DRAWING_ORDER', go check warning above for more explaination
        #endif
        for(unsigned int i = 0; i < sizeofarray(drawnPixel); i++)
        {
            drawnPixel[i] = 0;
        }
    #endif
}


struct Color
{
  int r;
  int g;
  int b;
};

struct Pointd;
struct Point
{
    int16_t x;
    int16_t y;
  
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(int x, int y)
    {
        this->x = (int16_t)x;
        this->y = (int16_t)y;
    }
    
    Point(const Pointd& p);
};

struct Pointd
{
    double x;
    double y;
    
    Pointd()
    {
        x = 0;
        y = 0;
    }

    Pointd(const Point& p)
    {
        x = (double)p.x;
        y = (double)p.y;
    }

    Pointd(int x, int y)
    {
        this->x = (double)x;
        this->y = (double)y;
    }  
};

Point::Point(const Pointd& p)
{
    x = (int16_t)p.x;
    y = (int16_t)p.y;
}

struct Size
{
    int16_t w;
    int16_t h;
};

struct BoundingBox
{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
};


//custom nice to have quick prints : 
template <typename T> void print(T input){Serial.print(input);} template<typename T, typename... Args> void print(T input, Args... other){Serial.print(input); print(other...);}/*inline*/ void println(){Serial.println();}template <typename T>void println(T input) {Serial.println(input);}template <typename T, typename... Args> void println(T input, Args... other){Serial.print(input);println(other...);}
template <typename T> void print1(T input){Serial.print(input);} template<typename T, typename... Args> void print1(T input, Args... other){Serial.print(input); Serial.print(", "); print1(other...);}/*inline*/ void println1(){Serial.println();}template <typename T>void println1(T input) {Serial.println(input);}template <typename T, typename... Args> void println1(T input, Args... other){Serial.print(input);Serial.print(", ");println1(other...);}
#if enableTestPrints
/*inline*/ void testprintln(){Serial.println();}template <typename T>void testprintln(T input) {Serial.println(input);}template <typename T, typename... Args> void testprintln(T input, Args... other){Serial.print(input);println(other...);}
#else
/*inline*/ void testprintln(){}template <typename T>void testprintln(T input) {}template <typename T, typename... Args> void testprintln(T input, Args... other){}
#endif
void printerror(){println("ERROR in file ",__FILE__," in function ",__func__," at line ",__LINE__);}
template <typename T> void printerror(T input){println("ERROR in file ",__FILE__," in function ",__func__," at line ",__LINE__,", ",input);}
template <typename T, typename...Args> void printerror(T input, Args... other){println("ERROR in file ",__FILE__," in function ",__func__," at line ",__LINE__,", ",input,other...);}

//the holy grail of printing functions
template <typename T>
void debugHelper(int index, const char* funcInput, T input)
{
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
	}

    print(" = ");
    println(input);

    index++;
}


template <typename T, typename... Args>
void debugHelper(int index, const char* funcInput, T input, Args... other)
{
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
	}

    print(" = ",input,", ");

    //skip the comma for next variable
    index++;

    debugHelper(index, funcInput, other...);
}

template <typename T>
void printArrayHelper(T* input, size_t size)
{
    for(int i = 0; i < size; i++)
    {
        print(input[i]);
        if(i != size - 1)
        {
            print(", ");
        }
    }
}

//very fucking cool function that helps you print an array without having to input the size
#define printArray(x) printArrayHelper(x, sizeof(x) / sizeof(x[0]))
#define printlnArray(x) printArrayHelper(x, sizeof(x) / sizeof(x[0])); println()

#define DEBUG(...) debugHelper(0, #__VA_ARGS__, __VA_ARGS__)

#define DC_PIN 8
#define CS_PIN 10
#define RST_PIN 9
#define BLK_PIN 2

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

#define FRAMEBUFFER_SIZE SCREEN_WIDTH*SCREEN_HEIGHT*2

#define FONT_WIDTH  5
#define FONT_HEIGHT 6

#define ILI9341_CASET 0x2A
#define ILI9341_PASET 0x2B
#define ILI9341_RAMWR 0x2C


#if WOKWI_SIM
    #define DELAY delay
#else
    #define DELAY delay
#endif

//for indexing the right character
/*inline*/ const char* fontChar = "\x1A""aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890+-.,!?=:/*()'_$<>[]~#;";

//the font
const uint8_t font[] = {0b00000001,0b00010101,0b00010101,0b00010000,0b00000000,0b01110100,0b10100100,0b11110111,0b01000111,0b11110001,0b10001100,0b01100001,0b00001110,0b01001010,0b01001100,0b11110100,0b01111101,0b00011000,0b11111000,0b00000000,0b01110100,0b00100000,0b11100111,0b01000110,0b00010000,0b10001011,0b10000010,0b00010111,0b11000110,0b00101111,0b11110100,0b01100011,0b00011000,0b11111000,0b00001110,0b10001111,0b10100000,0b11101111,0b11000011,0b10010000,0b10000111,0b11000100,0b01000111,0b00010000,0b10000100,0b11111100,0b00111001,0b00001000,0b01000000,0b00001110,0b10001011,0b11000010,0b11100111,0b01000010,0b00010011,0b10001011,0b11100001,0b00001111,0b01000110,0b00110001,0b10001100,0b01111111,0b00011000,0b11000100,0b00000100,0b00000001,0b00001000,0b01000111,0b00010000,0b10000100,0b00100011,0b10001000,0b00000010,0b00010000,0b10001000,0b11111000,0b10000100,0b00101001,0b00110010,0b00010000,0b10100110,0b00101001,0b00101000,0b11001011,0b00010100,0b10010100,0b01001000,0b01000010,0b00010000,0b10000010,0b10000100,0b00100001,0b00001000,0b01111100,0b00000000,0b01010101,0b01101011,0b00011101,0b11010110,0b10110101,0b10101101,0b01000000,0b00001111,0b01000110,0b00110001,0b10001110,0b01101011,0b01011001,0b11000100,0b00000000,0b01110100,0b01100010,0b11100111,0b01000110,0b00110001,0b10001011,0b10000001,0b11101000,0b11111010,0b00010000,0b11110100,0b01100011,0b11101000,0b01000000,0b00001111,0b10001011,0b11000010,0b00010111,0b01000110,0b00110001,0b10011011,0b11000000,0b00000100,0b00111101,0b00001000,0b11110100,0b01111101,0b00011000,0b11000100,0b00000110,0b01000001,0b00000100,0b11000111,0b01000001,0b10000011,0b10001011,0b10001000,0b11100010,0b00010000,0b10000100,0b11111001,0b00001000,0b01000010,0b00010000,0b00000000,0b10001100,0b01100010,0b11111000,0b11000110,0b00110001,0b10001011,0b10000000,0b00001000,0b11000101,0b01000100,0b10001100,0b01100010,0b10100101,0b00010000,0b00000000,0b10101101,0b01101010,0b10101010,0b11010110,0b10110101,0b10101010,0b10000001,0b00011000,0b10111010,0b00110001,0b10001100,0b01011101,0b00011000,0b11000100,0b00010001,0b10001011,0b11000010,0b11101000,0b11000101,0b11000100,0b00100001,0b00000000,0b00001111,0b10001001,0b00011111,0b11111000,0b10001000,0b10001000,0b01111100,0b10001100,0b00100001,0b00001000,0b11100111,0b01000100,0b01000100,0b01000111,0b11011101,0b00010011,0b00000110,0b00101110,0b10010100,0b10111110,0b00100001,0b00001011,0b11110000,0b11110000,0b01100010,0b11100111,0b11000011,0b11010001,0b10001011,0b10111110,0b00010001,0b00010001,0b00001000,0b01110100,0b01011101,0b00011000,0b10111001,0b11010001,0b01111000,0b01000010,0b00010111,0b01000110,0b10110101,0b10001011,0b10000000,0b01000010,0b01111100,0b10000100,0b00000000,0b00000001,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,0b01000000,0b00000000,0b00000000,0b00100001,0b00001000,0b01000010,0b00010000,0b00000100,0b01110100,0b01000100,0b01000000,0b00010000,0b00000000,0b11111000,0b00111110,0b00000000,0b00010000,0b00000000,0b00100000,0b00000000,0b00010001,0b00010001,0b00010000,0b01010001,0b00010100,0b00000000,0b00000000,0b10001000,0b01000010,0b00010000,0b01000010,0b00001000,0b01000010,0b00010001,0b00001000,0b01000010,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01111100,0b10001110,0b10100011,0b10001010,0b11100000,0b00001000,0b10001000,0b00100000,0b10000000,0b10000010,0b00001000,0b10001000,0b01110010,0b00010000,0b10000100,0b00111001,0b11000010,0b00010000,0b10000100,0b11100000,0b00000001,0b00010101,0b00010000,0b00000000,0b10101111,0b10101011,0b11101010,0b00000001,0b00000000,0b00000010,0b00010000};

//global::Array
template<typename T>
class Array
{
  public:
  T array[10];
  unsigned int size;
  T nothing;

  //Array::add
  void add(T input)
  {
    //If the size is bellow the total size of the array
    if(size < (sizeof(array) / sizeof(T)))
    {
      //we add an item at the end of the list
      array[size] = input;
      size += 1;//update the size
    }else 
    {
      println("ERROR, function 'add()' wasn't able to add an element to the end of the list because the array is full (max array size is : ",(sizeof(array) / sizeof(T)),", while current size is : ",size,")");
    }
  }

  //Array::remove
  void remove()
  {
    //if the size is bigger than 0 (cuz if size 0 than can't remove shit)
    if(size > 0)
    {
      size -= 1;//just make size smaller (we gonna overide values later)
    }else
    {
      println("ERROR, function 'remove()' wasn't able to remove the last element because the array size was ",size);
    }
  }

  //Array::remove
  void remove(unsigned int index)
  {
    //if the index is between 0 and the current size of the array (if its not, than can't delete)
    if(0 <= index && index <= min((size - 1), (sizeof(array) / sizeof(T) - 1)))
    {
      //go through all of the items after the index and move them one to the left
      for(unsigned int i = index; i < (size - 1); i++)
      {
        array[i] = array[i + 1];
      }

      //reduce the size
      size -= 1;
    }else
    {
      println("ERROR, tried accessing index : ",index," but the range of possible is : ",0," to ",size - 1);
    }
  }

  //Array::at
  T& at(unsigned int index)
  {
    //check if in the array
    if(0 <= index && index <= min((size - 1), (sizeof(array) / sizeof(T) - 1)))
    {
      return array[index];

    //if its not, give error
    }else
    {
      return nothing;//nothing object, useless object that doesn't do anything
      println("ERROR, tried accessing index : ",index," but the range of possible indexs are : ",0," to ",min((size - 1), (sizeof(array) / sizeof(T) - 1)));
    }

    println("WARNING : control reaches end of non-void function [-Wreturn-type] at line ",__LINE__);
  }

  T& operator[](unsigned int index)
  {
    return array[index];
  }

  //Array::Array
  Array()
  {
    this->size = 0;
  };
//   Array(const Array&) = delete;
//   Array& operator=(const Array&) = delete;

  //Array::~Array
  ~Array()
  {
    
  }
};

/*inline*/ int16_t clamp16(int input)
{
    int clamped = min(INT16_MAX, max(INT16_MIN, input));
    if(clamped != input) 
    {
        #ifndef DISABLE_WARNINGS 
            Serial.print(F("WARNING, clamped number '")); Serial.print(input); Serial.print(F("' to '")); Serial.print(clamped); Serial.println(F("'"));
        #endif
    }
    return (int16_t)(clamped);
}

/*inline*/ int16_t clamp16(double input)
{
    return clamp16((int)input);
}

/*inline*/ uint16_t color(byte red, byte green, byte blue)
{    
    #if true //WOKWI_SIM
        // maping the colors from 255 to  their respective map
        red = red * 32 / 256;
        green = green * 64 / 256;
        blue = blue * 32 / 256;

        return ((uint16_t)(red) << 11) + ((uint16_t)(green) << 5) + (uint16_t)(blue);
    #else
        // maping the colors from 255 to  their respective map
        red = red * 64 / 256;
        green = green * 32 / 256;
        blue = blue * 32 / 256;

        return ((uint16_t)(blue) << 11) + ((uint16_t)(red) << 5) + (uint16_t)(green);
    #endif
}

/*inline*/ uint16_t color(Color input)
{
  // maping the colors from 255 to  their respective map
  input.r = input.r * 32 / 256;
  input.g = input.g * 64 / 256;
  input.b = input.b * 32 / 256;
  
  return ((uint16_t)(input.r) << 11) + ((uint16_t)(input.g) << 5) + (uint16_t)(input.b);
}

//other name for the color function (used becuase vs code provides rgb color picking for this specific function)
uint16_t rgb(byte red, byte green, byte blue)
{
    return color(red, green, blue);
}

/*inline*/ Color toColor(uint16_t input)
{
  Color variable;

  variable.r = (((input & 0b1111100000000000) >> 11)) * 256 / 32;
  variable.g = (((input & 0b0000011111100000) >>  5)) * 256 / 64;
  variable.b = (((input & 0b0000000000011111) >>  0)) * 256 / 32;

  return variable;
}

/*inline*/ uint16_t color565(int r, int g, int b)
{
    r = max(0, min(31, r));
    g = max(0, min(63, g));
    b = max(0, min(31, b));

    return ((uint16_t)(r) << 11) + ((uint16_t)(g) << 5) + (uint16_t)(b);
}

/*inline*/ Color toColor565(uint16_t input)
{
    Color c = {0, 0, 0};
    c.r = ((input & 0xF800) >> 11);
    c.g = ((input & 0x7E0)  >>  5);
    c.b = ((input & 0x1F)   >>  0);

    return c;
}

/*inline*/ long long powi(long base, long exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

/*inline*/ unsigned long long upowi(long base, long exp){
    unsigned long long res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

/*inline*/ int getDigits(long long input, int i1, int i2 = -1)
{
    if(i2 == -1)
    {
        i2 = i1;
    }

    return (input / powi(10, i1 - 1) * powi(10, i1 - 1) - input / powi(10, i2) * powi(10, i2)) / powi(10, i1 - 1);
}

/*inline*/ int getDigits(unsigned long long input, int i1, int i2 = -1)
{
    if(i2 == -1)
    {
        i2 = i1;
    }

    return (input / upowi(10, i1 - 1) * upowi(10, i1 - 1) - input / upowi(10, i2) * upowi(10, i2)) / upowi(10, i1 - 1);
}

/*inline*/ double strToNum(const char* str, size_t len = SIZE_MAX)
{
    //figure out the length of "str" (the string) if not already been done (if len equals SIZE_MAX)
    if(len == SIZE_MAX)
    {
        len = 0;
        while(str[len] != '\0')
        {
            len++;
        }
    }
    
    //index to go through the number
    unsigned int i = 0;
    int outputIndex = 0;
    int exponent = 0;
    bool dot = false;
    bool negative = 0;

    double num = 0;

    while(true)
    {
        // println("-> '",str[i],"'");

        //skip all leading spaces or separators
        while(i < len && (str[i] == ' ' || str[i] == '\n' || str[i] == ',' || str[i] == '\''))
        {
            // test print println("skipping");
            i++;
            // test print println("-> '",str[i],"'");
        }

        if(i < len && outputIndex == 0 && str[i] == '-')
        {
            negative = 1;
            i++;
            continue;
        }

        //if we reached the end of the string get out of the loop
        if(i >= len)
        {
            // test print println("getting out of loop");
            break;
        }

        //if we saw a dot (indicates decimal number we set dot to true)
        if(str[i] == '.')
        {
            // test print println("saw dot, disabling exponent count");
            dot = true;
            i++;
            continue;
        }

        char c = str[i];
        int digit = 0;
        if('0' <= c && c <= '9')
        {
            digit = c - '0';//get the digit based on the nifty character trick
            // test print println("saw digit, converted to ",digit);

        }else
        {
            //if its not a digit than throw an error and get out of the function
            // println("ERROR, strToNumber function failed, '",str,"' is not a number");
            // return NAN;
            break;
        }

        num += digit * pow(10, -outputIndex);
        // test print println("added ",digit * pow(10, -outputIndex)," to number : ",num);

        outputIndex++;
        i++;
        if(dot == false)
        {
            exponent++;
            // test print println("increased exponent : ",exponent);
        }
    }

    return (1 - 2 * negative) * num * pow(10, exponent - 1);
}

/**
 * @brief this function pivots a point around a center point by the designated angle
 * @param p point that is getting rotate around center
 * @param c the center point
 * @param a the angle in degrees at which "p" is getting rotated
 * @retval the rotate point around the center based on the angle
 */
/*inline*/ Pointd pivot(Pointd p, Pointd c, double a) 
{
    float rad = a * PI / 180.0;
    float dx = p.x - c.x;
    float dy = p.y - c.y;
    return {
        (int16_t)(c.x + dx * cos(rad) - dy * sin(rad)),
        (int16_t)(c.y + dx * sin(rad) + dy * cos(rad))
    };
}

/*this is a very dumb function to let me see differences between stuff that have a different index so I can see if my shit is optimal, it probably doesn't do what you think it does*/
/*inline*/ uint16_t convertNumberToColor(uint8_t number)
{
    number %= 10;   

    switch (number)
    {
        case 0: return TFT_RED;
        case 1: return TFT_ORANGE;
        case 2: return TFT_YELLOW;
        case 3: return TFT_GREENYELLOW;
        case 4: return TFT_GREEN;
        case 5: return TFT_CYAN;
        case 6: return TFT_BLUE;
        case 7: return TFT_PURPLE;
        case 8: return TFT_MAGENTA;
        case 9: return TFT_PINK;
    }

    return 0;
}

/*inline*/ bool fontUnpacker(int i)
{
  int index = i / 8;
  bool output = (font[index] & (1 << (7 - (i % 8)))) != 0;
  return output;
}

/*inline*/ void writeCommand(uint8_t cmd) {
    #if WOKWI_SIM
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);
        SPI_BUS.transfer(cmd);
        digitalWrite(CS_PIN, HIGH);
    #else
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);
        
        // Manual register transfer
        SPI5_HW->IFCR = 0xFFFFFFFF;
        SPI5_HW->CR2 = 1; // 1 byte
        SPI5_HW->CR1 |= SPI_CR1_CSTART;
        
        while (!(SPI5_HW->SR & SPI_SR_TXP));
        *((volatile uint8_t*)&SPI5_HW->TXDR) = cmd;
        
        while (!(SPI5_HW->SR & SPI_SR_RXP));
        volatile uint8_t dummy = *((volatile uint8_t*)&SPI5_HW->RXDR);
        (void)dummy;
        
        while (!(SPI5_HW->SR & SPI_SR_EOT));
        SPI5_HW->IFCR = SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
        
        digitalWrite(CS_PIN, HIGH);
    #endif
}

/*inline*/ void writeData(uint8_t data) {
    #if WOKWI_SIM
        digitalWrite(DC_PIN, HIGH);
        digitalWrite(CS_PIN, LOW);
        SPI_BUS.transfer(data);
        digitalWrite(CS_PIN, HIGH);
    #else
        digitalWrite(DC_PIN, HIGH);
        digitalWrite(CS_PIN, LOW);
        
        SPI5_HW->IFCR = 0xFFFFFFFF;
        SPI5_HW->CR2 = 1;
        SPI5_HW->CR1 |= SPI_CR1_CSTART;
        
        while (!(SPI5_HW->SR & SPI_SR_TXP));
        *((volatile uint8_t*)&SPI5_HW->TXDR) = data;
        
        while (!(SPI5_HW->SR & SPI_SR_RXP));
        volatile uint8_t dummy = *((volatile uint8_t*)&SPI5_HW->RXDR);
        (void)dummy;
        
        while (!(SPI5_HW->SR & SPI_SR_EOT));
        SPI5_HW->IFCR = SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
        
        digitalWrite(CS_PIN, HIGH);
    #endif
}
// #define writeData println("LINE : ",__LINE__);writeData

#if WOKWI_SIM
    void setWindow(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
        

        int16_t cx1 = max(0, min(240, x1));
        int16_t cy1 = max(0, min(320, y1));
        int16_t cx2 = max(-1, min(239, x2));
        int16_t cy2 = max(-1, min(319, y2));

        #ifndef DISABLE_WARNINGS
            if(cx1 != x1) println(F("WARNING, setWindow clamped x1 ("),x1,F(") to "),cx1);
            if(cy1 != y1) println(F("WARNING, setWindow clamped y1 ("),y1,F(") to "),cy1);
            if(cx2 != x2) println(F("WARNING, setWindow clamped x2 ("),x2,F(") to "),cx2);
            if(cy2 != y2) println(F("WARNING, setWindow clamped y2 ("),y2,F(") to "),cy2);
        #endif

        x1 = cx1;
        y1 = cy1;
        x2 = cx2;
        y2 = cy2;

        if(y2 - y1 + 1 < 0 || x2 - x1 + 1 < 0)
        {
            #ifndef DISABLE_WARNINGS
                Serial.println("WARNING, 0 size setWindow");
            #endif
            
            return;
        }
        
        writeCommand(ILI9341_CASET);
        writeData((uint16_t)cx1 >> 8);
        writeData((uint16_t)cx1 & 0xFF);
        writeData((uint16_t)cx2 >> 8);
        writeData((uint16_t)cx2 & 0xFF);
        
        writeCommand(ILI9341_PASET);
        writeData((uint16_t)cy1 >> 8);
        writeData((uint16_t)cy1 & 0xFF);
        writeData((uint16_t)cy2 >> 8);
        writeData((uint16_t)cy2 & 0xFF);
        
        writeCommand(ILI9341_RAMWR);
    }

#else

    #if defined(EMULATE_SCREEN)

        /*inline*/ void displayFrameBufferSerial() {
            uint8_t* buffer = (uint8_t*)screenBuffer;
            for (uint16_t row = 0; row < 320; row++) {
                udp.beginPacket(computerIP, PORT);
                udp.write((uint8_t*)&row, 2);        // 2 bytes for row index
                udp.write(buffer + row * 480, 480);  // 480 bytes of pixel data
                udp.endPacket();
                delayMicroseconds(500);
            }
        }

    #endif

    /*inline*/ void displayFrameBuffer() {
        
        #if defined(EMULATE_SCREEN)
            displayFrameBufferSerial();
        #endif

        // **DISABLE INTERRUPTS - Critical section**
        // noInterrupts();

        // RESET SPI5 completely before each frame
        SPI5_HW->CR1 &= ~SPI_CR1_SPE; // Disable
        delayMicroseconds(10);
        SPI5_HW->IFCR = 0xFFFFFFFF; // Clear all flags
        SPI5_HW->CR1 |= SPI_CR1_SPE; // Re-enable
        delayMicroseconds(10);
        
        writeCommand(0x2A);
        writeData(0x00); writeData(0x00);
        writeData(0x00); writeData(0xEF);
        
        writeCommand(0x2B);
        writeData(0x00); writeData(0x00);
        writeData(0x01); writeData(0x3F);
        
        writeCommand(0x2C);
        
        digitalWrite(DC_PIN, HIGH);
        digitalWrite(CS_PIN, LOW);
        
        // for(uint32_t i = 0; i < SCREEN_BUFFER_SIZE; i++) {
        //     SPI5_HW->IFCR = 0xFFFFFFFF; // Clear flags EVERY byte
        //     SPI5_HW->CR2 = 1;
        //     SPI5_HW->CR1 |= SPI_CR1_CSTART;
            
        //     while (!(SPI5_HW->SR & SPI_SR_TXP));
        //     *((volatile uint8_t*)&SPI5_HW->TXDR) = screenBuffer[i];
            
        //     while (!(SPI5_HW->SR & SPI_SR_EOT));
        // }

        for(uint32_t i = 0; i < SCREEN_BUFFER_SIZE; i += 2) {
            // Send HIGH byte first, then LOW byte
            uint8_t hi = screenBuffer[i + 1];  // High byte
            uint8_t lo = screenBuffer[i];      // Low byte
            
            // Send HIGH byte
            SPI5_HW->IFCR = 0xFFFFFFFF;
            SPI5_HW->CR2 = 1;
            SPI5_HW->CR1 |= SPI_CR1_CSTART;
            while (!(SPI5_HW->SR & SPI_SR_TXP));
            *((volatile uint8_t*)&SPI5_HW->TXDR) = hi;
            while (!(SPI5_HW->SR & SPI_SR_EOT));
            
            // Send LOW byte
            SPI5_HW->IFCR = 0xFFFFFFFF;
            SPI5_HW->CR2 = 1;
            SPI5_HW->CR1 |= SPI_CR1_CSTART;
            while (!(SPI5_HW->SR & SPI_SR_TXP));
            *((volatile uint8_t*)&SPI5_HW->TXDR) = lo;
            while (!(SPI5_HW->SR & SPI_SR_EOT));
        }
        
        // // **NEW: CRITICAL CLEANUP FOR TOUCH TO WORK**
        // // Wait for the SPI to completely finish
        // // while (SPI5_HW->SR & SPI_SR_BSY);
        // while (SPI5_HW->SR & SPI_SR_EOT) {}  // Wait for End Of Transfer
        // while (!(SPI5_HW->SR & SPI_SR_TXC));  // Wait for TX Complete
                
        // // Clear ALL flags one more time
        // SPI5_HW->IFCR = 0xFFFFFFFF;
        
        // // Deselect display CS
        // digitalWrite(CS_PIN, HIGH);
        
        // // **Give the SPI bus a moment to settle**
        // delayMicroseconds(10);

        // Wait for the SPI to completely finish
        delayMicroseconds(50);  // Give it time to finish

        // Clear ALL flags one more time
        SPI5_HW->IFCR = 0xFFFFFFFF;

        // Deselect display CS
        digitalWrite(CS_PIN, HIGH);

        // Give the SPI bus a moment to settle
        delayMicroseconds(10);

        // **RE-ENABLE INTERRUPTS**
        // interrupts();
    }

    
    
#endif

/*inline*/ Size getTextBounds(const char* text, int16_t fontsize)
{
  unsigned int i = 0;
  int lineLen = 0;
  int maxLineLen = 0;
  int nofnewlines = 1;
  while(text[i] != '\0')
  {
    if(text[i] == '\n')
    {
      nofnewlines += 1;
      lineLen = 0; //reset line length
    }else
    { 
      lineLen += (FONT_WIDTH + 1) * fontsize;//tft.textWidth((const char*)(&text[i]));
    }

    //we get the longest of all of the lines
    if(lineLen > maxLineLen)
    {
      maxLineLen = lineLen;
    }
    

    i++;
  }


  return {(int16_t)(maxLineLen - fontsize), (int16_t)((nofnewlines * (FONT_HEIGHT + 1) - 1) * fontsize)};
}

/*inline*/ Size getTextBounds(String text, int16_t fontsize)
{
    return getTextBounds(text.c_str(), fontsize);
}

/**
 * @brief takes p3 and checks if its to the right of the line segment p1 p2
 * @param p1 first point of the line 
 * @param p2 second point of the line
 * @param p3 the point you want to know if is to the right or left (the left and right are determined by the p1 -> p2 order, meaning if you invert p1 and p2 you invert the output "right" inverts to "left")
 * @retval negative means p3 is left, 0 means p3 is perfecly in between, positive means p3 is right
 */
/*inline*/ int isToRight(Point p1, Point p2, Point p3)
{
    return -((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
}


//global::TFT
class TFT 
{
    public:
    int16_t vx;
    int16_t vy;
    int16_t vw;
    int16_t vh;
    int16_t gx;
    int16_t gy;
    int16_t cursor_x_start;
    int16_t cursor_x;
    int16_t cursor_y;
    int8_t  fontSize;
    uint16_t fontColor;
    Point pencil[15];
    int8_t pencilIndex;


    //TFT::setBrightness
    /**
     * @brief changes the percieved brightness of the TFT screen
     * @param percent the brightness percentage you want
     */
    void setBrightness(int percent)
    {
        #if defined(BLK_PIN)
        
            analogWrite(BLK_PIN, percent * 255 / 100);

        #else

            ::println("couldn't set brightness the Backlight LED Pin (BLK_PIN) wasn't defined (set to something)");

        #endif
    }

    //TFT::getTextBounds
    Size getTextBounds(const char* text, int16_t w, int16_t h, int16_t fontSize)
    {
        return getTextBounds(text, w, h, fontSize);
    }

    //TFT::begin
    // begin() stays mostly the same but ensure SPE stays on
    void begin()
    {

        //set backlight pin to output (so you output a voltage)
        pinMode(BLK_PIN, OUTPUT);
        
        //set brightness by default to max (255)
        setBrightness(100);  // full brightness


        ::println(__func__," ",__FILE__);
        #if !WOKWI_SIM
            if(!SDRAM.begin())
            {
                ::println("ERROR, could not initialize the SDRAM");
                while(true);
            }

            Serial.println("Testing SDRAM access...");
            
            screenBuffer = (uint8_t*)SDRAM.malloc(SCREEN_WIDTH * 2 * SCREEN_HEIGHT);

            if(screenBuffer == nullptr)
            {
                ::println("ERROR, allocation to SDRAM failed");
                while(true);
            }else
            {
                ::println("SUCCESS, the SDRAM seems to work");
                for(unsigned int i = 0; i < SCREEN_BUFFER_SIZE; i++)
                {
                    screenBuffer[i] = 0;
                }
            }   
            

            //clear the drawnPixel array (does nothing if we inverted the drawing order)
            resetDrawnPixel();
        #endif

        pinMode(DC_PIN, OUTPUT);
        pinMode(CS_PIN, OUTPUT);
        pinMode(RST_PIN, OUTPUT);
        
        digitalWrite(CS_PIN, HIGH);
        // digitalWrite(DC_PIN, HIGH);
        
        digitalWrite(RST_PIN, LOW);
        DELAY(20);
        digitalWrite(RST_PIN, HIGH);
        DELAY(150);
        
        #if WOKWI_SIM
            ::println("WOKWI_SIM");
            SPI_BUS.setClockDivider(SPI_CLOCK_DIV2);
            SPI_BUS.begin();
        #else
            
            // Let Arduino library init SPI5
            Serial.println("Initializing with SPI1.begin()...");
            SPI1.begin();
            SPI1.beginTransaction(SPISettings(80000000, MSBFIRST, SPI_MODE0)); // FAST!
            
            Serial.println("SPI1.begin() done, checking SPI5 registers...");
            Serial.print("SPI5->CR1:  0x"); Serial.println(SPI5_HW->CR1, HEX);
            Serial.print("SPI5->SR:   0x"); Serial.println(SPI5_HW->SR, HEX);
            Serial.print("SPI5->CFG1: 0x"); Serial.println(SPI5_HW->CFG1, HEX);
            Serial.print("SPI5->CFG2: 0x"); Serial.println(SPI5_HW->CFG2, HEX);
            
            if (!(SPI5_HW->CR1 & SPI_CR1_SPE)) {
                Serial.println("ERROR: SPI5 not enabled!");
                while(1);
            }

            
            Serial.println("SPI5 is ON! Testing register writes...");
        #endif

        writeCommand(0xC1);  // PWCTR2
        writeData(0x10);     // SAP[2:0];BT[3:0]

        // VCOM control
        writeCommand(0xC5);  // VMCTR1
        writeData(0x3e);
        writeData(0x28);
        
        writeCommand(0xC7);  // VMCTR2
        writeData(0x86);
        
        // Memory access control (rotation)
        writeCommand(0x36);  // MADCTL

        // #if WOKWI_SIM
            writeData(0x48);     // MX, BGR (adjust for your screen orientation)
        // #else
        //     ::println("doing thei thing please work for the fucking love of god ");   
        //     writeData(0x08);
        // #endif
        // Pixel format

        
        writeCommand(0x3A);  // PIXFMT
        writeData(0x55);     // 16-bit color (RGB565)
        
        // Frame rate
        writeCommand(0xB1);  // FRMCTR1
        writeData(0x00);
        writeData(0x18);     // 79Hz
        
        // Display function control
        writeCommand(0xB6);  // DFUNCTR
        writeData(0x08);
        writeData(0x82);
        writeData(0x27);
        
        // Gamma settings (optional but recommended)
        writeCommand(0xE0);  // GMCTRP1 (Positive Gamma)
        writeData(0x0F);
        writeData(0x31);
        writeData(0x2B);
        writeData(0x0C);
        writeData(0x0E);
        writeData(0x08);
        writeData(0x4E);
        writeData(0xF1);
        writeData(0x37);
        writeData(0x07);
        writeData(0x10);
        writeData(0x03);
        writeData(0x0E);
        writeData(0x09);
        writeData(0x00);
        
        writeCommand(0xE1);  // GMCTRN1 (Negative Gamma)
        writeData(0x00);
        writeData(0x0E);
        writeData(0x14);
        writeData(0x03);
        writeData(0x11);
        writeData(0x07);
        writeData(0x31);
        writeData(0xC1);
        writeData(0x48);
        writeData(0x08);
        writeData(0x0F);
        writeData(0x0C);
        writeData(0x31);
        writeData(0x36);
        writeData(0x0F);
        
        // Exit sleep and turn on display
        writeCommand(0x11);  // SLPOUT
        DELAY(120);
        
        writeCommand(0x29);  // DISPON (Display ON)
        DELAY(20);
        
        ::println("Display init complete!");
    }

    //TFT::setViewport
    void setViewport(int16_t x, int16_t y, int16_t w, int16_t h)
    {
        w = w + x - 1;
        h = h + y - 1;
    
        x = max( 0, min(240, x));
        y = max( 0, min(320, y));
        w = max(-1, min(239, w));
        h = max(-1, min(319, h));

        w = w - x + 1;
        h = h - y + 1;

        vx = x;
        vy = y;
        vw = w;
        vh = h;
    }

    //TFT::drawPixel
    void drawPixel(int16_t x, int16_t y, uint16_t color) {

        // //update position based on global
        // x += gx;
        // y += gy;

        //if the pixel is not inside of the viewport
        if (x < vx || vx + vw - 1 < x || y < vy || vy + vh - 1 < y) return;

        #if WOKWI_SIM            
            setWindow(x, y, x, y);
            writeData(color >> 8);
            writeData(color & 0xFF);
        #else
            // delay(500);

            #if defined(INVERT_DRAWING_ORDER)
                //draw the pixel in the screen buffer
                *((uint16_t*)(screenBuffer + ((y) * SCREEN_WIDTH * 2) + ((x) * 2))) = color;
            #else
                // calculate the index in the array based on the position of the pixel (assuming that each pixel has a different index and that the array is all of the rows of the screen one after the other starting from top of the screen to the bottom)
                int truei = (x + SCREEN_WIDTH * y);
                
                //index it in the array of bytes (uint8_t) to see if we've already drawn at this place (if yes, don't waste time on drawing it)(if no, draw it and add it to the list)
                if(!(drawnPixel[truei / 8] & (0b1 << (truei % 8))))
                {
                    //draw the pixel in the screen buffer
                    *((uint16_t*)(screenBuffer + ((y) * SCREEN_WIDTH * 2) + ((x) * 2))) = color;
                    
                    //add the pixel to the list of no draws
                    drawnPixel[truei / 8] |= (0b1 << (truei % 8));
                }
            #endif

        #endif
    }

    //TFT::drawPixel
    void drawPixel(Point p, uint16_t color)
    {
        drawPixel(p.x, p.y, color);
    }

    //TFT::drawPixelNoCheck
    void drawPixelNoCheck(int16_t x, int16_t y, uint16_t color) {
        // //update position to be based on global
        // x += gx;
        // y += gy;

        #if WOKWI_SIM            
            setWindow(x, y, x, y);
            writeData(color >> 8);
            writeData(color & 0xFF);
        #else
            *((uint16_t*)(screenBuffer + (y * SCREEN_WIDTH * 2) + (x * 2))) = color;
        #endif
    }

    //TFT::fillRect
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
        
        #if WOKWI_SIM
            //update position to be based on global
            // x += gx;
            // y += gy;
        #endif

        w = w + x - 1;
        h = h + y - 1;
    
        x = max((vx), min((vx + vw), x)); // (vx), (vx + vw)
        y = max((vy), min((vy + vh), y)); // (vy), (vy + vh)
        w = max((vx - 1), min((vx + vw - 1), w)); // (vx - 1), (vx + vw - 1)
        h = max((vy - 1), min((vy + vh - 1), h)); // (vy - 1), (vy + vh - 1)

        w = w - x + 1;
        h = h - y + 1;
        
        //if on mega, then directly transfer the fillRect to the screen
        #if WOKWI_SIM   
            setWindow(x, y, x + w - 1, y + h - 1);
            
            uint32_t totalPixels = (uint32_t)w * (uint32_t)h;
            uint8_t hi = color >> 8;
            uint8_t lo = color & 0xFF;
            
            digitalWrite(CS_PIN, LOW);
            digitalWrite(DC_PIN, HIGH);

            for (uint32_t i = 0; i < totalPixels; i++) {

                SPI_BUS.transfer(hi);
                SPI_BUS.transfer(lo);
            }

            digitalWrite(CS_PIN, HIGH);

        //else, on giga, we have enough space for a screen buffer so write to the screen buffer instead
        #else

            #if defined(INVERT_DRAWING_ORDER)
            
                for(int i = x; i <= (x + w - 1); i++)
                {
                    for(int j = y; j <= (y + h - 1); j++)
                    {
                        *((uint16_t*)(screenBuffer + ((j) * SCREEN_WIDTH * 2) + ((i) * 2))) = color;
                    }
                }
            #else

                // 1. Calculate how many pixels to draw to get to the first 8-bit boundary
                int startPixels = (8 - (x % 8)) % 8;
                if (startPixels > w) startPixels = w; 

                // 2. Calculate how many FULL 8-pixel blocks are in the middle
                int middlePacks = (w - startPixels) / 8;

                // 3. Calculate how many pixels are left over at the end
                int endPixels = (w - startPixels) % 8;

                for (int j = 0; j < h; j++) {
                    int current_y = y + j;
                    // int drawnIdxBase = (x + y * SCREEN_WIDTH) / 8; // Example base index

                    // --- PART 1: THE START (Slow bits) ---
                    for (int i = 0; i < startPixels; i++) {
                        drawPixel(x + i, current_y, color);
                    }

                    // --- PART 2: THE MIDDLE (The "Speed Demon" Section) ---
                    // Calculate the starting byte index for this row
                    int byteIdx = (x + startPixels + (current_y * SCREEN_WIDTH)) / 8;

                    for (int l = 0; l < middlePacks; l++) {
                        uint8_t& status = drawnPixel[byteIdx + l];

                        if (status == 0x00) { // ALL EMPTY
                            // The compiler will likely "unroll" this into a single SDRAM burst!
                            for (int i = 0; i < 8; i++) {
                                drawPixelNoCheck(x + startPixels + l * 8 + i, current_y, color);
                            }
                            status = 0xFF; // Mark all 8 as drawn
                        } 
                        else if (status != 0xFF) { // SOME EMPTY
                            for (int i = 0; i < 8; i++) {
                                drawPixel(x + startPixels + l * 8 + i, current_y, color);
                            }
                        }
                        // If status == 0xFF, we do NOTHING. We just skip 8 pixels in 1 cycle!
                    }

                    // --- PART 3: THE END (Remaining bits) ---
                    int endX = x + startPixels + (middlePacks * 8);
                    for (int i = 0; i < endPixels; i++) {
                        drawPixel(endX + i, current_y, color);
                    }
                }



                // //go through every possibilities of the rectangles
                // for(int i = 0 ; i < w; i++)
                // {
                //     for(int j = 0; j < h; j++)
                //     {
                //         //draw the pixel at the coordinates
                //         drawPixel(x + i, y + j, color);
                //     }
                // }
            #endif
        #endif
    }


    void testfillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
        
        #if WOKWI_SIM
            //update position to be based on global
            // x += gx;
            // y += gy;
        #endif

        w = w + x - 1;
        h = h + y - 1;
    
        x = max((vx), min((vx + vw), x)); // (vx), (vx + vw)
        y = max((vy), min((vy + vh), y)); // (vy), (vy + vh)
        w = max((vx - 1), min((vx + vw - 1), w)); // (vx - 1), (vx + vw - 1)
        h = max((vy - 1), min((vy + vh - 1), h)); // (vy - 1), (vy + vh - 1)

        w = w - x + 1;
        h = h - y + 1;
        
        //if on mega, then directly transfer the fillRect to the screen
        #if WOKWI_SIM   
            setWindow(x, y, x + w - 1, y + h - 1);
            
            uint32_t totalPixels = (uint32_t)w * (uint32_t)h;
            uint8_t hi = color >> 8;
            uint8_t lo = color & 0xFF;
            
            digitalWrite(CS_PIN, LOW);
            digitalWrite(DC_PIN, HIGH);

            for (uint32_t i = 0; i < totalPixels; i++) {

                SPI_BUS.transfer(hi);
                SPI_BUS.transfer(lo);
            }

            digitalWrite(CS_PIN, HIGH);

        //else, on giga, we have enough space for a screen buffer so write to the screen buffer instead
        #else

            for(int j = 0; j < h; j++)
            {
                for(int i = 0; i < w; i++)
                {
                    drawPixelNoCheck(x + i, y + j, color);
                }
            }

            // //go through every possibilities of the rectangles
            // for(int i = 0 ; i < w; i++)
            // {
            //     for(int j = 0; j < h; j++)
            //     {
            //         //draw the pixel at the coordinates
            //         drawPixel(x + i, y + j, color);
            //     }
            // }
        #endif
    }

    //TFT::fillScreen
    void fillScreen(uint16_t colour)
    {
        fillRect(vx, vy, vw, vh, colour);
    }

    //TFT::drawRect
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t colour)
    {
        //big switch (when the b is x, big switch switches between left and right, when b is y, it switches up and down
        for(int a = 0; a <= 1; a += 1)
        {
            //x and y switch
            for(int b = 0; b <= 1; b += 1)
            {
                // setWindow(x + ((b)?(0):(((a)?(w - 1):(0)))), y + ((b)?(((a)?(h - 1):(0))):(0)), x + ((b)?(w - 1):(((a)?(w - 1):(0)))), y + ((b)?(((a)?(h - 1):(0))):(h - 1)));

                fillRect(x + ((b)?(0):(((a)?(w - 1):(0)))),
                         y + ((b)?(((a)?(h - 1):(0))):(0)),
                         x + ((b)?(w - 1):(((a)?(w - 1):(0)))) - (x + ((b)?(0):(((a)?(w - 1):(0))))) + 1,
                         y + ((b)?(((a)?(h - 1):(0))):(h - 1)) - (y + ((b)?(((a)?(h - 1):(0))):(0))) + 1,
                         colour);

                // uint8_t hi = colour >> 8;
                // uint8_t lo = colour & 0xFF;
                
                // digitalWrite(DC_PIN, HIGH);
                // digitalWrite(CS_PIN, LOW);

                // for (int i = 0; i < ((b)?(w):(h)); i++) {
                //     SPI_BUS.transfer(hi);//BE CAREFULL' WON'T WORK ON GIGA (NO TRANSACTIONS)
                //     SPI_BUS.transfer(lo);
                // }
                // digitalWrite(CS_PIN, HIGH);
            }
        }
    }

    //TFT::drawChar
    void drawChar(char c, int16_t x, int16_t y, int16_t si, uint16_t colour)
    {
        //return if the character is space (we don't need to draw space)
        if(c == ' ' || c == '\t')
        {
            return;
        }

        int charIndex = -1;
        for (int i = 0; (int unsigned)i < strlen(fontChar); i++)
        {
            if(fontChar[i] == c)
            {
                charIndex = i;
                break;
            }
        }

        //si ont a pas trouvé le charactère (c)
        if (charIndex == -1)
        {
            Serial.print("ERROR, couldn't find the character : '"); Serial.print(c); Serial.print("' -> "); Serial.println((uint8_t)c);
            // DELAY(1000);
            charIndex = 0;//put the "unknown" character

            // return;
        }

        //iChar c'est l'index de la lettre. (A,B,C, etc...)
        for (int iChar = charIndex; iChar < 1 + charIndex; iChar ++) //ont rajoute charIndex pour modifier où ont itère (trust sa marche)
        {
            //itération de la position y de la lettre
            for (int posY = 0; posY < 6 * si; posY += si) //ont ajoute la position pour déplacé la lettre
            {
            //itération de la position x de la lettre
            for (int posX = 0; posX < 5 * si; posX += si)
            {
                //ont vas déterminé l'index qu'il faut pour déterminé l'index dans la variables font
                int trueIndex = iChar * 5 * 6 + posY / si * 5 + posX / si;

                if (fontUnpacker(trueIndex))
                {
                    fillRect((uint16_t)(posX + x), (uint16_t)(posY + y), (uint16_t)(si), (uint16_t)(si), colour);
                }
            }
            }
        }
    }

    //TFT::setCursor
    void setCursor(int16_t cursor_x, int16_t cursor_y)
    {
        this->cursor_x  = cursor_x;
        this->cursor_y  = cursor_y;
    }

    //TFT::setCursor
    void setCursor(int16_t cursor_x, int16_t cursor_y, int8_t fontSize, uint16_t fontColor)
    {
        this->cursor_x  = cursor_x;
        this->cursor_y  = cursor_y;
        this->fontSize  = fontSize;
        this->fontColor = fontColor;
    }

    //TFT::setCursor
    void setCursor(int16_t cursor_x, int16_t cursor_y, int8_t fontSize, uint16_t fontColor, int16_t cursor_x_start)
    {
        this->cursor_x = cursor_x;
        this->cursor_y = cursor_y;
        this->fontSize = fontSize;
        this->fontColor = fontColor;
        this->cursor_x_start = cursor_x_start;
    }

    //TFT::print
    void s_print(const char* s)
    {
        if(s == nullptr)
        {
            Serial.print("ERROR line ");Serial.print(__LINE__);Serial.println(" in function print, the string inputed in the function did not point to a valid place in memory (it was a nullptr)");
            return;
        }

        //iterate through all of the string
        int i = 0;
        while(s[i] != '\0')
        {

            if(s[i] == '\n')
            {
                cursor_y += (FONT_HEIGHT + 1) * fontSize;//step the cursor_y down (since new line)
                cursor_x = cursor_x_start;//reset x
                
            }else
            {
                drawChar(s[i], cursor_x, cursor_y, fontSize, fontColor);

                cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character
            }

            i++;
        }
    }

    //TFT::print
    void s_print(String s)
    {
        s_print(s.c_str());
    }

    //TFT::print
    void s_print(char c)
    {
        if(c == '\n')
        {
            cursor_y += (FONT_HEIGHT + 1) * fontSize;//step the cursor_y down (since new line)
            cursor_x = cursor_x_start;//reset x
            
        }else
        {
            //draw the character
            drawChar(c, cursor_x, cursor_y, fontSize, fontColor);

            cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character
        }
    }

    //TFT::print
    void s_print(long long n)
    {

        int nlength = 0;//length of the number
        {
            long long n2 = n;//copy n
            while(0 < n2)
            {
                //everytime that ther is a new number we get rid of it and add to the counter of numbers we have
                n2 /= 10;
                nlength += 1;
            }
        }


        //we will go through all of the digits of the number, starting from the left (the biggest digits, to the smallest)
        while(nlength > 0)
        {

            //convert the number into a character
            char converted = '0' + getDigits(n, nlength);

            //draw that character
            drawChar(converted, cursor_x, cursor_y, fontSize, fontColor);

            //move the cursor to the right
            cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character

            //update our index, which is nlength
            nlength -= 1;
        }

    }

    //TFT::print
    void s_print(unsigned long long n)
    {
        int nlength = 0;//length of the number
        {
            long long n2 = n;//copy n
            while(0 < n2)
            {
                //everytime that there is a new number we get rid of it and add to the counter of numbers we have
                n2 /= 10;
                nlength += 1;
            }
        }

        //we will go through all of the digits of the number, starting from the left (the biggest digits, to the smallest)
        while(nlength > 0)
        {
            //convert the number into a character
            char converted = '0' +  getDigits(n, nlength);

            //draw that character
            drawChar(converted, cursor_x, cursor_y, fontSize, fontColor);

            //move the cursor to the right
            cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character

            //update our index, which is nlength
            nlength -= 1;
        }
    }

    //TFT::print
    void s_print(long n)
    {
        s_print((long long)(n));
    }

    //TFT::print
    void s_print(unsigned long n)
    {
        s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(int n)
    {
        s_print((long long)(n));
    }

    //TFT::print
    void s_print(unsigned int n)
    {
        s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(unsigned char n)
    {
        s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(double d)
    {

        long long n = d*1000000;//convert double to long long

        int nlength = 0;//length of the number
        {
            long long n2 = n;//copy n
            while(0 < n2)
            {
                //everytime that ther is a new number we get rid of it and add to the counter of numbers we have
                n2 /= 10;
                nlength += 1;
            }
        }

        //we will go through all of the digits of the number, starting from the left (the biggest digits, to the smallest)
        int i = nlength;
        while(6 < i)
        {

            //convert the number into a character
            char converted = '0' +  getDigits(n, i);

            //draw that character
            drawChar(converted, cursor_x, cursor_y, fontSize, fontColor);

            //move the cursor to the right
            cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character

            //update our index, which is i
            i -= 1;
        }

        //draw the middle dot
        drawChar('.', cursor_x, cursor_y, fontSize, fontColor);
        
        //move the cursor to the right
        cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character


        //get rid of the digits before the dot
        n = getDigits(n, 0, 6);

        //update nlength to go reverse so we don't include ending zero digits
        {
            nlength = 0;//reset nlength
            long long n2 = n;//copy n
            while(0 < n2)
            {
                //remove the most significant digit
                n2 = getDigits(n2, 1, 6 - nlength);

                nlength += 1;

                if(6 < nlength - 1)
                {
                    Serial.print("ERROR line ");Serial.print(__LINE__);Serial.println(", nlength hast gone outside of what it should be at");
                    while(true);//hold
                }
            }

            nlength -= 1; //decrease nlength by one because was causing issues (wouldn't get the right size)
        }


        //print all of the last digits after the dot
        for(int i = 0; i < nlength; i++)
        {

            //convert the number into a character
            char converted = '0' + getDigits(n, 6 - i);

            //draw that character
            drawChar(converted, cursor_x, cursor_y, fontSize, fontColor);

            //move the cursor to the right
            cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character
        }

    }

    void print(){}

    template<typename T> 
    void print(T input){s_print(input);}

    template<typename T, typename... Args>
    void print(T input, Args... other){s_print(input); print(other...);}

    void println(){s_print('\n');}

    template<typename T>
    void println(T input){s_print(input); s_print('\n');}

    template<typename T, typename... Args>
    void println(T input, Args... other){s_print(input); println(other...);}



    //TFT::drawText
    void drawText(const char* s, int16_t x, int16_t y, int16_t si, uint16_t colour, bool wrapText)
    {
        int i = 0;
        int displacement = 0;
        while((unsigned int)i < strlen(s))
        {
            char sChar = s[i];
            if(sChar == '\n')
            {
                y += si * 7;//move the text down one line
                displacement = -(i + 1);
                
            }else if(sChar != ' ')//if its not a space
            {
                drawChar(sChar, x + i * 6 * si + displacement * 6 * si, y, si, colour);
            }

            if(sChar != '\n')
            {
                if((SCREEN_WIDTH - 1 < (x + i * 6 * si + displacement * 6 * si) + (FONT_WIDTH + 1) * si) && wrapText)
                {
                    //simulate a new line
                    y += si * 7;//move the text down one line
                    displacement = -(i + 1); 
                }
            }
            
            i++;
        }
    }

    //TFT::drawText
    void drawText(const char* s, int16_t x, int16_t y, int16_t si, uint16_t colour)
    {
        drawText(s, x, y, si, colour, 0);
    }


    //TFT::drawText
    void drawText(String s, int16_t x, int16_t y, int16_t si, uint16_t colour)
    {
        drawText(s.c_str(), x, y ,si, colour, 0);
    }
    //TFT::drawText
    void drawText(String s, int16_t x, int16_t y, int16_t si, uint16_t colour, bool wrapText)
    {
        drawText(s.c_str(), x, y ,si, colour, wrapText);
    }

    //TFT::drawLine
    void drawLine(double x1, double y1, double x2, double y2, uint16_t colour)
    {
        ((x1)>(x2)?(x1):(x2)) += 1;
        ((y1)>(y2)?(y1):(y2)) += 1;

        //get the rule of the line (y = ax + b)
        double a = (y2 - y1) / (x2 - x1);
        double b = y1 - a * x1;

        //get the total width and height for later iteration
        int w = abs((int)(x2 - x1));
        int h = abs((int)(y2 - y1));

        //iterate either over the height (if the line is more horizontal) or wdith (if its more vertical)
        for(int i = 0; i < ((-1 <= a && a <= 1)?(h):(w)); i++)
        {
            uint16_t x3;
            uint16_t y3;
            uint16_t w3;
            uint16_t h3;

            //if line is more horizontal we get the horizontal blocks
            if(-1 <= a && a <= 1)
            {
                double y     = (min((int)y1,(int)y2) + i);
                double x     = (y2 == y1)?(x1):((y - b) / a);
                double nexty = (min((int)y1,(int)y2) + i + 1);
                double nextx = (y2 == y1)?(x1):((nexty - b) / a);

                int width  = (int)ceil(max(nextx, x)) - (int)floor(min(nextx, x));
                int xstart = floor(min(nextx, x));

                // x3 = clamp16(xstart);
                // y3 = clamp16(y);
                // x4 = clamp16(xstart + width);
                // y4 = clamp16(y);
                x3 = clamp16(xstart);
                y3 = clamp16(y);
                w3 = clamp16(width);
                h3 = clamp16(1);

                // nOfPixels = width;
            }else
            {
                double x     = (min((int)x1,(int)x2) + i);
                double y     = (x2 == x1)?(y1):(a * x + b);
                double nextx = (min((int)x1,(int)x2) + i + 1);
                double nexty = (x2 == x1)?(y1):(a * nextx + b);

                int height  = (int)ceil(max(nexty, y)) - (int)floor(min(nexty, y));
                int ystart = floor(min(nexty, y));

                // x3 = clamp16(x);
                // y3 = clamp16(ystart);
                // x4 = clamp16(x);
                // y4 = clamp16(ystart + height);
                x3 = clamp16(x);
                y3 = clamp16(ystart);
                w3 = clamp16(1);
                h3 = clamp16(height);

                // nOfPixels = height;
            }


            fillRect(x3, y3, w3, h3, colour);
            // setWindow(x3, y3, x4, y4);

            // uint8_t hi = colour >> 8;
            // uint8_t lo = colour &  0xFF;

            // digitalWrite(DC_PIN, HIGH);
            // digitalWrite(CS_PIN, LOW);

            // for(int k = 0; k < nOfPixels; k++)
            // {
            //     SPI_BUS.transfer(hi);//WON'T WORK ON GIGA, NO TRANSACTIONS
            //     SPI_BUS.transfer(lo);
            // }
            
            // digitalWrite(CS_PIN, HIGH);
        }

    }

    //TFT::drawLine
    void drawLine(Point p1, Point p2, uint16_t colour){drawLine(p1.x, p1.y, p2.x, p2.y, colour);}

    //TFT::drawOctantOfCircle
    void drawOctantOfCircle(int octant, double x, double y, double r, uint16_t colour)
    {
        if(0 <= octant && octant <= 7)
        {
            bool b  = !((bool)(octant & 0b00000010));
            int  c  = (b != ((bool)(octant & 0b00000100))) * 2 - 1;
            int  a  = ((bool)(octant & 0b00000100) != (bool)(octant & 0b00000001)) * 2 - 1;

            //a is for small switch
            //b is for switching x and y axis
            //c is for big switch

            double distance = (r / sqrt(2.0));
            double s = r - distance;

            for(int i = 0; i < (int)ceil(s) + 1; i++)
            {
                // uint16_t x1;
                // uint16_t y1;
                // uint16_t x2;
                // uint16_t y2;
                int nOfPixels;

                if(b)
                {
                    double ya     = y + c * (-r + i - 0.5);
                    double xa     = a * sqrt(pow(r, 2.0) - pow(ya - y, 2.0)) + x;
                    double nextya = y + c * (-r + i + 0.5);
                    double nextxa = a * sqrt(pow(r, 2.0) - pow(nextya - y, 2.0)) + x;

                    //check for nan 
                    if(xa != xa)
                    {
                        xa = x;
                    }

                    //check for nan
                    if(nextxa != nextxa)
                    {
                        nextxa = x;
                    }

                    println1(ya, xa, nextya, nextxa);

                    int xstart = floor(min(nextxa, xa));
                    int width  = ceil(max(nextxa, xa)) - xstart;

                    // x1 = clamp16(xstart);
                    // y1 = clamp16(ya);
                    // x2 = clamp16(xstart + width);
                    // y2 = clamp16(ya);

                    nOfPixels = width;
                }else
                {
                    double xa     = x + c * (-r + i);
                    double ya     = a * sqrt(pow(r, 2.0) - pow(xa - x, 2.0)) + y;
                    double nextxa = x + c * (-r + i + 1);
                    double nextya = a * sqrt(pow(r, 2.0) - pow(nextxa - x, 2.0)) + y;

                    //check for nan
                    if(ya != ya)
                    {
                        ya = 0.0;
                    }

                    //check for nan
                    if(nextya != nextya)
                    {
                        nextya = 0.0;
                    }

                    int ystart = floor(min(nextya, ya));
                    int height = ceil(max(nextya, ya)) - ystart;

                    // x1 = clamp16(xa);// - ((c<0)?(1):(0)));
                    // y1 = clamp16(ystart);
                    // x2 = clamp16(xa);
                    // y2 = clamp16(ystart + height);

                    nOfPixels = height;
                }

                #if !WOKWI_SIM
                    SPI_BUS.beginTransaction(SPISettings(SPI_SETTINGS, MSBFIRST, SPI_MODE0));
                #endif

                digitalWrite(CS_PIN, LOW);

                // setWindow(x1, y1, x2, y2);

                uint8_t hi = colour >> 8;
                uint8_t lo = colour &  0xFF;

                digitalWrite(DC_PIN, HIGH);

                for(int k = 0; k < nOfPixels; k++)
                {

                    SPI_BUS.transfer(hi);
                    SPI_BUS.transfer(lo);

                }
                
                digitalWrite(CS_PIN, HIGH);

                #if !WOKWI_SIM
                    SPI_BUS.endTransaction();
                #endif
            }
        }else

        {
            ::println("ERROR, drawOctantCircle recieved '",octant,"' but the range of possible octants are from 0 to 7 (this makes for 8 possiblilities because there are 8 octants in a circle)");
        }
    }
    //TFT::drawCircle
    void drawCircle(double x, double y, double r, uint16_t colour)
    {
        ::println("ACCESS DENIED");
        return;

        //normal  : (sqrt(pow(r, 2.0) - pow(x - a, 2.0)) + b );
        //inverse : sqrt(pow(r, 2.0) - pow(y - b, 2.0)) + a ;

        //draw circle in 8 parts
        for(int i = 0; i < 8; i++)
        {
            drawOctantOfCircle(i, x, y, r, colour);
        }
    }

    //TFT::fillCircle
    void fillCircle(double x, double y, double r, uint16_t colour)
    {
        int totalheight = (int)ceil(y + r) - (int)floor(y - r);
        for(int i = 0; i <= totalheight; i++)
        {
            //normal  : (sqrt(pow(r, 2.0) - pow(x - a, 2.0)) + b );
            //inverse : sqrt(pow(r, 2.0) - pow(y - b, 2.0)) + a ;

            int startY = ((int)floor(y - r) + i);
            double funcStart1 = sqrt(pow(r, 2.0) - pow(((y - r + i) - 0.5) - y, 2.0));
            double funcStart2 = sqrt(pow(r, 2.0) - pow(((y - r + i) + 0.5) - y, 2.0));

            //check if funcStart1 is Nan and set it to 0 if it is
            if(funcStart1 != funcStart1)
            {
                funcStart1 = 0.0;
            }

            //check if funcStart2 is Nan and set it to 0 if it is
            if(funcStart2 != funcStart2)
            {
                funcStart2 = 0.0;
            }
            
            int startX = floor(min(x - funcStart1, x - funcStart2));
            int width  = ceil(max(x + funcStart1, x + funcStart2)) - startX + 1;

            fillRect(clamp16(startX), clamp16(startY), clamp16(width), clamp16(startY), colour);
        }
    }

    //TFT::drawTriangle
    void drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour)
    {
        //simply draw lines between all of the points
        drawLine(x1, y1, x2, y2, colour);
        drawLine(x1, y1, x3, y3, colour);
        drawLine(x2, y2, x3, y3, colour);
    }

    //TFT::fillTriangle
    void fillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour)
    {
        
        // debug triangle
        // drawTriangle(x1, y1, x2, y2, x3, y3, color(255, 0, 0));

        //classify all of the x and y coordinates highest to lowest y
        {
            int16_t y[3];
            int16_t x[3];

            y[0] = y1;
            y[1] = y2;
            y[2] = y3;
            x[0] = x1;
            x[1] = x2;
            x[2] = x3;

            //find the lowest of the numbers
            int16_t best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                printerror("could not find the lowest number");
            }

            y1 = y[best_i];//set smallest number
            x1 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                printerror("could not find the lowest number");
            }

            y2 = y[best_i];//set smallest number
            x2 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                printerror("could not find the lowest number");
            }

            y3 = y[best_i];//set smallest number
            x3 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            if(x1 == INT16_MAX || x2 == INT16_MAX || x3 == INT16_MAX || y1 == INT16_MAX || y2 == INT16_MIN || y3 == INT16_MAX){printerror("was not able to sort the coordinates given in a correct order (had INT16_MIN in numbers)");}
        }


        //1 and 2
        float a1 = (float)(y1 - y2) / (float)(x1 - x2);
        float b1 = (float)y1 - a1 * (float)x1;


        //1 and 3
        float a2 = (float)(y1 - y3) / (float)(x1 - x3);
        float b2 = (float)y1 - a2 * (float)x1;


        //2 and 3
        float a3 = (float)(y2 - y3) / (float)(x2 - x3);
        float b3 = (float)y2 - a3 * (float)x2;


        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        float xs = (x2==x3)?(x2):(y3 - b3) / a3;
        float xe = (x1==x3)?(x1):(y3 - b2) / a2;

        //get the increment for those lines
        float xis = (x2==x3)?(0):1 / a3;
        float xie = (x1==x3)?(0):1 / a2;

        //go through all of the lines one by one top to bottom until we reach the middle
        for(float i = y3; i > y2; i--)
        { 
            //draw the line of the triangle
            fillRect(MIN(xs, xe), i, MAX(xs, xe) - MIN(xs, xe) + 1, 1, colour);

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }


        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        xs = (x1==x3)?(x1):(y2 - b2) / a2;
        xe = (x1==x2)?(x1):(y2 - b1) / a1;

        //get the increment for those lines
        xis = (x1==x3)?(0):1 / a2;
        xie = (x1==x2)?(0):1 / a1;

        //go through all of the lines one by one middle to the bottom
        for(float i = y2; i >= y1; i--)
        {
            //draw the line of the triangle
            fillRect(MIN(xs, xe), i, MAX(xs, xe) - MIN(xs, xe) + 1, 1, colour);

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }
    }

    //TFT::fillTriangle
    void fillTriangle(Point p1, Point p2, Point p3, uint16_t colour)
    {
        fillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, colour);
    }

    void fill3dTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour)
    {
        
        // debug triangle
        // drawTriangle(x1, y1, x2, y2, x3, y3, color(255, 0, 0));

        //classify all of the x and y coordinates highest to lowest y
        {
            int16_t y[3];
            int16_t x[3];

            y[0] = y1;
            y[1] = y2;
            y[2] = y3;
            x[0] = x1;
            x[1] = x2;
            x[2] = x3;

            //find the lowest of the numbers
            int16_t best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                printerror("could not find the lowest number");
            }

            y1 = y[best_i];//set smallest number
            x1 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                printerror("could not find the lowest number");
            }

            y2 = y[best_i];//set smallest number
            x2 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                printerror("could not find the lowest number");
            }

            y3 = y[best_i];//set smallest number
            x3 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            if(x1 == INT16_MAX || x2 == INT16_MAX || x3 == INT16_MAX || y1 == INT16_MAX || y2 == INT16_MIN || y3 == INT16_MAX){printerror("was not able to sort the coordinates given in a correct order (had INT16_MIN in numbers)");}
        }


        //1 and 2
        float a1 = (float)(y1 - y2) / (float)(x1 - x2);
        float b1 = (float)y1 - a1 * (float)x1;


        //1 and 3
        float a2 = (float)(y1 - y3) / (float)(x1 - x3);
        float b2 = (float)y1 - a2 * (float)x1;


        //2 and 3
        float a3 = (float)(y2 - y3) / (float)(x2 - x3);
        float b3 = (float)y2 - a3 * (float)x2;



        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        float xs = (x2==x3)?(x2):(y3 - b3) / a3;
        float xe = (x1==x3)?(x1):(y3 - b2) / a2;

        //get the increment for those lines
        float xis = (x2==x3)?(0):1 / a3;
        float xie = (x1==x3)?(0):1 / a2;

        //go through all of the lines one by one top to bottom until we reach the middle
        for(float i = y3; i > y2; i--)
        { 
            //draw the line of the triangle
            fillRect(MIN(xs, xe), i, MAX(xs, xe) - MIN(xs, xe) + 1, 1, colour);

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }


        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        xs = (x1==x3)?(x1):(y2 - b2) / a2;
        xe = (x1==x2)?(x1):(y2 - b1) / a1;

        //get the increment for those lines
        xis = (x1==x3)?(0):1 / a2;
        xie = (x1==x2)?(0):1 / a1;

        //go through all of the lines one by one middle to the bottom
        for(float i = y2; i >= y1; i--)
        {
            //draw the line of the triangle
            fillRect(MIN(xs, xe), i, MAX(xs, xe) - MIN(xs, xe) + 1, 1, colour);

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }
    }

    /**
     * @brief set down the pencil used to START drawing lines connecting dots (resets any previous drawing progress)
     * @param x the x coordinate of the starting point (starting dot of the drawing, the next dashPencil call will draw an imaginary line between this dot and the next one)
     * @param y the y coordinate of the starting point (starting dot of the drawing, the next dashPencil call will draw an imaginary line between this dot and the next one)
     */
    void setPencil(int16_t x, int16_t y)
    {
        //Reset the pencil index
        pencilIndex = 0;

        //set the first position to the position specified in the arguments
        pencil[pencilIndex] = {x, y};

        // ::println("set pencil : ");
        // for(int i = 0; i < (pencilIndex + 1); i++)
        // {
            // ::println("[",i,"] = {",pencil[i].x,", ",pencil[i].y,"}");
        // }
    }
    void setPencil(Point p){setPencil(p.x, p.y);}

    /**
     * @brief create a line from the previous point to the point defined in the function (dash pencil to the next point)
     * @param x the x coordinate of the next point connecting last point (the pencil will dash from the last point to this one creating an imaginary line between both points)
     * @param y the y coordinate of the next point connecting last point (the pencil will dash from the last point to this one creating an imaginary line between both points)
     */
    void dashPencil(int16_t x, int16_t y)
    {
        //add one to the pencil index
        pencilIndex++;

        //set the current pencil Point specified in the arguments
        pencil[pencilIndex] = {x, y};

        // ::println("set pencil : ");
        // for(int i = 0; i < (pencilIndex + 1); i++)
        // {
            // ::println("[",i,"] = {",pencil[i].x,", ",pencil[i].y,"}");
        // }
    }
    void dashPencil(Point p){dashPencil(p.x, p.y);}

    /**
     * @brief this finalizes the pencil path and draws it (draws outline) (this does not reset drawing progress)
     */
    void drawPencil(uint16_t color)
    {
        //goal : go through each points in order and trace lines between them forming the outline of the shape

        //go through all of the pencil points
        for(int i = 0; i <= (pencilIndex - 1); i++)
        {
            //get current point (the Point at index "i")
            Point curr = pencil[i];

            //get the next point
            Point next = pencil[i + 1];

            //join them by a line
            drawLine(curr, next, color);
        }
    }

    /**
     * @brief this finalizes the pencil path and fills it (draws outline + inside outline) (this does not reset drawing progress you can theoretically call drawPencil() to draw outline on top of that)
     * @note when the first point and last point aren't the same, code assumes you meant to connect one the last point to the first point
     */
    void fillPencil(uint16_t color)
    {
        //goal : this one is going to be more clunky and longer but we want to draw the complex shape by drawing the triangles that compose said shape
        
        //make a temporary pencil copy so we can set back temp pixel as well as its previous index
        Point tempPencil[sizeofarray(pencil)];
        for(int i = 0; i < (int)sizeofarray(tempPencil); i++)
        {
            tempPencil[i] = pencil[i];
        }
        int tempPencilIndex = pencilIndex;

        //check if the last point is the same as the first point (we get rid of the last point because we already have it (its the first point) no need for it twice)
        {
            Point first = pencil[0]; 
            Point last  = pencil[pencilIndex];

            if(first.x == last.x && first.y == last.y)
            {
                pencilIndex--;
            }
        }
        
        //invert the order of the points if they are counterclockwise
        {
            long long sum = 0;
            //get the rotation of the points given (counterclockwise or clockwise, if they are counterclockwise, we invert their order)
            for(int i = 0; i < pencilIndex + 1; i++)
            {
                sum += (pencil[i + 1].x - pencil[i + 0].x)  * (pencil[i + 1].y + pencil[i + 0].y);
            }


            if(sum < 0)
            {
                //invert the pencil positions if counter clockwise
                for(int i = 0; i < (pencilIndex + 1) / 2; i++)
                {
                    //store pencil[i] temporarly
                    Point temp = pencil[i];
                    
                    //set pencil[i] to its opposite value (so we invert the order of the array last goes to first etc...)
                    pencil[i] = pencil[pencilIndex - i];

                    //set the last index to the first index we stored temporarly
                    pencil[pencilIndex - i] = temp;
                }
            }
        }

        int i = 0;
        //as long as the triangle converter isn't finish we loop
        while(pencilIndex > 0)
        {
            
            //get the first three coordinates
            Point p1 = pencil[(i + 0) % (pencilIndex + 1)];
            Point p2 = pencil[(i + 1) % (pencilIndex + 1)];
            Point p3 = pencil[(i + 2) % (pencilIndex + 1)];


            //check if the third point is to the right of the first two points
            int d = isToRight(p1, p2, p3);

            if(d < 0)
            {
            }

            //check if p3 is to the right of the line passing through p1 and p2 (we don't need to do extra calculation if we know the later condition of if we create a triangle fails (which it does if p3 is not to the right or zero))
            bool pointInsideTriangle = false;
            if(d >= 0)
            {
                //check if any points are inside of the triangle
                for(int j = 0; j < pencilIndex + 1; j++)
                {
                    //get if the current pencil point is to the right of all of the segments
                    int n1 = isToRight(p1, p2, pencil[j]);
                    int n2 = isToRight(p2, p3, pencil[j]);
                    int n3 = isToRight(p3, p1, pencil[j]);

                    //if they are all positive, meaning if pencil point is inside the triangle (not including the edge of it)
                    if(n1 > 0 && n2 > 0 && n3 > 0)
                    {
                        //the current point is inside of the triangle, "pointInsideTriangle" becomes true, because we found a point inside the triangle
                        pointInsideTriangle = true;
                        break;
                    }
                }
            
            }
            
            //if special conditions are true, then we can draw a triangle there
            if(d >= 0 && pointInsideTriangle == false)
            {
                //draw the triangle
                fillTriangle(p1, p2, p3, color);

                //get index of p2
                int p2index = (i + 1) % (pencilIndex + 1);

                //remove p2 (push all of the following back by one, it'll overwrite p2 in the process)
                for(int j = p2index; j <= (pencilIndex - 1); j++)
                {
                    pencil[j + 0] = pencil[j + 1];
                }

                //decrease the pencilIndex by one since we removed a point
                pencilIndex--;

                //increase the index "i" by one to move on to the next points (wrap around if it went past pencilIndex)
                i = (i + 1) % (pencilIndex + 1);
            
            //else if the three points are not valid to draw the triangle simply increase index "i" by one to move on to the next points and try again
            }else
            {
                //increase the index "i" by one to move on to the next points (wrap around if it went past pencilIndex)
                i = (i + 1) % (pencilIndex + 1);
            }
        }
    
        //restore the pencil array to what it was previously using the tempPencil array and tempPencilIndex
        for(int j = 0; j < (int)sizeofarray(pencil); j++)
        {
            pencil[j] = tempPencil[j];
        }
        pencilIndex = tempPencilIndex;
    }


    //TFT::TFT
    TFT()
    {
        //Variable Initializations
        this->vx = 0;
        this->vy = 0;
        this->vw = SCREEN_WIDTH;
        this->vh = SCREEN_HEIGHT;
        this->gx = 0;
        this->gy = 0;
        this->cursor_x_start = 0;
        this->cursor_x = 0;
        this->cursor_y = 0;
        this->fontSize = 1;
        this->fontColor = 0xFFFF;
        clearArray(pencil, {0, 0});
        this->pencilIndex = 0;
    }
};

/*inline*/ TFT tft;

class Rectangle 
{
    public:
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
    double r;
    uint16_t colour;

    void pencil()
    {
        //rotated point
        Pointd p1 = pivot({x - w/2, y - h/2}, {x, y}, r);
        Pointd p2 = pivot({x + w/2, y - h/2}, {x, y}, r);
        Pointd p3 = pivot({x - w/2, y + h/2}, {x, y}, r);
        Pointd p4 = pivot({x + w/2, y + h/2}, {x, y}, r);

        //set shape the rotated rectangle
        tft.setPencil(p1);
        tft.dashPencil(p2);
        tft.dashPencil(p4);
        tft.dashPencil(p3);
        tft.dashPencil(p1);
    }

    void draw()
    {
        pencil();

        tft.drawPencil(colour);
    }

    void fill()
    {
        pencil();

        tft.fillPencil(colour);
    }

    Rectangle(int x, int y, int w, int h, double r, uint16_t colour)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->r = r;
        this->colour = colour;
    }

    Rectangle()
    {
        this->x = 0;
        this->y = 0;
        this->w = 100;
        this->h = 100;
        this->r = 0;
        this->colour = rgb(255, 255, 255);
    }
};


//this function does not include the tft.begin() nor the ui.begin() It is only for SERIAL
/*inline*/ void SerialBegin()
{
    Serial.begin(9600);
}

/*inline*/ void SerialWait()
{
    while(!Serial);
    delay(500);
}

#endif

