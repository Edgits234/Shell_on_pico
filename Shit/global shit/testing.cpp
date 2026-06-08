/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

//usefull pack:
#if true
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
	void printarrayhelper(T array, size_t size)
	{
		for(size_t i = 0; i < size; i++)
		{
			println("[",i,"] = ",array[i]);
		}
	}
	template<typename T>
	void printarrayhelper(T array, size_t size, const char* inBetween)
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
    #define printarray(x) printarrayhelper(x, sizeof(x) / sizeof(x[0]))
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
    #define sizeofarray(x) (sizeof(x)/sizeof(x[0]))
#endif





struct point3d 
{
    float x;
    float y;
    float z;
};

int main()
{

    uint16_t arr[] = {5, 2, 19, 2304, 1092, 2384, 19091, 23, 45, 8, 910};
    int  pos[sizeofarray(arr)] = {5, 2, 19, 2304, 1092, 2384, 19091, 23, 45, 8, 910};//{0, 1, 2}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}, {16, 17, 18}, {19, 20, 21}, {22, 23, 24}, {25, 26, 27}, {28, 29, 30}

    radixSort(arr, sizeofarray(arr), pos);

    printarray(arr);
    println();
    printarray(pos);
}

