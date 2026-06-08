#ifndef AwesomeUI_h
#ifndef UI_SETTINGS
#endif
//this is useless ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef I_KNOW_WHAT_IM_DOING
#endif
point3d point3d::operator+(const point3d& other) const
  {
    return {x + other.x, y + other.y, z + other.z};
  }
point3d point3d::operator-(const point3d& other) const
  {
    return {x - other.x, y - other.y, z - other.z};
  }
point3d point3d::operator-() const
  {
    return {-x, -y, -z};
  }
// struct Color
// {
//   byte red;
//   byte green;
//   byte blue;
// };

#if WOKWI_SIM
Adafruit_FT6206 ctp = Adafruit_FT6206();
// Initialize capacitive touch object
  SPISettings spiSettings(80000000, MSBFIRST, SPI_MODE0);
#else
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

int strcmp(const char* str1, const char* str2, unsigned int len1, unsigned int len2 )
{
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
    println("ERROR in file ",__FILE__," in function ",__func__,"() at line ",__LINE__,", was not able to allocate memory for buckets array (you are probably running out of space)");
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
void Arraya::add(T input)
  {
    // we allocate the size for the new array
    T* newArray = new T[size + 1];

    if(newArray == nullptr)
    {
      println("WELL WE'VE JUST FOUND THE ERROR, THIS STUPID ASS ARRAY TRIED GETTING MEMORY BUT IT FAILED AND NOW WE BOUT TO BUST THE WHOLE FUCKING THING");
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
void Arraya::remove()
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
void Arraya::remove(unsigned int index)
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
T Arraya::at(unsigned int index)
  {
    // if the index is in bound
    if (0 <= index && index <= size - 1)
    {
      return array[index];
    }
    else
    {
      println("ERROR, invalid index (the index you gave doesn't point to an element in the array)");
      while(1);// bug finding
      return 0;
    }
  }
Arraya::Arraya()
  {
    //variable initializations (note to self, add this in front of any and all cosntructors)
    this->array = nullptr;
    this->size = 0;
  }
// Arraya(const Arraya&) = delete;
  // Arraya& operator=(const Arraya&) = delete;

  Arraya::~Arraya()
  {
    delete[] array; // remove array from the memory
  }
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
/*inline*/ double strMath(const char* str, int len , void* extraData , double (*handleWord)(void* extradata, const char* word, int len) )
{
  //figure out the length if it wasn't provided in the input (if len was equal to -1)
  if(len == -1)
  {
    len = 0;
    while(str[len] != '\0')
    {
      len++;
    }

    println("length is ",len);
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

  print("str math -> '");
  for(int i = 0; i < len; i++)
  {
    print(str[i]);
  }
  println("'");

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
    for(int i = 0; i < len; i++)
    {
      print(str[i]);
    }
    println(" -> ",0);
    return 0;
  }else if(strcmp(str,"middle",len) == 0 || strcmp(str,"centered",len) == 0 || strcmp(str,"center",len) == 0)
  {
    for(int i = 0; i < len; i++)
    {
      print(str[i]);
    }
    println(" -> ",input.totalLen / 2 - input.len / 2);
    return input.totalLen / 2 - input.len / 2;
  }else if((strcmp(str,"right",len) == 0 && input.vertical == 0) || ((strcmp(str,"bottom",len) == 0 || strcmp(str,"down",len) == 0 || strcmp(str,"lower",len) == 0) && input.vertical == 1))
  {
    for(int i = 0; i < len; i++)
    {
      print(str[i]);
    }
    println(" -> ",input.totalLen - input.len);
    return input.totalLen - input.len;
  }

  println("ERROR, '",str,"' is not correct keyword (tip: your make sure your 'top'/'bottom' and 'right'/'left' are not inverted)");
  return 0;
}
/*inline*/ int setPos(const char* str, uint16_t len, int totalLen, bool vertical)
{
  HandleSetPosWordsStruct extraData = {len, totalLen, vertical};
  int mathOutput = (int)(strMath(str, -1, (void*)(&extraData), handleSetPosWords));

  println("result : ",mathOutput);
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

    //if the keys got changed, we check if we pressed spacebar
    // if(kbd.available())
    // {

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
        
        if(kbd.checkForKey(KEY_SPACEBAR))
        {
          cursorClicky = true;
          return true;
        }else
        {
          cursorClicky = false;    
        }
      }
    // }

    return false;

  #endif
}
/*inline*/ Point getPoint()
{
  #if WOKWI_SIM
    TS_Point p = ctp.getPoint(); // Get the touch point

    // fix the points, bcs they reverse for some reason
    p.x = SCREEN_WIDTH  - p.x;
    p.y = SCREEN_HEIGHT - p.y;

    return {p.x, p.y};
  #else

    return {globalx, globaly};
  #endif
}
/*inline*/ int16_t gvx = 0;
/*inline*/ int16_t gvy = 0;
/*inline*/ int16_t gvw = SCREEN_WIDTH;
/*inline*/ int16_t gvh = SCREEN_HEIGHT;
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
virtual void UIelement::update(){}
virtual void UIelement::handleInput(Point p, bool holding, bool lostfocus){}
virtual void UIelement::handleKeyboardInput(){}
virtual void UIelement::tick(){}
virtual void UIelement::draw(){}
virtual void UIelement::selectionChanged(uint8_t change){selected = change;}
//defaults to change
  UIelement::UIelement()
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
    this->extradata = nullptr;
    this->settings = 0b00000001;
  }
virtual UIelement::~UIelement(){}
// In AwesomeUI.h, add this BEFORE the UI class definition (around line 300):

/*inline*/ UI* g_pathBuffer[10];
//global::UI 
//class to manage the UI array, (updating ui, input handling for ui, acts as the middle man between the ui elements and the inputs of the user)
/*inline*/ uint8_t enabletouch = 1;
#if WOKWI_SIM
#else
#endif
//UI::printarray
  void UI::printarray()
  {
    println(" this function should not be playing (line ",__LINE__,")");
    // test print println("printing array");
    // test print println("the size is : ",uiPointerArray.size);

    // test print
    //println("(size : ",uiPointerArray.size,")");
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      println("[",i,"] = ",uiPointerArray.at(i)->id);
    }
  }
//UI::exits
  //check if the element exists based on its pointer
  bool UI::exists(UIelement* element)
  {
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      if(element == uiPointerArray.at(i))
      {
        return true;
      }
    }

    return false;
  }
//check if an element exists based on its id
  bool UI::exists(const char* id)
  {
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      UIelement* elem = uiPointerArray.at(i);
      
      //we check if elem is a nullptr JUST IN CASE
      if(elem == nullptr)
      {
        println("ERROR line ",__LINE__,", detected a nullptr element");
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
  }
//UIManager::touchCollide
  bool UI::touchCollide(Point p, int16_t x, int16_t y, int16_t w, int16_t h)
  {
    return collide(x, y, w, h, p.x - pointRadius, p.y - pointRadius, pointRadius*2, pointRadius*2);
  }
//UI::findElementWithId
  UIelement* UI::findElementWithId(const char* id)
  {
    // println("this function should not be called (line ",__LINE__,")");
    // println("in file '",__FILE__,"', in function '",__func__,", at line '",__LINE__,"'");
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      if(strcmp(uiPointerArray.at(i)->id, id) == 0)
      {
        return uiPointerArray.at(i);
      }
    }

    println("ERROR, COULD NOT FIND THE UI ELEMENT WITH ID:'",id,"' in the following list of UIs : ");
    println("Array size (",uiPointerArray.size,")");
    printarray();
    println("");
    return nullptr;
  }
//UI::getTotalDisplacement
  DisplacePointUI UI::getTotalDisplacement()
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
        println("ERROR, went down too many indexs (you might have too many elements in elements);");
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
  RectangleParams UI::getCombinedRectangle()
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
//UI::getCanvas3D

  //UI::remove
  void UI::remove(const char* id)
  {
    println("SHOULD NOT BE REMOVING ANY UI ELEMENT WHAT THE FUCK");
    // we go through all of the ui elements
    for (unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      // if the ui element has the specific id we are looking for
      if (strcmp(uiPointerArray.at(i)->id, id) == 0)
      {
        delete uiPointerArray.at(i);
        uiPointerArray.remove(i); // don't forget to remove it from the array too
        
        return;
      }
    }
    
    // if we didn't find a corresponding id
    println("ERROR, couldn't find '", id, "' in the list of ui elements");
  }
//UI::remove
  void UI::remove(UIelement* ptr)
  {
    // we go through all of the ui elements
    for (unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      //if the ui element has the specific pointer we are looking for
      if(uiPointerArray.at(i) == ptr)
      {
        delete uiPointerArray.at(i);
        uiPointerArray.remove(i); // don't forget to remove it from the array too
        return;//return early no need to continue checking
      }
    }
    
    // // if we didn't find a corresponding id
    println("ERROR line ",__LINE__," in ",__FILE__," couldn't find the pointer in the list of ui elements");
  }
//UI::select
  /**
   @param p the point where a touch even happent
   @brief this function gets the UIelement that is touching the point provided in the current UI object
   @retval returns the pointer to that UIelement
  */
  UIelement* UI::select(Point p)
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
      
      for(int i = uiPointerArray.size - 1; i >= 0 ; i--)
      {
        UIelement* elem = uiPointerArray.at(i);

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
              if(collided)
              {
                //the current element becomes the best element
                bm = elem;
              }
            }else
            {

              //if the pixel is not inside of the window
              bool collided = touchCollide(p, d.x + elem->x, d.y + elem->y, elem->w, elem->h);

              //if the z_index of the current element is bigger than the best element
              if(collided && (bm->z_index < elem->z_index))
              {
                //if it is, the current element becomes the best element
                bm = elem;
              }
            }
          }
        }else
        {
          println("ERROR line ",__LINE__,", detected a nullptr in the uiPointerArray at index ",i);
        }
      }
    }

    //return best match
    return bm;
  }
//UI::handleInput
  void UI::handleInput(Point p, bool holding, bool focus)
  {
    
    //has a new touch started and this UI is selected 
    if(holding == 0 && focus == 1)
    {
      println("started a new touch");

      //if the selected element isn't nullptr (if there was a prior selected element)
      if(selectedElement != nullptr)
      {
        println("making an element DESELECTED");

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
          //if the parent is selectable
          if(parent->selectable == 1)
          {
            //set the parent to selected 2 (meaning it holds an element that is selected)
            parent->selectionChanged(2);
          }
        }

        //set this current UI object to selected 2 because it holds an element that is selected
        selected = 2;

        println("making an element selected");

        //make the new selected element selected  (if it is selectable of course)
        if(selectedElement->selectable == 1)
        {
          //use the select() function (gives more control to the element, on what to do for selection)
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

    //go through all of the uiPointerArray and handleInput for them
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      if(uiPointerArray.at(i) == nullptr)
      {
        println("UH OH, NOT GOOD, WE HAVE A NULLPTR!!!---------------------------------------------notice");
      }else
      {
        void (*userFunc)(UIelement* self, Point p, bool holding, bool focus) = uiPointerArray.at(i)->userHandleInput;

        //if the user function is not a nullptr (exists, then play it)
        if(userFunc != nullptr)
        {
          (*userFunc)(uiPointerArray.at(i), p, holding, focus);//play the custom user function (before actuall handle input)
        }

        uiPointerArray.at(i)->handleInput(p, holding, focus);// play update functioon for all YOU NEED TO ADD THE Z_INDEX THINGY DON'T FORGET ABOUT IT PLEASE--------------------------------------
      }
    }
  }
//UI::handleKeyboardInput
  void UI::handleKeyboardInput()
  {

    // println("WHAT THE FUCK, IT IS NOT SUPPOSED TO DO THIS FUNCTION ---------------------------------------notice");
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      if(uiPointerArray.at(i) == nullptr)
      {
        println("UH OH, NOT GOOD, WE HAVE A NULLPTR!!!---------------------------------------------notice");
      }else
      {
        void (*userFunc)(UIelement* self) = uiPointerArray.at(i)->userHandleKeyboardInput;

        //if the user function is not a nullptr (exists, then play it)
        if(userFunc != nullptr)
        {
          (*userFunc)(uiPointerArray.at(i));//play the custom user function (before actuall handle input)
        }

        uiPointerArray.at(i)->handleKeyboardInput();// play update functioon for all YOU NEED TO ADD THE Z_INDEX THINGY DON'T FORGET ABOUT IT PLEASE--------------------------------------
      }
    }
  }
//UI::addUIpointer
  void UI::addUIpointer(UIelement *pointer)
  {
    uiPointerArray.add(pointer); // add the pointer at the end of the array
  }
//UI::removeUIpointer 
  //this removes from the array only
  void UI::removeUIpointer(UIelement *pointer)
  {
    println("this function should not playing right now (line 991)");
    // we go through all of the UIelement pointers in the array
    for(unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      // we find the corresponding pointer (the same pointer as in the function input)
      if(uiPointerArray.at(i) == pointer)
      {
        uiPointerArray.remove(i); // we remove the pointer from the list
      }
    }
  }
//UI::tick
  void UI::tick()
  {
    println("this function should not be called (line : 1009)");
    // maybe change the order idk
    for (unsigned int i = 0; i < uiPointerArray.size; i++)
    {
      uiPointerArray.at(i)->tick();
    }
  }
//UI::clear
  void UI::clear()
  {
    unsigned int staticSize = uiPointerArray.size;

    // we go through all of the ui elements
    for (unsigned int i = 0; i < staticSize; i++)
    {
      
      if(uiPointerArray.at(0) == nullptr)
      {
        println("ERROR line ",__LINE__," in ",__FILE__,", nullptr detected in the uiPointerArray");
        while(true);
      }else
      {
        
        // then we delete
        delete uiPointerArray.at(0);
        uiPointerArray.remove(0); // don't forget to remove from the array too
      }
    }
  }
//UI::touchUpdateAddition
  virtual void UI::touchUpdateAddition(){}
//UI::update
  // FIX 4: Add bounds checking to update() loop
  void UI::update()
  {

    //testprintln("touchUpdateAddition");
    
    touchUpdateAddition();

    //after the keyboard (bcs emulation is weird and stops the whole code so we don't want to stop code after we drew a window)
    #if defined(INVERT_DRAWING_ORDER)

      println("drawing the background");

      //first bit fo UI_SETTINGS is supposed to be "are we not clearing the screen?"
      if(isManager && !(UI_SETTINGS & 1))
      {
        tft.fillScreen(basecolor);
      }

    #endif

    //show cursor on GIGA (because we are using the keyboard)
    #if !WOKWI_SIM
      if(isManager && enabletouch)
      {
        // println("drawing the cursor");

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

    //go through all of the possible z_indexs (switch between min->max and max->min depending on drawing order)
    #if defined(INVERT_DRAWING_ORDER)
    for(int j = INT8_MIN; j < INT8_MAX; j++)
    #else
    for(int j = INT8_MAX - 1; j >= INT8_MIN; j--)
    #endif
    {
      //go through all ofthe list of UIelements
      for (int i = (int)uiPointerArray.size - 1; i >= 0 ; i--)
      {
        UIelement* ptr = uiPointerArray.at(i);//get ui element

        //if its a nullptr, print error
        if(ptr == nullptr)
        {
          println("ERROR, nullptr detected in uiPtrArray (go to line ",__LINE__," to see where this print statement was put)");
          continue;
        }

        //if its not then update it and draw bound box if its selected
        if(ptr->z_index == j)
        {
          // println("drawing element ",ptr->id);

          //invert the user update and the element update (the user update must always be able to overwrite the element update)
          #if defined(INVERT_DRAWING_ORDER)

            ptr->update();

            //if the user update function exists 
            if(ptr->userUpdate != nullptr)
            {
              (*ptr->userUpdate)(ptr);//play the custom user function
            }

          #else

            //if the user update function exists 
            if(ptr->userUpdate != nullptr)
            {
              (*ptr->userUpdate)(ptr);//play the custom user function
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

    #if !defined(INVERT_DRAWING_ORDER)

      //first bit fo UI_SETTINGS is supposed to be "are we not clearing the screen?"
      if(isManager && !(UI_SETTINGS & 1))
      {
        tft.fillScreen(basecolor);
      }

    #endif


    // test print println("displaying the frame buffer");
    if(isManager && !(UI_SETTINGS & 0b100))
    {
      // test print println("step one (!kbd.Available => ",kbd.Available,")");
      //UI_SETTINGS == 1                   -> true
      //UI_SETTINGS == 0 && !kbd.Available -> true  
      if((UI_SETTINGS & 0b10) || !kbd.Available)
      {
        // test print println("step two");
        //wokwi_sim's graphical commands print straight to the screen, we can therefor skip the displayFrameBuffer part... and fuck I just remembered I changed everything to be drawn in inverse order, damn thats annoying
        #if !WOKWI_SIM
          displayFrameBuffer();//display on the actuall screen
          resetDrawnPixel();//reset the drawn pixel so that we can actually darw afterwards
        #endif
        // test print println("you should be seeing stuff now");
      }
    }
  }
UI::UI()
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
// bool selected = false;

  //UIManager::begin
  void UIManager::begin()
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
      
        //always do once every repetition but if kbd.Available is bigger than 0 repeat until it is 0
        do
        {
          //update keyboard (let the keyboard fetch the keys that are being pressed)
          kbd.update();

          //if any keys are being pressed break out of everything
          if(!kbd.keysClear()) goto endLoop;

        } while (kbd.Available > 0);

      #endif
      
      //wait a little bit because why not
      delay(1000);
    }

    #if !defined(EMULATE_KEYBOARD)
    endLoop:
    #endif

    Serial.println("Starting...");    

    //initialize customGraphics library
    tft.begin();
    
    //fill with base color or smth
    tft.fillScreen(basecolor);
    #if !WOKWI_SIM
      resetDrawnPixel();//reset the drawn pixel so that we can draw afterwards (bcs, drawing is front to back)
    #endif

    selected = 1;

    #if WOKWI_SIM
      if (!ctp.begin(40))
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
//UIManager::touchUpdateAddition
  //add the touch updating to the UIManager UI only because we don't want to update the whole touch thingy when we simply want to update UIs
  void UIManager::touchUpdateAddition()
  {

    //update the keyboard (fetch the keys that have been pressed or unpressed)
    kbd.update();

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
          if (millis() - lastTouch <= 75)
          #else
          if (millis() - lastTouch <= 200)
          #endif
          {
            holding = true;
          }
          else
          {
            holding = false;
          }

          handleInput(p, holding, focus);

          if(touchInput != nullptr)
          {
            (*touchInput)(p, holding, focus);
          }

          lastTouch = millis();
        }
      }

      if(millis() - lastTouch > 75 && focus == 1)
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

    handleKeyboardInput();
  }
UIManager::UIManager()
  {
    //variable initializations
    this->number = 0;
    this->initialized = 0;

    isManager = true;//set is manager to true because... its the manager

    // x = 0;
    // y = 0;
    // w = SCREEN_WIDTH;
    // h = SCREEN_HEIGHT;
  }
/*inline*/ UIManager ui;
//Text::handleKeyboardInput
  void Text::handleKeyboardInput()
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
  void Text::draw()
  {
    DisplacePointUI d = ui1->getTotalDisplacement();
    // tft.drawText(fixedText + text, (x + d.x), (y + d.y), fontsize, colour);
    //combine both the fixed text and the text (for cursor and selector reasons
    // String combined = fixedText + text;
    tft.setCursor((x + d.x), (y + d.y), fontsize, colour, (x + d.x));

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
  void Text::update()
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
  void Text::print(){}
//Text::println
  void Text::println(){fixedText += '\n';}
//Text::~Text
  Text::~Text()
  {
    // delete[] id;//remove the id that was alocated in memory for this ui element
    ::println("Text destructor for ID : ",id," <- NOTICE ------------------------------------------------------------");
  }
//Button::handleinput
  void Button::handleInput(Point p, bool holding, bool focus)
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
  void Button::draw()
  {
    DisplacePointUI d = ui1->getTotalDisplacement();

    #if defined(INVERT_DRAWING_ORDER)
    
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
  void Button::update()
  {
    //if the state of the button changed
    if(buttonState != lastButtonState)
    {
      if(function != nullptr)
      {
        (*function)(buttonState);//play the custom function
      }
    }

    draw();

    lastButtonState = buttonState;
  }
//Button::~Button
  Button::~Button()
  {
    // delete[] id;//de alocatio
    //n of the id (cuz we alocated that right)
    println("Button destructor for ID : ",id," <- NOTICE ------------------------------------------------------------");
  }
//Menu::handleInput
  void Menu::handleInput(Point p, bool holding, bool focus)
  {
    //let handleInput propagate to childrens
    ui.handleInput(p, holding, focus);
  }
//Menu::handleKeyboardInput
  void Menu::handleKeyboardInput()
  {
    //let hanldeKeyboardInput propagate to childrens
    ui.handleKeyboardInput();
  }
//Menu::draw
  void Menu::draw()
  {
    //get the real position (instead of the relative position)
    Point p = absPos();

    //draw rectangle of the menu
    tft.fillRect(p.x, p.y, w, h, colour);
  }
//Menu::update
  void Menu::update()
  {
    #if defined(INVERT_DRAWING_ORDER)
      //draw stuff
      draw();

      //let draw function propagate to childs
      ui.update();
    #else
      //let draw function propagate to childs
      ui.update();
      
      //draw stuff
      draw();
    #endif
  }
//Menu::selectionChanged
  void Menu::selectionChanged(uint8_t change)
  {
    selected = change;//select the current element
    ui.selected = change;//set selected of ui to true (forward selection to children)
  }
//Menu::~Menu
  Menu::~Menu()
  {
    //nothing yet
  }
// //global::Canvas
// class Canvas2D : public UIelement
// {
//   public:
//   __attribute__((deprecated("YOU SHOULDN'T TOUCH THIS VARIABLE UNLESS YOU KNOW WHAT YOU ARE DOING!!!")))
//   uint8_t commands = 0;  
// };


#if false
//will be in the SDRAM, have to initialize inni the setup

  //add handle input to be able to move the camera and rotate it
  void Canvas3D::handleKeyboardInput()
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
  void Canvas3D::sortTri()
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
Point Canvas3D::getScreenPos(point3d p)
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
uint16_t Canvas3D::addTriangle(point3d a, point3d b, point3d c, uint16_t colour)
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
uint16_t Canvas3D::addCuboid(point3d p, point3d dim, point3d rot, uint16_t colour)
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
void Canvas3D::draw()
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
void Canvas3D::update()
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
Canvas3D::~Canvas3D(){}
#endif
//this function gets called during the destructo rof the Window element (this is for some use that I needed, don't ask)

  //Window::updateChildUIVariables
  void Window::updateChildUIVariables()
  {
    ui.x = x;
    ui.y = y + 10;
    ui.w = w;
    ui.h = h - 10;
    ui.basecolor = colour;
  }
//Window::setx
  void Window::setx(const char* input)
  {
    x = setPos(input, w, ui1->w, 0);
    ui.x = x;
  }
void Window::setx(int16_t input)
  {
    x = input;
    ui.x = x;
  }
//Window::sety
  void Window::sety(const char* input)
  {
    y = setPos(input, h, ui1->h, 1);
    ui.y = y + 10;
  }
void Window::sety(int16_t input)
  {
    y = input;
    ui.y = y + 10;
  }
//Window::handleInput
  void Window::handleInput(Point p, bool holding, bool focus)
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

    if(focus == 1 && holding == 0 && deleteCollided == 1 && windowCollided == 1 && selected == 1) 
    {
      ui1->remove(this);//remove self
      return;
    }

    //if we are starting a new click and its on the window
    if(focus == 1 && holding == 0 && movecollided == 1 && windowCollided == 1 && selected == 1)
    {
      startSelect = true;
      startPoint = p;
    }else if(focus == 0)
    {
      startSelect = 0;
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
  void Window::handleKeyboardInput()
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
          w = SCREEN_WIDTH;
          h = SCREEN_HEIGHT + 10;
        }
      }
    }

    ui.handleKeyboardInput();
  }
//Window::draw
  void Window::draw()
  {
    updateChildUIVariables();
    DisplacePointUI d = ui1->getTotalDisplacement();
    
    

    // Store viewport
    int16_t vx = tft.vx;
    int16_t vy = tft.vy;
    int16_t vw = tft.vw;
    int16_t vh = tft.vh;

    #if defined(INVERT_DRAWING_ORDER)
    
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
void Window::update()
  {
    updateChildUIVariables();
    draw();
  }
//set select() function (this function is to assure that when the ui element is touched, it should also set its UI class that it is holding to touched)
  void Window::selectionChanged(uint8_t change)
  {
    selected = change;//make element deselected
    ui.selected = change;//also make UI class unselected
  }
//Window::~Window
  Window::~Window()
  {
    println("Windows destructor for ID : ",id," <- NOTICE ------------------------------------------------------------");

    //play the mistery deathCallback function if it is not a nullptr
    if(deathCallback != nullptr)
    {
      (*deathCallback)(deathCallbackInput);//play the function
    }

    //clear all of the elements in the Array
    ui.clear();
  }
// get the desired ui
/*inline*/ Text& UI::getText(const char *id)
{
  // we go through all of the ui elements
  return *((Text*)(findElementWithId(id)));

  // if we didn't find a corresponding id
  println("ERROR, couldn't find '", id, "' in the list of ui elements");
}
// get the desired ui
/*inline*/ Button& UI::getButton(const char* id)
{
  return *((Button*)findElementWithId(id));

  // if we didn't find a corresponding id
  println("ERROR, couldn't find '", id, "' in the list of ui elements");
}
/*inline*/ Window& UI::getWindow(const char* id)
{
  return *((Window*)findElementWithId(id));

  // if we didn't find a corresponding id
  println("ERROR, couldn't find '", id, "' in the list of ui elements");
}
/*inline*/ Menu& UI::getMenu(const char* id)
{
  return *((Menu*)findElementWithId(id));
}
/*inline*/ Canvas3D& UI::getCanvas3D(const char* id)
{
  return *((Canvas3D*)findElementWithId(id));

  // if we didn't find a corresponding id
  println("ERROR, couldn't find '", id, "' in the list of ui elements");
}
//this function gets called during the destructo rof the Window element (this is for some use that I needed, don't ask)
  

  //if the window ever dies then its going to call this function (make it static so complier don't go KABOOM)
  static void Terminal::deathCallbackTerminal(void* input)
  {
    if(input != nullptr)
    {
      Terminal* terminal = (Terminal*)(input);

      terminal->windowDied = 1;

      terminal->ui1->remove(terminal);      
    }else
    {
      println("ERROR line ",__LINE__,", the input was a nullptr");
    }
  }
//Terminal::handleInput
  void Terminal::handleInput(Point p, bool holding, bool focus)
  {
    //if we started a new click
    if(holding == 0 && focus == 1)
    {
      DisplacePointUI d = ::ui.getTotalDisplacement();

      //did the touch touch the top bar of the window
      barCollision = ::ui.touchCollide(p, d.x + window.x, d.y + window.y, window.w, 10);
    }
  }
//Terminal::handleKeyboardInput
  void Terminal::handleKeyboardInput()
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

    // DEBUG(window.selected);

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
          println("ERROR line ",__LINE__,", zero or bellow zero length command");
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
  void Terminal::update()
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
Terminal::~Terminal()
  {
    
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

    println("Terminal destructor for ID : ",id," <- NOTICE ------------------------------------------------------------");
  }
/*inline*/ Terminal& UI::getTerminal(const char* id)
{
  return *((Terminal*)findElementWithId(id));

  // if we didn't find a corresponding id
  println("ERROR, couldn't find '", id, "' in the list of ui elements");
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
