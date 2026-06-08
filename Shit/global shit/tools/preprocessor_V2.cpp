#include <string>
#include <fstream>
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
	unsigned long millis() {
    // static ensures the start time is only recorded once
    static auto start_time = std::chrono::steady_clock::now();
    
    auto current_time = std::chrono::steady_clock::now();
    
    // Calculate the duration and cast it to milliseconds
    return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
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

std::string readfile()
{
    std::ifstream file("input.txt");

    if(!file.is_open()) {
        // file doesn't exist or can't be opened
        std::cout << "error couldn't read file!" << std::endl;
        return "";
    }

    // whole file into one string
    std::string output((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

    file.close();

    return output;
}
void sethfile(std::string str)
{
    //test writing to file 

    std::ofstream file("output.h");

    if(!file.is_open()) {
        // file doesn't exist or can't be opened
        std::cout << "error couldn't open file !" << std::endl;
        return;
    }
    
    file << str;

    file.close();
}
void setcppfile(std::string str)
{
    //test writing to file 

    std::ofstream file("output.cpp");

    if(!file.is_open()) {
        // file doesn't exist or can't be opened
        std::cout << "error couldn't open file !" << std::endl;
        return;
    }
    
    file << str;

    file.close();
}



//the code to parse
#if true //{
const int linesBeforeCode = __LINE__;
std::string code = readfile();
#endif //}

//the output .h file
std::string hfile = "";
std::string cppfile = "";

#define npos std::string::npos

int getLine(int charIndex);//predefine function for unse in the boundCheckHelper

bool boundCheckHelper(int index, int line)
{
  if(0 <= index && index < code.length()) 
  {
    return true; 
  }else
  {
    println("ERROR line ",line," in string at line ",getLine(index),", bound check failed (index was ",index,")");
    return false;
  }
}

#define boundCheck(x) (boundCheckHelper(x, __LINE__))

int getLine(int charIndex)
{
    if(!(0 <= charIndex && charIndex < code.length())) return 0;

    int nOfNewLines = 0;
    while(charIndex > 0)
    {
        if(boundCheck(charIndex) && code[charIndex] == '\n')
        {
            nOfNewLines += 1;
        }
        charIndex -= 1;
    }

    return nOfNewLines /*+ linesBeforeCode*/ + 1;
}

int getLineChar(int charIndex)
{
    if(!(0 <= charIndex && charIndex < code.length())) return 0;

    int i = charIndex;
    while(true)
    {
        //if we are one in front of a character that indicates the start of a line
        if(i == -1 || (boundCheck(i) && code[i] == '\n'))
        {
            //get out of the loop
            break;
        }
        i -= 1;
    }

    return charIndex - i;
}

std::string location(int charIndex)
{
    return std::to_string(getLine(charIndex)) + ":" + std::to_string(getLineChar(charIndex));
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

bool foundKeyword(int i, const char* keyword, const char* startCharacters = "\n /};\t", const char* endCharacters = nullptr)
{

    if(i > (int)code.length() - 1 - (int)strlen(keyword) /*check if we are going to hit the end with i*/) return false;

    //check to find the "class" or "struct" keyword (Fif we do find it, the next thing has to be a class)
    for(int i2 = 0; i2 < (int)strlen(keyword); i2++)
    {
      //if we find one not matching character, the code[i] does not contain class
      if(boundCheck(i + i2) && keyword[i2] != code[i + i2])
      {
        return false;
      }   
    }

    bool success1 = false;
    bool success2 = false;

    //go through all of the special characters and check if it there is any special characters in front of the words (if there isn't then its not a valid keyword)
    if(startCharacters == nullptr)
    {
        success1 = true;
    }else
    {
        int j = 0;
        while(startCharacters[j] != '\0')
        {
            if(boundCheck(i - 1) && code[i - 1] == startCharacters[j])
            {
                success1 = true;
                break;
            }

            j++;
        }
    }

    //go through all of the special characters and check if it there is any special characters in front of the words (if there isn't then its not a valid keyword)
    if(endCharacters == nullptr)
    {
        success2 = true;
    }else
    {
        int j = 0;
        while(endCharacters[j] != '\0')
        {
            if(boundCheck(i + strlen(keyword)) && code[i + strlen(keyword)] == endCharacters[j])
            {
                success2 = true;
                break;
            }

            j++;
        }

        if(boundCheck(i + strlen(keyword)) && code[i + strlen(keyword)] == '\0')
        {
            success2 = true;
        }
    }

    return (success1 && success2);
}



//skips until it finds something that is not a space or a new line
int skipToLetter(int i, int d)
{
  //skip any new line or space in front of the variable declaration
  while(boundCheck(i) && (code[i] == '\n' || code[i] == ' ' || code[i] == '	'))
  {
    i += d;

    //break after being one outside of the range
    if(i < 0 || code.length() - 1 < i)
    {
        break;
    }
  }

  return i;
}

//skips : newlines, spaces, tabs, comments
int skipToLine(int i, int d)
{
    // println("started search (",getLine(i),":",getLineChar(i),")");

    bool longcomment = false;
    bool linecomment = false;

    {
        // print("code[i] -> '",(code[i] == '\n')?("\\n"):(code.substr(i, 1)),"' -> ");

        //break after being one outside of the range
        if(i < 0 || code.length() - 1 < i)
        {
            return i;
        }

        //check for any sorts of comments (check for /* first and then check for // line comment)
        if(boundCheck(i + 1) && code[i] == '/' && code[i + 1] == '*' && !longcomment && !linecomment)
        {
            // print("LONG COMMENT ENABLED, ");
            longcomment = true;
        }

        //check for line comments "//"
        if(boundCheck(i + 1) && code[i] == '/' && code[i + 1] == '/' && !longcomment && !linecomment)
        {
            // print("LINE COMMENT ENABLED, ");
            linecomment = true;

        //check for a "\n" new line character and currently line comment but not long comment
        }else if(boundCheck(i) && code[i] == '\n' && !longcomment && linecomment)
        {
            // print("LINE COMMENT DISABLED, ");
            linecomment = false;
        }

        //check for a "*/" and if we are currently long comment
        if(boundCheck(i - 2) && code[i - 2] == '*' && code[i - 1] == '/' && longcomment && !linecomment)
        {
            // print("LONG COMMENT DISABLED, ");
            longcomment = false;
        }

        // println();
    }

    //skip any new line or space in front of the variable declaration
    while(boundCheck(i) && (code[i] == '\n' || code[i] == ' ' || code[i] == '	' || longcomment || linecomment))
    {
        i += d;

        // print("code[i] -> '",(code[i] == '\n')?("\\n"):(code.substr(i, 1)),"' -> ");

        //break after being one outside of the range
        if(i < 0 || code.length() - 1 < i)
        {
            break;
        }

        //check for any sorts of comments (check for /* first and then check for // line comment)
        if(boundCheck(i + 1) && code[i] == '/' && code[i + 1] == '*' && !longcomment && !linecomment)
        {
            // print("LONG COMMENT ENABLED, ");
            longcomment = true;
        }

        //check for line comments "//"
        if(boundCheck(i + 1) && code[i] == '/' && code[i + 1] == '/' && !longcomment && !linecomment)
        {
            // print("LINE COMMENT ENABLED, ");
            linecomment = true;

        //check for a "\n" new line character and currently line comment but not long comment
        }else if(boundCheck(i) && code[i] == '\n' && !longcomment && linecomment)
        {
            // print("LINE COMMENT DISABLED, ");
            linecomment = false;
        }

        //check for a "*/" and if we are currently long comment
        if(boundCheck(i - 2) && code[i - 2] == '*' && code[i - 1] == '/' && longcomment && !linecomment)
        {
            // print("LONG COMMENT DISABLED, ");
            longcomment = false;
        }

        // println();
    }

    return i;
}

//skips : custom input
int skipToCustom(int i, int d, const char* custom, bool exclude = 0)
{
    //skip any new line or space in front of the variable declaration
    while(true)
    {

        bool success = false;

        //if excluding custom str, then success is true unless character is the same as any characters in custom array
        if(exclude)
        {
            success = true;

        //if not excluding str, means including it, any time we find a character from custom inside of code means its good (so false unless proven otherwise)
        }else
        {
            success = false;
        }

        //check custom and put if valid skip inside of success variable
        if(custom != nullptr)
        {
            int j = 0;
            while(custom[j] != '\0')
            {
                if(exclude)
                {
                    if(boundCheck(i) && code[i] == custom[j])
                    {
                        success = false;
                        break;
                    }
                }else
                {
                    if(boundCheck(i) && code[i] == custom[j])
                    {
                        success = true;
                        break;
                    }
                }

                j++;
            }
        }

        //check if wasn't a success
        if(!success)
        {
            break;
        }

        i += d;

        //break after being one outside of the range
        if(i < 0 || code.length() - 1 < i)
        {
            break;
        }
    }

    return i;
}

bool currentlyMacro   = false;
int main()
{
    
    println("-----------------------------------------------------------------");
    

    int lastLine = 0;
    int startLine = 0;

    int i = 0;
    //iterate through all of the string
    while(i < code.length())
    {
        // if(1 <= getLine(i) && getLine(i) <= 10);
        // {
        //     if(lastLine != getLine(i))
        //     {
        //         lastLine = getLine(i);
        //         startLine = i;
        //     }

        //     println(i - startLine + 1,"\t -> \t\"",code[i],"\" \t(char:",currentlyChar,")\t(str:",currentlyString,")\t(comment:",currentlyComment,")\t(class:",currentlyInClass,")\t(func:",currentlyInFunc,")\t(macro:",currentlyMacro,")");
        // }

        boundCheck(i);


        //check to find the "//$hdr" and "//$end" lines
        if(foundKeyword(i, "//$hdr", "\n", "\n"))
        {
            //store index (we need to remember for substr)
            int startIndex = i;

            //go through the code until you find the next //$end line
            while(!foundKeyword(i, "//$end", "\n", "\n"))
            {
                i++;
            }

            //add to index to skip "//$end" comment line
            i += 6;

            boundCheck(startIndex);
            boundCheck(i);

            //add it to the hfile
            hfile += code.substr(startIndex, i - startIndex + 1);

            //don't forget to set last index (last line to right after $end so at i)
            li = i;
        }

        if(boundCheck(i - 1) && (code[i - 1] == '/' && code[i] == '/' && !currentlyString && !currentlyLongComment && !currentlyLineComment))
        {
            currentlyLineComment = true;
        }else if(code[i] == '\n' && currentlyLineComment && !currentlyLongComment && !currentlyString)
        {
            currentlyLineComment = false;
        }
        
        //if we found the start of /* */ we permanetly ingore the line
        if(boundCheck(i - 1) && (code[i - 1] == '/' && code[i] == '*' && !currentlyString  && !currentlyLongComment && !currentlyLineComment))
        {
            // code.erase(i - 1, 1);//erase the slashes
            // i -= 1;//update i (we moved stuff in the string)
            currentlyLongComment = true;
        }else if(boundCheck(i - 1) && code[i - 1] == '*' && code[i] == '/' && currentlyLongComment && !currentlyLineComment && !currentlyString)
        {
            // code.erase(i, 1);//erase the slashes
            // i -= 1;//update i (we moved stuff in the string)
            currentlyLongComment = false;
        }

        //if either currentlyLineComment or currentlyLongComment is true than we are currently in a comment so set currentlyComment to true
        if(currentlyLineComment || currentlyLongComment)
        {
            currentlyComment = true;
        }else
        {
            currentlyComment = false;
        }

        //to ignore any kind of strings
        if(code[i] == '\"' && !currentlyComment)
        {
            if(i == 0)
            {
                currentlyString = !currentlyString;//switch currently string state

            //check if there are is an even number of backslash characters before the " character
            }else
            {
                //go back until we don't find backslahes
                int temp = i - 1;
                while(code[temp] == '\\')
                {
                    temp--;
                }
                temp++;

                //figure out the number of backslashes
                int nOfBackslashes = i - temp;

                //if its an even number of backslashes then invert string state (since that means its not a "fake" double quote character)
                if(nOfBackslashes % 2 == 0)
                {
                    currentlyString = !currentlyString;//switch currently string state
                }

            }
        }else if(code[i] == '\'' && !currentlyString && !currentlyComment)
        {
            if(i == 0)
            {
                currentlyChar = !currentlyChar;//switch currently char state
            }else if(boundCheck(i - 1) && ((code[i - 1] == '\\' && boundCheck(i - 2) && code[i - 2] == '\\') || (code[i - 1] != '\\')))//check for weird \' characters that don't actually do anything
            {
                currentlyChar = !currentlyChar;//switch currently char state
            } 
        }

        //if we see '#' then we prob are doing some macro or preprocessed bullshit
        if(code[i] == '#' && !currentlyComment && !currentlyString && !currentlyChar && !currentlyInFunc)
        {
            currentlyMacro = true;

        //if its been a new line, we can cancel currentlyMacro (also check for line continuations with '\' character) (also check if its the last index instead of a new line)
        }else if(boundCheck(i - 1) && (((code[i] == '\n' && i != 0/*because will break after*/ && code[i - 1] != '\\') || i == code.length() - 1 /*checks if we are at the end of the code (last index)*/) && !currentlyComment && !currentlyString && !currentlyChar /*&& !currentlyInFunc*/ && currentlyMacro))
        {
            li += 1;
            li = skipToLetter(li, 1);

            //to ignore any kind of new lines at the end of the line we are about to print with a new line (so we don't have extra new lines)
            int i2 = i;
            i2 = skipToLetter(i2, -1);

            // println("\nTHIS MUST BE A MACRO");
            
            boundCheck(li);
            boundCheck(i2);

            std::string macro = code.substr(li, i2 - li + 1);

            // println("--------------START----------------");
            // println(macro);
            hfile += macro + '\n';

            int li2 = skipToLine(li, 1);

            //if its not "#define", "#include", "#warning", "#error" then let it go to .cpp file
            if(!foundKeyword(li2, "#define", "\n\t };/", " \t\n") && !foundKeyword(li2, "#include", "\n\t };/", " \t\n") && !foundKeyword(li2, "#warning", "\n\t };/", " \t\n") && !foundKeyword(li2, "#error", "\n\t };/", " \t\n"))
            {
                // println("FOUND CPP FILE MACRO");
                // println(macro);
                cppfile += macro + '\n';
            }
            // println("---------------END-----------------");

            currentlyMacro = false;
            li = i;//update last i (after the end of a macro)
        }

        //check if we just saw the "class" keyword and if we did, the next {} brackets are the class so at the end of the bracket, we undo currentlyInClass boolean
        if(!currentlyChar && !currentlyComment && !currentlyString && !currentlyInFunc && !currentlyMacro && !currentlyInClass && (!classKeyword || foundKeyword(i, "class", "\n /}; >", "\n /{; ") || foundKeyword(i, "struct", "\n /}; >", "\n /{; ")))
        {
            classKeyword = foundKeyword(i, "class", "\n /}; >", "\n /{; ");
            bool structKeyword = foundKeyword(i, "struct", "\n /}; >", "\n /{; ");
            
            //check if there is a template<> thingy in front of the class using skipToLine with li
            int li2 = skipToLine(li + 1, 1);

            //check for the template keyword
            if((classKeyword || structKeyword) && foundKeyword(li2, "template", "\t\n}; >", " \t<"))
            {
                hfile += "\n#warning template class, please put \"$hdr ... $end\" around it\n";
            }

            //if we found the classKeyword we wanna find the class' name
            if(classKeyword || structKeyword)
            {

                int i2 = 0;
                if(classKeyword)
                {
                    i2 = i + strlen("class");
                }else if(structKeyword)
                {
                    classKeyword = true;//structs essentially act the same as classes for our purposes
                    i2 = i + strlen("struct");
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
                println("GOT CLASS NAME '",className,"'");
            }
        }

        //check to skip dumb stuff like "public:" and "private"
        if(!currentlyComment && !currentlyChar && !currentlyString && !currentlyInFunc && !currentlyMacro && !currentlyMacro && currentlyInClass)
        {

            if(foundKeyword(i, "public:"))
            {
                //skip until we find a letter
                li += 1;
                li = skipToLetter(li, 1);
                
                boundCheck(li);
                boundCheck(i);

                //add it to the file
                hfile += code.substr(li, i - li) + "public:" + '\n';

                //update li
                li = i + strlen("public:");
                
            }else if(foundKeyword(i, "private:"))
            {
                //skip until we find a letter
                li += 1;
                li = skipToLetter(li, 1);

                boundCheck(li);
                boundCheck(i);

                //add it to the file
                hfile += code.substr(li, i - li) + "private:" + '\n';

                //update li
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
                int i2 = skipToLetter(i - 1, -1);
                int i3 = i2;

                bool constKeyword = false;
                //extra skip if we stopped at const in between
                if(boundCheck(i2 - 4) && foundKeyword(i2 - 4, "const", "\n\t)/ ", "\n\t{/ "))
                {
                    constKeyword = true;
                    i2 -= 5;
                    i2 = skipToLetter(i2, -1);
                }

                //if its a function declaration or smth similar
                if(boundCheck(i2) && code[i2] == ')')
                {
                    //check for "template" keyword in front
                    int li2 = skipToLine(li + 1, 1);

                    //if algorithm found "template" keyword
                    if(foundKeyword(li2, "template", "\t\n}; >", " \t<") || foundKeyword(li2, "inline", ")\t\n};/ >", " \t\n"))
                    {
                        // println("\nTHIS MUST BE A TEMPLATE OR INLINE FUNCTION!!");

                        //skip any new line or space in front of the variable declaration
                        li = skipToLetter(li + 1, 1);

                        //set funcStart and also set templateFunc to true (signifies to the parser that we will have to get the function as a whole)
                        funcStart = li;
                        templateFunc = true;

                        li = i;//updeate last i, counts as a "new line" kind of
                        nOfBrackets += 1;//add to the number of brackets
                        truenOfBrackets += 1;
                    }else
                    {
                        funcInputStart = lastOutsideParenthesis;
                        funcInputEnd   = i2;

                        //skip any new line or space in front of the variable declaration
                        li = skipToLetter(li + 1, 1);

                        boundCheck(li);
                        boundCheck(i3);

                        // println("\nTHIS MUST BE A FUNCTION DECLARATION");
                        // println(code.substr(li, i3 - li + 1),";");
                        hfile += code.substr(li, i3 - li + 1) + ';' + '\n';

                        //update the func start
                        funcStart = li;
                        normalFunc = true;

                        li = i;//updeate last i, counts as a "new line" kind of
                        nOfBrackets += 1;//add to the number of brackets
                        truenOfBrackets += 1;

                        //get the start index of the function name (important for .cpp file)
                        int nameEnd = skipToLetter(lastOutsideParenthesis - 1, -1);

                        //skip the name of the funciton (name can only be specified characters)
                        int nameStart = skipToCustom(nameEnd, -1, "[]+=-~abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");

                        //update the funcNameStart
                        funcNameStart = nameStart + 1;
                        funcNameEnd   = nameEnd;

                        //store the function input without the default args
                        std::string str = "";

                        
                        // println("BEFORE STARTING!! -> array size = ",lastEqualsParenthesis.size());

                        if(lastEqualsParenthesis.size() == 0)
                        {
                            boundCheck(funcInputStart);
                            boundCheck(funcInputEnd);

                            str = code.substr(funcInputStart, funcInputEnd - funcInputStart + 1);
                        }else
                        {
                            boundCheck(lastOutsideParenthesis);
                            boundCheck((lastEqualsParenthesis.at(0) - 1));

                            //get first parenthesis up to "one before the first equal"
                            str += code.substr(lastOutsideParenthesis, (lastEqualsParenthesis.at(0) - 1) - lastOutsideParenthesis + 1);
                            
                            // println("STARTING !!!");

                            for(int i = 1; i < (int)lastEqualsParenthesis.size() - 1; i += 2)
                            {
                                // println("REPEATING!!!");

                                //get comma index
                                int comma = lastEqualsParenthesis.at(i);

                                //get next equal index
                                int equal = lastEqualsParenthesis.at(i + 1);

                                boundCheck(comma);
                                boundCheck(equal - 1);

                                //get the string between them
                                std::string strBetween = code.substr(comma, (equal - 1) - comma + 1);

                                //add it onto the "str" variable
                                str += strBetween;

                                //repeat until you've erased all of the default arguments
                            }

                            // println("ENDED !!!");

                            boundCheck(lastEqualsParenthesis.at(lastEqualsParenthesis.size() - 1));
                            boundCheck(i2);

                            //get last comma up to end of parenthesis
                            str += code.substr(lastEqualsParenthesis.at(lastEqualsParenthesis.size() - 1), i2 - lastEqualsParenthesis.at(lastEqualsParenthesis.size() - 1) + 1);
                            
                        }

                        //transfer string into the long ass variable name that I hate the name because its too complex
                        funcInputExcludeDefaultArgs = str;
                    }

                }else
                {
                    //did we just see a classKeyword?? if yes, than we should be entering the class
                    if(classKeyword)
                    {
                        li += 1;
                        li = skipToLetter(li, 1);

                        // println("\nTHIS MUST BE A CLASS OR A STRUCT");
                        // println(code.substr(li, i - li + 1));

                        boundCheck(li);
                        boundCheck(i);

                        hfile += code.substr(li, i - li + 1) + '\n';

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
                    // println("\nTHIS MUST BE THE END OF CLASS \"",className,"\"");
                    // println("};");

                    hfile += "};\n";

                    //set stuff to be outside of the class
                    currentlyInClass = false;
                    classnOfBrackets = -1823;//set teh nOfBrackets to something that doesn't make sense so that code doesn't panic / do some stupid shit
                    className = "";//clear the class name
                    li = i;
                }

                // println("line ",getLine(i)," REMOVED 0 TO nOfBrackets -> ",nOfBrackets);
            }
        }

        //keep track of the number of parenthesis
        if(code[i] == '(' && !currentlyComment && !currentlyString && !currentlyChar)
        {

            //keep track of the last parenthesis that was outside
            if(nOfParenthesis == 0)
            {
                lastOutsideParenthesis = i;
            }

            // println("increased nofparenthesis (",location(i),")");

            nOfParenthesis += 1;
        
        //decrease number of parenthesis when we see ')'
        }else if(code[i] == ')' && !currentlyComment && !currentlyString && !currentlyChar)
        {
            nOfParenthesis -= 1;
        }

        //if we have 1 or more brackets, than we are 100% in a function (note: actually no... not 100% sure, but we do checks before hand to make sure)
        if(nOfBrackets >= 1)
        {
            currentlyInFunc = true;
        }else
        {
            currentlyInFunc = false;

            //if its a template function, we want to print it
            if(templateFunc)
            {
                if(funcStart == -1823)
                {
                    println("ERROR line ",__LINE__,", funcStart was not a valid number");
                }

                boundCheck(funcStart);
                boundCheck(i);

                std::string fullFunc = code.substr(funcStart, i - funcStart + 1);

                // println(fullFunc);
                hfile += fullFunc + '\n';

                templateFunc = false;
                funcStart    = -1823;
            }else if(normalFunc)
            {

                if(funcStart == -1823)
                {
                    println("ERROR line ",__LINE__,", funcStart was not a valid number");
                    println("function at (",getLine(i),":",getLineChar(i),")");
                }

                boundCheck(funcStart);
                boundCheck((funcNameStart - 1));
                boundCheck(funcNameStart);
                boundCheck((funcInputStart - 1));
                boundCheck((funcInputEnd + 1));
                boundCheck(i);

                std::string funcStartStr    = code.substr(funcStart, (funcNameStart - 1) - funcStart + 1);
                std::string funcMiddleStr   = code.substr(funcNameStart, (funcInputStart - 1) - funcNameStart + 1);
                std::string funcEndStr      = code.substr((funcInputEnd + 1), i - (funcInputEnd + 1) + 1);

                // println("THIS MUST BE WHAT CPP FUNCTION LOOKS LIKE");

                //NOTE TO SELF, DON'T FORGET ABOUT GETTING RID OF THE DEFAULT ARGUMENTS OF FUNCTIONS 

                //I don't gotchu lol
  
                //if its in a class we want that "ClassName::functionName" look
                if(currentlyInClass)
                {
                    // println(funcStartStr + className + "::" + funcMiddleStr + funcInputExcludeDefaultArgs + funcEndStr);
                    cppfile += funcStartStr + className + "::" + funcMiddleStr + funcInputExcludeDefaultArgs + funcEndStr + '\n';
                }else
                {
                    // println(funcStartStr + funcMiddleStr + funcInputExcludeDefaultArgs + funcEndStr);
                    cppfile += funcStartStr + funcMiddleStr + funcInputExcludeDefaultArgs + funcEndStr  + '\n';
                }

                normalFunc   = false;
                funcStart    = -1823;
            }
        }

        //check to find an equal sign in the code (useful for curtting variable declaration to only have the declaration not the value its set to)
        if(code[i] == '=' && !currentlyString && !currentlyChar && !currentlyComment && !currentlyInFunc && !currentlyMacro)
        {
            lastEqualIndex = i;
        }

        //keep track of all of the equal signs at parenthesis level 1
        if(nOfParenthesis == 1 && !currentlyString && !currentlyChar && !currentlyComment && !currentlyInFunc && !currentlyMacro)
        {
            if(inParenthesisLevel1 == false)
            {
                //set in parenthesisLevel1 to true to stop clearing of array to happen
                inParenthesisLevel1 = true;
                
                // println("clearing the list at (",getLine(i),":",getLineChar(i),")");
                //reset array
                lastEqualsParenthesis.clear();

            }

            //if we found an equal sign inside of a level one parenthesis
            if(code[i] == '=' && !currentlyString && !currentlyChar && !currentlyComment && !currentlyInFunc && !currentlyMacro)
            {
                //set found equal sign level 1 to true (so we go search for the comma which is a few characters forward)
                foundEqualParLevel1 = true;
                
                // println("added equal stuff to list");
                //add the current index onto it
                lastEqualsParenthesis.push_back(i);

            //else if we found a comma instead store it in the array if if foundEqualParLevel1 is true because that means we saw a equal sign before 
            }else if(foundEqualParLevel1 && code[i] == ',' && !currentlyString && !currentlyChar && !currentlyComment && !currentlyInFunc && !currentlyMacro)
            {
                // println("added comma stuff to list");
                //there isn't any comma at the end of the function input so simply set the comma position as the end of the function
                lastEqualsParenthesis.push_back(i);

                //cancel the foundEqualParLevel1 to indicate that we aren no longer searching for a comma at level parenthesis one
                foundEqualParLevel1 = false;
            }
        
        //wait for next parenthesis to clear
        }else if(nOfParenthesis <= 0)
        {
            if(foundEqualParLevel1)
            {
                // println("added stuff to list (should be last one)");

                //there isn't any comma at the end of the function input so simply set the comma position as the end of the function
                lastEqualsParenthesis.push_back(i);

                //cancel the foundEqualParLevel1 to indicate that we aren no longer searching for a comma at level parenthesis one
                foundEqualParLevel1 = false;
            }

            //reset the inParenthesis guard that tells the code if an equal is the first inside of a parenthesis (level 1)
            inParenthesisLevel1 = false;
        }

        //iterate through all of the special characters (but only if we aren't in a string of sorts)
        if(code[i] == ';' && !currentlyString && !currentlyChar && !currentlyComment && !currentlyInFunc && !currentlyMacro)
        {
            li = skipToLetter(li + 1, 1);

            boundCheck(li);
            boundCheck(i);

            //get the line
            std::string line = code.substr(li, i - li + 1);
            
            bool foundSpace = line.find(' ') != npos; //boolean variable to indicate if we found a space or not

            if(line.length() == 0)
            {
                println("ERROR ",__LINE__," we have a problem line.length() is ",line.length());
            }

            if(foundSpace == true && line[0] != '#')
            {
                int middle = skipToLine(li, 1);
                
                if(foundKeyword(middle, "class", "\n /}; >", "\n /{; ") || foundKeyword(middle, "struct", "\n /}; >", "\n /{; "))
                {
                    // println("THIS MUST BE A CLASS PRE-DEFINITION");
                    // println(line);

                    hfile += line + '\n';
                }else
                {

                    if(currentlyInClass)
                    {   
                        // println("THIS MUST BE A VARIABLE DEFINITION (INSIDE A CLASS OR A STRUCT)");
                        // println(line);

                        //simply keep the variable as is inside of the .h file, no need to make it show up in the .cpp file (C++ 11)
                        hfile += line + '\n';

                    }else
                    {

                        //if there is an equal in the variable declaration cut it
                        if(li + 1 <= lastEqualIndex && lastEqualIndex <= i)
                        {
                            //li             -> start of the declaration (including all of the weird comments before)
                            //middle         -> start of the declaration (excluding all of the weird comemnts before)
                            //lastEqualIndex -> the index of the equal in the variable declaration
                            //i              -> end of the declaration (includes the ";")

                            //bound check before substr
                            boundCheck(li);
                            boundCheck(middle - 1);

                            //get substring (li to middle)
                            std::string str1 = code.substr(li, (middle - 1) - li + 1);
                        

                            //bound check before substr
                            boundCheck(middle);
                            boundCheck(lastEqualIndex - 1);

                            //get substr (middle to lastEqualIndex)
                            std::string str2 = code.substr(middle, (lastEqualIndex - 1) - middle + 1);


                            //combine strings and put it all inside of the hfile
                            hfile += str1 + "extern " + str2 + ";" + "\n";

                            //combine strings and put it all inside of the cppfile
                            cppfile += line + "\n";

                        //if there was no equal sign within the variable declaration
                        }else
                        {
                            //add extern keyword at the front in .h file and keep .cpp file intact

                            //li             -> start of the declaration (including all of the weird comments before)
                            //middle         -> start of the declaration (excluding all of the weird comemnts before)
                            //lastEqualIndex -> the index of the equal in the variable declaration
                            //i              -> end of the declaration (includes the ";")

                            //bound check before substr
                            boundCheck(li);
                            boundCheck(middle - 1);

                            //get substring (li to middle)
                            std::string str1 = code.substr(li, (middle - 1) - li + 1);
                        
                            //bound check before substr
                            boundCheck(middle);
                            boundCheck(i);

                            //get substr (middle to i)
                            std::string str2 = code.substr(middle, i - middle + 1);

                            // println("THIS MUST BE A VARIABLE DECLARATION");
                            // println(str1,"extern ",str2);

                            //combine strings and put it all inside of the hfile (";" character already included)
                            hfile += str1 + "extern " + str2 + "\n";

                            //combine strings and put it all inside of the cppfile
                            cppfile += line + "\n";
                        }
                    }

                }
            }

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
    
    // println(hfile);

    sethfile(hfile);
    setcppfile(cppfile);
    
    /*
    The goal : 
    - to find all function and variable declarations

    */
}
