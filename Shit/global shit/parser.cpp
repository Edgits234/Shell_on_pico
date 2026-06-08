#include <vector>

//usefull pack:
#if true //{
  #include <iostream>
	#include <cmath>// for std::abs
	#include <cstdlib> // for rand(), srand(), RAND_MAX
	#include <chrono>//for the delay function
	#include <thread>//for the delay function
	#include <algorithm> // For std::min
	void delay(int i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(i));
	}
	void println() {
		std::cout<<std::endl;
	}
	template<typename T> void println(T input) {
		std::cout<<input<<std::endl;
	}
	template<typename T, typename... Args> void println(T input, Args... other) {
		std::cout<<input;
		println(other...);
	}
	template<typename T> void print(T input) {
		std::cout<<input;
	}
	template<typename T, typename... Args> void print(T input, Args... other) {
		std::cout<<input;
		print(other...);
	}
	void printbin(int input)
	{
		for(int i = 32; i >= 0; i--)
		{
			print((input & (1 << i)) >> i);
		}
		println();
	}
	template<typename T>
	void printarray(T array, size_t size)
	{
		for(size_t i = 0; i < size; i++)
		{
			println("[",i,"] = ",array[i]);
		}
	}
	template<typename T>
	void printarray(T array, size_t size, const char* inBetween)
	{
		if(size > 0)
		{
			print(array[0]);
		}

		for(size_t i = 1; i < size; i++)
		{
			print(inBetween);
			print(array[i]);
		}
	}
	int random(int min, int max)
	{
		return min + (std::rand() % (max - min + 1));
	}
	unsigned long long factorial(int num)
	{
		unsigned long long output = 1;
	
		for(int i = num; i > 0; i--)
		{
			output *= i;
		}
	
		return output;
	}
	bool strcmp(const char* s1, const char* s2)
	{
		while((*s1 == *s2))
		{
			s1++;
			s2++;

			if(!(bool)(*s1))
			{ 
				return true;
			}
		}

		return false;
	}
	//the holy grail of printing functions
	template<typename... Args>
	void debugHelper(const char* funcInput, Args... other)
	{
		unsigned int commaIndex = 0;
		bool afterComma = true;

		(
			[&](auto& var)
			{
				//find the next comma (or the end char)
				while(funcInput[commaIndex] != ',' && funcInput[commaIndex] != '\0')
				{
					if(afterComma && funcInput[commaIndex] == ' ')
					{
						commaIndex++;
						continue;
					}
					print(funcInput[commaIndex]);
					commaIndex++;
				}
				
				
				print(" = ");
				println(var);
				
				commaIndex++;
			}(other),
			...
		);
	}
	#define debug(...)(debugHelper(#__VA_ARGS__, __VA_ARGS__))
  #define DEBUG(...)(debugHelper(#__VA_ARGS__, __VA_ARGS__))
  #define arraysize(x)(sizeof(x) / sizeof(x[0]))
  #define LINE_DEBUG println("line : ",__LINE__);
#endif //}


//the code to parse
#if true //{
const int linesBeforeCode = __LINE__;
std::string code = R"(

#include <vector>

//usefull pack:
#if true //{
    #include <iostream>
	#include <cmath>// for std::abs
	#include <cstdlib> // for rand(), srand(), RAND_MAX
	#include <chrono>//for the delay function
	#include <thread>//for the delay function
	#include <algorithm> // For std::min
	void delay(int i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(i));
	}
	void println() {
		std::cout<<std::endl;
	}
	template<typename T> void println(T input) {
		std::cout<<input<<std::endl;
	}
	template<typename T, typename... Args> void println(T input, Args... other) {
		std::cout<<input;
		println(other...);
	}
	template<typename T> void print(T input) {
		std::cout<<input;
	}
	template<typename T, typename... Args> void print(T input, Args... other) {
		std::cout<<input;
		print(other...);
	}
	void printbin(int input)
	{
		for(int i = 32; i >= 0; i--)
		{
			print((input & (1 << i)) >> i);
		}
		println();
	}
	template<typename T>
	void printarray(T array, size_t size)
	{
		for(size_t i = 0; i < size; i++)
		{
			println("[",i,"] = ",array[i]);
		}
	}
	template<typename T>
	void printarray(T array, size_t size, const char* inBetween)
	{
		if(size > 0)
		{
			print(array[0]);
		}

		for(size_t i = 1; i < size; i++)
		{
			print(inBetween);
			print(array[i]);
		}
	}
	int random(int min, int max)
	{
		return min + (std::rand() % (max - min + 1));
	}
	unsigned long long factorial(int num)
	{
		unsigned long long output = 1;
	
		for(int i = num; i > 0; i--)
		{
			output *= i;
		}
	
		return output;
	}
	bool strcmp(const char* s1, const char* s2)
	{
		while((*s1 == *s2))
		{
			s1++;
			s2++;

			if(!(bool)(*s1))
			{ 
				return true;
			}
		}

		return false;
	}
	//the holy grail of printing functions
	template<typename... Args>
	void debugHelper(const char* funcInput, Args... other)
	{
		unsigned int commaIndex = 0;
		bool afterComma = true;

		(
			[&](auto& var)
			{
				//find the next comma (or the end char)
				while(funcInput[commaIndex] != ',' && funcInput[commaIndex] != '\0')
				{
					if(afterComma && funcInput[commaIndex] == ' ')
					{
						commaIndex++;
						continue;
					}
					print(funcInput[commaIndex]);
					commaIndex++;
				}
				
				
				print(" = ");
				println(var);
				
				commaIndex++;
			}(other),
			...
		);
	}
	#define debug(...)(debugHelper(#__VA_ARGS__, __VA_ARGS__))
  #define DEBUG(...)(debugHelper(#__VA_ARGS__, __VA_ARGS__))
  #define arraysize(x)(sizeof(x) / sizeof(x[0]))
  #define LINE_DEBUG println("line : ",__LINE__);
#endif //}


//the code to parse
#if true //{
con

)";
#endif //}

//the output .h file
std::string file = "";

#define npos std::string::npos

int getLine(int charIndex);//predefine function for unse in the boundCheckHelper

bool boundCheckHelper(int index, int line)
{
  if(0 <= index && index < code.length()) 
  {
    return true; 
  }else
  {
    println("ERROR line ",line," in string at line ",getLine(index),", bound check failed");
    return false;
  }
}

#define boundCheck(x)(boundCheckHelper(x, __LINE__))


const char specialChars[] = {'\n', ' ', '/', '}', ';', '\t'};
int li = -1;//last i
bool currentlyString  = false;
bool currentlyChar    = false;
uint8_t nOfSlashes = 0;
bool currentlyComment = false;
bool currentlyInFunc  = false;
bool classKeyword     = false;
bool currentlyInClass = false;
int  classnOfBrackets = -1823;
int  classStart       = -1823;
std::string className = "";
int nOfBrackets = 0;
int truenOfBrackets = 0;

int getLine(int charIndex)
{
    if(!(0 <= charIndex && charIndex < code.length())) return 0;

    int nOfNewLines = 0;
    while(charIndex > 0)
    {
        if(code[charIndex] == '\n')
        {
            nOfNewLines += 1;
        }
        charIndex -= 1;
    }

    return nOfNewLines + linesBeforeCode + 1;
}

size_t strlen(const char* str)
{
    //iterate until we find the ending character
    int i = 0;
    while(str[i] != '\0')
    {
        i++;
    }

    return i;
}

bool foundKeyword(int i, const char* keyword)
{

    if(i > (int)code.length() - 1 - (int)strlen(keyword) /*check if we are going to hit the end with i*/) return false;

    //check to find the "class" or "struct" keyword (Fif we do find it, the next thing has to be a class)
    for(int i2 = 0; i2 < (int)strlen(keyword); i2++)
    {
      //if we find one not matching character, the code[i] does not contain class
      if(keyword[i2] != code[i + i2])
      {
        return false;
      }   
    }

    for(int i2 = 0; i2 < arraysize(specialChars); i2++)
    {
      if(i - 1 >= 0)
      {
        return true;
      }else if(boundCheck(i - 1) && code[i - 1] == specialChars[i2])
      {
        return true;
      }
    }

    return false;
}

//skips until it finds something that is not a space or a new line
int skipToLetter(int i, int d)
{
  //skip any new line or space in front of the variable declaration
  while(code[i] == '\n' || code[i] == ' ' || code[i] == '	')
  {
    i += d;
  }

  return i;
}

bool currentlyMacro   = false;
int main()
{

    println("-----------------------------------------------------------------");

    int i = 0;
    //iterate through all of the string
    while(i < code.length())
    {
        boundCheck(i);
        //to ignore any kind of comments
        if(code[i] == '/' && !currentlyString && !currentlyComment)
        {
            nOfSlashes += 1;
        }else if(code[i] != '/' && !currentlyString && !currentlyComment)
        {
            nOfSlashes = 0;//reset    
        }

        //only way to reset the comment by waiting for the next line, so we reset the counter and comment bool every line
        if(code[i] == '\n')
        {
            nOfSlashes = 0;
            currentlyComment = 0;
        }

        //if we found double slash, we permenantly ignore the line
        if(nOfSlashes >= 2)
        {
            // code.erase(i - 1, 1);//erase the slashes
            // i -= 1;//update i (we moved stuff in the string)
            currentlyComment = true;
        }
        
        //if we found the start of /* */ we permanetly ingore the line
        if(boundCheck(i - 1) && (code[i - 1] == '/' && code[i] == '*' && !currentlyString && !currentlyComment))
        {
            // code.erase(i - 1, 1);//erase the slashes
            // i -= 1;//update i (we moved stuff in the string)
            currentlyComment = true;
        }else if(boundCheck(i - 1) && nOfSlashes >= 1 && code[i - 1] == '*' && currentlyComment && !currentlyString)
        {
            // code.erase(i, 1);//erase the slashes
            // i -= 1;//update i (we moved stuff in the string)
            currentlyComment = false;
        }

        //to ignore any kind of strings
        if(code[i] == '\"' && !currentlyComment)
        {
            if(i == 0)
            {
                currentlyString = !currentlyString;//switch currently string state
            }else if(boundCheck(i - 1) && code[i - 1] != '\\')//check for weird \" characters that don't actually do anything
            {
                currentlyString = !currentlyString;//switch currently string state
            }
        }else if(code[i] == '\'' && !currentlyString && !currentlyComment)
        {
            if(i == 0)
            {
                currentlyChar = !currentlyChar;//switch currently char state
            }else if(boundCheck(i - 1) && code[i - 1] != '\\')//check for weird \' characters that don't actually do anything
            {
                currentlyChar = !currentlyChar;//switch currently char state
            } 
        }

        //if we see '#' then we prob are doing some macro or preprocessed bullshit
        if(code[i] == '#' && !currentlyComment && !currentlyString && !currentlyChar)
        {
            currentlyMacro = true;

        //if its been a new line, we can cancel currentlyMacro (also check for line continuations with '\' character)
        }else if(boundCheck(i - 1) && (code[i] == '\n' && i != 0/*because will break after*/ && code[i - 1] != '\\' && !currentlyComment && !currentlyString && !currentlyChar && currentlyMacro))
        {
            
            li += 1;
            li = skipToLetter(li, 1);

            println("THIS MUST BE A MACRO");
            
            boundCheck(li);
            boundCheck(i);
            
            // println("--------------START----------------");
            println(code.substr(li, i - li + 1));
            file += code.substr(li, i - li + 1) + '\n';
            // println("---------------END-----------------");

            currentlyMacro = false;
            li = i;//update last i (after the end of a macro)
        }

        //check if we just saw the "class" keyword and if we did, the next {} brackets are the class so at the end of the bracket, we undo currentlyInClass boolean
        if(!currentlyChar && !currentlyComment && !currentlyString && !currentlyInFunc && !currentlyMacro && !currentlyInClass && !classKeyword)
        {
            classKeyword = foundKeyword(i, "class ");
            bool structKeyword = foundKeyword(i, "struct ");
            
            //if we found the classKeyword we wanna find the class' name
            if(classKeyword || structKeyword)
            {

                int i2 = 0;
                if(classKeyword)
                {
                    i2 = i + strlen("class ");
                }else if(structKeyword)
                {
                    classKeyword = true;//structs essentially act the same as classes for our purposes
                    i2 = i + strlen("struct ");
                }
                
                //skip any new line or space in front of the variable declaration
                while(boundCheck(i2) && (code[i2] == '\n' || code[i2] == ' '))
                {
                    i2 += 1;
                }
                
                int i3 = i2;
                //skip anything that is a letter
                while(boundCheck(i3 + 1) && (code[i3 + 1] != '\n' && code[i3 + 1] != ' ' && code[i3 + 1] != '{' && code[i3 + 1] != ':'))
                {
                    i3 += 1;
                }
                
                
                boundCheck(i2);
                boundCheck(i3);
                
                //get the class name
                className = code.substr(i2, i3 - i2 + 1);
                // println("GOT CLASS NAME '",className,"'");
            }
        }

        //check to skip dumb stuff like "public:" and "private"
        if(!currentlyComment && !currentlyChar && !currentlyString && !currentlyInFunc && !currentlyMacro && !currentlyMacro && currentlyInClass)
        {

            if(foundKeyword(i, "public:"))
            {
                li = i + strlen("public:");
            }else if(foundKeyword(i, "private:"))
            {
                li = i + strlen("private:");
            }
        }

        //update number of brackets
        if(code[i] == '{' && !currentlyComment && !currentlyString && !currentlyChar)
        {
            //if we have more than one bracket, we don't want to do some bullshit inside of the functions so we always increase the brackets if we see one
            if(nOfBrackets > 0)
            {
                li = i;//updeate last i, counts as a "new line" kind of
                nOfBrackets += 1;//add to the number of brackets
                truenOfBrackets += 1;
                // println("line ",getLine(i)," ADDED   1 TO nOfBrackets -> ",nOfBrackets);

            //if we don't have anybrackets yet (still in the phase where we want to find variable declarations (outside of a function) we will check if the bracket is from a function")
            }else if(i != 0 && nOfBrackets == 0)
            {
                //find the index of the last none space or new line
                int i2 = i - 1;
                while(code[i2] == ' ' || code[i2] == '\n' || code[i2] == '	')
                {
                    i2 -= 1;
                }

                //if its a function declaration or smth similar
                if(code[i2] == ')')
                {

                  li += 1;
                  //skip any new line or space in front of the variable declaration
                  while(code[li] == '\n' || code[li] == ' ' || code[li] == '	')
                  {
                      li += 1;
                  }
                  
                  println("THIS MUST BE A FUNCTION DECLARATION");
                  println(code.substr(li, i2 - li + 1),";");
                  file += code.substr(li, i2 - li + 1) + ';' + '\n';
                  // println("----------------------------------------------");

                    li = i;//updeate last i, counts as a "new line" kind of
                    nOfBrackets += 1;//add to the number of brackets
                    truenOfBrackets += 1;
                    // println("line ",getLine(i)," ADDED   1 TO nOfBrackets -> ",nOfBrackets);
                }else
                {
                    //did we just see a classKeyword?? if yes, than we should be entering the class
                    if(classKeyword)
                    {
                        li += 1;
                        li = skipToLetter(li, 1);

                        println("THIS MUST BE A CLASS OR A STRUCT");
                        println(code.substr(li, i - li + 1));

                        file += code.substr(li, i - li + 1) + '\n';

                        li = i;//updeate last i, special case here because we are entering in the class
                        classKeyword = false;
                        currentlyInClass = true;
                        classnOfBrackets = truenOfBrackets;
                    }

                    truenOfBrackets += 1;
                    // println("line ",getLine(i)," ADDED   0 TO nOfBrackets -> ",nOfBrackets);
                }
            }

        }else if(code[i] == '}' && !currentlyComment && !currentlyString && !currentlyChar)
        {
            //bound check (we do some fucked shit when its not a function declaration which might be giving us a smaller than usual number of brackets)
            if(nOfBrackets > 0)
            {
                nOfBrackets -= 1;//decrese the number of brackerts
                truenOfBrackets -= 1;
                li = i;//updeate last i, counts as a "new line" kind of
                // println("line ",getLine(i)," REMOVED 1 TO nOfBrackets -> ",nOfBrackets);
            }else
            {
                truenOfBrackets -= 1;

                //are we getting out of a class???
                if(truenOfBrackets == classnOfBrackets && currentlyInClass)
                {
                    println("}");

                    //set stuff to be outside of the class
                    currentlyInClass = false;
                    classnOfBrackets = -1823;//set teh nOfBrackets to something that doesn't make sense so that code doesn't panic / do some stupid shit
                    className = "";//clear the class name
                    li = i;
                }

                // println("line ",getLine(i)," REMOVED 0 TO nOfBrackets -> ",nOfBrackets);
            }
        }

        //if we have 1 or more brackets, than we are 100% in a function (note: actually no... not 100% sure, but we do checks before hand to make sure)
        if(nOfBrackets >= 1)
        {
            currentlyInFunc = true;
        }else
        {
            currentlyInFunc = false;
        }
         

        // WAS FOR DEBUGING
        // if(code[i] == ';')
        // {
        //     println("======================================================================================");
        //     debug(code[i] == ';');
        //     debug(!currentlyString);
        //     debug(!currentlyChar);
        //     debug(!currentlyComment);
        //     debug(!currentlyInFunc);
        //     debug(!currentlyMacro);
        //     println("======================================================================================");
        // }

        //iterate through all of the special characters (but only if we aren't in a string of sorts)
        if(code[i] == ';' && !currentlyString && !currentlyChar && !currentlyComment && !currentlyInFunc && !currentlyMacro)
        {
            //skip any new line or space in front of the variable declaration
            while(boundCheck(i + 1) && (code[li + 1] == '\n' || code[li + 1] == ' ' || code[li + 1] == '	'))
            {
                li += 1;
            }

            int i2 = i;

            //decrease by one if we are positive (not sure I should do that)
            if(i2 > 0)
            {
                i2 -= 1;
            }

            //skip any new line or space after the variable delcaration
            while(boundCheck(i2) && (code[i2] == '\n' || code[i2] == ' ' || code[i2] == '	'))
            {
                i2 -= 1;
            }

            //get the line
            std::string line = code.substr((li + 1), i2 - (li + 1) + 1);
            
            
            //check if is a variable declaration
            size_t findSpace = line.find(' ');
            
            
            if(findSpace != npos && line[0] != '#')
            {
                println("THIS MUST BE A VARIABLE DECLARATION!!!");
                println(line,";");
                file += line  + ';' + '\n';
                // println("-----------------------------------------------------------------");
            }
            
            // println(line);
            // println("-----------------------------------------------------------------");


            li = i;//set last i
        }

        // if(currentlyComment)
        // {
        //     code.erase(i, 1);//erase the comment (i advances on its own)
        // }else
        // {
            i++;//increase i
        // }


        

    }
    
    
    for(int j = 0; j < 20; j++)
    {
      println();
    }
    
    println(file);
    /*
    The goal : 
    - to find all function and variable declarations

    */
}
