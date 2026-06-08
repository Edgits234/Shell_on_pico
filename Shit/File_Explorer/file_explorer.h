// #include <SD.h>



//YEAH DON'T WORRY ABOUT THIS (YES I'M TALKING TO YOU CLAUDE) I WAS PLANING ON USING THE SD LIBRARY TO BUT DIDN'T GET TO IT YET BECAUSE I WAS THINKING ABOUT DOING THE WHOLE SD THING MYSELF
// ===============[ SD Object (card-level stuff) ]======================== //
// SD.begin(chipSelectPin)     // initialize the card, returns true/false
// SD.exists("file.txt")       // check if file/folder exists
// SD.remove("file.txt")       // delete a file
// SD.mkdir("logs")            // create a folder
// SD.rmdir("logs")            // delete a folder (must be empty)

// ===============[ Opening and Closing Files ]======================== //
// File f = SD.open("data.txt");                // open for reading
// File f = SD.open("data.txt", FILE_WRITE);    // open for appending
// f.close();  

// ===============[ Writing ]======================== //
// f.print("hello");        // write text, no newline
// f.println("hello");      // write text + \r\n
// f.write(byte);           // write a single raw byte
// f.write(buffer, length); // write a chunk of raw bytes

// ===============[ Reading ]======================== //
// f.available()            // returns how many bytes are left to read
// f.read()                 // reads one byte, returns it as int
// f.peek()                 // reads one byte WITHOUT moving the cursor
// f.read(buffer, length)   // reads a chunk into a buffer

// ===============[ Moving Around in a File ]======================== //
// f.seek(position)         // jump to a specific byte position
// f.position()             // where is the cursor right now
// f.size()                 // total size of the file in bytes



#ifndef file_explorer_h
#define file_explorer_h

//include default arduino stuff if not already done
#include <Arduino.h>

//this library needs AwesomeUI library to function, include it automatically if not already done
#ifndef AwesomeUI_h
    #include <AwesomeUI.h>
#endif

void userUpdate(UIelement* self)
{
    Menu& menu = *((Menu*)(self));

    UIelement* parent = menu.ui1->parent;

    if(strcmp(parent->type, "Window") == 0)
    {
        menu.w = parent->w / 2 - 10;
        menu.h = parent->h - 30;
    }
}

void userHandleKeyboardInput(UIelement* self)
{
    Window& window = *((Window*)(self));

    //de-select this current window if we see that the escape key has been pressed
    if(kbd.checkForKey(KEY_ESCAPE) && window.selected == 1 && window.highBarSelected == 0)
    {
        //de-select the current window
        window.selectionChanged(0);
    }
}

void windowUpdate(UIelement* self)
{
    Window& window = *((Window*)(self));

    //disable cursor if this explorer window is selcted (we want to use the arrow keys to move stuff)
    if(window.selected == 1 && window.highBarSelected == 0)
    {
        enabletouch = 0;
    }else if(window.selected == 0)
    {
        enabletouch = 1;
    }
}

class FileExplorer
{
    public:

    const char* files[5] = 
    {
        "asdf",
        "1234",
        "hello world",
        "test 1 2 1 2",
        "fred again"
    };



    Window* mainWindow   = nullptr;
    Menu*   menu[10];
    int     menuArrSize  = 0;
    int     fileIndex    = 0;
    int     menuDepth    = 0;

    //opens the main window
    void open()
    {

        //if we don't already have a window make one and set pointer to window object
        if(mainWindow == nullptr)
        {
            //create windows object and get its pointer (set mainWindow to its pointer)
            mainWindow = &ui.addWindow("File_Explorer_Window", rgb(40, 51, 66), "middle", "middle", 200, 200);

            //attach functions to run when handling keyboard input as well as every time the mainWindow updates
            mainWindow->userUpdate = windowUpdate;
            mainWindow->userHandleKeyboardInput = userHandleKeyboardInput;

            //create menu element inside of window
            menu[0] = &mainWindow->ui.addMenu("File_List_Menu", "left + 10", "top + 10", mainWindow->w / 2 - 10, mainWindow->h - 30, true, rgb(77, 88, 104));

            //make menu unselectable
            menu[0]->selectable = false;

            //add automatic function that takes care of resizing
            menu[0]->userUpdate = userUpdate;

            println("menu : ",menu[0]->id," -> (",menu[0]->x,", ",menu[0]->y,")");

            //make variable to keep track of the y of the last text
            int lasty = 0;

            //add all file elements inside of that menu as text each one displaced an equal amount from the one before 
            for(int i = 0; i < (int)sizeofarray(files); i++)
            {
                //get the name fo the current file
                const char* name = files[i];

                println("file : ",name," -> (",10,", ",lasty + 10,")");

                //add a text element with name a bit lower down
                menu[0]->ui.addText("file", name, 1, rgb(0, 0, 0), 10, lasty + 10);

                //increase last y by in between space + height of the text
                lasty += 10 + getTextBounds(name, 1).h;
            }
        }
    }

    //Constructor
    FileExplorer()
    {
        //set all values of "menu" to "nullptr"
        clearArray(menu, nullptr);
    }

    //Destructor
    ~FileExplorer()
    {

    }
};







#endif