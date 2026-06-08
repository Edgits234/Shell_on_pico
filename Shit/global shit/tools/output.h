//original file

#include <Arduino.h>
#ifndef AwesomeUI_h
#define AwesomeUI_h
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
//this is useless ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef I_KNOW_WHAT_IM_DOING
#define DONT_TOUCH_THIS __attribute__((deprecated("IMPORTANT!!, YOU SHOULDN'T TOUCH THIS VARIABLE UNLESS YOU KNOW EXACTLY WHAT YOU ARE DOING!")))
#endif
//#define MIN_PRESSURE 3

// #include <Adafruit_GFX.h>
// #include <Adafruit_ILI9341.h>
// #include <TFT_eSPI.h>
// #define DISABLE_WARNINGS
#include "CustomGraphics.h"
// #include <SD.h>

// struct Point
// {
//   int16_t x;
//   int16_t y;
// };

struct RectangleParams
{
int16_t x;
int16_t y;
int16_t w;
int16_t h;
};
struct point3d
{
float x;
float y;
float z;
point3d operator+(const point3d& other) const;
point3d operator-(const point3d& other) const;
point3d operator-() const;
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
extern Adafruit_FT6206 ctp ;
// Initialize capacitive touch object
  extern SPISettings spiSettings(80000000, MSBFIRST, SPI_MODE0);
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

int strcmp(const char* str1, const char* str2, unsigned int len1, unsigned int len2 = SIZE_MAX);
/**
 * @brief this function sorts the inputed array of uint32_t from lowest to highest
 * @param arr this is the array that you want to modify / sort
 * @param size this is the size of the array you want to modify / sort
 */
void radixSort(uint32_t* arr, size_t size);
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

#warning template class, please put "$hdr ... $end" around it
template<typename T>
class Arraya
{
public:
T* array;
unsigned int size;
void add(T input);
void remove();
void remove(unsigned int index);
T at(unsigned int index);
Arraya();
// Arraya(const Arraya&) = delete;
  // Arraya& operator=(const Arraya&) = delete;

  ~Arraya();
};
/**
 * @param p : point
 * @param c : center
 * @param r : rotation (in degrees I think)
 * @brief rotates a point around the desired center based on the rotation (applies the rotation in the following order, Y -> X -> Z)
 * @retval outputs the rotated point
 */
/*inline*/ point3d rotateAroundAxis(point3d p, point3d c, point3d r);
/*inline*/ double strMath(const char* str, int len = -1, void* extraData = nullptr, double (*handleWord)(void* extradata, const char* word, int len) = nullptr);
/**
 * @brief this function is a helper function that sets the x and y positions automatically when putting words like "middle", "top", "right", while letting normal numbers pass
 * @param pos : this is the position of the object you want to move
 * @param len : this is the length of the object you want to move
 * @param totalLen : this is the total length (usually the container of the object)
 * @param vertical : this tells the function if we are treating this as x or y (0 -> x, 1 -> y), its purpose is to stop stuff like (x, y) -> ("top", "right") which is reversed
 */
/*inline*/ int setPos(int pos, uint16_t len, int totalLen, bool vertical);
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
double handleSetPosWords(void* extraData, const char* str, int len);
/*inline*/ int setPos(const char* str, uint16_t len, int totalLen, bool vertical);
/*inline*/ extern int16_t globalx ;
/*inline*/ extern int16_t globaly ;
/*inline*/ extern bool cursorClicky ;
/*inline*/ bool touched();
/*inline*/ Point getPoint();
/*inline*/ extern int16_t gvx ;
/*inline*/ extern int16_t gvy ;
/*inline*/ extern int16_t gvw ;
/*inline*/ extern int16_t gvh ;
/*inline*/ void setTestViewport(int16_t x, int16_t y, int16_t w, int16_t h);
/*inline*/ void cancelTestViewport();
// input two rectangles and get if they touch or not
/*inline*/ bool collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
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
/*inline*/ RectangleParams combineRectangles16(RectangleParams r1, RectangleParams r2);
//we might not need this function anymroe ------------------------------------------------------------------------------------------------------------------------------------------------------------------
// RectangleParams combine2Rectangles16(RectangleParams r1, RectangleParams r2)
// {
//   RectangleParams r3 = combineRectangles16({r1.x, r1.y, r1.w, r1.h}, {r2.x, r2.y, r2.w, r2.h});
//   // RectangleParams r4 = combineRectangles16({r1.lx, r1.ly, r1.lw, r1.lh}, {r2.lx, r2.ly, r2.lw, r2.lh});

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
UI* ui1;
// the parent ui
  const char* type;
// constant character pointer (string) that describes the type of the ui element
  const char* id;
// the id, same idea as pointers, but instead use a const char pointer (string) provided by the user
  int16_t x;
int16_t y;
int16_t w;
int16_t h;
int8_t z_index;
uint8_t selected;
// is this element selected?
  uint8_t selectable;
// is the element selectable (in other words, can its selected variable be changed?)
  void* extradata;
// extra data, mostly for user customized ui elements (using userUpdate, userHandleInput or userHandleKeyboardInput, etc...)
  void (*userUpdate)(UIelement* self);
//this function gets called before the UIelement's update (so you can draw your own custom stuff on top)
  void (*userHandleInput)(UIelement* self, Point p, bool holding, bool lostfocus);
//this function is to get the touch inputs (technically is now "cursor input")
  void (*userHandleKeyboardInput)(UIelement* self);
//this is to get the keybaord input (use the kbd object to get stuff about the keyboard)

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
virtual void update();
virtual void handleInput(Point p, bool holding, bool lostfocus);
virtual void handleKeyboardInput();
virtual Point absPos();
virtual void tick();
virtual void draw();
virtual void selectionChanged(uint8_t change);
//defaults to change
  UIelement();
virtual ~UIelement();
};
// forward definition of the Text, button, Terminal, and Canvas3D class
class Text;
class Button;
class Menu;
class Window;
class Canvas3D;
class Terminal;
// In AwesomeUI.h, add this BEFORE the UI class definition (around line 300):

/*inline*/ extern UI* g_pathBuffer[10];
//global::UI 
//class to manage the UI array, (updating ui, input handling for ui, acts as the middle man between the ui elements and the inputs of the user)
/*inline*/ extern uint8_t enabletouch ;
class UI 
{
public:
Array<UIelement*> uiPointerArray;
// we are simply creating an array of pointers to UIelement object with a custom class (this class does some very basic memory managements for you and is kind of like vector exept all of the features are missing exept "push_back" which is now "add" and "remove" just removes at last index or the specified index)
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
#if WOKWI_SIM
int pointRadius;
#else
int pointRadius;
#endif
//UI::printarray
  void printarray();
//is that too many variables? meh probably not thats like uhhhhhhhhhh 128 bytes.. dayum 128 bytes, ok thats maybe a bit much... we have 8 MB right...
  int16_t x;
int16_t y;
int16_t w;
int16_t h;
//UI::exits
  //check if the element exists based on its pointer
  bool exists(UIelement* element);
//check if an element exists based on its id
  bool exists(const char* id);
//UIManager::touchCollide
  bool touchCollide(Point p, int16_t x, int16_t y, int16_t w, int16_t h);
//UI::findElementWithId
  UIelement* findElementWithId(const char* id);
//UI::getTotalDisplacement
  DisplacePointUI getTotalDisplacement();
//UI::getCombinedRectangle
  RectangleParams getCombinedRectangle();
template <typename T1, typename T2>
  Text& addText(const char* id_input, String text, int fontsize, uint16_t color, T1 posX, T2 posY);
//UI::addText 
  Text& getText(const char* id);
//UI::getText

  /**
   * @brief adds a button
   * @param id_input the id of the ui element (cannot be changed once set)
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
  Button& addButton(const char* id_input, String text, int fontsize, uint16_t colour, T3 textOffsetX, T4 textOffsetY, bool background, uint16_t backgroundcolor, T1 posX, T2 posY, uint16_t width, uint16_t height, void (*function1)(bool input), bool toggle);
//UI::addButton
  Button& getButton(const char* id);
//UI::getButton

  template <typename T1, typename T2>
  Menu& addMenu(const char* id, T1 x, T2 y, int16_t w, int16_t h, uint8_t background, uint16_t colour);
//UI::addMenu
  Menu& getMenu(const char* id);
//UI::getMenu

  template <typename T1, typename T2>
  Window& addWindow(const char* id_input, uint16_t colour, T1 xpos, T2 ypos, uint16_t width, uint16_t height);
//UI::addWindow
  Window& getWindow(const char* id);
//UI::getWindow

  template <typename T1, typename T2>
  Terminal& addTerminal(const char* id_input, T1 window_x, T2 window_y, int16_t window_w, int16_t window_h, uint16_t backgroundColor, uint16_t textColor);
//UI::addTerminal
  Terminal& getTerminal(const char* id);
//UI::getTerminal

  template<typename T1, typename T2>
  Canvas3D& addCanvas3D(const char* id, T1 x, T2 y, int16_t w, int16_t h, bool background = 1, uint16_t backgroundColour = 0);
//UI::addCanvas3D
  Canvas3D& getCanvas3D(const char* id);
//UI::getCanvas3D

  //UI::remove
  void remove(const char* id);
//UI::remove
  void remove(UIelement* ptr);
//UI::select
  /**
   @param p the point where a touch even happent
   @brief this function gets the UIelement that is touching the point provided in the current UI object
   @retval returns the pointer to that UIelement
  */
  UIelement* select(Point p);
//UI::handleInput
  void handleInput(Point p, bool holding, bool focus);
//UI::handleKeyboardInput
  void handleKeyboardInput();
//UI::addUIpointer
  void addUIpointer(UIelement *pointer);
//UI::removeUIpointer 
  //this removes from the array only
  void removeUIpointer(UIelement *pointer);
//UI::tick
  void tick();
//UI::clear
  void clear();
//UI::touchUpdateAddition
  virtual void touchUpdateAddition();
//UI::update
  // FIX 4: Add bounds checking to update() loop
  void update();
UI();
};
//get absolute position (position acounting all of the parent positions)
Point UIelement::absPos();
//global::UIManager
class UIManager : public UI
{
public:
void (*touchInput)(Point p, bool holding, bool lostfocus);
int number;
//what the fuck is that ??? ----------------------------------------------------------------------
  uint8_t initialized;
// bool selected = false;

  //UIManager::begin
  void begin();
//UIManager::touchUpdateAddition
  //add the touch updating to the UIManager UI only because we don't want to update the whole touch thingy when we simply want to update UIs
  void touchUpdateAddition();
UIManager();
};
/*inline*/ extern UIManager ui;
//global::Text
class Text : public UIelement
{
public:
bool mode;
//this variable is absolutely useless, as well as modew, modeh, and mode in the input of the text constructor
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
    Size info = getTextBounds(text, fontsize);
    x = setPos(input, info.w, ui1->w, 0);
  }
template<typename T>
  void sety(T input)
  {
    Size info = getTextBounds(text, fontsize);
    // x = setPos(input, w1, ui1->w, 0);
    y = setPos(input, info.h, ui1->h, 1);
  }
//Text::handleKeyboardInput
  void handleKeyboardInput();
//Text::draw
  void draw();
//Text::update
  void update();
//Text::print
  void print();
template<typename T> void print(T input){::print(input); fixedText += input;}
//Text::println
  void println();
template<typename T> void println(T input){::println(input); fixedText += input; fixedText += '\n';}
//Text::Text
  template <typename T1, typename T2>
  Text(UI* ui1, bool mode, const char* id_input, String text, int fontsize, uint16_t colour, T1 xpos, T2 ypos, uint16_t modew, uint16_t modeh)
  {
    //Variable Initializations (note to self : always add this to any and all constructor unless you want to change the default values of the variables)
    this->mode = false;
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

    id = id_input;//set the pointer of the id to the pointer of the id_input because its a const char pointer most likely

    this->mode = mode;
    this->text = text;
    this->fontsize = fontsize;
    this->colour = colour;
    
    Size info = getTextBounds(text, fontsize);//(text, 0, 0, &x1, &y1, &w1, &h1);

    x = setPos(xpos, info.w, ui1->w, 0);
    y = setPos(ypos, info.h, ui1->h, 1);

    // ui1->addUIpointer(this); // add to the ui manager list
  }
//Text::~Text
  ~Text();
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
void (*function)(bool buttonState);
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
  void handleInput(Point p, bool holding, bool focus);
//Button::draw
  void draw();
//Button::update
  void update();
//Button::Button
  template <typename T1, typename T2, typename T3, typename T4>
  Button(UI* ui1, const char* id_input, String text, int fontsize, uint16_t colour, T3 textOffsetX, T4 textOffsetY, bool background, uint16_t backgroundcolor, T1 posX, T2 posY, uint16_t width, uint16_t height, void (*function1)(bool buttonState), bool toggle)
  {
    //Variable initializations (note to self add this to any and all constructors)
    this->text = "";
    this->fontsize = 1;
    this->colour = 0x0000;
    this->backgroundcolor = 0;
    this->background = false;
    this->lastButtonState = false;
    this->buttonState = false;
    this->toggleable = false;


    this->type = "Button";//set the type so that we can know what it is
    this->ui1 = ui1;
    // we replicate all of the values above
    toggleable = toggle;
    
    id = id_input;

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

    function = function1;
    this->background = background;
    this->backgroundcolor = backgroundcolor;
    this->w = width;
    this->h = height;

    x = setPos(posX, w, ui1->w, 0);
    y = setPos(posY, h, ui1->h, 1);
  }
//Button::~Button
  ~Button();
};
//global::Menu
class Menu : public UIelement
{
//make everything public
  public:
UI ui;
//UI class, contains ui elements
  uint16_t colour;
//colour of the background of the Menu
  uint8_t background;
//Menu::setx
  template<typename T>
  void setx(T input)
  {
    x = setPos(input, w, ui1->w, 0);
  }
//Menu::sety
  template<typename T>
  void sety(T input)
  {
    y = setPos(input, h, ui1->h, 1);
  }
//Menu::handleInput
  void handleInput(Point p, bool holding, bool focus);
//Menu::handleKeyboardInput
  void handleKeyboardInput();
//Menu::draw
  void draw();
//Menu::update
  void update();
//Menu::selectionChanged
  void selectionChanged(uint8_t change);
//Menu::Menu
  template<typename T1, typename T2>
  Menu(UI* ui1, const char* id, T1 x, T2 y, int16_t w, int16_t h, uint8_t background, uint16_t colour)
  {
    //Variable initializations (note to self, add this to any and all constructors!)
    this->colour = 0;
    this->background = true;

    this->type = "Menu";
    this->id = id;

    this->ui1 = ui1;
    this->background = background;
    this->colour = colour;

    this->w = w;
    this->h = h;

    this->x = setPos(x, w, ui1->w, 0);
    this->y = setPos(y, h, ui1->h, 1);
  }
//Menu::~Menu
  ~Menu();
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
vertexPos tri[sizeofarray(pos)];
//This is the triangle positions, you have to say which position to use in the list of positions (pos array), just put the index of the desired position
  TriPoint renderPos[sizeofarray(tri)];
uint8_t lastSelected;
uint8_t showDebug;
uint32_t* depthBuffer;
//will be in the SDRAM, have to initialize inni the setup

  //add handle input to be able to move the camera and rotate it
  void handleKeyboardInput();
//sorts all of the triangles closest to farthest from camera
  void sortTri();
Point getScreenPos(point3d p);
uint16_t addTriangle(point3d a, point3d b, point3d c, uint16_t colour);
uint16_t addCuboid(point3d p, point3d dim, point3d rot, uint16_t colour);
void draw();
void update();
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

    //set the id
    this->id = id;//this technically just copies the id pointer (but this should be fine because its constants, trust me on this one)

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
~Canvas3D();
};
#endif
//global::Window
class Window : public UIelement
{
public:
UI* ui1;
UI ui;
//add the ui (this is the middle man between the ui and the user. when user asks for ui.addButton, it adds a button and communicates to the outside via this object)
  uint16_t colour;
// had a realisation, to change the fuckkk in teh redrawAffectedUIS thing. we need to put the changed condition outside, like have it in a function to make the function optimized when two elements are in each other, get me?-------------------------------------------------------------------------------------------------------------
  bool startSelect;
Point startPoint;
void* deathCallbackInput;
//this is what is going to get inputed to the deathCallBack function
  void (*deathCallback)(void* input);
//this function gets called during the destructo rof the Window element (this is for some use that I needed, don't ask)

  //Window::updateChildUIVariables
  void updateChildUIVariables();
//Window::setx
  void setx(const char* input);
void setx(int16_t input);
//Window::sety
  void sety(const char* input);
void sety(int16_t input);
//Window::handleInput
  void handleInput(Point p, bool holding, bool focus);
//Window::handleKeyboardInput
  void handleKeyboardInput();
//Window::draw
  void draw();
void update();
//set select() function (this function is to assure that when the ui element is touched, it should also set its UI class that it is holding to touched)
  void selectionChanged(uint8_t change);
//Window::Window
  template <typename T1, typename T2>
  Window(UI* ui1, const char* id_input, uint16_t colour, T1 xpos, T2 ypos, uint16_t width, uint16_t height)
  {
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
    
    // if(id_input != nullptr)
    // {
    //   id = new char[strlen(id_input) + 1]; // tell c++ to give us some storage and give the pointer to that storage
    //   strcpy(id, id_input);                // copy the id_input string to the location in storage
    // }
    id = id_input;

    this->colour = colour;
    this->w = width;
    this->h = height;

    //set the position based on the thing idk
    x = setPos(xpos, w, ui1->w, 0);
    y = setPos(ypos, h, ui1->h, 1);

    updateChildUIVariables();
  }
//Window::~Window
  ~Window();
};
template <typename T1, typename T2>
Text& UI::addText(const char *id_input, String text, int fontsize, uint16_t colour, T1 posX, T2 posY)
{
  Text* element = new Text(this, false, id_input, text, fontsize, colour, posX, posY, 0, 0);
  uiPointerArray.add((UIelement*)element);
  return *element;
}
// get the desired ui
/*inline*/ Text& UI::getText(const char *id);
template <typename T1, typename T2, typename T3, typename T4>
Button& UI::addButton(const char* id_input, String text, int fontsize, uint16_t colour, T3 textOffsetX, T4 textOffsetY, bool background, uint16_t backgroundcolor, T1 posX, T2 posY, uint16_t width, uint16_t height, void (*function1)(bool input), bool toggle)
{
  Button* element = new Button(this, id_input, text, fontsize, colour, textOffsetX, textOffsetY, background, backgroundcolor, posX, posY, width, height, function1, toggle);
  uiPointerArray.add((UIelement*)element);
  return *element;
}
// get the desired ui
/*inline*/ Button& UI::getButton(const char* id);
template <typename T1, typename T2>
Window& UI::addWindow(const char* id_input, uint16_t colour, T1 xpos, T2 ypos, uint16_t width, uint16_t height)
{
  Window* element = new Window(this, id_input, colour, xpos, ypos, width, height);
  uiPointerArray.add((UIelement*)element);
  return *element;
}
/*inline*/ Window& UI::getWindow(const char* id);
template <typename T1, typename T2>
Menu& UI::addMenu(const char* id, T1 x, T2 y, int16_t w, int16_t h, uint8_t background, uint16_t colour)
{
  Menu* element = new Menu(this, id, x, y, w, h, background, colour);
  uiPointerArray.add((UIelement*)(element));
  return *element;
}
/*inline*/ Menu& UI::getMenu(const char* id);
template<typename T1, typename T2>
Canvas3D& UI::addCanvas3D(const char* id, T1 x, T2 y, int16_t w, int16_t h, bool background, uint16_t backgroundColour)
{
  Canvas3D* element = new Canvas3D(this, id, x, y, w, h, background, backgroundColour);
  uiPointerArray.add((UIelement*)element);
  return *element;
}
/*inline*/ Canvas3D& UI::getCanvas3D(const char* id);
//global::Terminal
class Terminal : public UIelement
{
public:
Window& window = ::ui.addWindow("Terminal_Window", color(50, 50, 50), 0, 0, 50, 50);
//hostage window
  Text& text = window.ui.addText("Terminal_Text", "", 1, color(0, 255, 0), 0, 0);
//hostage text
  uint8_t terminalSelect = 0;
//helper variable to see if teh window just got selected
  uint8_t pressedEnter = 0;
//helper variable to not repeat Enter when held
  uint8_t windowDied = 0;
//helper variable to check if the window died, and if it did, we should delete the whole Terminal object as well
  uint8_t barCollision = 0;
//stop code from registering  
  uint8_t cmdAvailable = 0;
int textScrollingSpeed = 10;
//speed / size of the steps each time you scroll
  char* cmdBuffer = nullptr;
//make a cmd buffer (which is going to the sdram)
  void* deathCallbackInput = nullptr;
//this is what is going to get inputed to the deathCallBack function
  void (*deathCallback)(void*) = nullptr;
//this function gets called during the destructo rof the Window element (this is for some use that I needed, don't ask)
  

  //if the window ever dies then its going to call this function (make it static so complier don't go KABOOM)
  static void deathCallbackTerminal(void* input);
//Terminal::handleInput
  void handleInput(Point p, bool holding, bool focus);
//Terminal::handleKeyboardInput
  void handleKeyboardInput();
//Terminal::update
  void update();
//Terminal::Terminal
  template <typename T1, typename T2>
  Terminal(UI* ui1, const char* id_input, T1 window_x, T2 window_y, int16_t window_w, int16_t window_h, uint16_t backgroundColor, uint16_t textColor)
  {
    this->type = "Terminal";//set the type so that we can know what it is

    //link up the ui that manages this element to this 
    ui = ui1;

    //set the id
    // id = new char[strlen(id_input) + 1]; // tell c++ to give us some storage and give the pointer to that storage
    // strcpy(id, id_input);                // copy the id_input string to the location in storage
    id = id_input;

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
~Terminal();
};
template <typename T1, typename T2>
Terminal& UI::addTerminal(const char* id_input, T1 window_x, T2 window_y, int16_t window_w, int16_t window_h, uint16_t backgroundColor, uint16_t textColor)
{
  Terminal* element = new Terminal(this, id_input, window_x, window_y, window_w, window_h, backgroundColor, textColor);
  uiPointerArray.add((UIelement*)element);
  return *element;
}
/*inline*/ Terminal& UI::getTerminal(const char* id);
/*inline*/ void nullfunc(bool nothing);
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
    
    //   ui.uiPointerArray.add(&window);
    
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
