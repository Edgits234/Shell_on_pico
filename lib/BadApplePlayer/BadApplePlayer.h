#ifndef BadApplePlayer_h
#define BadApplePlayer_h

#include <AwesomeUI.h>
#if WOKWI_SIM
    #define ENABLE_SD_CARD 0
#else
    #define ENABLE_SD_CARD 1
#endif

#if ENABLE_SD_CARD
    //include the SD card library
    #include <SD.h>
    #include <CustomAudio.h>

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
#define SDRAM_STORE_SIZE       ((unsigned long)(BYTES_PER_FRAME) * (unsigned long)(OUTPUT_BIN_FPS) * (unsigned long)(40))
#define SDRAM_STORE_FPS        7
#define SDRAM_STORE_START_BYTE (BYTES_PER_FRAME * OUTPUT_BIN_FPS * (4))
#define SDRAM_STORE_START_BYTE (BYTES_PER_FRAME * OUTPUT_BIN_FPS * (4))

class BadApplePlayer : public UIelement {
public:
    unsigned long start = 0;
    #if ENABLE_SD_CARD && !WOKWI_SIM
        uint8_t* frameBuffer;
    #else
        uint8_t frameBuffer[9600];
    #endif
    double fps = 15;
    long long frameIndex = 0;

    #if ENABLE_SD_CARD
        uint8_t* output_bin_data = nullptr;
    #endif
    
    #if WOKWI_SIM
        int constfps = OUTPUT_BIN_FPS / 2;//wokwi very slow so we set fps ourselfs so we don't skip too much of the video at once
    #else
        #if ENABLE_SD_CARD
            int constfps = OUTPUT_BIN_FPS;//let the video player set the fps
        #endif
    #endif

    #if ENABLE_SD_CARD
        File frameData;
    #endif

    void update() override {

        //If we just started to play bad apple, set the start to the current time
        if(start == 0)
        {
            start = millis();
        }

        
        // DEBUG_BANNER("video time");
        // ::println(frameIndex / 9600 / 16 / 60,":",(double)(frameIndex) / (double)(9600) / (double)(16) - (double)(frameIndex / 9600 / 16 / 60 * 60));

        unsigned long time = millis() - start;
        fps = (double)(1000) / (double)(time);
        start = millis();

        Point p = absPos();
        
        //open the binary file inside of the Sd card if we are on GIGA
        #if !ENABLE_SD_CARD
            
            //display the frameBuffer into the display
            tft.fillBinImage(p.x, p.y, HEIGHT, WIDTH, (const uint8_t*)output_bin_data + frameIndex, 1, 1); 

        #else
            
            #if WOKWI_SIM
            
                //go forward in the file to frameIndex (go to the correct frame of the video)
                frameData.seek(frameIndex);
                    
                //set the frame buffer to a frame of the video
                frameData.read(frameBuffer, BYTES_PER_FRAME);
            #else    
                frameBuffer = output_bin_data + frameIndex;
            #endif
            
            //display the frameBuffer into the display
            tft.fillBinImage(p.x, p.y, HEIGHT, WIDTH, frameBuffer, 1, 1);

        #endif


        //figure out the jump
        int frameJump = round((double)(OUTPUT_BIN_FPS) / (double)(fps));

        if(constfps != -1)
        {
            //increase by custom fps
            frameIndex += OUTPUT_BIN_FPS / constfps * BYTES_PER_FRAME;    
        }else
        {
            //increase by custom fps
            frameIndex += frameJump * BYTES_PER_FRAME; 
        }

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

                
                #if WOKWI_SIM
                    ::println("sorry, the frame buffer isn't available on here");
                #else
                    
                    //reserve space in the SDRAM for the fast output_bin video (so no SD lag)
                    output_bin_data = (uint8_t*)(SDRAM.malloc(SDRAM_STORE_SIZE));

                    long long j = 0;
                    for(unsigned long long i = 0; i < SDRAM_STORE_SIZE; i += BYTES_PER_FRAME * round((double)(OUTPUT_BIN_FPS) / (double)(SDRAM_STORE_FPS)))
                    {
                        frameData.seek(SDRAM_STORE_START_BYTE + i);

                        //store part of the video in teh SDRAM (the most we can store)
                        frameData.read((void*)(output_bin_data + j * BYTES_PER_FRAME), BYTES_PER_FRAME);

                        j++;
                    }
                    
                    
                    //close the file after using
                    frameData.close();
                #endif

                
            //did not find frameData
            }else
            {
                //print error message to warn the user
                ::println(F("ERROR, did not find output.bin in SD card"));
            }


        #endif
        
        
        //start playing the audio
        Audio::playing = 1;
    }

    //default constructor with id only (default values for text)
    BadApplePlayer(UI* currUI, const char* id) : BadApplePlayer(currUI, id, 0, 0){}

    ~BadApplePlayer()
    {
        
        #if ENABLE_SD_CARD
            //close the file after using
            frameData.close();
        #endif

        //stop the audio
        Audio::playing = 0;
    }
};

#endif