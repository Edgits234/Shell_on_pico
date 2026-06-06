

// #define UI_SETTINGS 0b00000001
#include <AwesomeUI.h>
#if WOKWI_SIM
    #define ENABLE_SD_CARD 0
#else
    #define ENABLE_SD_CARD 1
#endif

#if ENABLE_SD_CARD
    //include the SD card library
    #include <SD.h>

    //set an OUTPUT_BIN_SIZE manualy (will be set later based on the size of the file we are reading)
    uint32_t OUTPUT_BIN_SIZE = 0;
#else
    //store bad apple in the flash bcs we don't have access to change sd card in
    #include <bad_apple_frame_buffer.h> //includes OUTPUT_BIN_SIZE
#endif


#define SD_CS_PIN 7

#define WIDTH        320
#define HEIGHT       240
#define BYTES_PER_FRAME (WIDTH * HEIGHT / 8)  // 9600
#define OUTPUT_BIN_FPS 16

// Pinout defaults (see fs.hpp):
//   SD CS   → GP17
//   SD MOSI → GP19  (SPI0 MOSI)
//   SD MISO → GP16  (SPI0 MISO)
//   SD SCK  → GP18  (SPI0 SCK)

// CustomGraphics does not have this feature
// uint16_t lineBuffer[WIDTH];

unsigned long start = 0;

class BadApplePlayer : public UIelement {
public:
    uint8_t frameBuffer[9600];
    double fps = 15;
    long long frameIndex = 0;

    #if ENABLE_SD_CARD
        File frameData;
    #endif

    void update() override {

        unsigned long time = millis() - start;
        fps = (double)(1000) / (double)(time);
        start = millis();

        Point p = absPos();
        
        //open the binary file inside of the Sd card if we are on GIGA
        #if !ENABLE_SD_CARD
            
            //display the frameBuffer into the display
            tft.fillFullScreenBinImage(p.x, p.y, (const uint8_t*)output_bin_data + frameIndex, 1, 1); 

        #else
            
            //go forward in the file to frameIndex (go to the correct frame of the video)
            frameData.seek(frameIndex);
                
            //set the frame buffer to a frame of the video
            frameData.read(frameBuffer, BYTES_PER_FRAME);
            
            //display the frameBuffer into the display
            tft.fillFullScreenBinImage(p.x, p.y, frameBuffer, 1, 1);

        #endif

        //figure out the jump
        int frameJump = round((double)(OUTPUT_BIN_FPS) / (double)(fps));

        //increase by custom fps
        frameIndex += frameJump * BYTES_PER_FRAME;
        
        //if we reached the end of the vid reset it
        if(frameIndex >= OUTPUT_BIN_SIZE)
        {
            //reset frame buffer
            frameIndex = 0;
        }

        //print the output_bin_data array
        // for(int j = 0; j < HEIGHT; j++)
        // {
        //     for(int i = 0; i < WIDTH; i++)
        //     {
        //         int trueIndex = j * WIDTH + i;
        //         uint8_t currByte = pgm_read_byte(output_bin_data + frameIndex + trueIndex / 8);
        //         uint8_t currBit  = currByte & (1 << (trueIndex % 8));
        //         uint16_t colour  = (currBit) ? (rgb(255, 255, 255)) : (rgb(0, 0, 0));
        //
        //         tft.drawPixel(j, i, colour);
        //     }
        // }
         
        
    }

    BadApplePlayer(UI* ui1, const char* id, int x, int y) {

        #if ENABLE_SD_CARD
            //start the SD card, this code assumes there is only one bad apple player            
            if(!SD.begin(SD_CS_PIN))
            {
                ::println(F("ERROR, SD did not begin correctly STOPPING THE PROGRAM!"));
                while(true);
            }
        #endif


        this->ui1        = ui1;
        this->id         = create_string_copy(id);
        this->type       = "BadApplePlayer";
        this->x          = 0;
        this->y          = 0;
        this->w          = WIDTH;
        this->h          = HEIGHT;
        this->selectable = false; // no input needed, its just a video
        this->settings   = 0;


        #if ENABLE_SD_CARD
            //read the file
            frameData = SD.open("output.bin", FILE_READ);

            //check if we were able to read the file
            if(frameData)
            {
                #if !defined(OUTPUT_BIN_SIZE)
                    OUTPUT_BIN_SIZE = frameData.size(); 
                #endif
                
            //did not find frameData
            }else
            {
                //print error message to warn the user
                ::println(F("ERROR, did not find output.bin in SD card"));
            }
        #endif
        
    }

    //default constructor with id only (default values for text)
    BadApplePlayer(UI* currUI, const char* id) : BadApplePlayer(currUI, id, 0, 0){}

    ~BadApplePlayer()
    {
        
        #if ENABLE_SD_CARD
            //close the file after using
            frameData.close();
        #endif

    }
};

void setup() {
    ui.begin();

    Window& win = ui.add<Window>("win");
    win.add<BadApplePlayer>("player");
}

void loop() {
    ui.update();
}



