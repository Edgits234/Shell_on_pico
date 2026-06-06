
#ifndef AwesomeUI_h
#define AwesomeUI_h

#include <Utility.h>

#ifndef UI_SETTINGS
  /*
  Helper : 
  0b00000000
    ##^^^^^^
    ##87654321

  1 -> if 0 : clears frame buffer at the start of a new ui.update() 
  2 -> if 0 : don't draw on screen if we are waiting for keyboard input (to catch up on keyboard lag because you can type faster than you can update the screen)
  3 -> if 0 : display the screen buffer on the screen *(frame buffer = screen buffer)
  4 -> ?
  5 -> ?
  6 -> ?
  7 -> ?
  8 -> ?

  "?" means nothing/unknown
  */
  #define UI_SETTINGS 0b00000000
#endif

#ifndef MAX_ELEMENTS
  #define MAX_ELEMENTS 10
#endif

// Pins for the DFR0665 Display
#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9

// Pins for the XPT2046 Touch Controller (THIS IS FOR THE SCREEN IRL)(Verify these with DFRobot documentation)
#define T_CLK 52 // Shares SCK pin
#define T_DO 50  // Shares MISO pin
#define T_DIN 51 // Shares MOSI pin
#define T_CS 3   // This MUST be a unique digital pin (e.g., Pin 3)

// These are typical starting values for many 2.8"/3.2" screens with the XPT2046 chip
// Use these as placeholders until you run the calibration sketch on your hardware:
#define TS_MINX 200
#define TS_MAXX 3840
#define TS_MINY 400
#define TS_MAXY 3880

#include "CustomGraphics.h"

void nullfunc(bool nothing);

struct RectangleParams
{
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;
  // int16_t lx;
  // int16_t ly;
  // uint16_t lw;
  // uint16_t lh;
};

struct point3d
{
  float x;
  float y;
  float z;

  point3d operator+(const point3d& other) const
  {
    return {x + other.x, y + other.y, z + other.z};
  }

  point3d operator-(const point3d& other) const
  {
    return {x - other.x, y - other.y, z - other.z};
  }

  point3d operator-() const
  {
    return {-x, -y, -z};
  }
};

struct vertexPos
{
  uint16_t a;
  uint16_t b;
  uint16_t c;
  uint16_t colour;
};

// struct DoubleRectangleParams
// {
//   int16_t x;
//   int16_t y;
//   int16_t w;
//   int16_t h;
//   int16_t lx;
//   int16_t ly;
//   int16_t lw;
//   int16_t lh;
// };

struct RectangleParamsInt
{
  int x;
  int y;
  int w;
  int h;
};

struct DisplacePointUI
{
  int16_t x;
  int16_t y;
  // int16_t lx;
  // int16_t ly;
};

struct TriPoint
{
  Point a;
  Point b;
  Point c;
};

// struct Color
// {
//   byte red;
//   byte green;
//   byte blue;
// };

#if WOKWI_SIM
  #include <Wire.h> // Required for I2C communication
  #include <Adafruit_FT6206.h>
  #include <CustomKeyboard.h>
  Adafruit_FT6206 ctp = Adafruit_FT6206(); // Initialize capacitive touch object
  SPISettings spiSettings(80000000, MSBFIRST, SPI_MODE0);


#else

  // #include <USBHostGiga.h>//this is for the keyboard
  // #include <XPT2046_Touchscreen.h>

  // Create touchscreen object
  // XPT2046 ALSO uses SPI1 (shares MOSI, MISO, SCK with display)
  // XPT2046_Touchscreen ts(T_CS);

  // The hero (correct): IN homage to the GOAT, I would have never figured this out by myself

  #include <CustomKeyboard.h>
#endif

// template <typename T> void print(T input){Serial.print(input);} template<typename T, typename... Args> void print(T input, Args... other){Serial.print(input); print(other...);}void println(){Serial.println();}template <typename T>void println(T input) {Serial.println(input);}template <typename T, typename... Args> void println(T input, Args... other){Serial.print(input);println(other...);}
// template <typename T> void print1(T input){Serial.print(input);} template<typename T, typename... Args> void print1(T input, Args... other){Serial.print(input); Serial.print(", "); print1(other...);}void println1(){Serial.println();}template <typename T>void println1(T input) {Serial.println(input);}template <typename T, typename... Args> void println1(T input, Args... other){Serial.print(input);Serial.print(", ");println1(other...);}

// #if enableTestPrints
// void testprintln(){Serial.println();}template <typename T>void testprintln(T input) {Serial.println(input);}template <typename T, typename... Args> void testprintln(T input, Args... other){Serial.print(input);println(other...);}
// #else
// void testprintln(){}template <typename T>void testprintln(T input) {}template <typename T, typename... Args> void testprintln(T input, Args... other){}
// #endif

// Point addPoints(Point p1, Point p2)
// {
//   return {p1.x + p2.x, p1.y + p2.y};
// }

//commented this part because it was causing some warnings that I didn't really like, also had to disable Canvas3D because it was using that
// uint32_t floatToSortable(float f) {
//     uint32_t bits = *((uint32_t*)&f);  // Reinterpret as bits
//    
//     if (bits & 0x80000000) {  // Negative
//         return ~bits;  // Flip all bits
//     } else {  // Positive
//         return bits ^ 0x80000000;  // Flip sign bit only
//     }
// }
//
// float sortableToFloat(uint32_t bits) {
//     if (bits & 0x80000000) {  // Was positive
//         bits ^= 0x80000000;
//     } else {  // Was negative
//         bits = ~bits;
//     }
//     return *((float*)&bits);
// }

template<typename T1, typename T2>
int strcmp(T1 str1_input, T2 str2_input, unsigned int len1, unsigned int len2 = SIZE_MAX)
{
  HandleFlashString<T1> str1 = str1_input;
  HandleFlashString<T2> str2 = str2_input;

  //figure out the length of the corresponding string if not provided
  if(len1 == SIZE_MAX)
  {
    while(str1[len1] != '\0')
    {
      len1++;
    }
  }

  //figure out the length of the corresponding string if not provided
  if(len2 == SIZE_MAX)
  {
    while(str2[len2] != '\0')
    {
      len2++;
    }
  }

  //go through all of the characters inside of the smallest string
  for(unsigned int i = 0; i < MIN(len1, len2); i++)
  {
    //check each characters inside the smallest string, if they aren't equal then output difference of the string
    if(str1[i] != str2[i])
    {
      return str1[i] - str2[i];//Return difference between the incorrect charactersf
    }
  }

  return 0;
}

template<typename T1, typename T2>
int flash_strcmp(T1 str1_input, T2 str2_input)
{
  HandleFlashString<T1> str1 = str1_input;
  HandleFlashString<T2> str2 = str2_input;
  
  size_t i = 0;
  while (true) {
    char c1 = str1[i]; // Pulls safely via your working operator[]
    char c2 = str2[i]; // Pulls safely via your working operator[]
    
    if (c1 != c2 || c1 == '\0') {
      return (c1 - c2);
    }
    i++;
  }
}

/**
 * @brief this function sorts the inputed array of uint32_t from lowest to highest
 * @param arr this is the array that you want to modify / sort
 * @param size this is the size of the array you want to modify / sort
 */
void radixSort(uint32_t* arr, size_t size)
{
  uint16_t count[256];
  uint16_t* buckets = new uint16_t[size];

  //check for error in memory allocation
  if(buckets == nullptr)
  {
    println(F("ERROR in file "),__FILE__,F(" in function "),__func__,F("() at line "),__LINE__,F(", was not able to allocate memory for buckets array (you are probably running out of space)"));
  }

  //----------- sort by the least significant byte of the uint16_t -----------//

  //reset / clear the count array
  for(int i = 0; i < 256; i++)
  {
    count[i] = 0;
  }

  //go through all of the array
  for(size_t i = 0; i < size; i++)
  {
    //get the first byte of the uint16_t 
    uint8_t bits = arr[i] & 0b0000000011111111;

    //add one to that specific bit in count
    count[bits] += 1;
  }

  //reorder it in array form
  size_t truei = 0;
  for(size_t i = 0; i < 256; i++)
  {
    int countSize = count[i];//store the count[i]
    count[i] = truei;//set count to the truei (the current position)
    truei += countSize;//update the countsize to skip the number of size for count idk
  }

  //go through all of the array
  for(size_t i = 0; i < size; i++)
  {
    //get the first byte of the uint16_t 
    uint8_t bits = arr[i] & 0b0000000011111111;

    //get current position of specific number (based on the bits)
    uint16_t position = count[bits];

    //set that place of the array at that position in a temp array
    buckets[position] = arr[i];
    
    //increase the count (which is now the position) by one so that the next arr[i] with same bits goes in position just next to that
    count[bits] += 1;
  }



  //----------- sort by the most significant byte of the uint16_t -----------//

  //reset / clear the count array
  for(int i = 0; i < 256; i++)
  {
    count[i] = 0;
  }

  //go through all of the array
  for(size_t i = 0; i < size; i++)
  {
    //get the last byte of the uint16_t 
    uint8_t bits = (buckets[i] & 0b1111111100000000) >> 8;

    //add one to that specific bit in count
    count[bits] += 1;
  }

  //reorder it in array form
  truei = 0;
  for(int i = 0; i < 256; i++)
  {
    int countSize = count[i];//store the count[i]
    count[i] = truei;//set count to the truei (the current position)
    truei += countSize;//update the countsize to skip the number of size for count idk
  }

  //go through all of the array
  for(size_t i = 0; i < size; i++)
  {
    //get the first byte of the uint16_t 
    uint8_t bits = (buckets[i] & 0b1111111100000000) >> 8;

    //get current position of specific number (based on the bits)
    uint16_t position = count[bits];

    //set that place of the array at that position in a temp array
    arr[position] = buckets[i];
    
    //increase the count (which is now the position) by one so that the next arr[i] with same bits goes in position just next to that
    count[bits] += 1;
  }

  //free the buckets array we allocated earlier
  delete[] buckets;
}

/**
 * @brief this function sorts the inputed arrays of uint32_t from lowest to highest, and sorts secarr based on that
 * @param arr this is the array that you want to modify / sort
 * @param size this is the size of the array you want to modify / sort
 * @param secarr this is the secondary array, can be any type, the code will order them in the same order as array
 */
template<typename T>
void radixSort(uint32_t* arr, size_t size, T* secarr)
{
  uint32_t count[256];
  uint32_t* buckets = new uint32_t[size];
  T* secarr2 = new T[size];

  //----------- sort by the least significant byte of the uint32_t -----------//

  for(int k = 0; k < 2; k++)
  {
    //reset / clear the count array
    for(int i = 0; i < 256; i++)
    {
      count[i] = 0;
    }

    //go through all of the array
    for(size_t i = 0; i < size; i++)
    {
      //get the first byte of the uint32_t 
      uint8_t bits = (arr[i] & (0b0000000011111111 << (k * 8))) >> (k * 8);

      //add one to that specific bit in count
      count[bits] += 1;
    }

    //reorder it in array form
    size_t truei = 0;
    for(int i = 0; i < 256; i++)
    {
      int countSize = count[i];//store the count[i]
      count[i] = truei;//set count to the truei (the current position)
      truei += countSize;//update the countsize to skip the number of size for count idk
    }

    //go through all of the array
    for(size_t i = 0; i < size; i++)
    {
      //get the first byte of the uint32_t 
      uint8_t bits = (arr[i] & (0b0000000011111111 << (k * 8))) >> (k * 8);

      //get current position of specific number (based on the bits)
      uint32_t position = count[bits];

      //set that place of the array at that position in a temp array
      buckets[position] = arr[i];

      //also do for the secondary array
      secarr2[position] = secarr[i];
      
      //increase the count (which is now the position) by one so that the next arr[i] with same bits goes in position just next to that
      count[bits] += 1;
    }



    //----------- sort by the most significant byte of the uint16_t -----------//

    //reset / clear the count array
    for(int i = 0; i < 256; i++)
    {
      count[i] = 0;
    }

    //go through all of the array
    for(size_t i = 0; i < size; i++)
    {
      //get the last byte of the uint32_t 
      uint8_t bits = (buckets[i] & (0b1111111100000000 << (k * 8))) >> (8 + (k * 8));

      //add one to that specific bit in count
      count[bits] += 1;
    }

    //reorder it in array form
    truei = 0;
    for(int i = 0; i < 256; i++)
    {
      int countSize = count[i];//store the count[i]
      count[i] = truei;//set count to the truei (the current position)
      truei += countSize;//update the countsize to skip the number of size for count idk
    }

    //go through all of the array
    for(size_t i = 0; i < size; i++)
    {
      //get the first byte of the uint16_t 
      uint8_t bits = (buckets[i] & (0b1111111100000000 << (k * 8))) >> (8 + (k * 8));

      //get current position of specific number (based on the bits)
      uint32_t position = count[bits];

      //set that place of the array at that position in a temp array
      arr[position] = buckets[i];
      
      //also do for the secondary array
      secarr[position] = secarr2[i];

      //increase the count (which is now the position) by one so that the next arr[i] with same bits goes in position just next to that
      count[bits] += 1;
    }
  }

  delete[] buckets;
  delete[] secarr2;
}

template<typename T>
class Arraya
{
  public:
  T* array;
  unsigned int size;

  void add(T input)
  {
    // we allocate the size for the new array
    T* newArray = new T[size + 1];

    if(newArray == nullptr)
    {
      println(F("WELL WE'VE JUST FOUND THE ERROR, THIS STUPID ASS ARRAY TRIED GETTING MEMORY BUT IT FAILED AND NOW WE BOUT TO BUST THE WHOLE FUCKING THING"));
      while(1);// bug finding
    }else
    {
      for (unsigned int i = 0; i < size; i++)
      {
        newArray[i] = array[i]; // we set the new array to the previous array
      }

      // we set the new value to add at the end
      newArray[size] = input;

      // we get rid of the previous array
      delete[] array;
      array = nullptr; // idk, just to be sure

      // set the array pointer to the new array pointer
      array = newArray;

      // we up the size by one
      size++;
    }
  }

  void remove()
  {
    // we allocate the size for the new array
    T* newArray = new T[size - 1];

    for (unsigned int i = 0; i < size - 1; i++)
    {
      newArray[i] = array[i]; // we set the new array to the previous array
    }

    // we get rid of the previous array
    delete[] array;
    array = nullptr; // idk, just to be sure

    // set the array to the new array
    array = newArray;

    // we up the size by one
    size--;
  }

  void remove(unsigned int index)
  {
    // we allocate the size for the new array
    T* newArray = new T[size - 1];

    for (unsigned int i = 0; i < index; i++)
    {
      newArray[i] = array[i]; // we set the new array to the previous array
    }

    for (unsigned int i = index; i < size - 1; i++)
    {
      newArray[i] = array[i + 1]; // we set the new array to the previous array
    }

    // we get rid of the previous array
    delete[] array;
    array = nullptr; // idk, just to be sure

    // set the array to the new array
    array = newArray;

    // we up the size by one
    size--;
  }

  T at(unsigned int index)
  {
    // if the index is in bound
    if (0 <= index && index <= size - 1)
    {
      return array[index];
    }
    else
    {
      println(F("ERROR, invalid index (the index you gave doesn't point to an element in the array)"));
      while(1);// bug finding
      return 0;
    }
  }

  Arraya()
  {
    //variable initializations (note to self, add this in front of any and all cosntructors)
    this->array = nullptr;
    this->size = 0;
  };
  // Arraya(const Arraya&) = delete;
  // Arraya& operator=(const Arraya&) = delete;

  ~Arraya()
  {
    delete[] array; // remove array from the memory
  }
};

/**
 * @param p : point
 * @param c : center
 * @param r : rotation (in degrees I think)
 * @brief rotates a point around the desired center based on the rotation (applies the rotation in the following order, Y -> X -> Z)
 * @retval outputs the rotated point
 */
/*inline*/ point3d rotateAroundAxis(point3d p, point3d c, point3d r)
{
    r.x /= 180 / PI;
    r.y /= 180 / PI;
    r.z /= 180 / PI;

    float dx = p.x - c.x;
    float dy = p.y - c.y;
    float dz = p.z - c.z;

    float rx;
    float ry;
    float rz;

    //rotate the y axis
    rx = dx * cos(r.y) - dz * sin(r.y);
    rz = dx * sin(r.y) + dz * cos(r.y);
    dx = rx;
    dz = rz;

    //rotate the x axis
    ry = dy * cos(r.x) - dz * sin(r.x);
    rz = dy * sin(r.x) + dz * cos(r.x);
    dy = ry;
    dz = rz;

    //rotate the z axis
    rx = dx * cos(r.z) - dy * sin(r.z);
    ry = dx * sin(r.z) + dy * cos(r.z);

    return {rx + c.x, ry + c.y, rz + c.z};
}

/*inline*/ double strMath(const char* str, int len = -1, void* extraData = nullptr, double (*handleWord)(void* extradata, const char* word, int len) = nullptr)
{
  //figure out the length if it wasn't provided in the input (if len was equal to -1)
  if(len == -1)
  {
    len = 0;
    while(str[len] != '\0')
    {
      len++;
    }

    // println("length is ",len);
  }
  
  const char signs[9] = {'*','/','+','-'};
  const byte order[9] = { 0 , 0 , 1 , 1 };

  //ignore spaces and parenthesis incompassing the whole string
  while(true)
  {
    //get rid of spaces at the front
    if(str[0] == ' ')
    {
      str += 1;
      len -= 1;
    
    //get rid of spaces at the end
    }else if(str[len - 1] == ' ')
    {
      len -= 1;
    
    //get rid of any parenthesis encompassion the whole string
    }else if(str[0] == '(' && str[len - 1] == ')')
    {

      //check if those parenthesis actually "connect" 
      int parenthesisLevel = 0;
      for(int i = 0; i < len; i++)
      {
        if(str[i] == '(')
        {
          parenthesisLevel += 1;
        }else if(str[i] == ')')
        {
          parenthesisLevel -= 1;
        }
        
        if(i == len - 1)
        {
          //get rid of the thing
          str += 1;
          len -= 2;

          //set parenthesisLevel to 1 to stop it from going out of the loop
          parenthesisLevel = 1;
          break;
        }

        if(parenthesisLevel <= 0)
        {
          break;
        }
      }

      //parenthesisLevel is set to zero if we found inside of the string a parenthesis below or equal to zero
      if(parenthesisLevel == 0)
      {
        //go outside of the loop
        break;
      }
    }else
    {
      //if none of the stuff was done, then get out of the loop
      break;
    }
  }

  // print("str math -> '");
  // for(int i = 0; i < len; i++)
  // {
  //   print(str[i]);
  // }
  // println("'");

  //make a variable to remember if we ever found a operator (if we didn't then its probably just a normal number)
  bool foundAnySigns = false;

  //go through all possible order values 0-255
  for(int i = 255; i >= 0; i--)
  { 
    //start out default at parenthesis level 0, increase when ")", decrease when "("
    int parenthesisLevel = 0;

    //go through all of the string BACKWARDS checking to find a sign with order "i"
    for(int j = len - 1; j >= 0; j--)
    {
      if(str[j] == ')')
      {
        parenthesisLevel += 1;
      }else if(str[j] == '(')
      {
        parenthesisLevel -= 1;
      }

      if(parenthesisLevel == 0)
      {
        //go through all of the signs with that order (order "i")
        for(int k = 0; k < (int)(sizeofarray(order)); k++)
        {
          //this plays for all signs that have order "i"
          if(order[k] == i)
          {
            //if the str character at index "j" is the same as the sign character indexed by "k" inside of the signs array
            if(str[j] == signs[k])
            {
              //found the last operation to do at index "j" of str!!!

              //if we have nothing to the left its probably a negative number so skip it
              if(j == 0 && str[j] == '-')
              {
                return -strMath(str + j + 1, len - j - 1, extraData, handleWord);
              }

              // do strMath for the left and right part of the operation
              double left = strMath(str, j, extraData, handleWord);
              double right = strMath(str + j + 1, len - j - 1, extraData, handleWord);
              double result = 0;

              //IMPORTANT NOTE : EXCEPTION FOR NEGATIVE NUMBER, IF THERE ISN'T ANYTHING TO THE LEFT OF THE NUMBER THEN WE DO THE WEIRD NINJUTS BULLSHIT NEGATIVE NUMBER!!!!

              //do the right mathematical operation based on what str[j] is equal
              if      (str[j] == '+')
              {
                result = left + right;
              }else if(str[j] == '-')
              {
                result = left - right;
              }else if(str[j] == '*')
              {
                result = left * right;
              }else if(str[j] == '/')
              {
                result = left / right;
              }
              
              return result;
            } 
          }
        }
      } 
    }
  }

  //if we didn't find any signs then its probably just a number (check len bigger than zero to make sure we aren't working with a empty string)
  if(len > 0 && foundAnySigns == false)
  {
    //check before sending to strToNum function if it has any non number characters
    for(int i = 0; i < len; i++)
    {
      //if its not a number
      if((str[i] < '0' || '9' < str[i]) && str[i] != '-' && str[i] != ' ')
      {

        //send it to the handleWord if it exists
        if(handleWord != nullptr)
        {
          return (*handleWord)(extraData, str, len);
        }

        return NAN;
      }
    }

    return strToNum(str, len);
  }

  return NAN;
}


/**
 * @brief this function is a helper function that sets the x and y positions automatically when putting words like "middle", "top", "right", while letting normal numbers pass
 * @param pos : this is the position of the object you want to move
 * @param len : this is the length of the object you want to move
 * @param totalLen : this is the total length (usually the container of the object)
 * @param vertical : this tells the function if we are treating this as x or y (0 -> x, 1 -> y), its purpose is to stop stuff like (x, y) -> ("top", "right") which is reversed
 */
/*inline*/ int setPos(int pos, uint16_t len, int totalLen, bool vertical){return pos;}
/**
 * @brief this function is a helper function that sets the x and y positions automatically when putting words like "middle", "top", "right", while letting normal numbers pass
 * @param pos : this is the position of the object you want to move
 * @param len : this is the length of the object you want to move
 * @param totalLen : this is the total length (usually the container of the object)
 * @param vertical : this tells the function if we are treating this as x or y (0 -> x, 1 -> y), its purpose is to stop stuff like (x, y) -> ("top", "right") which is reversed
 */

struct HandleSetPosWordsStruct
{
  uint16_t len;
  int totalLen;
  bool vertical;
};

double handleSetPosWords(void* extraData, const char* str, int len)
{
  HandleSetPosWordsStruct input = *((HandleSetPosWordsStruct*)(extraData));

  // test print print(__func__,"(");
  // test print for(int i = 0; i < len; i++)
  // test print {
  // test print   print(str[i]);
  // test print }
  // test print println(", ",input.len,", ",input.totalLen,", ",input.vertical,")");

  if((strcmp(str,"left",len) == 0 && input.vertical == 0) || ((strcmp(str,"top",len) == 0 || strcmp(str,"up",len) == 0 || strcmp(str,"upper",len) == 0) && input.vertical == 1))
  {
    // for(int i = 0; i < len; i++)
    // {
    //   print(str[i]);
    // }
    // println(" -> ",0);
    return 0;
  }else if(strcmp(str,"middle",len) == 0 || strcmp(str,"centered",len) == 0 || strcmp(str,"center",len) == 0)
  {
    // for(int i = 0; i < len; i++)
    // {
    //   print(str[i]);
    // }
    // println();
    // println(input.totalLen," / ",2," - ",input.len," / ",2);
    // println(" -> ",input.totalLen / 2 - input.len / 2);
    return input.totalLen / 2 - input.len / 2;
  }else if((strcmp(str,"right",len) == 0 && input.vertical == 0) || ((strcmp(str,"bottom",len) == 0 || strcmp(str,"down",len) == 0 || strcmp(str,"lower",len) == 0) && input.vertical == 1))
  {
    // for(int i = 0; i < len; i++)
    // {
    //   print(str[i]);
    // }
    // println(" -> ",input.totalLen - input.len);
    return input.totalLen - input.len;
  }

  println(F("ERROR, '"),str,F("' is not correct keyword (tip: your make sure your 'top'/'bottom' and 'right'/'left' are not inverted)"));
  return 0;
}

/*inline*/ int setPos(const char* str, uint16_t len, int totalLen, bool vertical)
{
  HandleSetPosWordsStruct extraData = {len, totalLen, vertical};
  int mathOutput = (int)(strMath(str, -1, (void*)(&extraData), handleSetPosWords));

  return mathOutput;
}

/*inline*/ int16_t globalx = 0;
/*inline*/ int16_t globaly = 0;
/*inline*/ bool cursorClicky = false;
/*inline*/ bool touched()
{
  #if WOKWI_SIM
    return ctp.touched();
  #else

    //if we haven't pressed ctrl, alt and have not pressed a previous key
    if(kbd.keys.lctrl == 0 && kbd.keys.lalt == 0)
    {
      //if we just pressed the up arrow
      if(kbd.checkForKey(KEY_UPARROW))
      {
        globaly -= 5;
      }
      
      //if we just pressed the down arrow
      if(kbd.checkForKey(KEY_DOWNARROW))
      {
        globaly += 5;        
      }
      
      //if we just pressed the left arrow
      if(kbd.checkForKey(KEY_LEFTARROW))
      {
        globalx -= 5;
      }
      
      //if we just pressed the right arrow
      if(kbd.checkForKey(KEY_RIGHTARROW))
      {
        globalx += 5;          
      }
      
    }

    if(kbd.checkForKey(KEY_SPACEBAR))
    { 
      cursorClicky = true;
      return true;
    }else
    {
      cursorClicky = false;    
    }

    return false;

  #endif
}

/*inline*/ Point getPoint()
{
  #if WOKWI_SIM
    TS_Point p = ctp.getPoint(); // Get the touch point

    // fix the points, bcs they reverse for some reason
    p.x = tft.screen_width  - p.x;
    p.y = tft.screen_height - p.y;

    return {p.x, p.y};
  #else

    return {globalx, globaly};
  #endif
}

/*inline*/ int16_t gvx = 0;
/*inline*/ int16_t gvy = 0;
/*inline*/ int16_t gvw = tft.screen_width;
/*inline*/ int16_t gvh = tft.screen_height;
/*inline*/ void setTestViewport(int16_t x, int16_t y, int16_t w, int16_t h)
{
  gvx = tft.vx;
  gvy = tft.vy;
  gvw = tft.vw;
  gvh = tft.vh;

  tft.setViewport(x, y, w, h);
}

/*inline*/ void cancelTestViewport()
{
  tft.setViewport(gvx, gvy, gvw, gvh);
}


// input two rectangles and get if they touch or not
/*inline*/ bool collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
  //returns false if any of the length of the rectangles are negative
  if(w1 < 0 || h1 < 0 || w2 < 0 || h2 < 0)
  {
    return false;
  }

  return !((x2 > x1 + w1 && x2 + w2 > x1 + w1) || (x2 < x1 && x2 + w2 < x1)) && !((y2 > y1 + h1 && y2 + h2 > y1 + h1) || (y2 < y1 && y2 + h2 < y1)); // && !((y2 > y1 + h1 && y2 + h2 > y1 + h1) || (y2 > y1 && y2 + h2 > y1));
}

// uint16_t color(byte red, byte green, byte blue)
// {
//   // maping the colors from 255 to  their respective map
//   red = red * 32 / 256;
//   green = green * 64 / 256;
//   blue = blue * 32 / 256;
//
//   return ((uint16_t)(red) << 11) + ((uint16_t)(green) << 5) + (uint16_t)(blue);
// }
//
// uint16_t color(Color input)
// {
//   // maping the colors from 255 to  their respective map
//   // println(input.red," * ",31," = ",input.red * 32);
//   // println(input.red * 31," / 255 = ",input.red * 32 / 255);
//   input.red = input.red * 32 / 256;
//   input.green = input.green * 64 / 256;
//   input.blue = input.blue * 32 / 256;
//
//   // println();
//   // println("Red:",input.red);
//   // Serial.println(input.red,BIN);
//   // println("Green:",input.green);
//   // Serial.println(input.green,BIN);
//   // println("Blue:",input.blue);
//   // Serial.println(input.blue,BIN);
//
//   return ((uint16_t)(input.red) << 11) + ((uint16_t)(input.green) << 5) + (uint16_t)(input.blue);
// }
//
// Color toColor(uint16_t input)
// {
//   Color variable;
//
//   variable.red   = ((input & 0xF800) >> 11) * 256 / 32;
//   variable.green = ((input & 0x7E0)  >>  5) * 256 / 62;
//   variable.blue  = ((input & 0x1F)   >>  0) * 256 / 32;
//
//   return variable;
// }

//takes in pairs of 2 rectangles. VERY CURSED gonna regret that but meh whatever
/*inline*/ RectangleParams combineRectangles16(RectangleParams r1, RectangleParams r2)
{
  int16_t x1 = max(r1.x, r2.x);
  int16_t y1 = max(r1.y, r2.y);
  int16_t x2 = min(r1.x + r1.w, r2.x + r2.w);
  int16_t y2 = min(r1.y + r1.h, r2.y + r2.h);
  
  int16_t  x = x1;
  int16_t  y = y1;
  int16_t w = max(0, x2 - x1);
  int16_t h = max(0, y2 - y1);

  return {x, y, w, h};

  //test this function with teh following : 
  // tft.drawRect(20, 20, 100, 50, color(0,255,0));
  // tft.drawRect(30, 200, 50, 60, color(0,0,255));
  // RectangleParams r = combineRectangles({30, 200, 50, 60}, {20, 20, 100, 50});
  // tft.drawRect(r.x, r.y, r.w, r.h, color(255,255,255));
}

//we might not need this function anymroe ------------------------------------------------------------------------------------------------------------------------------------------------------------------
// RectangleParams combine2Rectangles16(RectangleParams r1, RectangleParams r2)
// {
//   RectangleParams r3 = combineRectangles16({r1.x, r1.y, r1.w, r1.h}, {r2.x, r2.y, r2.w, r2.h});
//   // RectangleParams r4 = combineRectangles16({r1.lx, r1.ly, r1.lw, r1.lh}, {r2.lx, r2.ly, r2.lw, r2.lh});
//
//   return {r3.x, r3.y, r3.w, r3.h};
// }

// RectangleParams combineRectangles(RectangleParamsInt r1, RectangleParams r2)
// {
//   return combineRectangles16((RectangleParams){(int16_t)r1.x, (int16_t)r1.y, (uint16_t)r1.w, (uint16_t)r1.h}, (RectangleParams){(int16_t)r2.x, (int16_t)r2.y, (uint16_t)r2.w, (uint16_t)r2.h});// typecast that BITCH
// }

class UI;

//global::UIelement
class UIelement
{
  public:
  UI* ui1; // the parent ui
  const char* type; // constant character pointer (string) that describes the type of the ui element
  char* id; //id string representing the name of the element
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;
  int8_t z_index;
  uint8_t selected;  // is this element selected?
  uint8_t selectable; // is the element selectable (in other words, can its selected variable be changed?)
  UI* container; // pointer to the UI class that an element holds (if it holds anything in the first place)
  void* extradata; // this is a useless variable, but I'm keeping it because ya never know when its going to be useful
  Function<void, UIelement*>                    userTick;//userTick(UIelement* self) // this function ALWAYS gets called BEFORE update (updating the element as well as drawing on the screen)
  Function<void, UIelement*>                    userUpdate;//userUpdate(UIelement* self) // this function gets called before the UIelement's update (so you can draw your own custom stuff on top)
  Function<void, UIelement*, Point, bool, bool> userHandleInput;//userHandleInput(UIelement* self, Point p, bool holding, bool lostfocus) // this function is to get the touch inputs (technically is now "cursor input")
  Function<void, UIelement*>                    userHandleKeyboardInput;//userHandleKeyboardInput(UIelement* self) // this is to get the keybaord input (use the kbd object to get stuff about the keyboard)
  Function<void, UIelement*>                    onDeath;//onDeath(UIelement* self) // this function plays when this UI element dies (when its destructor gets called)

  /*0b00000000
    ##^^^^^^
    ##876543216

  1 -> show selected outline
  2 -> ?
  3 -> ?
  4 -> ?
  5 -> ?
  6 -> ?
  7 -> ?
  8 -> ?*/
  uint8_t settings;

  virtual void setx(int input);
  virtual void sety(int input);
  virtual void setx(const char* input);
  virtual void sety(const char* input);
  virtual void update(){}
  virtual void handleInput(Point p, bool holding, bool lostfocus){}
  virtual void handleKeyboardInput(){}

  virtual Point absPos();

  virtual void tick(){}
  virtual void draw(){}
  virtual void selectionChanged(uint8_t change){selected = change;}//defaults to change
  UIelement()
  {
    this->ui1 = nullptr;
    this->type = nullptr;
    this->id = nullptr;
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->z_index = 0;
    this->selected = false;
    this->selectable = true;
    this->container = nullptr;
    this->extradata = nullptr;
    this->settings = 0b00000001;
  }
  virtual ~UIelement()
  {
    if(onDeath)
    {
      onDeath(this);
    }
  }
};

// forward definition of the Text, button, Terminal, and Canvas3D class
class Text;
class Button;
class Menu;
class Window;
class Canvas3D;
class Terminal;

// In AwesomeUI.h, add this BEFORE the UI class definition (around line 300):

/*inline*/ UI* g_pathBuffer[10];
/*inline*/ uint8_t enabletouch = 1;

#define RELW(a) ((int32_t)(currUI->w) * a / tft.screen_width)
#define RELH(a) ((int32_t)(currUI->h) * a / tft.screen_height)

class UIBridge
{
  public:
  UI* currUI;
  Array<UIelement*, MAX_ELEMENTS>* arr; // we are simply creating an array of pointers to UIelement object with a custom class (this class does some very basic memory managements for you and is kind of like vector exept all of the features are missing exept "push_back" which is now "add" and "remove" just removes at last index or the specified index)
  
  template <typename T1, typename T2>
  Text& addText(const char* id_input, String text, int fontsize, uint16_t color, T1 posX, T2 posY);//UI::addText 
  Text& addText(const char* id_input);//UI::addText
  Text& getText(const char* id, bool globalScope, int line, const char* file);//UI::getText

  /**
   * @brief adds a button
   * @param id_input the id of the ui element (can be changed once set)
   * @param text the text that the button is displaying
   * @param fontsize the size of the text
   * @param colour the colour of the text (use "color()" function to input color with rgb (0 to 255 for each color))
   * @param textOffsetX the position in x axis of the text, can be inputed as number (Ex:1, 2, 10, 20, etc...) or as string (Ex:"middle", "left", "right", etc...)
   * @param textOffsetY the position in y axis of the text, can be inputed as number (Ex:1, 2, 10, 10, etc...) or as string (Ex:"middle", "top", "down", etc...)
   * @param background is there a background? (in the case that there is no backgorund, the position of the text will take over and won't simply be the offset position based on the background position)
   * @param backgroundColor the color of the background (if there is no background, the color you input doesn't matter)
   * @param posX the position in the x axis of the background
   * @param posY the position in the y axis of the background
   * @param width the width of the background
   * @param height the height of the background
   * @param function1 a function that plays whenever the button changes states
   * @param toggle the state of the button. Is it a toggle or a simple, push down to activate, stop pushing to deactivate
   * @retval returns a button reference, (you can globaly initialize a button and set its variable to the button)
   */
  template <typename T1, typename T2, typename T3, typename T4>
  Button& addButton(const char* id_input, String text, int fontsize, uint16_t colour, T3 textOffsetX, T4 textOffsetY, bool background, uint16_t backgroundcolor, T1 posX, T2 posY, uint16_t width, uint16_t height, Function<void, Button*, bool> function, bool toggle, int line = __builtin_LINE(), const char* file = __builtin_FILE());//UI::addButton
  Button& addButton(const char* id_input);
  Button& getButton(const char* id, bool globalScope, int line, const char* file);//UI::getButton

  /**
   * @brief adds a button
   * @param id the id of the ui element (can be changed once set)
   * @param x the position in the x axis of the background
   * @param y the position in the y axis of the background
   * @param w the width of the background
   * @param h the height of the background
   * @param background is there a background?
   * @param colour the color of the background (if there is no background, the color you input doesn't matter)
   * @retval returns a Menu reference, (you can globaly initialize a Menu and set its variable to the Menu)
   */
  template <typename T1, typename T2>
  Menu& addMenu(const char* id, T1 x, T2 y, int16_t w, int16_t h, uint8_t background, uint16_t colour);//UI::addMenu
  Menu& addMenu(const char* id);
  Menu& getMenu(const char* id, bool globalScope, int line, const char* file);//UI::getMenu

  template <typename T1, typename T2>
  Window& addWindow(const char* id_input, uint16_t colour, T1 xpos, T2 ypos, uint16_t width, uint16_t height);//UI::addWindow
  Window& addWindow(const char* id_input);
  Window& getWindow(const char* id, bool globalScope, int line, const char* file);//UI::getWindow

  template <typename T1, typename T2>
  Terminal& addTerminal(const char* id_input, T1 window_x, T2 window_y, int16_t window_w, int16_t window_h, uint16_t backgroundColor, uint16_t textColor);//UI::addTerminal
  Terminal& addTerminal(const char* id_input);
  Terminal& getTerminal(const char* id, bool globalScope, int line, const char* file);//UI::getTerminal

  template<typename T1, typename T2>
  Canvas3D& addCanvas3D(const char* id, T1 x, T2 y, int16_t w, int16_t h, bool background = 1, uint16_t backgroundColour = 0);//UI::addCanvas3D
  Canvas3D& addCanvas3D(const char* id);
  Canvas3D& getCanvas3D(const char* id, bool globalScope, int line, const char* file);//UI::getCanvas3D

  //global function to create a UIelement of any type
  template<typename T, typename... Args>
  T& add(const char* id, Args... args)
  {
    T* element = new T(currUI, id, args...);   //call element constructor and create dynamically allocate memory for it
    arr->add((UIelement*)element); //add it to the element array list inside of the current UI
    return *element;               //return a reference to that specific element
  }

  //global function to create a UIelement of any type
  template<typename T, typename... Args>
  T& get(const char* id, bool globalScope = 0, int line = __builtin_LINE(), const char* file = __builtin_FILE());
  

  //UI::exits
  //check if the element exists based on its pointer
  bool exists(UIelement* element)
  {
    for(unsigned int i = 0; i < arr->size; i++)
    {
      if(element == arr->at(i))
      {
        return true;
      }
    }

    return false;
  }

  //check if an element exists based on its id
  bool exists(const char* id, bool globalScope = 0)
  {
    for(unsigned int i = 0; i < arr->size; i++)
    {
      UIelement* elem = arr->at(i);
      
      //we check if elem is a nullptr JUST IN CASE
      if(elem == nullptr)
      {
        println(F("ERROR line "),__LINE__,F(", detected a nullptr element"));
        continue;//continue just to be sure we don't use the elem
      }else
      {
        //if the strings are the same
        if(strcmp(id, elem->id) == 0)
        {
          return true;
        }
      }
    }

    return false;
  }

  void remove(const char* id);

  //UI::remove
  void remove(UIelement* ptr)
  {
    // we go through all of the ui elements
    for (unsigned int i = 0; i < arr->size; i++)
    {
      //if the ui element has the specific pointer we are looking for
      if(arr->at(i) == ptr)
      {
        delete arr->at(i);
        arr->remove(i); // don't forget to remove it from the array too
        return;//return early no need to continue checking
      }
    }
    
    // // if we didn't find a corresponding id
    println(F("ERROR line "),__LINE__,F(" in "),__FILE__,F(" couldn't find the pointer in the list of ui elements"));
  }

  //UI::clear
  void clear()
  {
    unsigned int staticSize = arr->size;

    // we go through all of the ui elements
    for (unsigned int i = 0; i < staticSize; i++)
    {
      
      if(arr->at(0) == nullptr)
      {
        println(F("ERROR line "),__LINE__,F(" in "),__FILE__,F(", nullptr detected in the arr"));
        while(true);
      }else
      {
        
        // then we delete
        delete arr->at(0);
        arr->remove(0); // don't forget to remove from the array too
      }
    }
  }

  UIBridge(UI* currUI);
};


//global::UI 
//class to manage the UI array, (updating ui, input handling for ui, acts as the middle man between the ui elements and the inputs of the user)
class UI : public UIBridge
{

  public:
  Array<UIelement*, MAX_ELEMENTS> arr; // we are simply creating an array of pointers to UIelement object with a custom class (this class does some very basic memory managements for you and is kind of like vector exept all of the features are missing exept "push_back" which is now "add" and "remove" just removes at last index or the specified index)
  unsigned long lastTouch;
  bool holding;
  bool focus;
  uint16_t basecolor;
  UI* prevUI;
  bool isManager; 
  uint8_t selected;
  UIelement* parent;
  uint8_t kbdShortcuts;
  UIelement* selectedElement;
  unsigned long drawingTime;

  #if WOKWI_SIM
    int pointRadius;
  #else
    int pointRadius;
  #endif

  //UI::printarray
  void printarray()
  {
    // test print println(F(" this function should not be playing (line "),__LINE__,F(")"));
    // test print println("printing array");
    // test print println("the size is : ",arr.size);

    // test print
    //println("(size : ",arr.size,")");
    for(unsigned int i = 0; i < arr.size; i++)
    {
      println(F("["),i,F("] = "),arr.at(i)->id);
    }
  }

  //is that too many variables? meh probably not thats like uhhhhhhhhhh 128 bytes.. dayum 128 bytes, ok thats maybe a bit much... we have 8 MB right...
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;

  //UIManager::touchCollide
  bool touchCollide(Point p, int16_t x, int16_t y, int16_t w, int16_t h)
  {
    return collide(x, y, w, h, p.x - pointRadius, p.y - pointRadius, pointRadius*2, pointRadius*2);
  }

  //UI::findElementWithId
  UIelement* findElementWithId(const char* id, int line = __builtin_LINE(), const char* file = __builtin_FILE())
  {
    // println("this function should not be called (line ",__LINE__,")");
    // println("in file '",__FILE__,"', in function '",__func__,", at line '",__LINE__,"'");
    for(unsigned int i = 0; i < arr.size; i++)
    {
      if(strcmp(arr.at(i)->id, id) == 0)
      {
        return arr.at(i);
      }
    }

    println(F("ERROR at line "),line,F(" in "),file,F(", COULD NOT FIND THE UI ELEMENT WITH ID: '"),id,F("' in the following list of UIs : "));
    println(F("Array size ("),arr.size,F(")"));
    printarray();
    println(F(""));
    return nullptr;
  }

  //UI::globalFindElementWithId
  UIelement* globalFindElementWithId(const char* id, int line = __builtin_LINE(), const char* file = __builtin_FILE())
  {

    if(this->arr.size > 0)
    {
      
    }
    // println("this function should not be called (line ",__LINE__,")");
    // println("in file '",__FILE__,"', in function '",__func__,", at line '",__LINE__,"'");
    UIelement* elem;
    UI* curr[30];
    int i[30];
    clearArray(curr, nullptr)
    clearArray(i, 0);
    curr[0] = this;
    int k = 0;
    
    while(this->arr.size > 0U)
    {
      elem = curr[k]->arr.at(i[k]);


      // for(int n = 0; n < k; n++)
      // {
      //   print("  ");
      // }
      // println("[",i[k],"] (size: ",curr[k]->arr.size,", k: ",k,") = ",elem->id);


      if(strcmp(elem->id, id) == 0)
      {
        return curr[k]->arr.at(i[k]);
      }

      //if element CAN contain elements and if the array of elements actually contains elements
      if(elem->container != nullptr && elem->container->arr.size > 0)
      {
        //update the k coutner to remember the index somewhere else
        k++;

        //if recursion passed the level we are able to store then give error and continue searching in current ui array
        if(sizeofarray(i) <= (size_t)(k))
        {
          println(F("ERROR line "),line,F(" in "),file,F(", recursion for globalFind went too deep ("),k,F(")"));

          k--;
        }else
        {
          //update the curr element (so we search in the container)
          curr[k] = elem->container;
        }
        
      }else
      {
        i[k]++;
      }

      while(curr[k]->arr.size <= (unsigned int)(i[k]))
      {
        //if we are done searching inside of current UI
        if(k == 0)
        {
          //get out of the loop to print error since we didn't find the UIelement the user was looking for
          goto breakOutOfLoop;
        }

        //go back one level
        k--;

        //increase the index too, we don't want to stay at the same element we were before going inside the container
        i[k]++;
      }
    }
    breakOutOfLoop:

    println(F("ERROR at line "),line,F(" in "),file,F(", COULD NOT FIND THE UI ELEMENT WITH ID: '"),id,F("' in the following list of UIs : "));

    clearArray(curr, nullptr)
    clearArray(i, 0);
    curr[0] = this;
    k = 0;

    //print the array in its fullest
    while(this->arr.size > 0U)
    {
      elem = curr[k]->arr.at(i[k]);


      for(int n = 0; n < k; n++)
      {
        print(F("  "));
      }
      println(F("["),i[k],F("] = "),elem->id);


      //if element CAN contain elements and if the array of elements actually contains elements
      if(elem->container != nullptr && elem->container->arr.size > 0)
      {
        //update the k coutner to remember the index somewhere else
        k++;

        //if recursion passed the level we are able to store then give error and continue searching in current ui array
        if(sizeofarray(i) <= (size_t)(k))
        {
          println(F("ERROR line "),line,F(" in "),file,F(", recursion for globalFind went too deep ("),k,F(")"));

          k--;
        }else
        {
          //update the curr element (so we search in the container)
          curr[k] = elem->container;
        }
        
      }else
      {
        i[k]++;
      }

      while(curr[k]->arr.size <= (unsigned int)(i[k]))
      {
        //if we are done searching inside of current UI
        if(k == 0)
        {
          //get out of the loop to print error since we didn't find the UIelement the user was looking for
          goto breakOutOfLoop2;
        }

        //go back one level
        k--;

        //increase the index too, we don't want to stay at the same element we were before going inside the container
        i[k]++;
      }
    }
    breakOutOfLoop2:

    println();
    return nullptr;
  }


  //UI::getTotalDisplacement
  DisplacePointUI getTotalDisplacement()
  {
    UI* currentUI = this;
    DisplacePointUI t = {0,0};
    int i = 0; 
    while(true)
    {
      t.x += currentUI->x;
      t.y += currentUI->y;

      //if we itreated for too long (stuck in some kind of loop) we just print some error stuff and get out of the loop
      if(i > 30)
      {
        println(F("ERROR, went down too many indexs (you might have too many elements in elements);"));
        break;
      }

      //if the previous ui is a nullptr then we break;
      if(currentUI->prevUI == nullptr)
      {
        break;
      }

      currentUI = currentUI->prevUI;

      i++;
    }

    return t;
  }

  //UI::getCombinedRectangle
  RectangleParams getCombinedRectangle()
  {
      int pathLen = 0;
      
      UI* temp = this;
      while(temp != nullptr && pathLen < 10)
      {
          // CHECK FOR LOOPS!
          for(int i = 0; i < pathLen; i++) {
              if (g_pathBuffer[i] == temp) {
                  Serial.println(F("!!! CIRCULAR REFERENCE DETECTED !!!"));
                  Serial.print(F("Loop at depth: ")); Serial.println(pathLen);
                  while(1);
              }
          }
          
          g_pathBuffer[pathLen++] = temp;
          temp = temp->prevUI;
      }
      
      if (pathLen >= 10) {
          Serial.println(F("!!! PATH TOO DEEP !!!"));
          while(1);
      }
      
      // Now calculate absolute positions with ONE pass
      int16_t absX = 0, absY = 0;
      
      for(int i = pathLen - 1; i >= 0; i--)  // Root to leaf
      {
          absX += g_pathBuffer[i]->x;
          absY += g_pathBuffer[i]->y;
      }
      
      // Start with this UI's rectangle
      RectangleParams r = {absX, absY, w, h};
      
      // Intersect with each parent
      int16_t cumX = 0, cumY = 0;
      for(int i = pathLen - 1; i > 0; i--)  // Don't include 'this' (index 0)
      {
          cumX += g_pathBuffer[i]->x;
          cumY += g_pathBuffer[i]->y;
          
          r = combineRectangles16(r, {cumX, cumY, g_pathBuffer[i]->w, g_pathBuffer[i]->h});
      }
      
      return r;
  }

  
  //UI::select
  /**
   @param p the point where a touch even happent
   @brief this function gets the UIelement that is touching the point provided in the current UI object
   @retval returns the pointer to that UIelement
  */
  UIelement* select(Point p)
  {
    //if the point that has been pressed is not inside of the current window, then we know nothing is going to be selected
    {
      RectangleParams r = getCombinedRectangle();
      if(!touchCollide(p, r.x, r.y, r.w, r.h)) return nullptr;
    }

    //globaly set the total displacement (we know its never going to change)
    DisplacePointUI d = getTotalDisplacement();

    UIelement* bm = nullptr;

    for(int j = INT8_MIN; j <= INT8_MAX; j++)
    {
      //bm -> bestMatch (its the element that is colliding with the point that has the highest z)
      
      for(int i = arr.size - 1; i >= 0 ; i--)
      {
        UIelement* elem = arr.at(i);

        if(elem != nullptr)
        {
          if(elem->z_index == j)
          {
            if(bm == nullptr)
            {
              //bm isn't set to anything yet, so the current element becomes the best element IF ITS BEING TOUCHED

              //if the pixel is not inside of the window
              bool collided = touchCollide(p, d.x + elem->x, d.y + elem->y, elem->w, elem->h);

              //if it is being touched
              if(elem->selectable == 1 && collided)
              {
                //the current element becomes the best element
                bm = elem;
              }
            }else
            {

              //if the pixel is not inside of the window
              bool collided = touchCollide(p, d.x + elem->x, d.y + elem->y, elem->w, elem->h);

              //if the z_index of the current element is bigger than the best element (and check if the element is selectable)
              if(elem->selectable == 1 && collided && (bm->z_index < elem->z_index))
              {
                //if it is, the current element becomes the best element
                bm = elem;
              }
            }
          }
        }else
        {
          println(F("ERROR line "),__LINE__,F(", detected a nullptr in the arr at index "),i);
        }
      }
    }

    //return best match
    return bm;
  }

  //UI::handleInput
  void handleInput(Point p, bool holding, bool focus)
  {
    
    //has a new touch started and this UI is selected 
    if(holding == 0 && focus == 1)
    {
      // println(F("started a new touch"));

      //if the selected element isn't nullptr (if there was a prior selected element)
      if(selectedElement != nullptr)
      {
        // println(F("making an element DESELECTED"));

        //if the element is selectable then we deselect it
        if(selectedElement->selectable == 1)
        {
          //use the deselect() function (gives more control to the element, on what to do for deselection)
          selectedElement->selectionChanged(0);
        }
      }

      //update the selected element
      selectedElement = select(p);

      //if selected element isn't nullptr (if we actually selected anything) AND if this current UI is being selected (if this UI is being selected it means that it can make its children selected) but if its not selected, it should still be able to unselect its children, its stupid, I know, but thats what it is...
      if(selectedElement != nullptr && selected)
      {
        //if this UI has a parent associated with it
        if(parent != nullptr)
        {
          //if the parent and the selected element is selectable
          if(parent->selectable == 1 && selectedElement->selectable == 1)
          {
            //set the parent to selected 2 (meaning it holds an element that is selected)
            parent->selectionChanged(2);
          }
        }

        if(selectedElement->selectable == 2)
        {
          //set this current UI object to selected 2 because it holds an element that is selected
          selected = 2;
        }

        // println(F("making an element selected"));

        //make the new selected element selected  (if it is selectable of course)
        if(selectedElement->selectable == 1)
        {
          //use the select() function (gives more control to the element, on what to do for selection)
          ::println("selecting : \"",selectedElement->id,"\"");
          selectedElement->selectionChanged(1);
        }

      //else if its the main manager then we should be selecting it when we can't select anything else
      }else if(isManager == 1)
      {
        selected = 1;
      }

    //if we stopped holding the element
    }//else if(holding == 0 && focus == 0)
    // {
    //   //deselect whatever element we were holding
    //   if(selectedElement != nullptr)
    //   {
    //     //deselect the previously selected element
    //     selectedElement->selected = 0;
    //   }
    // }

    //go through all of the arr and handleInput for them
    for(unsigned int i = 0; i < arr.size; i++)
    {
      if(arr.at(i) == nullptr)
      {
        println(F("UH OH, NOT GOOD, WE HAVE A NULLPTR!!!---------------------------------------------notice"));
      }else
      {
        Function<void, UIelement*, Point, bool, bool>& userFunc = arr.at(i)->userHandleInput;

        //if the user function is not a nullptr (exists, then play it)
        if(userFunc)
        {
          userFunc(arr.at(i), p, holding, focus);//play the custom user function (before actuall handle input)
        }

        arr.at(i)->handleInput(p, holding, focus);// play update functioon for all YOU NEED TO ADD THE Z_INDEX THINGY DON'T FORGET ABOUT IT PLEASE--------------------------------------
      }
    }
  }
  
  //UI::handleKeyboardInput
  void handleKeyboardInput()
  {

    // println("WHAT THE FUCK, IT IS NOT SUPPOSED TO DO THIS FUNCTION ---------------------------------------notice");
    for(unsigned int i = 0; i < arr.size; i++)
    {
      if(arr.at(i) == nullptr)
      {
        println(F("UH OH, NOT GOOD, WE HAVE A NULLPTR!!!---------------------------------------------notice"));
      }else
      {
        Function<void, UIelement*>& userFunc = arr.at(i)->userHandleKeyboardInput;

        //if the user function exists, then play it
        if(userFunc)
        {
          userFunc(arr.at(i));//play the custom user function (before actuall handle input)
        }

        arr.at(i)->handleKeyboardInput();// play update functioon for all YOU NEED TO ADD THE Z_INDEX THINGY DON'T FORGET ABOUT IT PLEASE--------------------------------------
      }
    }
  }

  //UI::addUIpointer
  void addUIpointer(UIelement *pointer)
  {
    arr.add(pointer); // add the pointer at the end of the array
  }
  
  //UI::removeUIpointer 
  //this removes from the array only
  void removeUIpointer(UIelement *pointer)
  {
    println(F("this function should not playing right now (line 991)"));
    // we go through all of the UIelement pointers in the array
    for(unsigned int i = 0; i < arr.size; i++)
    {
      // we find the corresponding pointer (the same pointer as in the function input)
      if(arr.at(i) == pointer)
      {
        arr.remove(i); // we remove the pointer from the list
      }
    }
  }
  
  //UI::tick
  void tick()
  {
    // maybe change the order idk
    for (unsigned int i = 0; i < arr.size; i++)
    {
      arr.at(i)->tick();
    }
  }

  //UI::touchUpdateAddition
  virtual void touchUpdateAddition(){}

  //UI::update
  void update()
  {

    //testprintln("touchUpdateAddition");
    
    touchUpdateAddition();

    drawingTime = millis();//temporarly store time of start of drawing

    //after the keyboard (bcs emulation is weird and stops the whole code so we don't want to stop code after we drew a window)
    #if defined(NORMAL_DRAWING_ORDER)

      //first bit fo UI_SETTINGS is supposed to be "are we not clearing the screen?"
      if(isManager && !(UI_SETTINGS & 1))
      {
        tft.fillScreen(basecolor);
      }

    #endif

    #if !defined(NORMAL_DRAWING_ORDER)
      
      //show cursor on GIGA (because we are using the keyboard)
      #if !WOKWI_SIM

        if(isManager && enabletouch)
        {

          uint16_t cursorColor = color(0, 0, 255);

          if(cursorClicky)
          {
            cursorColor = color(255, 0, 0);
          }

          //upper part of the cursor
          tft.fillRect(globalx, globaly - 6, 1, 5, cursorColor);

          //lower part of the cursor
          tft.fillRect(globalx, globaly + 1, 1, 5, cursorColor);

          //lefter part of the cursor
          tft.fillRect(globalx - 6, globaly, 5, 1, cursorColor);

          //righter part of the cursor
          tft.fillRect(globalx + 1, globaly, 5, 1, cursorColor);
        }
      #endif
      
    #endif

    //go through all of the possible z_indexs (switch between min->max and max->min depending on drawing order)
    #if defined(NORMAL_DRAWING_ORDER)
    for(int j = INT8_MIN; j < INT8_MAX; j++)
    #else
    for(int j = INT8_MAX - 1; j >= INT8_MIN; j--)
    #endif
    {
      //go through all ofthe list of UIelements
      for (int i = (int)arr.size - 1; i >= 0 ; i--)
      {
        UIelement* ptr = arr.at(i);//get ui element

        //if its a nullptr, print error
        if(ptr == nullptr)
        {
          println(F("ERROR, nullptr detected in uiPtrArray (go to line "),__LINE__,F(" to see where this print statement was put)"));
          continue;
        }

        //if its not then update it and draw bound box if its selected
        if(ptr->z_index == j)
        {
          // println("drawing element ",ptr->id);
          
          if(ptr->userTick)
          {
            ptr->userTick(ptr);
          }
          
          ptr->tick();

          //invert the user update and the element update (the user update must always be able to overwrite the element update)
          #if defined(NORMAL_DRAWING_ORDER)

            ptr->update();

            //if the user update function exists 
            if(ptr->userUpdate)
            {
              ptr->userUpdate(ptr);//play the custom user function
            }

          #else

            //if the user update function exists 
            if(ptr->userUpdate)
            {
              ptr->userUpdate(ptr);//play the custom user function
            }

            ptr->update();

          #endif

          //is the ui selected AND selectable in the first place
          if(ptr->selected == 1 && ptr->settings & 0b1)
          {
            //get total displacement because positions are local (based on the parent's positiond)
            DisplacePointUI d = getTotalDisplacement();

            // println("drawing selected bounding box");
            tft.drawRect(ptr->x + d.x - 5, ptr->y + d.y - 5, ptr->w + 10, ptr->h + 10, 0xFFFF);//draw bounding box if its selected
          }
        }
      }
    }  

    #if !defined(NORMAL_DRAWING_ORDER)

      //first bit fo UI_SETTINGS is supposed to be "are we not clearing the screen?"
      if(isManager && !(UI_SETTINGS & 1))
      {
        tft.fillScreen(basecolor);
      }

    #endif

    #if defined(NORMAL_DRAWING_ORDER)
      
      //show cursor on GIGA (because we are using the keyboard)
      #if !WOKWI_SIM

        if(isManager && enabletouch)
        {

          uint16_t cursorColor = color(0, 0, 255);

          if(cursorClicky)
          {
            cursorColor = color(255, 0, 0);
          }

          //upper part of the cursor
          tft.fillRect(globalx, globaly - 6, 1, 5, cursorColor);

          //lower part of the cursor
          tft.fillRect(globalx, globaly + 1, 1, 5, cursorColor);

          //lefter part of the cursor
          tft.fillRect(globalx - 6, globaly, 5, 1, cursorColor);

          //righter part of the cursor
          tft.fillRect(globalx + 1, globaly, 5, 1, cursorColor);
        }
      #endif
      
    #endif


    // test print println("displaying the frame buffer");
    if(isManager && !(UI_SETTINGS & 0b100))
    {
      //wokwi_sim's graphical commands print straight to the screen, we can therefor skip the displayFrameBuffer part... and fuck I just remembered I changed everything to be drawn in inverse order, damn thats annoying
      #if !WOKWI_SIM
        displayFrameBuffer();//display on the actuall screen
        resetDrawnPixel();//reset the drawn pixel so that we can actually darw afterwards
      #endif
    }
  
    //calculate time it took to draw and set drawingTime to that
    //drawing time temporarly used as storer of start time of drawing
    drawingTime = millis() - drawingTime;
    
  }


  UI() : UIBridge(this)
  {
    //variable initializations
    this->lastTouch = 0;
    this->holding = false;
    this->focus = false;
    this->basecolor = 0;
    this->prevUI = nullptr;
    this->isManager = false;
    this->selected = 0;
    this->parent = nullptr;
    this->kbdShortcuts = 0;
    this->selectedElement = nullptr;
    #if WOKWI_SIM
      this->pointRadius = 7;
    #else
      this->pointRadius = 5;
    #endif
    this->x = 0;
    this->y = 0;
    this->w = 240;
    this->h = 320;
  }
};

//global function to create a UIelement of any type
template<typename T, typename... Args>
T& UIBridge::get(const char* id, bool globalScope, int line, const char* file)
  {
    //create UIelement (base element class) pointer (we are going to set it in the following code)
    UIelement* elem;

    //find the element based on scope
    if(globalScope)
    {
      elem = currUI->globalFindElementWithId(id, line, file);
    }else 
    {
      elem = currUI->findElementWithId(id, line, file);    
    }

    //if we DIDN'T an element, return a dummy element (error handled by find element function)
    if(elem == nullptr)
    {
      //use default element constructor (empty constructor) and return dummy item
      static T dummy(currUI, "dummy");
      return dummy;
    }

    //if we found an element, return a reference to that element
    return *((T*)(elem));
  }
  
UIBridge::UIBridge(UI* currUI = nullptr)
{
  this->currUI = currUI;
  
  if(currUI == nullptr)
  {
    arr = nullptr;
  }else
  {
    arr = &currUI->arr;
  }
}

//UI::remove
void UIBridge::remove(const char* id)
{
  println(F("SHOULD NOT BE REMOVING ANY UI ELEMENT WHAT THE FUCK"));

  currUI->printarray();

  // we go through all of the ui elements
  for (unsigned int i = 0; i < arr->size; i++)
  {
    // if the ui element has the specific id we are looking for
    if (strcmp(arr->at(i)->id, id) == 0)
    {
      UIelement* elem = arr->at(i);
      delete elem;

      DEBUG_BANNER("after deleting the Shell");
      currUI->printarray();

      //remove from pointer (and not known i, since the destructor of the element might have deleted some elements)
      remove(elem);

      DEBUG_BANNER("after remove of \"",id,"\" : ");
      currUI->printarray();


      return;
    }
  }
  
  // if we didn't find a corresponding id
  println(F("ERROR, couldn't find '"), id, F("' in the list of ui elements"));
}


// #define RELW(a, b) (b * (a / tft.screen_width ))//relative width
// #define RELH(a, b) (b * (a / tft.screen_height))//relative height

//get absolute position (position acounting all of the parent positions)
Point UIelement::absPos()
{
  if(ui1 == nullptr)
  {
    //not normal, this shouldn't be happening as all UIelements must be inside of a UI to even be showed up
    return {x, y};
  }else
  {
    DisplacePointUI d = ui1->getTotalDisplacement();
    return {(int16_t)(d.x + x), (int16_t)(d.y + y)};
  }
}

void UIelement::setx(int input)
{
  x = setPos(input, w, ui1->w, 0);
}

void UIelement::setx(const char* input)
{
  x = setPos(input, w, ui1->w, 0);
}

void UIelement::sety(int input)
{
  y = setPos(input, h, ui1->h, 1);
}

void UIelement::sety(const char* input)
{
  y = setPos(input, h, ui1->h, 1);
}

//global::UIManager
class UIManager : public UI
{
  public:

  Function<void, Point, bool, bool> touchInput;//void touchInput(Point p, bool holding, bool lostfocus);
  int number;//what the fuck is that ??? ----------------------------------------------------------------------
  uint8_t initialized;
  // bool selected = false;

  //UIManager::begin
  void begin()
  {
    

    if(initialized == 1) return;
    initialized = 1;
    // Serial.begin(9600);
    // DELAY(3000);
    // Serial.println("Starting...");
    // Serial.println("DO NOT FUCKING FORGET ABOUT SAVING CHANGES TO THE ONLINE VERSION OF WOKWI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    kbd.begin();

    //wait for serial or keyboard input
    while(!Serial)
    {
      #if !defined(EMULATE_KEYBOARD)
      
        //always do once every repetition but if kbd.available is bigger than 0 repeat until it is 0
        do
        {
          //update keyboard (let the keyboard fetch the keys that are being pressed)
          kbd.update();

          //if any keys are being pressed break out of everything
          if(!kbd.keysClear()) goto endLoop;

        } while (kbd.available > 0);

      #endif
      
      //wait a little bit because why not
      delay(1000);
    }

    #if !defined(EMULATE_KEYBOARD)
    endLoop:
    #endif

    Serial.println("Starting...");  
    kbd.begin();


    //initialize customGraphics library
    tft.begin();


    //fill with base color or smth
    tft.fillScreen(basecolor);
    #if !WOKWI_SIM
      resetDrawnPixel();//reset the drawn pixel so that we can draw afterwards (bcs, drawing is front to back)
    #endif

    selected = 1;

    #if WOKWI_SIM
      if (!ctp.begin())
      { // Initialize the capacitive touch screen
        Serial.println("Couldn't start FT6206 touchscreen controller");
        while (1);
      }
      Serial.println("Capacitive touchscreen started");
    #else
      // Initialize your resistive touchscreen here
      
      // Start SPI1 (shared with display)
      // SPI1.begin();

      // if (!ts.begin(SPI1)) {
      //   Serial.println("ERROR: Touch controller not found!");
      //   Serial.println("Check your T_CS wire (should be pin 3)");
      //   while(1);
      // }

      // DON'T initialize XPT2046 library - we're doing it manually
      // pinMode(T_CS, OUTPUT);
      // digitalWrite(T_CS, HIGH);
    #endif
  }

  void handleTouch()
  {
    
    if(enabletouch == 1)
    {
      if(touched())
      {
        Point p = getPoint();

        //testprintln("god the point, now handling for input");

        if(p.x != 240 && p.y != 320)
        {
          focus = true;

          // check if we are holding
          #if WOKWI_SIM
          if ((long long)(millis()) - (long long)(lastTouch) - (long long)(drawingTime) <= 75)
          #else
          if ((long long)(millis()) - (long long)(lastTouch) - (long long)(drawingTime) <= 200)
          #endif
          {
            holding = true;
          }else
          {
            holding = false;
          }

          handleInput(p, holding, focus);

          if(touchInput)
          {
            touchInput(p, holding, focus);
          }

          lastTouch = millis();
        }
      }

      #if WOKWI_SIM
      if ((long long)(millis()) - (long long)(lastTouch) > 75)
      #else
      if ((long long)(millis()) - (long long)(lastTouch) > 200)
      #endif
      {
        handleInput({0,0}, false, 0);

        // disable all of the button thingy idk
        holding = 0;
        focus = 0;//undo the focus
      }

    }else if(enabletouch == 0)
    {
      //just tell everything, HEY, WE STOPPED THE TOUCH
      handleInput({0,0}, false, 0);

      // disable all of the button thingy idk
      holding = 0;
      focus = 0;//undo the focus
    }

    if(selected == 1)
    {
      // if(kbd.keys.lctrl == 1 && kbd.keys.lshift == 0 && kbd.keys.lalt == 0 && kbd.lastKey == 0 && kbd.currKey == KEY_T && kbdShortcuts != 1)
      // {
      //   kbdShortcuts = 1;//set to one so we ignore repeats
      //   addTerminal("terminal1", "middle", "middle", 200, 200, color(0,0,0), color(0, 255, 0));
      // }

      if(kbd.keysClear())
      {
        kbdShortcuts = 0;//reset kbd shortcuts back to zero so we can use keyboard shortcuts again
      }
    }
  }

  //UIManager::touchUpdateAddition
  //add the touch updating to the UIManager UI only because we don't want to update the whole touch thingy when we simply want to update UIs
  void touchUpdateAddition()
  {
    //update keyboard (fetch new keys)
    kbd.update();

    //handle for touch inputs
    handleTouch();
    
    //let all other elements use keyboard info
    handleKeyboardInput();
    
    //as long as we have keys being pressed, loop
    while(kbd.available)
    {
      //update keyboard (fetch new keys)
      kbd.update();

      //we didn't draw so make it zero
      drawingTime = 0;

      //handle for touch inputs
      handleTouch();
      
      //let all other elements use keyboard info
      handleKeyboardInput();
    }
  }

  UIManager()
  {
    //Initialize the UIBridge to use the "addText" and "get..." functions
    UIBridge::currUI = (UI*)(this);
    UIBridge::arr    = &arr;

    //variable initializations
    this->number = 0;
    this->initialized = 0;

    isManager = true;//set is manager to true because... its the manager

    // x = 0;
    // y = 0;
    // w = SCREEN_WIDTH;
    // h = SCREEN_HEIGHT;
  }
};

/*inline*/ UIManager ui;

//global::Text
class Text : public UIelement
{
  public:
  String fixedText;
  String text;
  int8_t fontsize;
  uint16_t colour;

  //for when we want the text to be editable by the user
  uint8_t editable;
  uint8_t lastSelected;
  uint8_t updateTextSize;
  unsigned int lastBufferLength;

  template<typename T>
  void setx(T input)
  {
    String combined = fixedText + text;
    Size info = getTextBounds(combined, fontsize);
    x = setPos(input, info.w, ui1->w, 0);
  }

  template<typename T>
  void sety(T input)
  {
    String combined = fixedText + text;
    Size info = getTextBounds(combined, fontsize);
    // x = setPos(input, w1, ui1->w, 0);
    y = setPos(input, info.h, ui1->h, 1);
  }

  //Text::handleKeyboardInput
  void handleKeyboardInput()
  {
    //make sure that we don't accidentally lock editable inside of one state
    if(editable == 1)
    {
      //if the text recieved a new click
      if(selected == 1 && lastSelected == 0)
      {
        lastSelected = 2;

        //update teh keyboard input
        kbd.buffer = text;//the text should have been set to the kbd buffer so it should be fine
        kbd.enableBuffer = false; //If we just clicked on the window, we don't ant to register keyboard for the new presses so disable that bitch

        //we disable the touch (makes the cursor dissapear so we can use the arrows to select text, escape to get out)
        enabletouch = 0;

      //if the text isn't in focus anymore (shouldn't happen) or if the escape key was pressed
      }else if((selected == 0 && lastSelected == 1) || (kbd.checkForKey(KEY_ESCAPE)))
      {
        text = kbd.buffer;//update text for last time 
        lastSelected = 0;//update the lastSelected (its used to tell us if selection has changed)
        selected = 0;//force element to be unselected
        kbd.enableBuffer = false;//disable the buffer (to go back to normal)

        //re-enable the touch
        enabletouch = 1;

        //re-enable the rapid fire DELAY
        kbd.delayLimiter = 0;
      }

      //if the text is currently being selected
      if(lastSelected == 1)
      {
        text = kbd.buffer;
      }

      //when we actually stop clicking on space
      if(lastSelected == 2 && !kbd.checkForKey(KEY_SPACEBAR))
      {
        lastSelected = 1;
        kbd.enableBuffer = true;
        kbd.buffer = text;
        
        //enable normal key repeat timing for writting on keyboard
        kbd.delayLimiter = 1;
      }
    }
  }

  //Text::draw
  void draw()
  {
    DisplacePointUI d = ui1->getTotalDisplacement();
    // tft.drawText(fixedText + text, (x + d.x), (y + d.y), fontsize, colour);
    //combine both the fixed text and the text (for cursor and selector reasons
    // String combined = fixedText + text;
    tft.setCursor((x + d.x), (y + d.y), fontsize, colour, (x + d.x), (y + d.y));

    //print the fixed text first
    tft.print(fixedText);

    //if the cursor is inside of the text (bound check) and it is editable (we want to draw the cursor)
    if(0 <= kbd.cursorIndex && kbd.cursorIndex <= (int)text.length() && editable)
    {
      if(kbd.cursorIndex == 0)
      {
        if(selected == 1)
        {
          //print the cursor
          tft.fillRect(tft.cursor_x, tft.cursor_y - fontsize, 1, (FONT_HEIGHT + 2) * fontsize, color(100, 100, 255));
        }
        
        //print the rest of the text
        tft.print(text.substring(kbd.cursorIndex, text.length()));

      //else if we are at the start of any line draw the cursor one to the right (so we can actually see it)
      }else if(kbd.buffer[kbd.cursorIndex - 1] == '\n')
      {
        //print the first part of the text
        tft.print(text.substring(0, kbd.cursorIndex));

        if(selected == 1)
        {
          //print the cursor
          tft.fillRect(tft.cursor_x, tft.cursor_y - fontsize, 1, (FONT_HEIGHT + 2) * fontsize, color(100, 100, 255));
        }

        //print the rest of the text
        tft.print(text.substring(kbd.cursorIndex, text.length()));


      //if the cursor is at the very tippy left we do smth different
      }else if(kbd.cursorIndex == (int)text.length())
      {
        //print the whole text
        tft.print(text);

        if(selected == 1)
        {
          //print the cursor
          tft.fillRect(tft.cursor_x - 1, tft.cursor_y - fontsize, 1, (FONT_HEIGHT + 2) * fontsize, color(100, 100, 255));
        }

      //if the cursor isn't at some weird place, do standart to display cursor
      }else if(0 <= kbd.cursorIndex && kbd.cursorIndex < (int)text.length())
      {
        //print the first part of the text
        tft.print(text.substring(0, kbd.cursorIndex));

        if(selected == 1)
        {
          //print the cursor
          tft.fillRect(tft.cursor_x - 1, tft.cursor_y - fontsize, 1, (FONT_HEIGHT + 2) * fontsize, color(100, 100, 255));
        }
        
        //print the rest of the text
        tft.print(text.substring(kbd.cursorIndex, text.length()));
      }

    //else if the cursor is, draw the text like a normal person.. without the cursor
    }else
    {

      //print the whole text
      tft.print(text);
    }
    
  }

  //Text::update
  void update()
  {
    if(updateTextSize == 1)
    {
      Size info = getTextBounds(fixedText + text, fontsize);//(text, 0, 0, &x1, &y1, &w1, &h1);
      w = info.w;
      h = info.h;
    }

    // ::println(text);
    draw();
  }

  //Text::print
  void print(){} template<typename T> void print(T input){::print(input); fixedText += input;}  
  
  //Text::println
  void println(){fixedText += '\n';} template<typename T> void println(T input){::println(input); fixedText += input; fixedText += '\n';} 

  //Text::Text
  template <typename T1, typename T2>
  Text(UI* ui1, const char* id_input, String text, int fontsize, uint16_t colour, T1 xpos, T2 ypos, uint16_t modew, uint16_t modeh)
  {
    //Variable Initializations (note to self : always add this to any and all constructor unless you want to change the default values of the variables)
    this->fixedText = "";
    this->text = "";
    this->fontsize = 1;
    this->colour = 0x0000;
    this->editable = 0;
    this->lastSelected = 0;
    this->updateTextSize = 1;
    this->lastBufferLength = 0;

    this->type = "Text";//set the type of the object (so that we can know what it is)
    this->ui1 = ui1;
    // we replicate all of the values above

    //this is the length of the string
    size_t len = strlen(id_input);

    //allocate memory for a id that is the same as input (we add one to include the \0 terminator character)
    this->id = new char[len + 1];
    
    //copy the string over to "id" storage
    strcpy(this->id, id_input);

    this->text = text;
    this->fontsize = fontsize;
    this->colour = colour;
    
    Size info = getTextBounds(text, fontsize);//(text, 0, 0, &x1, &y1, &w1, &h1);

    x = setPos(xpos, info.w, ui1->w, 0);
    y = setPos(ypos, info.h, ui1->h, 1);

    // ui1->addUIpointer(this); // add to the ui manager list
  }

  //default constructor with id only (default values for text)
  Text(UI* currUI, const char* id_input) : Text(currUI, id_input, "Hello World!", 1, rgb(0, 100, 0), "middle", "middle", 0, 0){}

  //Text::~Text
  ~Text()
  {
    // delete[] id;//remove the id that was alocated in memory for this ui element
    ::println(F("Text destructor for ID : "),id,F(" <- NOTICE ------------------------------------------------------------"));
  
    //don't forget to enable back the enabletouch (if we are editing) 
    if(selected == 1 && editable)
    {
      enabletouch = true;
    }

    //de-alocate memory for the id (AFTER PRINTING MESSAGE CONTAINING THAT ID)
    delete[] this->id;
  }
};

//global::Button
class Button : public UIelement
{
  public:
  int16_t tx;
  int16_t ty;
  String text;
  int8_t fontsize;
  uint16_t colour;
  uint16_t backgroundcolor;
  bool background;
  bool usingTextPos;
  bool lastButtonState;
  bool buttonState;
  bool toggleable;
  Function<void, Button*, bool> onClick; //onClick(Button* self, bool buttonState)

  //Button::setx
  template<typename T>
  void setx(T input)
  {
    x = setPos(input, w, ui1->w, 0);
    // y = setPos(input, h, ui1->h, 1);
  }

  //Button::sety
  template<typename T>
  void sety(T input)
  {
    // x = setPos(input, w, ui1->w, 0);
    y = setPos(input, h, ui1->h, 1);
  }

  //Button::setTextx
  template<typename T>
  void setTextx(T input)
  {
    Size info = getTextBounds(text, fontsize);
    tx = setPos(input, info.w, w, 0);
  }

  //Button::setTexty
  template<typename T>
  void setTexty(T input)
  {
    Size info = getTextBounds(text, fontsize);
    // tx = setPos(input, info.w, w, 0);
    ty = setPos(input, info.h, h, 1);
  }  

  //Button::handleinput
  void handleInput(Point p, bool holding, bool focus)
  {
    DisplacePointUI d = ui1->getTotalDisplacement();

    if(background == false)
    {
      Size info = getTextBounds(text, fontsize);
      //probably not good ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

      bool collided = ::ui.touchCollide(p, (tx + d.x),(ty + d.y),info.w,info.h);

      if(toggleable)
      {
        //if a new touch started 
        if(selected == 1 && holding == 0 && focus == 1 && collided == 1)
        {
          //invert the buttons state
          buttonState = !buttonState;
        }
      }else
      {
        //if a new touch started on the button
        if(selected == 1 && holding == 0 && focus == 1 && collided == 1) 
        {
          //activate the button
          buttonState = 1;
        }else if(selected == 1 && holding == 0 && focus == 0)
        {
          //disactivate the button
          buttonState = 0;
        }
      }
    }else
    {
      bool collided = ::ui.touchCollide(p, (x + d.x),(y + d.y),w,h);

      if(toggleable)
      {
        //if a new touch started 
        if(selected == 1 && holding == 0 && focus == 1 && collided == 1)
        {
          
          //invert the buttons state
          buttonState = !buttonState;
        }
      }else
      {
        //if a new touch started on the button
        if(selected == 1 && holding == 0 && focus == 1 && collided == 1) 
        {
          //activate the button
          buttonState = 1;
        }else if(selected == 1 && holding == 0 && focus == 0)
        {
          //disactivate the button
          buttonState = 0;
        }
      }

    }
  }

  //Button::draw
  void draw()
  {
    DisplacePointUI d = ui1->getTotalDisplacement();

    #if defined(NORMAL_DRAWING_ORDER)
    
      if(background)
      {
        tft.fillRect((x + d.x),(y + d.y),w,h,backgroundcolor);
      }

      tft.drawText(text, (tx + x + d.x), (ty + y + d.y), fontsize, colour);
    
    #else
    
      tft.drawText(text, (tx + x + d.x), (ty + y + d.y), fontsize, colour);
  
      if(background)
      {
        tft.fillRect((x + d.x),(y + d.y),w,h,backgroundcolor);
      }
      
    #endif
  }

  //Button::update
  void update()
  {
    //if the state of the button changed
    if(buttonState != lastButtonState)
    {
      //if the function exists
      if(onClick)
      {
        onClick(this, buttonState);//play the custom function
      }
    }

    draw();

    lastButtonState = buttonState;
  }

  //Button::Button
  template <typename T1, typename T2, typename T3, typename T4>
  Button(UI* ui1, const char* id_input, String text, int fontsize, uint16_t colour, T3 textOffsetX, T4 textOffsetY, bool background, uint16_t backgroundcolor, T1 posX, T2 posY, int16_t width, int16_t height, Function<void, Button*, bool> onClick, bool toggle)
  {
    //Variable initializations (note to self add this to any and all constructors)
    this->ui1 = ui1;
    this->text = "";
    this->fontsize = 1;
    this->colour = 0x0000;
    this->backgroundcolor = 0;
    this->background = false;
    this->lastButtonState = false;
    this->buttonState = false;
    this->toggleable = false;


    this->type = "Button";//set the type so that we can know what it is
    // we replicate all of the values above
    toggleable = toggle;
    
    //this is the length of the string
    size_t len = strlen(id_input);

    //allocate memory for a id that is the same as input (we add one to include the \0 terminator character)
    this->id = new char[len + 1];
    
    //copy the string over to "id" storage
    strcpy(this->id, id_input);;

    this->text = text;
    this->fontsize = fontsize;
    this->colour = colour;
    
    Size info = getTextBounds(text, fontsize);//(text, 0, 0, &x1, &y1, &w1, &h1);

    //if we don't have a background
    if(width == 0 || height == 0 || background == false)
    {
      tx = setPos(textOffsetX, info.w, ui1->w, 0);
      ty = setPos(textOffsetY, info.h, ui1->h, 1);
    }else
    {
      tx = setPos(textOffsetX, info.w, width, 0);
      ty = setPos(textOffsetY, info.h, height, 1);
    }
    
    this->onClick = onClick;
    this->background = background;
    this->backgroundcolor = backgroundcolor;
    this->w = width;
    this->h = height;
    // this->toggleable = toggle;

    x = setPos(posX, w, ui1->w, 0);
    y = setPos(posY, h, ui1->h, 1);
  }

  //default constructor for id only
  Button(UI* currUI, const char* id) : Button(currUI, id, "Button", 1, rgb(50, 50, 0), "middle", "middle", true, rgb(100, 100, 0), "middle", "middle", RELW(200), RELH(100), nullptr, false){}

  //Button::~Button
  ~Button()
  {
    
    //n of the id (cuz we alocated that right)
    println(F("Button destructor for ID : "),id,F(" <- NOTICE ------------------------------------------------------------"));

    delete[] id;//de alocation
  }
};



//global::Menu
class Menu : public UIBridge, public UIelement
{
  //make everything public
  public:
  UI ui; //UI class, contains ui elements
  uint16_t colour; //colour of the background of the Menu
  uint8_t background;
  uint8_t hide_after_edge = false;
  uint8_t handleScrolling = false;
  int scroll_x = 0;
  int scroll_y = 0;

  //Menu::setx
  template<typename T>
  void setx(T input)
  {
    x = setPos(input, w, ui1->w, 0);

    ui.x = this->x;
    ui.y = this->y;
    ui.w = this->w;
    ui.h = this->h;
  }

  //Menu::sety
  template<typename T>
  void sety(T input)
  {
    y = setPos(input, h, ui1->h, 1);

    ui.x = this->x;
    ui.y = this->y;
    ui.w = this->w;
    ui.h = this->h;
  }

  //Menu::handleInput
  void handleInput(Point p, bool holding, bool focus)
  {
    //let handleInput propagate to childrens
    ui.handleInput(p, holding, focus);
  }

  //Menu::handleKeyboardInput
  void handleKeyboardInput()
  {
    //let hanldeKeyboardInput propagate to childrens
    ui.handleKeyboardInput();
  }

  //Menu::draw
  void draw()
  {
    ui.x = this->x;
    ui.y = this->y;
    ui.w = this->w;
    ui.h = this->h;

    //get the real position (instead of the relative position)
    Point p = absPos();

    //draw rectangle of the menu
    tft.fillRect(p.x, p.y, w, h, colour);
  }

  //Menu::update
  void update()
  {
    ui.x = this->x;
    ui.y = this->y;
    ui.w = this->w;
    ui.h = this->h;

    int16_t vx = tft.vx;
    int16_t vy = tft.vy;
    int16_t vw = tft.vw;
    int16_t vh = tft.vh;
    
    #if defined(NORMAL_DRAWING_ORDER)

      //draw stuff
      draw();

      //set viewport (only draw in a certain range)
      if(hide_after_edge)
      {
        tft.setViewport(x, y, w, h);
      }     

      //let draw function propagate to childs
      ui.update();

      //put back the viewport as it was before
      if(hide_after_edge)
      {
        tft.setViewport(vx, vy, vw, vh);
      }

    #else
      
      //set viewport (only draw in a certain range)
      if(hide_after_edge)
      {
        tft.setViewport(x, y, w, h);
      } 

      //let draw function propagate to childs
      ui.update();
      
      //put back the viewport as it was before
      if(hide_after_edge)
      {
        tft.setViewport(vx, vy, vw, vh);
      }

      //draw stuff
      draw();
    #endif
  }

  //Menu::selectionChanged
  void selectionChanged(uint8_t change)
  {
    selected = change;//select the current element
    ui.selected = change;//set selected of ui to true (forward selection to children)
  }

  //Menu::Menu
  template<typename T1, typename T2>
  Menu(UI* ui1, const char* id, T1 x, T2 y, int16_t w, int16_t h, uint8_t background, uint16_t colour)
  {
    UIBridge::currUI = &ui;
    UIBridge::arr    = &ui.arr;

    container = &ui; // set self pointer to indicate to global UI class that we contain a UI class

    //Variable initializations (note to self, add this to any and all constructors!)
    this->colour = 0;
    this->background = true;

    this->type = "Menu";


    //this is the length of the string
    size_t len = strlen(id);

    //allocate memory for a id that is the same as input (we add one to include the \0 terminator character)
    this->id = new char[len + 1];
    
    //copy the string over to "id" storage
    strcpy(this->id, id);
    
    this->background = background;
    this->colour = colour;

    this->w = w;
    this->h = h;

    this->x = setPos(x, w, ui1->w, 0);
    this->y = setPos(y, h, ui1->h, 1);

    this->ui.x = this->x;
    this->ui.y = this->y;
    this->ui.w = this->w;
    this->ui.h = this->h;

    //also set prev UI of ui to ui1 (important but I missed it)
    this->ui.prevUI = this->ui1;
    this->ui.parent = this;//link up this uielement to the UI manager class so they can work in tandem
  }

  //default constructor for Menu
  Menu(UI* currUI, const char* id) : Menu(currUI, id, "middle", "middle", RELW(200), RELH(200), true, rgb(30, 30, 30)){}

  //Menu::~Menu
  ~Menu()
  {
    //de-allocation of id string
    delete[] this->id;
  }
};

// //global::Canvas
// class Canvas2D : public UIelement
// {
//   public:
//   __attribute__((deprecated("YOU SHOULDN'T TOUCH THIS VARIABLE UNLESS YOU KNOW WHAT YOU ARE DOING!!!")))
//   uint8_t commands = 0;  
// };


#if false
//global::Canvas3D
class Canvas3D : public UIelement
{
  public:
  UI* ui1;
  float   camFov;
  point3d camPos;
  point3d camRot;
  uint8_t background;
  uint16_t backgroundColour;

  //don't touch these variables or your head will blow up
  size_t posIndex;
  size_t triIndex;
  point3d pos[500];
  vertexPos tri[sizeofarray(pos)];//This is the triangle positions, you have to say which position to use in the list of positions (pos array), just put the index of the desired position
  TriPoint renderPos[sizeofarray(tri)];
  uint8_t lastSelected;
  uint8_t showDebug;
  uint32_t* depthBuffer;//will be in the SDRAM, have to initialize inni the setup

  //add handle input to be able to move the camera and rotate it
  void handleKeyboardInput()
  {
      //did a new click happen on the canvas
      if(selected == 1 && lastSelected == 0)
      {
        enabletouch = 0;//disable touch (this makes the cursor disapear)

        lastSelected = selected;//update last selected

      //if the text isn't in focus anymore (shouldn't happen) or if the escape key was pressed
      }else if((selected == 0 && lastSelected == 1) || kbd.checkForKey(KEY_ESCAPE))
      {
        //disable both (simulates pressing out of canvas)
        selected = 0;
        lastSelected = 0;

        enabletouch = 1;//re-enable touch (this makes the cursor appear once again)
      }

      //if we are selected, we should check for the wasd keys to move the camera
      if(selected == 1)
      {

        float moveSpeed = 0.1f;
      
      // Convert angles to radians
      float yaw = camRot.y * PI / 180;
      float pitch = camRot.x * PI / 180;
      
      // Forward vector (affected by yaw and pitch)
      point3d forward = {
          sin(yaw) * cos(pitch),   // X
          -sin(pitch),             // Y (negative because up is positive Y)
          cos(yaw) * cos(pitch)    // Z
      };
      
      // Right vector (perpendicular to forward, only affected by yaw)
      point3d right = {
          cos(yaw),   // X
          0,          // Y (always horizontal)
          -sin(yaw)   // Z
      };
      
      // Up vector (cross product: right × forward)
      point3d up = {
          right.y * forward.z - right.z * forward.y,
          right.z * forward.x - right.x * forward.z,
          right.x * forward.y - right.y * forward.x
      };
      
      // Apply movement
      if (kbd.checkForKey(KEY_W)) {
          camPos.x += forward.x * moveSpeed;
          camPos.y += forward.y * moveSpeed;
          camPos.z += forward.z * moveSpeed;
      }
      if (kbd.checkForKey(KEY_S)) {
          camPos.x -= forward.x * moveSpeed;
          camPos.y -= forward.y * moveSpeed;
          camPos.z -= forward.z * moveSpeed;
      }
      if (kbd.checkForKey(KEY_A)) {
          camPos.x -= right.x * moveSpeed;
          camPos.y -= right.y * moveSpeed;
          camPos.z -= right.z * moveSpeed;
      }
      if (kbd.checkForKey(KEY_D)) {
          camPos.x += right.x * moveSpeed;
          camPos.y += right.y * moveSpeed;
          camPos.z += right.z * moveSpeed;
      }
      if (kbd.checkForKey(KEY_SPACEBAR)) {
          camPos.x += up.x * moveSpeed;
          camPos.y += up.y * moveSpeed;
          camPos.z += up.z * moveSpeed;
      }
      if (kbd.keys.lshift == 1) {
          camPos.x -= up.x * moveSpeed;
          camPos.y -= up.y * moveSpeed;
          camPos.z -= up.z * moveSpeed;
      }

      if(kbd.checkForKey(KEY_LEFTARROW))
      {
        camRot.y -= 3;
      }

      if(kbd.checkForKey(KEY_RIGHTARROW))
      {
        camRot.y += 3;
      }

      if(kbd.checkForKey(KEY_UPARROW))
      {
        camRot.x += 3;
        camRot.x = MIN(MAX(camRot.x, -90), 90);//clamp pitch (no upside down camera lol)
      }

      if(kbd.checkForKey(KEY_DOWNARROW))
      {
        camRot.x -= 3;
        camRot.x = MIN(MAX(camRot.x, -90), 90);//clamp pitch (no upside down camera lol)
      }

      if(kbd.checkForKey(KEY_F2))
      {
        showDebug ^= 0b00000001;//toggle first bit (first bit controls the show fps counter)
      }
      

    }
  }

  //sorts all of the triangles closest to farthest from camera
  void sortTri()
  {
    float dist[sizeofarray(tri)];

    {
      //get average of all points of each triangle
      point3d avg[sizeofarray(tri)];
      for(size_t i = 0; i < sizeofarray(tri); i++)
      {
        avg[i].x = (pos[tri[i].a].x + pos[tri[i].b].x + pos[tri[i].c].x) / 3; 
        avg[i].y = (pos[tri[i].a].y + pos[tri[i].b].y + pos[tri[i].c].y) / 3; 
        avg[i].z = (pos[tri[i].a].z + pos[tri[i].b].z + pos[tri[i].c].z) / 3; 
      }

      //calculate distance from the camera for each of the avg points
      for(size_t i = 0; i < sizeofarray(tri); i++)
      {
        dist[i] = sqrtf(powf(avg[i].x - camPos.x, 2.0) + powf(avg[i].y - camPos.y, 2.0) + powf(avg[i].z - camPos.z, 2.0));
      }
    }

    //convert the bytes to uint16_t (make C++ think its uint16_t)
    uint32_t* avgConverted = (uint32_t*)(dist);

    //convert from float to integer
    for(size_t i = 0; i < sizeofarray(tri); i++)
    {
      avgConverted[i] = floatToSortable(avgConverted[i]);
    }

    //sort them, from lowest to greatest
    radixSort(avgConverted, sizeofarray(tri), tri);
  }
  
  Point getScreenPos(point3d p)
  {
    //calculate the scale idk what it is
    float scale = tan(camFov * 0.5 * PI / 180.0);

    //calculate rotated point based on camera rotation
    point3d r = rotateAroundAxis(p, camPos, camRot);

    // Translate point relative to camera
    float dx = r.x - camPos.x;
    float dy = r.y - camPos.y;
    float dz = r.z - camPos.z;

    //if the point is in front of the camera we can draw it (if not, return some giberish values)
    if(dz > 0)
    {
      // Perspective divide (the magic)
      float px = dx / dz;
      float py = dy / dz;
      
      // Scale to screen with FOV
      int16_t sx =             (px / scale + 0.5) * (MIN(w, h) - 1);
      int16_t sy = MIN(w, h) - (py / scale + 0.5) * (MIN(w, h) - 1);//inverse y bcs thats just how the screen works 

      //return calculated values
      return {sx, sy};
    }else
    {
      //return giberish values because we can't draw the triangle
      return {INT16_MIN, INT16_MIN};
    }
  }

  uint16_t addTriangle(point3d a, point3d b, point3d c, uint16_t colour)
  {
    //bound check and display error to user if something went wrong
    if(posIndex >= sizeofarray(pos) - 3)
    {
      printerror("ran out of space for positions (posIndex reached the end of the array) in Canvas3D element with id \"",(id == nullptr)?("[nullptr id]"):(id),"\"");
      return UINT16_MAX;
    }else if(triIndex >= sizeofarray(pos) - 1)
    {
      printerror("ran out of space for triangles (triIndex reached the end of the array) in Canvas3D element with id \"",(id == nullptr)?("[nullptr id]"):(id),"\"");
      return UINT16_MAX;
    }

    //put the positions specified in the arguments in the list of positions
    pos[posIndex + 0] = a;
    pos[posIndex + 1] = b;
    pos[posIndex + 2] = c;

    //make the triangle
    tri[triIndex].a = (posIndex + 0);
    tri[triIndex].b = (posIndex + 1);
    tri[triIndex].c = (posIndex + 2);

    //include colour
    tri[triIndex].colour = colour;

    //increment posIndex and triIndex (so we don't use the same spaces next time)
    posIndex += 3;
    triIndex += 1;

    return triIndex - 1;
  }

  uint16_t addCuboid(point3d p, point3d dim, point3d rot, uint16_t colour)
  {
    //bound check and display error to user if something went wrong
    if(posIndex >= sizeofarray(pos) - 8)
    {
      printerror("ran out of space for positions (posIndex reached the end of the array) in Canvas3D element with id \"",(id == nullptr)?("[nullptr id]"):(id),"\"");
      return UINT16_MAX;//Return some garbage value
    }else if(triIndex >= sizeofarray(pos) - 12)
    {
      printerror("ran out of space for triangles (triIndex reached the end of the array) in Canvas3D element with id \"",(id == nullptr)?("[nullptr id]"):(id),"\"");
      return UINT16_MAX;//Return some garbage value
    }

    //put the positions specified in the arguments in the list of positions
    pos[posIndex + 0] = {p.x + 0    , p.y + 0    , p.z + 0    };
    pos[posIndex + 1] = {p.x + dim.x, p.y + 0    , p.z + 0    };
    pos[posIndex + 2] = {p.x + 0    , p.y + dim.y, p.z + 0    };
    pos[posIndex + 3] = {p.x + dim.x, p.y + dim.y, p.z + 0    };
    pos[posIndex + 4] = {p.x + 0    , p.y + 0    , p.z + dim.z};
    pos[posIndex + 5] = {p.x + dim.x, p.y + 0    , p.z + dim.z};
    pos[posIndex + 6] = {p.x + 0    , p.y + dim.y, p.z + dim.z};
    pos[posIndex + 7] = {p.x + dim.x, p.y + dim.y, p.z + dim.z};

    //rotate the positions arround the center point of the cuboid
    point3d centerPos = {p.x + 0.5f * dim.x, p.y + 0.5f * dim.y, p.z + 0.5f * dim.z};

    //go through all of the newly created points and rotate them around their center based on rot
    for(int i = 0; i < 8; i++)
    {
      //rotate the pos around the centerPos
      pos[posIndex + i] = rotateAroundAxis(pos[posIndex + i], centerPos, rot);
    }


    /*
    n     x  y  z
    0 -> [0, 0, 0]
    1 -> [1, 0, 0]
    2 -> [0, 1, 0]
    3 -> [1, 1, 0]
    4 -> [0, 0, 1]
    5 -> [1, 0, 1]
    6 -> [0, 1, 1]
    7 -> [1, 1, 1]
    */

    //---------- add the triangles ----------//

    //front face
    tri[triIndex +  0] = {(uint16_t)(posIndex + 2), (uint16_t)(posIndex + 1), (uint16_t)(posIndex + 0), convertNumberToColor( 0)};
    tri[triIndex +  1] = {(uint16_t)(posIndex + 3), (uint16_t)(posIndex + 1), (uint16_t)(posIndex + 2), convertNumberToColor( 1)};
    //back face
    tri[triIndex +  2] = {(uint16_t)(posIndex + 6), (uint16_t)(posIndex + 5), (uint16_t)(posIndex + 4), convertNumberToColor( 2)};
    tri[triIndex +  3] = {(uint16_t)(posIndex + 7), (uint16_t)(posIndex + 5), (uint16_t)(posIndex + 6), convertNumberToColor( 3)};

    //left face
    tri[triIndex +  4] = {(uint16_t)(posIndex + 4), (uint16_t)(posIndex + 2), (uint16_t)(posIndex + 0), convertNumberToColor( 4)};
    tri[triIndex +  5] = {(uint16_t)(posIndex + 6), (uint16_t)(posIndex + 2), (uint16_t)(posIndex + 4), convertNumberToColor( 5)};
    //right face
    tri[triIndex +  6] = {(uint16_t)(posIndex + 1), (uint16_t)(posIndex + 3), (uint16_t)(posIndex + 5), convertNumberToColor( 6)};
    tri[triIndex +  7] = {(uint16_t)(posIndex + 5), (uint16_t)(posIndex + 3), (uint16_t)(posIndex + 7), convertNumberToColor( 7)};
    
    //bottom face
    tri[triIndex +  8] = {(uint16_t)(posIndex + 4), (uint16_t)(posIndex + 1), (uint16_t)(posIndex + 0), convertNumberToColor( 8)};
    tri[triIndex +  9] = {(uint16_t)(posIndex + 5), (uint16_t)(posIndex + 1), (uint16_t)(posIndex + 4), convertNumberToColor( 9)};
    //top face
    tri[triIndex + 10] = {(uint16_t)(posIndex + 2), (uint16_t)(posIndex + 3), (uint16_t)(posIndex + 6), convertNumberToColor(10)};
    tri[triIndex + 11] = {(uint16_t)(posIndex + 6), (uint16_t)(posIndex + 3), (uint16_t)(posIndex + 7), convertNumberToColor(11)};

    //increment posIndex and triIndex (so we don't use the same spaces next time)
    posIndex +=  8;
    triIndex += 12;

    return triIndex - 8;
  }

  void draw()
  {
    sortTri();//sort all of the triangles closest to farthest from camera

    DisplacePointUI d = ui1->getTotalDisplacement();

    int16_t vx = tft.vx;
    int16_t vy = tft.vy;
    int16_t vw = tft.vw;
    int16_t vh = tft.vh;

    RectangleParams r = ui1->getCombinedRectangle();
    r = combineRectangles16(r, {(int16_t)(d.x + x), (int16_t)(d.y + y), w, h});

    tft.setViewport(r.x, r.y, r.w, r.h);

    //go through all of the sorted triangles and display them
    for(size_t i = 0; i < sizeofarray(tri); i++)
    {
      //check if the triangle is a valid triangle
      if(tri[i].a != 0 || tri[i].b != 0 || tri[i].c != 0 || tri[i].colour != 0)
      {
        //if it is we transform it into screen coordinates and draw it
        Point pa = getScreenPos(pos[tri[i].a]);
        Point pb = getScreenPos(pos[tri[i].b]);
        Point pc = getScreenPos(pos[tri[i].c]);

        if(showDebug == 1)
        {
          //draw triangle (not filled) Wire mesh rendering
          tft.drawTriangle(d.x + x + pa.x, d.y + y + pa.y, d.x + x + pb.x, d.y + y + pb.y, d.x + x + pc.x, d.y + y + pc.y, tri[i].colour);
        }else if(showDebug == 0)
        {
          tft.fillTriangle(d.x + x + pa.x, d.y + y + pa.y, d.x + x + pb.x, d.y + y + pb.y, d.x + x + pc.x, d.y + y + pc.y, tri[i].colour);
        }
      }
    }

    tft.setViewport(vx, vy, vw, vh);

    //check if background is enabled (if it is we should be drawing the background)
    if(background == 1)
    {
      //draw background
      tft.fillRect(d.x + x, d.y + y, w, h, backgroundColour);
    }
  }

  void update()
  {
    if(depthBuffer == nullptr)
    {
      #if !WOKWI_SIM
        //set depthBuffer pointer to allocated memory for depth buffer in the SDRAM (*4 because depth buffer contains uint32_t (4 bytes))
        depthBuffer = (uint32_t*)SDRAM.malloc(this->w * this->h * 4);
      #endif
    }

    draw();
  }

  //constructor
  template<typename T1, typename T2>
  Canvas3D(UI* ui1, const char* id, T1 x, T2 y, int16_t w, int16_t h, bool background = 1, uint16_t backgroundColour = 0)
  {
    //Variable intializations (note to self, add this to any and all constructors)
    this->ui1 = nullptr;
    this->camFov = 90;
    this->camPos = {0, 0, 0};
    this->camRot = {0, 0, 0};
    this->background = 1;
    this->backgroundColour = 0;
    this->posIndex = 0;
    this->triIndex = 0;
    this->lastSelected = 0;
    this->showDebug = 0;
    this->depthBuffer = nullptr;


    //this is the length of the string
    size_t len = strlen(id);

    //allocate memory for a id that is the same as input (we add one to include the \0 terminator character)
    this->id = new char[len + 1];
    
    //copy the string over to "id" storage
    strcpy(this->id, id);


    //set a pointer to the ui parent of this object
    this->ui1 = ui1;

    //set width first
    this->w = w;
    this->h = h;

    //set x and y with custom function
    this->x = setPos(x, w, ui1->w, 0);
    this->y = setPos(y, h, ui1->h, 1);

    //set the background
    this->background = background;
    this->backgroundColour = backgroundColour;

    //clear all of the triangles (so they don't actually apear on the screen)
    for(size_t i = 0; i < sizeofarray(tri); i++)
    {
      tri[i].a = 0;
      tri[i].b = 0;
      tri[i].c = 0;
      tri[i].colour = 0;
    }
  }

  //default constructor for Canvas3D
  Canvas3D(UI* currUI, const char* id) : Canvas3D(currUI, id, "middle", "middle", RELW(200), RELH(200), true, rgb(50, 50, 255)){}

  ~Canvas3D()
  {
    //de-allocation of id char array
    delete[] this->id;
  }
};



#else


class Canvas3D : public UIelement
{
  public:

  //constructor
  template<typename T1, typename T2>
  Canvas3D(UI* ui1, const char* id, T1 x, T2 y, int16_t w, int16_t h, bool background = 1, uint16_t backgroundColour = 0){}

  //default constructor
  Canvas3D(UI* currUI, const char* id) : Canvas3D(currUI, id, "middle", "middle", RELW(200), RELH(200), true, rgb(50, 50, 255)){}
};


#endif


//global::Window
class Window : public UIBridge, public UIelement
{

  public:
  UI ui;//add the ui (this is the middle man between the ui and the user. when user asks for ui.addButton, it adds a button and communicates to the outside via this object)
  uint16_t colour;// had a realisation, to change the fuckkk in teh redrawAffectedUIS thing. we need to put the changed condition outside, like have it in a function to make the function optimized when two elements are in each other, get me?-------------------------------------------------------------------------------------------------------------
  bool startSelect;
  Point startPoint;
  void* deathCallbackInput;//this is what is going to get inputed to the deathCallBack function
  void (*deathCallback)(void* input);//this function gets called during the destructo rof the Window element (this is for some use that I needed, don't ask)
  bool highBarSelected = false;

  //Window::updateChildUIVariables
  void updateChildUIVariables()
  {
    ui.x = x;
    ui.y = y + 10;
    ui.w = w;
    ui.h = h - 10;
    ui.basecolor = colour;
  }

  //Window::setx
  void setx(const char* input)
  {
    x = setPos(input, w, ui1->w, 0);
    ui.x = x;
  }

  void setx(int16_t input)
  {
    x = input;
    ui.x = x;
  }

  //Window::sety
  void sety(const char* input)
  {
    y = setPos(input, h, ui1->h, 1);
    ui.y = y + 10;
  }

  void sety(int16_t input)
  {
    y = input;
    ui.y = y + 10;
  }

  //Window::handleInput
  void handleInput(Point p, bool holding, bool focus)
  {
    updateChildUIVariables();

    DisplacePointUI d = ui1->getTotalDisplacement();
    RectangleParams r = ui1->getCombinedRectangle();

    bool windowCollided = ::ui.touchCollide(p, r.x, r.y, r.w, r.h);//this is the previous window bellow. if its outside of the previous window, then we shouldn't be able to click it
    bool movecollided   = ::ui.touchCollide(p, x + d.x, y + d.y, w, 10);//collide(x + d.x, y + d.y, w, 10, p.x - ui1->pointRadius, p.y - ui1->pointRadius, ui1->pointRadius*2, ui1->pointRadius*2);
    bool deleteCollided = ::ui.touchCollide(p, (x + d.x) + w - 15, (y + d.y), 15, 10);

    //if we clicked the window anywhere
    if(focus == 1 && holding == 0 && selected == 1)
    {
      //do some stuff with the z_index so that it goes over all of the other windows in the UI element
    }

    //if we started clicking and we are clicking both the bar and the little x we delete the window
    if(focus == 1 && holding == 0 && deleteCollided == 1 && windowCollided == 1 && selected == 1) 
    {
      ui1->remove(this);//remove self
      return;
    }

    //if we are starting a new click and its on the window (bar at the top)
    if(focus == 1 && holding == 0 && movecollided == 1 && windowCollided == 1 && selected == 1)
    {
      //set start select true (indicating that the little bar is being clicked)
      startSelect = true;
      startPoint = p;
    }else if(focus == 0)
    {
      startSelect = 0;
    }

    //if we are currently clicking the high bar and selecting the element (set highBarSelected to true until the element is deselected or the movecollide not selected while the window is seleceted
    if(selected == 1 && startSelect == 1)
    {
      highBarSelected = true;
    }

    //if the element stopped being selected or if we aren't clicking on teh high bar anymore than we set "highBarSelected" to false
    if((selected == 0 && startSelect == 0) || (focus == 1 && movecollided == 0))
    {
      highBarSelected = false;
    }

    if(startSelect)
    {
      // println("COLLIDED, AND MOVING THE WINDOW");

      //get point difference
      int diffx = startPoint.x - p.x;
      int diffy = startPoint.y - p.y;

      //move the window around
      x -= diffx;
      y -= diffy;
      //also update all of the ui resting upon the window
      ui.x -= diffx;
      ui.y -= diffy;

      //set the reference point to the current point
      startPoint = p;
    }

    ui.handleInput(p, holding, focus);
  }
  
  //Window::handleKeyboardInput
  void handleKeyboardInput()
  {
    //if the window is currently selected
    if(selected == 1)
    {
      //if we are only pressing alt
      if(kbd.keys.lctrl == 1 && kbd.keys.lalt == 0 && kbd.keys.lshift == 0)
      {
        //if we are pressing the R key
        if(kbd.checkForKey(KEY_R))
        {
          //if we just pressed the up arrow
          if(kbd.checkForKey(KEY_UPARROW))
          {
            //update the size of the window
            y -= 5;
            h += 5;
          }
          
          //if we just pressed the down arrow
          if(kbd.checkForKey(KEY_DOWNARROW))
          {
            //update the size of the window
            h += 5;       
          }
          
          //if we just pressed the left arrow
          if(kbd.checkForKey(KEY_LEFTARROW))
          {
            //update the size of the window
            x -= 5;
            w += 5;
          }
          
          //if we just pressed the right arrow
          if(kbd.checkForKey(KEY_RIGHTARROW))
          {
            //update the size of the window
            w += 5;       
          }
        }
      }else if(kbd.keys.lctrl == 1 && kbd.keys.lalt == 0 && kbd.keys.lshift == 1)
      {
        //if we are pressing the R key
        if(kbd.checkForKey(KEY_R))
        {
          //if we just pressed the up arrow
          if(kbd.checkForKey(KEY_UPARROW))
          {
            //update the size of the window
            h -= 5;       
          }
          
          //if we just pressed the down arrow
          if(kbd.checkForKey(KEY_DOWNARROW))
          {
            //update the size of the window
            y += 5;
            h -= 5;
          }
          
          //if we just pressed the left arrow
          if(kbd.checkForKey(KEY_LEFTARROW))
          {
            //update the size of the window
            w -= 5;     
          }
          
          //if we just pressed the right arrow
          if(kbd.checkForKey(KEY_RIGHTARROW))
          {
            //update the size of the window
            x += 5;
            w -= 5;  
          }
        }
      }else if(kbd.keys.lctrl == 0 && kbd.keys.lalt == 0 && kbd.keys.lshift == 0)
      {
        //go full screen
        if(kbd.checkForKey(KEY_F11))
        {
          x = 0;
          y = -10;
          w = tft.screen_width;
          h = tft.screen_height + 10;
        }
      }
    }

    ui.handleKeyboardInput();
  }

  //Window::draw
  void draw()
  {
    updateChildUIVariables();
    DisplacePointUI d = ui1->getTotalDisplacement();
    
    

    // Store viewport
    int16_t vx = tft.vx;
    int16_t vy = tft.vy;
    int16_t vw = tft.vw;
    int16_t vh = tft.vh;

    #if defined(NORMAL_DRAWING_ORDER)
    
      // Draw window background
      tft.fillRect(d.x + ui.x, d.y + ui.y, ui.w, ui.h, colour);

      // NOW get comed rectangle for child UI
      {
        RectangleParams r = ui.getCombinedRectangle();

        tft.setViewport(r.x, r.y, r.w, r.h);
        
        ui.update();
        
        tft.setViewport(vx, vy, vw, vh);
      }
      
      // Draw window decorations
      tft.fillRect((x + d.x), (y + d.y), w, 10, color(100,100,100));
      tft.fillRect((x + d.x) + w - 15, (y + d.y), 15, 10, color(255,0,0));//if you ever change this, change the handle input collision too
      
      tft.drawLine(((x + d.x) + w - 15)+5, ((y + d.y))+2, ((x + d.x) + w)-5, ((y + d.y) + 10)-3, color(0,0,0));
      tft.drawLine(((x + d.x) + w - 15)+5, ((y + d.y) + 10)-3, ((x + d.x) + w)-5, ((y + d.y))+2, color(0,0,0));


    #else

      // Draw window decorations
      tft.drawLine(((x + d.x) + w - 15)+5, ((y + d.y))+2, ((x + d.x) + w)-5, ((y + d.y) + 10)-3, color(0,0,0));
      tft.drawLine(((x + d.x) + w - 15)+5, ((y + d.y) + 10)-3, ((x + d.x) + w)-5, ((y + d.y))+2, color(0,0,0));

      tft.fillRect((x + d.x) + w - 15, (y + d.y), 15, 10, color(255,0,0));//if you ever change this, change the handle input collision too
      tft.fillRect((x + d.x), (y + d.y), w, 10, color(100,100,100));

      // NOW get comed rectangle for child UI
      {
        RectangleParams r = ui.getCombinedRectangle();

        tft.setViewport(r.x, r.y, r.w, r.h);
        
        ui.update();
        
        tft.setViewport(vx, vy, vw, vh);
      }
      
      // Draw window background
      tft.fillRect(d.x + ui.x, d.y + ui.y, ui.w, ui.h, colour);

    #endif
  }

  //Window::update
  void update()
  {
    updateChildUIVariables();
    draw();
  }

  //set select() function (this function is to assure that when the ui element is touched, it should also set its UI class that it is holding to touched)
  void selectionChanged(uint8_t change)
  {
    selected = change;//make element deselected
    ui.selected = change;//also make UI class unselected
  }

  //Window::Window
  template <typename T1, typename T2>
  Window(UI* ui1, const char* id_input, uint16_t colour, T1 xpos, T2 ypos, int16_t width, int16_t height)
  {
    UIBridge::currUI = &ui;
    UIBridge::arr    = &ui.arr;

    container = &ui; // set self pointer to indicate to global UI class that we contain a UI class
    //UIBridge(ui);//set up the UIBridge so we can call functions

    //Variable initializations (add this to any and all constructors that you create in the futur)
    this->colour = 0;
    this->startSelect = false;
    this->deathCallbackInput = nullptr;
    this->deathCallback = nullptr;

    this->type = "Window";//set the type of the UIelement so we can know what it is
    // we replicate all of the values above
    ui.prevUI = ui1;//link up the two UI manager classes together to fix the broken displacement
    ui.parent = this;//link up this uielement to the UI manager class so they can work in tandem
    this->ui1 = ui1;
    
    
    if(id_input != nullptr)
    {
      //this is the length of the string
      size_t len = strlen(id_input);

      //allocate memory for a id that is the same as input (we add one to include the \0 terminator character)
      this->id = new char[len + 1];
      
      //copy the string over to "id" storage
      strcpy(this->id, id_input);  
    }

      
    this->colour = colour;
    this->w = width;
    this->h = height;

    //set the position based on the thing idk
    x = setPos(xpos, w, ui1->w, 0);
    y = setPos(ypos, h, ui1->h, 1);

    updateChildUIVariables();
  }

  //default window constructor
  Window(UI* currUI, const char* id_input) : Window(currUI, id_input, rgb(50, 50, 50), "middle", "middle", RELW(200), RELH(200)){}

  //Window::~Window
  ~Window()
  {
    println(F("Windows destructor for ID : "),id,F(" <- NOTICE ------------------------------------------------------------"));


    //de-allocation of id
    delete[] this->id;


    //play the mistery deathCallback function if it is not a nullptr
    if(deathCallback != nullptr)
    {
      (*deathCallback)(deathCallbackInput);//play the function
    }

    //clear all of the elements in the Array
    ui.clear();
  }
};

template <typename T1, typename T2>
Text& UIBridge::addText(const char *id_input, String text, int fontsize, uint16_t colour, T1 posX, T2 posY)
{
  Text* element = new Text(currUI, id_input, text, fontsize, colour, posX, posY, 0, 0);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
/*inline*/ Text& UIBridge::addText(const char *id_input)
{
  Text* element = new Text(currUI, id_input);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
/*inline*/ Text& UIBridge::getText(const char *id, bool globalScope = false, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
  UIelement* elem;
  if(globalScope)
  {
    elem = currUI->globalFindElementWithId(id, line, file);
  }else
  {
    elem = currUI->findElementWithId(id, line, file);
  }

  //if the ui element couldn't be found, return a static pointer to a UIelement dummy of that type
  if(elem == nullptr)
  {
    //create default static element
    static Text dummy(currUI, "dummy");
    return dummy;
  }

  return *((Text*)(elem));
}

template <typename T1, typename T2, typename T3, typename T4>
Button& UIBridge::addButton(const char* id_input, String text, int fontsize, uint16_t colour, T3 textOffsetX, T4 textOffsetY, bool background, uint16_t backgroundcolor, T1 posX, T2 posY, uint16_t width, uint16_t height, Function<void, Button*, bool> function, bool toggle, int line, const char* file)
{
  Button* element = new Button(currUI, id_input, text, fontsize, colour, textOffsetX, textOffsetY, background, backgroundcolor, posX, posY, width, height, function, toggle);
  element->ui1 = currUI;
  arr->add((UIelement*)element, line, file);
  return *element;
}
Button& UIBridge::addButton(const char* id_input)
{
  Button* element = new Button(currUI, id_input);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
// get the desired ui
/*inline*/ Button& UIBridge::getButton(const char* id, bool globalScope = false, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
  UIelement* elem;
  
  if(globalScope) 
  {
    elem = currUI->globalFindElementWithId(id, line, file);
  }else 
  {
    elem = currUI->findElementWithId(id, line, file);    
  }
  
  if(elem == nullptr)
  {
    static Button dummy(currUI, "dummy");
    return dummy;
  }
  
  
  return *((Button*)(elem));
}

template <typename T1, typename T2>
Window& UIBridge::addWindow(const char* id_input, uint16_t colour, T1 xpos, T2 ypos, uint16_t width, uint16_t height)
{
  Window* element = new Window(currUI, id_input, colour, xpos, ypos, width, height);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
Window& UIBridge::addWindow(const char* id_input)
{
  Window* element = new Window(currUI, id_input);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
/*inline*/ Window& UIBridge::getWindow(const char* id, bool globalScope = false, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
  UIelement* elem;

  if(globalScope) 
  {
    elem = currUI->globalFindElementWithId(id, line, file);
  }else 
  {
    elem = currUI->findElementWithId(id, line, file);    
  }

  if(elem == nullptr)
  {
    static Window dummy(currUI, "dummy");
    return dummy;
  }


  return *((Window*)(elem));
}

template <typename T1, typename T2>
Menu& UIBridge::addMenu(const char* id, T1 x, T2 y, int16_t w, int16_t h, uint8_t background, uint16_t colour)
{
  Menu* element = new Menu(currUI, id, x, y, w, h, background, colour);
  element->ui1 = currUI;
  arr->add((UIelement*)(element));
  return *element;
}
Menu& UIBridge::addMenu(const char* id)
{
  Menu* element = new Menu(currUI, id);
  element->ui1 = currUI;
  arr->add((UIelement*)(element));
  return *element;
}
/*inline*/ Menu& UIBridge::getMenu(const char* id, bool globalScope = false, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
  UIelement* elem;

  if(globalScope) 
  {
    elem = currUI->globalFindElementWithId(id, line, file);
  }else 
  {
    elem = currUI->findElementWithId(id, line, file);    
  }

  if(elem == nullptr)
  {
    static Menu dummy(currUI, "dummy");
    return dummy;
  }


  return *((Menu*)(elem));
}

template<typename T1, typename T2>
Canvas3D& UIBridge::addCanvas3D(const char* id, T1 x, T2 y, int16_t w, int16_t h, bool background, uint16_t backgroundColour)
{
  Canvas3D* element = new Canvas3D(currUI, id, x, y, w, h, background, backgroundColour);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
Canvas3D& UIBridge::addCanvas3D(const char* id)
{
  Canvas3D* element = new Canvas3D(currUI, id);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
/*inline*/ Canvas3D& UIBridge::getCanvas3D(const char* id, bool globalScope = false, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
  UIelement* elem;

  if(globalScope) 
  {
    elem = currUI->globalFindElementWithId(id, line, file);
  }else 
  {
    elem = currUI->findElementWithId(id, line, file);    
  }

  if(elem == nullptr)
  {
    static Canvas3D dummy(currUI, "dummy");
    return dummy;
  }


  return *((Canvas3D*)(elem));
}

//global::Terminal
class Terminal : public UIelement
{
  public:
  Window& window = ::ui.addWindow("Terminal_Window", color(50, 50, 50), 0, 0, 50, 50);//hostage window
  Text& text = window.addText("Terminal_Text", "", 1, color(0, 255, 0), 0, 0);//hostage text
  uint8_t terminalSelect = 0;//helper variable to see if teh window just got selected
  uint8_t pressedEnter = 0;//helper variable to not repeat Enter when held
  uint8_t windowDied = 0;//helper variable to check if the window died, and if it did, we should delete the whole Terminal object as well
  uint8_t terminalDying = 0;
  uint8_t barCollision = 0;//stop code from registering  
  uint8_t cmdAvailable = 0;
  int textScrollingSpeed = 10;//speed / size of the steps each time you scroll
  char* cmdBuffer = nullptr;//make a cmd buffer (which is going to the sdram)
  void* deathCallbackInput = nullptr;//this is what is going to get inputed to the deathCallBack function
  void (*deathCallback)(void*) = nullptr;//this function gets called during the destructo rof the Window element (this is for some use that I needed, don't ask)  

  //if the window ever dies then its going to call this function (make it static so complier don't go KABOOM)
  static void deathCallbackTerminal(void* input)
  {
    if(input != nullptr)
    {
      Terminal* terminal = (Terminal*)(input);

      terminal->windowDied = 1;

      if(!terminal->terminalDying)
      {
        terminal->ui1->remove(terminal);   
      }   
    }else
    {
      println(F("ERROR line "),__LINE__,F(", the input was a nullptr"));
    }
  }

  //Terminal::write
  void write(char c)
  {
    text.fixedText += c;
  }
  
  //Terminal::available
  uint8_t available()
  {
    return cmdAvailable;
  }

  //Terminal::read
  char* read()
  {
    cmdAvailable--;//decrease cmdAvailable
    return cmdBuffer;
  }

  //Terminal::handleInput
  void handleInput(Point p, bool holding, bool focus)
  {
    //if we started a new click
    if(holding == 0 && focus == 1)
    {
      barCollision = window.highBarSelected;
    }
  }

  //Terminal::handleKeyboardInput
  void handleKeyboardInput()
  {
    //check if cmdBuffer has not been initialized
    if(cmdBuffer == nullptr)
    {
      #if WOKWI_SIM
        cmdBuffer = new char[100];
      #else
        cmdBuffer = (char*)SDRAM.malloc(256);//get some space but in sdram instead because its BIG
        cmdBuffer[0] = '\0';//set it to empty string just to be sure
      #endif
    }

    //is the child window gone
    if(windowDied)
    {
      ui1->remove(this);//self destruct if child window is gone
    }

    //when we click the window (select it) it should also select the text
    if((window.selected == 1 || window.selected == 2) && terminalSelect == 0 && !barCollision)
    {
      terminalSelect = 1;//update terminalSelect
      text.selected = 1;
    }

    //when we deselect the text, it should also deselect the window
    if(text.selected == 0 && !barCollision)
    {
      terminalSelect = 0;//update terminalSelect
      window.selected = 0;
    }

    //if the text is being selected
    if(text.selected == 1)
    {  
      //did we press enter
      if(kbd.keys.lctrl == 0 && kbd.keys.lalt == 0 && kbd.keys.lshift == 0 && kbd.currKey == KEY_ENTER && pressedEnter == 0)
      {
        //get rid of the '\n' that pressing enter creates
        //simulate a backspace (to get rid of the '\n' character) very cursed, prob going to regret it later, but it works
        //we don't need to do anything if the string is already length 0
        if(kbd.cursorIndex != 0)
        {
            //remove the character just behind the cursorIndex
            kbd.buffer = kbd.buffer.substring(0, kbd.cursorIndex - 1) + kbd.buffer.substring(kbd.cursorIndex);

            kbd.cursorIndex -= 1;
        }

        //find the last '\n' char
        int index = kbd.buffer.length() - 2;
        while(index > 0 && kbd.buffer[index] != '\n')
        {
          index -= 1;
        }

        String textCommand = "";
        if((kbd.buffer.length()) - index <= 0)
        {
          println(F("ERROR line "),__LINE__,F(", zero or bellow zero length command"));
        }else
        {
          //get the command based on the last '\n' character index
          textCommand = kbd.buffer.substring(index, kbd.buffer.length()); //get the specific command typed in the chat
        }

        //throw whatever we just wrote into the fixed size (so we can't backspace it away)
        text.fixedText += kbd.buffer + '\n';

        strcpy(cmdBuffer, textCommand.c_str());//copy the command to a permanent command buffer so that the kernel can use the command and respond to the terminal
        cmdAvailable += 1;//make the command available

        //clear both buffers and text Just to be sure
        text.text = "";
        kbd.buffer = "";
        
        pressedEnter = 1;//update pressedEnter to prevent spam

        kbd.enableBuffer = false;//disable the buffer until we unpress enter .. just to be sure

      //if its literally any other key other then enter
      }else if(!kbd.checkForKey(KEY_ENTER) && pressedEnter == 1)
      {
        //then we can put back pressedEnter
        pressedEnter = 0;

        //and also re-enable the buffer since we disabled it last command
        kbd.enableBuffer = true;
      }else if(kbd.keys.lctrl == 0 && kbd.keys.lalt == 1 && kbd.keys.lshift == 0)
      {
        #define TERMINAL_MAX_SCROLL_SPEED 67
         

        //if we just pressed the up arrow
        if(kbd.checkForKey(KEY_UPARROW))
        {
          text.y -= textScrollingSpeed;
        }
        
        //if we just pressed the down arrow
        if(kbd.checkForKey(KEY_DOWNARROW))
        {
          text.y += textScrollingSpeed;
        }
        
        //if we just pressed the left arrow
        if(kbd.checkForKey(KEY_LEFTARROW))
        {
          text.x -= textScrollingSpeed;
        }
        
        //if we just pressed the right arrow
        if(kbd.checkForKey(KEY_RIGHTARROW))
        {
          text.x += textScrollingSpeed;          
        }

        //if we just pressed teh - key
        if(kbd.checkForKey(KEY_MINUS_UNDERSCORE))
        {
          //bound check (we don't want negative scrolling speed lol)
          if(textScrollingSpeed >= 0)
          {
            textScrollingSpeed -= 1;
          }
        }

        //if we just presseed the + (technically = key, but who fucking cares, close enough)
        if(kbd.checkForKey(KEY_EQUAL_PLUS))
        {
          //bound check (we don't want to go supersonic scrolling speeds)
          if(textScrollingSpeed <= TERMINAL_MAX_SCROLL_SPEED)
          {
            textScrollingSpeed += 1;
          }
        }

      }
        
    }

  }

  //Terminal::update
  void update()
  {
    //check if cmdBuffer has not been initialized
    if(cmdBuffer == nullptr)
    {
      #if WOKWI_SIM
        cmdBuffer = new char[100];
      #else
        cmdBuffer = (char*)SDRAM.malloc(256);//get some space but in sdram instead because its BIG
      #endif
    }

    //is the child window gone?
    if(windowDied)
    {
      ui1->remove(this);//self destruct if child window is gone
    }
  }

  //Terminal::Terminal
  template <typename T1, typename T2>
  Terminal(UI* ui1, const char* id_input, T1 window_x, T2 window_y, int16_t window_w, int16_t window_h, uint16_t backgroundColor, uint16_t textColor)
  {
    this->type = "Terminal";//set the type so that we can know what it is

    //link up the ui that manages this element to this 
    this->ui1 = ui1;

    if(id_input != nullptr)
    {

      //this is the length of the string
      size_t len = strlen(id_input);

      //allocate memory for a id that is the same as input (we add one to include the \0 terminator character)
      this->id = new char[len + 1];
      
      //copy the string over to "id" storage
      strcpy(this->id, id_input);
    
    }

    //update window to match
    window.colour = backgroundColor;
    window.w = window_w;
    window.h = window_h;
    window.setx(window_x);
    window.sety(window_y);

    //make sure that the index is in the right order so the terminal's update function always gets called first
    window.z_index = -100;
    text.z_index = -99;
    this->z_index = -98;

    //update text to match
    text.colour = textColor;
    text.editable = 1; //make the text editable
    text.settings &= ~0b1; //toggle OFF the settings that erases selection lines (so we don't see ugly rectangle arround the text box inside the termianl)
    text.updateTextSize = 0;// toggle OFF update text size to stop the text from ever updating the width and height so we can modify it ourselfs

    //change text dimentions to negative so that it doesn't overlap with anything (it'll mess with our logic otherwise)
    text.w = -1;
    text.h = -1; 

    //make sure position isn't a problem (because this is kind of like an invisible ui element)
    x = -100;
    y = -100;
    w = 0;
    h = 0;

    //add a death callback function to auto delete the Terminal class if the window was ever to be deleted
    window.deathCallback = Terminal::deathCallbackTerminal;
    window.deathCallbackInput = (void*)this;
  }

  //default constructor for Terminal
  Terminal(UI* currUI, const char* id_input) : Terminal(currUI, id_input, "middle", "middle", RELW(200), RELH(200), rgb(0, 0, 0), rgb(0, 255, 0)){}

  ~Terminal()
  {
    terminalDying = true;

    //delete window if it didn't die
    if(!windowDied)
    {
      //remove window
      ui1->remove(&window);
    }
    
    //play the mistery deathCallback function if it is not a nullptr
    if(deathCallback != nullptr)
    {
      (*deathCallback)(deathCallbackInput);//play the function
    }

    #if WOKWI_SIM
      delete[] cmdBuffer;
    #else
      SDRAM.free((void*)(cmdBuffer));//free the cmd buffer or else we boutta get some memory leaks
    #endif

    println(F("Terminal destructor for ID : "),id,F(" <- NOTICE ------------------------------------------------------------"));

    //de-allocation of id char array
    delete[] this->id;
  }
};

template <typename T1, typename T2>
Terminal& UIBridge::addTerminal(const char* id_input, T1 window_x, T2 window_y, int16_t window_w, int16_t window_h, uint16_t backgroundColor, uint16_t textColor)
{
  Terminal* element = new Terminal(currUI, id_input, window_x, window_y, window_w, window_h, backgroundColor, textColor);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
Terminal& UIBridge::addTerminal(const char* id_input)
{
  Terminal* element = new Terminal(currUI, id_input);
  element->ui1 = currUI;
  arr->add((UIelement*)element);
  return *element;
}
/*inline*/ Terminal& UIBridge::getTerminal(const char* id, bool globalScope = false, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
  UIelement* elem;

  if(globalScope) 
  {
    elem = currUI->globalFindElementWithId(id, line, file);
  }else 
  {
    elem = currUI->findElementWithId(id, line, file);    
  }

  if(elem == nullptr)
  {
    static Terminal dummy(currUI, "dummy");
    return dummy;
  }


  return *((Terminal*)(elem));
}


/*inline*/ void nullfunc(bool nothing){}

/*

// void drawScreen()
// {
  //   tft.fillScreen(ui.basecolor);
  //   tft.setCursor(10, 10);
  //   tft.setTextColor(0x0000);
  //   tft.setTextSize(2);
  //   tft.println("OS BOOTING...");
  
  //   tft.fillRect(10, 245, 50, 20, color(128, 120, 128));
  //   tft.setCursor(17, 251);
  //   tft.setTextColor(0x0000);
  //   tft.setTextSize(1);
  //   tft.println("Button");
  
  //   tft.fillRect(10, 305, 220, 5, color(128, 120, 128)); // uhm this is like...a slider
// }


// void buttonPressed(bool input)
// {
  //   println("THE BUTTON WAS PRESSED : ",input);
  // }
  
  
  // void setup()
  // {
    //   ui.begin();
    //   //ui.addText("Terminal", "terminal", 1, color(255,255,255), "left", "top");
    
    //   ui.arr.add(&window);
    
    //   ui.update();
    
    //   //DELAY(1000);
    
    //   window.x += 10;
    //   window.y += 10;
    //   window.w -= 50;
    //   window.h -= 50;
    
    //   //DELAY(100000);
    
    //   //DELAY(10000);
    // }
    
    
    // bool holding = false;
    // bool holdingSlider = false; // 0 : nothing or not holding slider, 1 : holding slider
    // bool holdingButton = false;
    // bool buttonState = false;
    // bool lastButtonState = false;
    // unsigned long lastTouch = 0;
    // int sliderValue = 0; // this is the slider value out of a hundread
    // int lastSliderValue = -1;
    // bool focus = false;
    void loop()
{
  // tft.fillScreen(ui.basecolor);
  ui.update();
  
  //DELAY(100);
  if(touched())
  {
    Point p = getPoint();
    
    focus = true;
    
    // check if we are holding
    #if WOKWI_SIM
    if (millis() - lastTouch <= 75)
    #else
    if (millis() - lastTouch <= 75)
    #endif
    {
      holding = true;
    }
    else
    {
      holdingSlider = 0; // we reset the holding slider to nothing
      
      holdingButton = 0;
      buttonState = 0;

      holding = false;
    }
    
    //println("handling input");
    ui.handleInput(p, holding, focus);
    
    // println("is holding ? : ",holding);
    
    // println("Touch detected at: X=",p.x," Y=",p.y);
    
    if (!(p.x == 240 && p.y == 320))
    {
      // Map coordinates as needed (capacitive often requires less mapping than resistive)
      
      tft.drawPixel(p.x, p.y, color(0, 0, 255));
      
      // Add UI interaction logic here
      if ((collide(10, 305, 220, 5, p.x - 4, p.y - 4, 8, 8) && (holding == 0 && holdingSlider == 0)) || (holdingSlider == 1))
      {
        // if its the first time we are clicking on the screen (like after letting go)
        if (holding == false)
        {
          println("holding slider = 1");
          holdingSlider = 1;
        }
        
        // get what the slider value would have to be
        
        //  - distance : (p.x - 10)
        //  - percentage : (p.x - 10) / 220 * 100
        
        sliderValue = (p.x - 10) * 100 / 220;
        
        // limit slider value
        sliderValue = min(max(sliderValue, 0), 100);
      }
      
      if (lastSliderValue != sliderValue)
      {
        // get rid of last slider point
        tft.fillCircle(10 + lastSliderValue * 220 / 100, 305 + 5 / 2, 7, ui.basecolor);
        tft.fillRect(10, 305, 220, 5, color(128, 120, 128));
        
        // set little dot on the slider
        tft.fillCircle(10 + sliderValue * 220 / 100, 305 + 5 / 2, 7, color(100, 94, 100));
        
        // get rid of last text
        tft.setTextSize(2);
        tft.setCursor(10, 305 - 30);
        tft.setTextColor(ui.basecolor);
        tft.print(lastSliderValue);
        tft.print("%");
        
        // set new text
        tft.setCursor(10, 305 - 30);
        tft.setTextColor(color(50, 50, 50));
        tft.print(sliderValue);
        tft.print("%");
      }
      
      // UI interaction logic for the button
      if (collide(10, 245, 50, 20, p.x - 4, p.y - 4, 8, 8))
      {
        // if its the first time we are clicking on the screen (like after letting go)
        if (holding == false)
        {
          holdingButton = 1;
        }
        
        if (holdingButton == true)
        {
          buttonState = true;
        }
      }
      else if (holding == 1)
      {
        buttonState = false;
      }
      
      if (lastButtonState != buttonState)
      {
        if (buttonState == 1)
        {
          tft.fillRect(10, 245, 50, 20, color(160, 145, 170));
          tft.setTextColor(color(100, 100, 100));
        }
        else
        {
          tft.fillRect(10, 245, 50, 20, color(128, 120, 128));
          tft.setTextColor(0x0000);
        }
        
        tft.setCursor(17, 251);
        tft.setTextSize(1);
        tft.println("Button");
      }
      
      lastTouch = millis();
      lastSliderValue = sliderValue;
      lastButtonState = buttonState;
    }
  }
  
  if(millis() - lastTouch > 75 && focus == 1)
  {
    //println("handling input");
    ui.handleInput({0,0}, false, 0);
    // disable all of the button thingy idk
    holding = 0;
    buttonState = 0;
    holdingButton = 0;
    focus = 0;//undo the focus
    
    // we display the button state (its the same as the one in the touched thingy)
    if (lastButtonState != buttonState)
    {
      if (buttonState == 1)
      {
        tft.fillRect(10, 245, 50, 20, color(160, 145, 170));
        tft.setTextColor(color(100, 100, 100));
      }
      else
      {
        tft.fillRect(10, 245, 50, 20, color(128, 120, 128));
        tft.setTextColor(0x0000);
      }
      
      tft.setCursor(17, 251);
      tft.setTextSize(1);
      tft.println("Button");
    }
    
    lastButtonState = 0; // don't forget to set the lastButtonState variable
  }
}

// void loop()
// {
  //   #if true
  
  //     ui.update();
  //     // window.x += 1;
  //     // window.y += 1;
  
  
  //     //DELAY(10);
  
  //     // Text& terminal = ui.getText("Terminal");
  
  //     // terminal.text = number;
  
  //     // ui.update();
  
  //     // DELAY(1000);
  
  //     // number++;
  //   #else
  //     kbd.update();
  
  //     Text& terminal = ui.getText("Terminal");
  
  //     if(kbd.available())
  //     {
    //       terminal.text = kbd.getBuffer();
    //     }
    
    //     ui.update();
    //   #endif
    // }
*/
    
#endif

