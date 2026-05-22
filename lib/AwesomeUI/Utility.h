#ifndef Utility_h
#define Utility_h

//include default arduino stuff
#include <Arduino.h>

#define LINE_DEBUG println(F("line : "),__LINE__);

// 1. Helper macros to turn whatever is in WOKWI_SIM into a "string"
#define STRINGIZE_INTERNAL(x) #x
#define STRINGIZE(x) STRINGIZE_INTERNAL(x)

//gets size of array
#define sizeofarray(x) (sizeof(x)/sizeof(x[0]))

//define MIN macro if necessary
#ifndef MIN
    #define MIN(a,b) (a<b?a:b)
#endif

//define MAX macro if hasn't already been done
#ifndef MAX
    #define MAX(a,b) (a>b?a:b)
#endif

#ifndef ABS
    #define ABS(a) (a<0?-a:a)
#endif

#define FLOOR(x) ((int32_t)(x) - ((x) < (int32_t)(x))) //FLOOR macro, behaves like floor, outputs a int32_t
#define  CEIL(x) ((int32_t)(x) + ((x) > (int32_t)(x))) //CEIL  macro, behaves like ceil , outputs a int32_t

#define clearArray(arr, ...) \
for(unsigned int __pAgD67o5 = 0; __pAgD67o5 < sizeofarray(arr); __pAgD67o5++)\
{\
    arr[__pAgD67o5] = __VA_ARGS__;\
}
#define LOWERCASE(x) (('A' <= x && x <= 'Z')?('a' - 'A' + x):(x))
#define UPPERCASE(x) (('a' <= x && x <= 'z')?('A' - 'a' + x):(x))
#define ISLETTER(x)  ((('a' <= x && x <= 'z')||('A' <= x && x <= 'Z'))?(true):(false))
#define ISNUMBER(x)  (('0' <= x && x <= '9')?(true):(false))

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

    bool operator==(const Point& p)
    {
        return p.x == x && p.y == y;
    }

    bool operator!=(const Point& p)
    {
        return p.x != x || p.y != y;
    }
  
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

    Pointd(double x, double y)
    {
        this->x = (double)x;
        this->y = (double)y;
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








void print(unsigned long long input)
{
    Serial.print((unsigned long)(input));
};

void println(unsigned long long input)
{
    Serial.println((unsigned long)(input));
};


void print(long long input)
{
    Serial.print((long)(input));
};


void println(long long input)
{
    Serial.println((long)(input));
};


//custom nice to have quick prints : 
template <typename T> void print(T input){Serial.print(input);} 
template <typename T>void println(T input) {Serial.println(input);}
template<typename T, typename... Args> void print(T input, Args... other){print(input); print(other...);}
template <typename T, typename... Args> void println(T input, Args... other){print(input);println(other...);}
void println(){Serial.println();}


//specific print for Point 
void print(Point input)
{
    print(F("{"),input.x,F(", "),input.y,F("}"));
}

//specific print for Point 
template<typename... Args>
void print(Point input, Args... other)
{
    print(F("{"),input.x,F(", "),input.y,F("}"), other...);
}

//specific print for Point 
void println(Point input)
{
    println(F("{"),input.x,F(", "),input.y,F("}"));
}

//specific print for Point 
template <typename... Args>
void println(Point input, Args... other)
{
    println(F("{"),input.x,F(", "),input.y,F("}"), other...);
}

template <typename T> void print1(T input){Serial.print(input);} template<typename T, typename... Args> void print1(T input, Args... other){Serial.print(input); Serial.print(", "); print1(other...);}/*inline*/ void println1(){Serial.println();}template <typename T>void println1(T input) {Serial.println(input);}template <typename T, typename... Args> void println1(T input, Args... other){Serial.print(input);Serial.print(", ");println1(other...);}

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

    print(F(" = "));
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

    println(F(" = "),input,F(", "));

    //skip the comma for next variable
    index++;

    debugHelper(index, funcInput, other...);
}

template <typename T>
void printArrayHelper(T* input, size_t size)
{
    for(unsigned int i = 0; i < size; i++)
    {
        print(F("["),i,F("] = "));
        print(input[i]);
        println();
    }
}


//very fucking cool function that helps you print an array without having to input the size
#define printArray(x) printArrayHelper(x, sizeof(x) / sizeof(x[0]))
#define printlnArray(x) printArrayHelper(x, sizeof(x) / sizeof(x[0])); println()

//automatically give what input arguments look like as well as the arguments themselfs
#define DEBUG(...) debugHelper(0, #__VA_ARGS__, __VA_ARGS__)






//create a standart struct where you create two types
template<typename A, typename B>
struct is_same
{
    //value inside is false because the two types are different
    static const bool value = false;
};

//C++ is going to choose this more specific version when the two types are both the same
template<typename A>
struct is_same<A, A>//specify template (a bit like overloading function but for classes instead)
{
    static const bool value = true;//value inside is true because they are the same
};

//create a weird template where Condition is a boolean (boolean not a type), and where you are telling c++ that Type is not a valid type
template<bool Condition, typename Type = void>
struct enable_if
{
    
};

template<typename Type>
struct enable_if<true, Type>
{
    typedef Type type;
};



/**
 * @brief switches between two types based on a condition, add "::type" at the end
 * 
 * `Condition` if false outputs T1 if true outputs T2
 * 
 * `T1` a type of your choosing
 * 
 * `T2` a type of your choosing
 * 
 */
template<bool Condition, typename T1, typename T2>
struct choose_type
{
    typedef T1 type;
};

template<typename T1, typename T2>
struct choose_type<true, T1, T2>
{
    typedef T2 type;
};






//============= CUSTOM CLASS TO STORE LAMBDAS =============//

template<typename Return, typename... Args>
class BaseCallable
{
    public:

    //virtual call command (this is so the compiler remembers that call exists so it can call LambdaCallable's call function without having to deal with the custom Lambda)
    virtual Return call(Args... args) = 0;

    //virtual clone function (so calls the LambdaCallable clone function to clone the LambdaCallable)
    virtual BaseCallable* clone() = 0;
    
    //virtual destructor because we want the destructor to destruct idk
    virtual ~BaseCallable(){}
};



template<typename Lambda, typename Return, typename... Args>
class LambdaCallable : public BaseCallable<Return, Args...>
{
    public:

    //store the lambda
    Lambda lambda;

    //clone function to (clones the lamdba too)
    LambdaCallable* clone()
    {
        return new LambdaCallable<Lambda, Return, Args...>(lambda);
    }

    //link call function with the actuall lambda
    Return call(Args... args)
    {
        //call operator()() with specified args and return specified Return type
        return lambda(args...);
    }

    //constructor that copies the to lambda
    LambdaCallable(const Lambda& lambda) : lambda(lambda) // copy constructor (COPY lambda to LambdaCallable::lambda variable)
    {

    }
};



//super sofisticated line tracker to track lines even for operator= one argument thing
template<typename T>
struct LineTracker
{
    T value;
    int line;
    const char* file;
    
    //constructor that translates any type into a line tracker but secretly also stores the line and files
    LineTracker(T input, int line1 = __builtin_LINE(), const char* file1 = __builtin_FILE()) :
    value(input),
    line(line1),
    file(file1)
    {}
};


template<typename Return, typename... Args>
class Function
{
    public:

    //this type is literally just here for the line number
    struct AVerySpecificTypeForAVerySpecificProblem{};

    //variable that points to a LambdaCallable disguised as a BaseCallable because we can't set the type of the lambda at compile time
    BaseCallable<Return, Args...>* lambdaCallable = nullptr;

    //std::is_same<A, B>
    //std::enable_if<condition, type>

    //weird structs that check compile time if its a function so that it doesn't accidentally choose a function
    template<typename T>
    struct is_Function
    {
        //create a static const variable to be able to index with :: (bcs static = only one in memory so can index easly idk)
        static const bool value = false;
    };

    //specific template if its a Function type with any Return type and any arguments I guess
    template <typename R, typename... A>
    struct is_Function<Function<R, A...>>
    {
        //static const variable to easly index when using it I guess
        static const bool value = true;
    };
    


    //Function constructor that sets the lambda but not a Function
    template<typename Lambda> //second typename has no name and default argument is either set to void or not set depening on compile time computed types
    Function(Lambda& lambda, typename enable_if<!is_Function<Lambda>::value, void>::type* = nullptr)
    {
        //dynamic memory allocation for a LambdaCallable object that we are going to store disguised as a BaseCallable to be able to call it
        lambdaCallable = new LambdaCallable<Lambda, Return, Args...>(lambda);
    }

    
    //constructor for functions that don't have the same template as this e
    template<typename Lambda>
    Function(Lambda& function, typename enable_if<is_Function<Lambda>::value, void>::type* = nullptr, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        if(function.lambdaCallable == nullptr) return;
        println(F("ERROR line "),line,F(" in "),file,F(", tried setting a Function class to another Function class with different Return type or Arguments"));
    }

    //Function constructor to copy another Function with same template
    Function(const Function<Return, Args...>& function)
    {
        //if we are copying ourself, shouldn't happen because constructor but who knows, we don't do anything
        if(this == &function) return;

        //if the function we are copying has a lambdaCallable associated with it
        if(function)
        {
            //set lambdaCallable to a clone of the lambdaCallable of the function
            lambdaCallable = function.lambdaCallable->clone();
        }
    }

    //Function constructor (same as default constructor, for nullptr)
    Function(void* ptr)
    {
        if(ptr != nullptr)
        {
            println(F("ERROR line "),__LINE__,F(", function was set to a pointer other than nullptr, this is not supposed to happen (this constructor might be running instead of another correct one)"));
        }
    }

    //default function constructor if you wish to set the lambda afterwards
    Function(){}

    //set a new lambda (ONLY IF ITS A FUNCTION)
    template<typename Lambda>
    typename enable_if<!is_Function<Lambda>::value, void>::type //if its a function we set a type, if its not we set a weird type that doesn't work so C++ compiler leaves us the heck alone
    operator=(const Lambda& lambda)
    {
        //destroy the previous lambda pointer storage variable (if available and not nullptr)
        if(lambdaCallable != nullptr)
        {
            delete lambdaCallable;
        }

        //dynamic memory allocation for a new LambdaCallable object
        lambdaCallable = new LambdaCallable<Lambda, Return, Args...>(lambda);
    }


    //give out error because trying to set Function to another Function with different arguements / return type
    template<typename Lambda>
    typename enable_if<is_Function<Lambda>::value, void>::type //if its a function we set a type, if its not we set a weird type that doesn't work so C++ compiler leaves us the heck alone
    operator=(LineTracker<Lambda> function)
    {
        if(function.value.lambdaCallable == nullptr) return;
        println(F("ERROR line "),function.line,F(" in "),function.file,F(", tried setting a Function class to another Function class with different Return type or Arguments"));
    }

    //copy another Function with same template
    void operator=(const Function<Return, Args...>& function)
    {
        //if we are copying ourself, shouldn't happen because constructor but who knows, we don't do anything
        if(this == &function) return;
    
        //delete this current lambda (we are going to replace it)
        if(lambdaCallable != nullptr)
        {
            //remove lambdaCallable from memory
            delete lambdaCallable;

            //set lambdaCallable to nullptr (the function we are copying might not have a lambda associated with it, in that case we are essentially copying an empty function and so its important we set the pointer to nullptr so the code knows that this lambdaCallable isn't linked yet)
            lambdaCallable = nullptr;
        }

        //if the function we are copying has a lambdaCallable associated with it
        if(function)
        {
            //set lambdaCallable to a clone of the lambdaCallable of the function
            lambdaCallable = function.lambdaCallable->clone();
        }
    }

    //this is to play the function, does lineTracker on every element
    template<typename Dummy = void, typename = typename enable_if<sizeof...(Args) >= 1 && is_same<Dummy, void>::value, void>::type>
    Return operator()(LineTracker<Args>... args)
    {
        if(lambdaCallable == nullptr)
        {
            int line = 0;
            const char* file = nullptr;

            //expand the args pack and set the line to the first packs
            int dummy[] = 
            {
                (
                    //set line and file to the recorded line and file
                    (line = args.line, file = args.file), 

                    //then we set the number in the dummy array to zer anyways
                    0

                //expand args pack
                )...
            };


            /*
            
            
            
            (int)((line == ((int)0)) ? (line = args.LineTracker<T>::line), (file = args.LineTracker<T>::file) : ((int)0)), ((int)0)
            
            
            
            
            */

            //so we don't get unused dummy variaible warning
            (void)(dummy);

            println(F("ERROR line "),line,F(" in "),file,F(", the Function call with \"()\" was impossible because Function wasn't set to any lambdas        tip : to check if a Function has been set (to a lambda) just check if the object itself is true or false (EX: \"Function<void, void> fn; if(fn){/*function has been set*/}else{/*function was not set*/}\")"));
            while(true);
        }

        return (*lambdaCallable).call(args.value...);
    }

    template<typename Dummy = void, typename = typename enable_if<sizeof...(Args) == 0 && is_same<Dummy, void>::value, void>::type>
    Return operator()(AVerySpecificTypeForAVerySpecificProblem dummy = {}, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        if(lambdaCallable == nullptr)
        {
            println(F("ERROR line "),line,F(" in "),file,F(", the Function call with \"()\" was impossible because Function wasn't set to any lambdas        tip : to check if a Function has been set (to a lambda) just check if the object itself is true or false (EX: \"Function<void, void> fn; if(fn){/*function has been set*/}else{/*function was not set*/}\")"));
            while(true);
        }

        return (*lambdaCallable).call();
    }

    
    //checking boolean value of this object will return if it has been assigned a lambda to or not (if the Function has been set)
    operator bool() const
    {
        //if lambdaCallable is a nullptr it means it hasn't been assigned to (so we check if isn't a nullptr)
        return lambdaCallable != nullptr;
    }

    //Destructor to destroy the dynamically allocated lambda pointer / call linker class
    ~Function()
    {
        //if the lambda Callable exists, delete it
        if(lambdaCallable != nullptr)
        {
            //destroy the lambda pointer storage variable thingy because Function object is getting destroyed (would cause memory leaks if we didn't delete)
            delete lambdaCallable;
        }
    }
    
};


//============= CUSTOM CLASS TO STORE LAMBDAS =============//



//=============== CUSTOM CLASS TO HALDE FLASH STRING HELPER ===============//

// template<typename T>
// class HandleFlashString
// {
//     public:
//   
//     void* strPtr;
//     const bool is_flash;
//
//     HandleFlashString(const char* strPtr) : strPtr((void*)(strPtr)), is_flash(false){}
//     HandleFlashString(const __FlashStringHelper* strPtr) : strPtr((void*)(strPtr)), is_flash(true){}
//
//     automatically return correct type when trying to get the actual pointer
//     operator const char* () const 
//     {
//         return (const char*)(strPtr);
//     }
//
//     operator const __FlashStringHelper* () const
//     {
//         return (const __FlashStringHelper*)(strPtr);
//     }
//
//     //automatically handle the array indexing
//     char operator[](size_t i) const
//     {
//         if(is_flash)
//         {
//             const char* flashAdr = (const char*)(strPtr);
//             return pgm_read_byte(flashAdr + i);
//         }else
//         {
//             const char* normalAdr = (const char*)(strPtr);
//             return normalAdr[i];
//         }
//     }
// };


template<typename T, typename Enable = void>
struct HandleFlashString
{
    void* strPtr;

    // template<typename Type>
    // HandleFlashString(HandleFlashString<Type> otherHandleFlash) : strPtr((void*)(otherHandleFlash.strPtr)){}
    template<typename U>
    HandleFlashString(const HandleFlashString<U>& strPtr) : strPtr((void*)(strPtr.strPtr)){}
    HandleFlashString(const char* strPtr) : strPtr((void*)(strPtr)){}
    


    // automatically return correct type when trying to get the actual pointer
    operator const char* () const 
    {
        return (const char*)(strPtr);
    }

    //automatically handle the array indexing
    char operator[](size_t i) const
    {
        const char* normalAdr = (const char*)(strPtr);
        return normalAdr[i];
    }

    char operator[](int i) const 
    {
        return operator[]((size_t)(i));
    }
};

template <typename T>
struct HandleFlashString<T, typename enable_if<is_same<T, const __FlashStringHelper*>::value || is_same<T, HandleFlashString<const __FlashStringHelper*>>::value>::type>
{

    void* strPtr;
    static const bool is_flash = true;

    HandleFlashString(const __FlashStringHelper* strPtr) : strPtr((void*)(strPtr)){}
    HandleFlashString(const HandleFlashString<const __FlashStringHelper*>& strPtr) : strPtr((void*)(strPtr.strPtr)){}

    operator const __FlashStringHelper* () const
    {
        return (const __FlashStringHelper*)(strPtr);
    }

    //automatically handle the array indexing
    char operator[](size_t i) const
    {
        const char* flashAdr = (const char*)(strPtr);
        return pgm_read_byte(flashAdr + i);
    }

    char operator[](int i) const 
    {
        return operator[]((size_t)(i));
    }
};

//=============== CUSTOM CLASS TO HALDE FLASH STRING HELPER ===============//




//global::Array
template<typename T>
class Array
{
  public:
  T array[20];
  unsigned int size;
  T nothing;

  //Array::add
  void add(T input, int line = __builtin_LINE(), const char* file = __builtin_FILE())
  {
    //If the size is bellow the total size of the array
    if(size < (sizeof(array) / sizeof(T)))
    {
      //we add an item at the end of the list
      array[size] = input;
      size += 1;//update the size
    }else 
    {
      println(F("ERROR at line "),line,F(" in "),file,F("function 'add()' wasn't able to add an element to the end of the list because the array is full (max array size is : "),(sizeof(array) / sizeof(T)),F(", while current size is : "),size,F(")"));
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
      println(F("ERROR, function 'remove()' wasn't able to remove the last element because the array size was "),size);
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
      println(F("ERROR, tried accessing index : "),index,F(" but the range of possible is : "),0,F(" to "),size - 1);
    }
  }

  //Array::at
  T& at(unsigned int index, int line = __builtin_LINE(), const char* file = __builtin_FILE())
  {
    //check if in the array
    if(0 <= index && (int)(index) <= (int)(min(((int)(size) - 1), (int)(sizeof(array) / sizeof(T) - 1))))
    {
      return array[index];

    //if its not, give error
    }else
    {
        println(F("ERROR at line "),line,F(" in "),file,F(", tried accessing index : "),index,F(" but the range of possible indexs are : "),0,F(" to "),min(((int)(size) - 1), (int)(sizeof(array) / sizeof(T) - 1)));
        delay(1000);

        return nothing;//nothing object, useless object that doesn't do anything
    }

    println(F("WARNING : control reaches end of non-void function [-Wreturn-type] at line "),__LINE__);
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

/**
 * @brief takes p3 and checks if its to the right of the line segment p1 p2
 * @param p1 first point of the line 
 * @param p2 second point of the line
 * @param p3 the point you want to know if is to the right or left (the left and right are determined by the p1 -> p2 order, meaning if you invert p1 and p2 you invert the output "right" inverts to "left")
 * @retval negative means p3 is left, 0 means p3 is perfecly in between, positive means p3 is right
 */
/*inline*/ int32_t isToRight(Point p1, Point p2, Point p3)
{
    return -((int32_t)(p2.x - p1.x) * (int32_t)(p3.y - p1.y) - (int32_t)(p2.y - p1.y) * (int32_t)(p3.x - p1.x));
}



//this function does not include the tft.begin() nor the ui.begin() It is only for SERIAL
/*inline*/ void SerialBegin()
{
    Serial.begin(115200);
}

/*inline*/ void SerialWait()
{
    while(!Serial);
    delay(500);
}



void recieveInput_h(char* str, size_t size, int line = __builtin_LINE(), const char* file = __builtin_FILE())
{
    int i = 0;

    // delay(1000);


    while(true) {

        // Check if data is available to read
        if (Serial.available() > 0) {

            char c = Serial.read();

            // if(c == '\b') {
            //     print(F("\\b"));
            // }else if(c == '\n') {
            //     print(F("\\n"));
            // }else if(c == '\r') {
            //     print(F("\\r"));
            // }else {
                
            // }

            if(0 <= i && i < (long)(size - 1)) {
                
                if(c != '\n' && c != '\r') {
                    if(c == '\b' || c == 127) {
                        print('\b');
                    }else{
                        print(c);
                    }   
                }

                str[i] = c;
                i++;
            }else if(0 <= i) {
                if(c == '\b' || c == 127) {
                    print('\b');
                }else if(c != '\n' && c != '\r') {
                    print(F("░"));
                }
                i++;
            }

            if(c == '\b' || c == 127) {
                
                if(i >= 2) {
                    i -= 2;
                }

                if(0 <= i && i < (long)(size - 1)) {
                    str[i] = '\0';
                }else if(0 <= i) {
                    // println(F("ERROR line "),line,F(" in "),file,F(", size of str insuficient to store character at "),i);
                }

                print(F(" \b"));
            }

            if(c == '\r')
            {
                if(i >= 1) {
                    i --;
                }

                if(0 <= i && i < (long)(size - 1)) {
                    str[i] = '\0';
                }

                break;
            }

            if(c == '\n') {
                if(i >= 1) {
                    i --;
                }

                if(0 <= i && i < (long)(size - 1)) {
                    str[i] = '\0';
                }

                break;
            }
        }

    }

    println();
    
    if(i <= 0)
    {
        println(F("ERROR line "),line,F(" in "),file,F(", the string you inputed has a negative length (note: how the heck did you manage a negative length string?? supposed to be impossible)"));
        return;
    }else if((long)(size) - 1 <= i)
    {
        println(F("ERROR line "),line,F(" in "),file,F(", the string you inputed was to big ("),i,F(" characters long) to fit inside of the input string ("),size - 1,F(" characters long)"));
    }

    str[MIN((long)(size) - 1, i)] = '\0';


}

#define recieveInput(str) recieveInput_h(str, sizeofarray(str))



/**
     * @brief function to visually show where index "i" is
     *
     * #### Example:
     * 
     * `this is the string`
     * 
     * `­ ­ ­ ­ ­ ­ ­ ­ ­ ­ ^ ­ ­ ­ ­ ­ ­ ­`
     * 
     * @param i the index
     * @param input the string

    */
void display_info(const char* input, int i, int iend = -1)
{
    if(iend == -1)
    {
        iend = i;
    }
    
    //print the last line {
    #if true
    
        //find the last new line character
        int last_new_line_char = i;
        while(input[last_new_line_char] != '\n' && last_new_line_char >= 0)
        {
            last_new_line_char--;
        }

        //find the next new line character
        int next_new_line_char = i;
        while(input[next_new_line_char] != '\n' && input[next_new_line_char] != '\0')
        {
            next_new_line_char++;
        }

        //print everything that is in between those two characters
        for(int j = last_new_line_char + 1; j <= next_new_line_char - 1; j++)
        {
            if(input[j] == '\0')
            {
                print(F("\\0"));
            }else
            {
                print(input[j]);
            }
        }

        //print a new line to end this printed line
        println();

    #endif
    //}
    
    //display a little arrow to point where we saw the supposed keyword {
    #if true

        //print all required spaces before the little arrow
        for(int j = last_new_line_char + 1; j < MIN(i, iend); j++)
        {
            print(F(" "));
        }

        if(i == iend)
        {
            //print the little arrow and new line
            println(F("^"));
        }else
        {
            //print a range 
            print(F("["));
            
            //print all required spaces before the little arrow
            for(int j = MIN(i, iend) + 1; j < MAX(i, iend) - 1; j++)
            {
                print(F("#"));
            }

            //print a range 
            println(F("]"));
        }
        

    #endif 
    //}
}



// Handle platform-specific memory configurations safely
#if defined(__AVR__)
  // Arduino Mega / AVR configuration
  extern char *__brkval;
  extern char *__malloc_heap_start;
  #ifndef RAMSTART
    #define RAMSTART 0x100
  #endif
  #define TOTAL_RAM ((size_t)(RAMEND) - (size_t)(RAMSTART) + 1)

// 1. Isolate the Arduino GIGA first using its specific hardware target definition
#elif defined(TARGET_GIGA) || defined(ARDUINO_GIGA)
  #include <malloc.h>
  #define TOTAL_RAM (512 * 1024) // GIGA has 512KB of user-accessible SRAM

// 2. Check for the Raspberry Pi Pico (Catches both Mbed core and Earle Philhower's core)
#elif defined(ARDUINO_ARCH_RP2040) || defined(PICO_BOARD) || defined(TARGET_RASPBERRYPI_PICO)
  #include <malloc.h>
  #define TOTAL_RAM (264 * 1024) // Pico has 264KB of SRAM

// 3. Fallback alternative for other MBED boards (like Nano 33 BLE)
#elif defined(ARDUINO_ARCH_MBED)
  #include <malloc.h>
  #define TOTAL_RAM (256 * 1024) 

#else
  // Default fallback limit
  #define TOTAL_RAM (64 * 1024)
#endif

// Returns the total number of free bytes available in RAM
uint32_t getRamFree()
{
#if defined(__AVR__)
    char topOfStack;
    if(__brkval == 0) {
        return (uint32_t)(&topOfStack - __malloc_heap_start);
    } else {
        return (uint32_t)(&topOfStack - __brkval);
    }
#elif defined(ARDUINO_ARCH_MBED) || defined(ARDUINO_ARCH_RP2040) || defined(PICO_BOARD)
    // Works perfectly on Mbed OS frameworks and native RP2040 frameworks
    struct mallinfo mi = mallinfo();
    return TOTAL_RAM - mi.uordblks;
#else
    return 0;
#endif
}

unsigned long getRamUsage(int precision = 100)
{
    unsigned long result = ((unsigned long)(TOTAL_RAM) - (unsigned long)(getRamFree())) * (unsigned long)(precision) / (unsigned long)(TOTAL_RAM);
    return result;
}

void printRamUsage(int precision = TOTAL_RAM)
{
    if(precision == 100)
    {
        println(getRamUsage(precision),"%");
    }else
    {
        println(getRamUsage(precision)," / ",precision," (",getRamUsage(100),"%)");
    }
}

long long double_to_long_long(double d)
{
    /*


    DOUBLE : 

    [ Signe ] [     Exposant     ] [                      Mantisse                      ]
      1 bit         11 bits                               52 bits

    valeur = (-1)^signe * (1.mantisse) * 2^(exposant - 1023)
          


    FLOAT : 
                            
    [ Signe ] [     Exposant     ] [                      Mantisse                      ]
      1 bit          8 bits                               23 bits

    valeur = (-1)^signe * (1.mantisse) * 2 ^ (exposant - 127)


    */

    return 0;
}


#if __SIZEOF_DOUBLE__ == 8
    typedef unsigned long long double_bits_t;
#else
    typedef unsigned long double_bits_t;
#endif

/**
 * Safely extracts the precise bits of a double without strict-aliasing warnings.
 */
double_bits_t extractBitsUniversal(double value) {
    union UniversalConverter {
        double inputDouble;
        double_bits_t outputBits;
    };
    UniversalConverter converter;
    converter.inputDouble = value;
    return converter.outputBits;
}

/**
 * Calculates the exact base-10 exponent of the smallest 100% precise digit.
 * Returns an integer representing the power of 10 (e.g., -7 means precise down to 10^-7).
 */
int getSmallestPreciseDecimalExponent(double value) {
    double_bits_t rawBits = extractBitsUniversal(value);
    
    int rawExponent;
    int bias;
    int mantissaBits;
    
    // 1. Detect architecture and set parameters dynamically
    if (sizeof(double) == 4) {
        // 32-bit float parameters (Arduino Mega)
        rawExponent = (rawBits >> 23) & 0xFF;
        bias = 127;
        mantissaBits = 23;
    } else {
        // 64-bit double parameters (PC)
        
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wshift-count-overflow"
         rawExponent = (rawBits >> 52) & 0x7FF;
        #pragma GCC diagnostic pop

        bias = 1023;
        mantissaBits = 52;
    }
    
    int trueBinaryExponent;
    
    // 2. Handle subnormal numbers, zeros, and special IEEE 754 states
    if (rawExponent == 0) {
        // Subnormal number boundary
        trueBinaryExponent = 1 - bias; 
    } else if ((sizeof(double) == 4 && rawExponent == 255) || (sizeof(double) == 8 && rawExponent == 2047)) {
        // Infinity or NaN: precision cannot be quantified
        return 0; 
    } else {
        // Standard normal number formula
        trueBinaryExponent = rawExponent - bias;
    }
    
    // 3. Find the binary power of the Least Significant Bit (LSB)
    int lowestBitBinaryPower = trueBinaryExponent - mantissaBits;
    
    // 4. Convert the binary power to a base-10 power using linear approximation (log10(2) ~ 0.30103)
    // 30103L / 100000L mimics log10(2) without relying on any math libraries.
    long scaledCalculation = (long)lowestBitBinaryPower * 30103L;
    
    int preciseDecimalExponent;
    if (scaledCalculation < 0) {
        // Adjust for standard C++ truncation behavior to properly floor negative results
        preciseDecimalExponent = (int)((scaledCalculation - 99999L) / 100000L);
    } else {
        preciseDecimalExponent = (int)(scaledCalculation / 100000L);
    }
    
    return preciseDecimalExponent;
}


char* create_string_copy(const char* str)
{
   if(str != nullptr)
   {
     //this is the length of the string
        size_t len = strlen(str);

        //allocate memory for a str that is the same as input (we add one to include the \0 terminator character)
        char* copy = new char[len + 1];
        
        //copy the string over to "copy" storage
        strcpy(copy, str);

        //return the created copy
        return copy;
   }

   println("ERROR at ",__LINE__," in ",__FILE__,", the string you tried to copy was a nullptr");
   return nullptr;
}


#endif

