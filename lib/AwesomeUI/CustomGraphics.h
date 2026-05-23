#ifndef CustomGraphics_h
#define CustomGraphics_h

#include <Utility.h>

//pins and usefull screen related constants

#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED)
  // Pin assignments for the Pico
  
  #define TFT_MISO_PIN 12 // GP12
  #define TFT_SCK_PIN  10 // GP10
  #define TFT_MOSI_PIN 11 // GP11

  #define CS_PIN   1  // GP1
  #define DC_PIN   6  // GP6
  #define RST_PIN  7  // GP7
  #define BLK_PIN  8  // GP8

  // Custom SPI object for the Pico's Mbed core
//   arduino::MbedSPI custom_spi(0, 3, 2); // Forces MISO=GP0, MOSI=GP3, SCK=GP2
#else
  // Legacy Arduino Mega assignments
  #define DC_PIN  8
  #define CS_PIN  10
  #define RST_PIN 9
  #define BLK_PIN 2
#endif

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

#define FRAMEBUFFER_SIZE SCREEN_WIDTH*SCREEN_HEIGHT*2

#define FONT_WIDTH  5
#define FONT_HEIGHT 6

#define ILI9341_CASET 0x2A
#define ILI9341_PASET 0x2B
#define ILI9341_RAMWR 0x2C

#define SPI_SETTINGS 40000000//8000000

#define TAB_WIDTH 8//max size that is going to be done

// I STOLE THIS FROM TFT_eSPI *MAKING THIS KNOWN OUT THERE*
// Default color definitions
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */

//include spi library for communication
#include <SPI.h>

// Are we running Wokwi simulation? (automatically assigns based on the current board (if its a mega its wokwiSIM))
#ifndef WOKWI_SIM
  #if defined(__AVR_ATmega2560__) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED)
    #define WOKWI_SIM 1
  #elif defined(ARDUINO_GIGA)
    #define WOKWI_SIM 0
  #else
    #warning "ERROR, if you don't have a GIGA or a MEGA board, this library most likely wont work, if you want to try anyways do '#define WOKWI_SIM [0 or 1]' just before including the library"
  #endif
#endif

#if !defined(NORMAL_DRAWING_ORDER)
    //default to normal drawing order
    #define NORMAL_DRAWING_ORDER 1
#endif

#if WOKWI_SIM
    #if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED)

        arduino::MbedSPI pico_wokwi_spi(TFT_MISO_PIN, TFT_MOSI_PIN, TFT_SCK_PIN);

        #define SPI_BUS pico_wokwi_spi 
    #else
        #define SPI_BUS SPI
    #endif

    #if defined(EMULATE_SCREEN)
        //detailed explaination : 
        //go read the explaination a couple lines before this one that explains why the arduino mega cannot have a screen buffer (if your intrested)
        //the screen emulation needs a screen buffer, without it we cannot print the state of the screen in the serial monitor, thats why we can't emulate the screen
        //the only way your going to see is with a screen connected to it
        #warning "IMPORTANT, SCREEN EMULATION ON ARDUINO MEGA CANNOT BE DONE DUE TO INSUFICIENT MEMORY, STRONGLY SUGGESTED THAT YOU GET RID OF THE \"#define EMULATE_SCREEN\" LINE"
    #endif

    #if !NORMAL_DRAWING_ORDER
        //detailed explaination : 
        //the arduino GIGA which is more powerful, also has more memory, because of this, I decided that it would be better to have a screen buffer
        //a screen buffer is something to store the screen, imagine storing the screen you are watching, all in memory, every color of every pixel in memory, thats a screen buffer
        //for optimisation reasons, I decided it would be better to draw front to back, meaning to draw the stuff in front before, meaning they hide everything you do afterwards, this can only be achieved with a screen buffer
        //except the arduino MEGA does not have enough memory to store that giant screen buffer, so on arduino mega we take the shortcut and directly display on the screen, this is slower, but its better than not displaying in the first place so deal with it
        #warning "IMPORTANT, ARDUINO MEGA CANNOT DRAW FRONT TO BACK BECAUSE IT HAS NO SCREEN BUFFER, STRONGLY SUGGESTED THAT YOU INVERT DRAWING ORDER WITH \"#define NORMAL_DRAWING_ORDER\""
    #endif
#else
    #include "SDRAM.h"

    //no longer needed  
    // #define SPI_BUS SPI1
    #define SPI_BUS println(F("YOU FORGOT TO GET RID OF THE SPI_BUS AT LINE "),__LINE__);SPI1

    //buffer instead : 
    // Point directly to SDRAM base + offset to avoid conflicts

    #define SCREEN_BUFFER_SIZE SCREEN_WIDTH*2*SCREEN_HEIGHT
    /*inline*/ uint8_t* screenBuffer = nullptr;
    //we don't need to waste sapce if we don't need the drawn pixel buffer
    #if !NORMAL_DRAWING_ORDER
        /*inline*/ uint8_t  drawnPixel[(240 * 320) / 8];
    #endif

    // Hardware pointer to SPI5 (the actual peripheral pins 11,12,13 use)
    #define SPI5_HW ((SPI_TypeDef *)SPI5_BASE)
#endif

#if !defined(ENABLE_TEXT_BACKTRACKING)
    //text backtracking isn't perfect
    #define ENABLE_TEXT_BACKTRACKING 1
#endif

/*inline*/ void resetDrawnPixel()
{
    //drawnPixel doesn't exist when inverting the drawing order
    #if !NORMAL_DRAWING_ORDER
        #if WOKWI_SIM
            #error add this line before #include <AwesomeUI.h> or #include <CustomGraphics.h>: '#define NORMAL_DRAWING_ORDER', go check warning above for more explaination
        #endif
        for(unsigned int i = 0; i < sizeofarray(drawnPixel); i++)
        {
            drawnPixel[i] = 0;
        }
    #endif
}

//this is sorta a little bit useless ------------------------------------------------------------------------------------------------------------------------
#if WOKWI_SIM
    #define DELAY delay
#else
    #define DELAY delay
#endif

//for indexing the right character
/*inline*/ const char* fontChar = "\x1A""aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890+-.,!?=:/*()'_$<>[]~#;&";

/*this is a very dumb function to let me see differences between stuff that have a different index so I can see if my shit is optimal, it probably doesn't do what you think it does*/
/*inline*/ uint16_t convertNumberToColor(uint8_t number)
{
    number %= 10;   

    switch (number)
    {
        case 0: return TFT_RED;
        case 1: return TFT_ORANGE;
        case 2: return TFT_YELLOW;
        case 3: return TFT_GREENYELLOW;
        case 4: return TFT_GREEN;
        case 5: return TFT_CYAN;
        case 6: return TFT_BLUE;
        case 7: return TFT_PURPLE;
        case 8: return TFT_MAGENTA;
        case 9: return TFT_PINK;
    }

    return 0;
}

//the font
const uint8_t font[] = {0b00000001,0b00010101,0b00010101,0b00010000,0b00000000,0b01110100,0b10100100,0b11110111,0b01000111,0b11110001,0b10001100,0b01100001,0b00001110,0b01001010,0b01001100,0b11110100,0b01111101,0b00011000,0b11111000,0b00000000,0b01110100,0b00100000,0b11100111,0b01000110,0b00010000,0b10001011,0b10000010,0b00010111,0b11000110,0b00101111,0b11110100,0b01100011,0b00011000,0b11111000,0b00001100,0b10010111,0b00100000,0b11101111,0b11000011,0b10010000,0b10000111,0b11000100,0b01000111,0b00010000,0b10000100,0b11111100,0b00111001,0b00001000,0b01000000,0b00001110,0b10001011,0b11000010,0b11100111,0b01000010,0b00010011,0b10001011,0b11100001,0b00001111,0b01000110,0b00110001,0b10001100,0b01111111,0b00011000,0b11000100,0b00000100,0b00000001,0b00001000,0b01000111,0b00010000,0b10000100,0b00100011,0b10001000,0b00000010,0b00010000,0b10001000,0b11111000,0b10000100,0b00101001,0b00110010,0b00010000,0b10100110,0b00101001,0b00101000,0b11001011,0b00010100,0b10010100,0b01001000,0b01000010,0b00010000,0b10000010,0b10000100,0b00100001,0b00001000,0b01111100,0b00000000,0b01010101,0b01101011,0b00011101,0b11010110,0b10110101,0b10101101,0b01000000,0b00001111,0b01000110,0b00110001,0b10001110,0b01101011,0b01011001,0b11000100,0b00000000,0b01110100,0b01100010,0b11100111,0b01000110,0b00110001,0b10001011,0b10000001,0b11101000,0b11111010,0b00010000,0b11110100,0b01100011,0b11101000,0b01000000,0b00001111,0b10001011,0b11000010,0b00010111,0b01000110,0b00110001,0b10011011,0b11000000,0b00000100,0b00111101,0b00001000,0b11110100,0b01111101,0b00011000,0b11000100,0b00000110,0b01000001,0b00000100,0b11000111,0b01000001,0b10000011,0b10001011,0b10001000,0b11100010,0b00010000,0b10000100,0b11111001,0b00001000,0b01000010,0b00010000,0b00000000,0b10001100,0b01100010,0b11111000,0b11000110,0b00110001,0b10001011,0b10000000,0b00001000,0b11000101,0b01000100,0b10001100,0b01100010,0b10100101,0b00010000,0b00000000,0b10101101,0b01101010,0b10101010,0b11010110,0b10110101,0b10101010,0b10000001,0b00011000,0b10111010,0b00110001,0b10001100,0b01011101,0b00011000,0b11000100,0b00010001,0b10001011,0b11000010,0b11101000,0b11000101,0b11000100,0b00100001,0b00000000,0b00001111,0b10001001,0b00011111,0b11111000,0b10001000,0b10001000,0b01111100,0b10001100,0b00100001,0b00001000,0b11100111,0b01000100,0b00101110,0b10000111,0b11011101,0b00010011,0b00000110,0b00101110,0b10010100,0b10111110,0b00100001,0b00001011,0b11110000,0b11110000,0b01100010,0b11100111,0b11000011,0b11010001,0b10001011,0b10111110,0b00010001,0b00010001,0b00001000,0b01110100,0b01011101,0b00011000,0b10111001,0b11010001,0b01111000,0b01000010,0b00010111,0b01000110,0b10110101,0b10001011,0b10000000,0b01000010,0b01111100,0b10000100,0b00000000,0b00000001,0b11110000,0b00000000,0b00000000,0b00000000,0b00000000,0b01000000,0b00000000,0b00000000,0b00100001,0b00001000,0b01000010,0b00010000,0b00000100,0b01110100,0b01000100,0b01000000,0b00010000,0b00000000,0b11111000,0b00111110,0b00000000,0b00010000,0b00000000,0b00100000,0b00000100,0b00100010,0b00010001,0b00001000,0b01010001,0b00010100,0b00000000,0b00000000,0b10001000,0b01000010,0b00010000,0b01000010,0b00001000,0b01000010,0b00010001,0b00001000,0b01000010,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01111100,0b10001110,0b10100011,0b10001010,0b11100000,0b00001000,0b10001000,0b00100000,0b10000000,0b10000010,0b00001000,0b10001000,0b01110010,0b00010000,0b10000100,0b00111001,0b11000010,0b00010000,0b10000100,0b11100000,0b00000001,0b00010101,0b00010000,0b00000000,0b10101111,0b10101011,0b11101010,0b00000001,0b00000000,0b00000010,0b00010001,0b00010100,0b01001011,0b01100100,0b11010000};

/*inline*/ bool fontUnpacker(int i)
{
  int index = i / 8;
  bool output = (font[index] & (1 << (7 - (i % 8)))) != 0;
  return output;
}

/*inline*/ void writeCommand(uint8_t cmd) {
    #if WOKWI_SIM
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);
        SPI_BUS.transfer(cmd);
        digitalWrite(CS_PIN, HIGH);
    #else
        digitalWrite(DC_PIN, LOW);
        digitalWrite(CS_PIN, LOW);
        
        // Manual register transfer
        SPI5_HW->IFCR = 0xFFFFFFFF;
        SPI5_HW->CR2 = 1; // 1 byte
        SPI5_HW->CR1 |= SPI_CR1_CSTART;
        
        while (!(SPI5_HW->SR & SPI_SR_TXP));
        *((volatile uint8_t*)&SPI5_HW->TXDR) = cmd;
        
        while (!(SPI5_HW->SR & SPI_SR_RXP));
        volatile uint8_t dummy = *((volatile uint8_t*)&SPI5_HW->RXDR);
        (void)dummy;
        
        while (!(SPI5_HW->SR & SPI_SR_EOT));
        SPI5_HW->IFCR = SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
        
        digitalWrite(CS_PIN, HIGH);
    #endif
}

/*inline*/ void writeData(uint8_t data) {
    #if WOKWI_SIM
        digitalWrite(DC_PIN, HIGH);
        digitalWrite(CS_PIN, LOW);
        SPI_BUS.transfer(data);
        digitalWrite(CS_PIN, HIGH);
    #else
        digitalWrite(DC_PIN, HIGH);
        digitalWrite(CS_PIN, LOW);
        
        SPI5_HW->IFCR = 0xFFFFFFFF;
        SPI5_HW->CR2 = 1;
        SPI5_HW->CR1 |= SPI_CR1_CSTART;
        
        while (!(SPI5_HW->SR & SPI_SR_TXP));
        *((volatile uint8_t*)&SPI5_HW->TXDR) = data;
        
        while (!(SPI5_HW->SR & SPI_SR_RXP));
        volatile uint8_t dummy = *((volatile uint8_t*)&SPI5_HW->RXDR);
        (void)dummy;
        
        while (!(SPI5_HW->SR & SPI_SR_EOT));
        SPI5_HW->IFCR = SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
        
        digitalWrite(CS_PIN, HIGH);
    #endif
}
// #define writeData println("LINE : ",__LINE__);writeData

#if WOKWI_SIM
    void setWindow(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
        

        int16_t cx1 = max(0, min(240, x1));
        int16_t cy1 = max(0, min(320, y1));
        int16_t cx2 = max(-1, min(239, x2));
        int16_t cy2 = max(-1, min(319, y2));

        #ifndef DISABLE_WARNINGS
            if(cx1 != x1) println(F("WARNING, setWindow clamped x1 ("),x1,F(") to "),cx1);
            if(cy1 != y1) println(F("WARNING, setWindow clamped y1 ("),y1,F(") to "),cy1);
            if(cx2 != x2) println(F("WARNING, setWindow clamped x2 ("),x2,F(") to "),cx2);
            if(cy2 != y2) println(F("WARNING, setWindow clamped y2 ("),y2,F(") to "),cy2);
        #endif

        x1 = cx1;
        y1 = cy1;
        x2 = cx2;
        y2 = cy2;

        if(y2 - y1 + 1 < 0 || x2 - x1 + 1 < 0)
        {
            #ifndef DISABLE_WARNINGS
                Serial.println("WARNING, 0 size setWindow");
            #endif
            
            return;
        }
        
        writeCommand(ILI9341_CASET);
        writeData((uint16_t)cx1 >> 8);
        writeData((uint16_t)cx1 & 0xFF);
        writeData((uint16_t)cx2 >> 8);
        writeData((uint16_t)cx2 & 0xFF);
        
        writeCommand(ILI9341_PASET);
        writeData((uint16_t)cy1 >> 8);
        writeData((uint16_t)cy1 & 0xFF);
        writeData((uint16_t)cy2 >> 8);
        writeData((uint16_t)cy2 & 0xFF);
        
        writeCommand(ILI9341_RAMWR);
    }

    void displayFrameBuffer()
    {
        //doesn't do anything on mega, there is no frame buffer in the first place
    }

#else

    #if defined(EMULATE_SCREEN)

        /*inline*/ void displayFrameBufferSerial() {
            uint8_t* buffer = (uint8_t*)screenBuffer;
            for (uint16_t row = 0; row < 320; row++) {
                udp.beginPacket(computerIP, PORT);
                udp.write((uint8_t*)&row, 2);        // 2 bytes for row index
                udp.write(buffer + row * 480, 480);  // 480 bytes of pixel data
                udp.endPacket();
                delayMicroseconds(500);
            }
        }

    #endif

    /*inline*/ void displayFrameBuffer() {
        
        #if defined(EMULATE_SCREEN)
            displayFrameBufferSerial();
        #endif

        // **DISABLE INTERRUPTS - Critical section**
        // noInterrupts();

        // RESET SPI5 completely before each frame
        SPI5_HW->CR1 &= ~SPI_CR1_SPE; // Disable
        delayMicroseconds(10);
        SPI5_HW->IFCR = 0xFFFFFFFF; // Clear all flags
        SPI5_HW->CR1 |= SPI_CR1_SPE; // Re-enable
        delayMicroseconds(10);
        
        writeCommand(0x2A);
        writeData(0x00); writeData(0x00);
        writeData(0x00); writeData(0xEF);
        
        writeCommand(0x2B);
        writeData(0x00); writeData(0x00);
        writeData(0x01); writeData(0x3F);
        
        writeCommand(0x2C);
        
        digitalWrite(DC_PIN, HIGH);
        digitalWrite(CS_PIN, LOW);
        
        // for(uint32_t i = 0; i < SCREEN_BUFFER_SIZE; i++) {
        //     SPI5_HW->IFCR = 0xFFFFFFFF; // Clear flags EVERY byte
        //     SPI5_HW->CR2 = 1;
        //     SPI5_HW->CR1 |= SPI_CR1_CSTART;
            
        //     while (!(SPI5_HW->SR & SPI_SR_TXP));
        //     *((volatile uint8_t*)&SPI5_HW->TXDR) = screenBuffer[i];
            
        //     while (!(SPI5_HW->SR & SPI_SR_EOT));
        // }

        for(uint32_t i = 0; i < SCREEN_BUFFER_SIZE; i += 2) {
            // Send HIGH byte first, then LOW byte
            uint8_t hi = screenBuffer[i + 1];  // High byte
            uint8_t lo = screenBuffer[i];      // Low byte
            
            // Send HIGH byte
            SPI5_HW->IFCR = 0xFFFFFFFF;
            SPI5_HW->CR2 = 1;
            SPI5_HW->CR1 |= SPI_CR1_CSTART;
            while (!(SPI5_HW->SR & SPI_SR_TXP));
            *((volatile uint8_t*)&SPI5_HW->TXDR) = hi;
            while (!(SPI5_HW->SR & SPI_SR_EOT));
            
            // Send LOW byte
            SPI5_HW->IFCR = 0xFFFFFFFF;
            SPI5_HW->CR2 = 1;
            SPI5_HW->CR1 |= SPI_CR1_CSTART;
            while (!(SPI5_HW->SR & SPI_SR_TXP));
            *((volatile uint8_t*)&SPI5_HW->TXDR) = lo;
            while (!(SPI5_HW->SR & SPI_SR_EOT));
        }
        
        // // **NEW: CRITICAL CLEANUP FOR TOUCH TO WORK**
        // // Wait for the SPI to completely finish
        // // while (SPI5_HW->SR & SPI_SR_BSY);
        // while (SPI5_HW->SR & SPI_SR_EOT) {}  // Wait for End Of Transfer
        // while (!(SPI5_HW->SR & SPI_SR_TXC));  // Wait for TX Complete
                
        // // Clear ALL flags one more time
        // SPI5_HW->IFCR = 0xFFFFFFFF;
        
        // // Deselect display CS
        // digitalWrite(CS_PIN, HIGH);
        
        // // **Give the SPI bus a moment to settle**
        // delayMicroseconds(10);

        // Wait for the SPI to completely finish
        delayMicroseconds(50);  // Give it time to finish

        // Clear ALL flags one more time
        SPI5_HW->IFCR = 0xFFFFFFFF;

        // Deselect display CS
        digitalWrite(CS_PIN, HIGH);

        // Give the SPI bus a moment to settle
        delayMicroseconds(10);

        // **RE-ENABLE INTERRUPTS**
        // interrupts();
    }

    
    
#endif

/*inline*/ Size getTextBounds(const char* text, int16_t fontsize)
{
  unsigned int i = 0;
  int lineLen = 0;
  int maxLineLen = 0;
  int nofnewlines = 1;
  while(text[i] != '\0')
  {
    if(text[i] == '\n')
    {
      nofnewlines += 1;
      lineLen = 0; //reset line length
    }else
    { 
      lineLen += (FONT_WIDTH + 1) * fontsize;//tft.textWidth((const char*)(&text[i]));
    }

    //we get the longest of all of the lines
    if(lineLen > maxLineLen)
    {
      maxLineLen = lineLen;
    }
    

    i++;
  }


  return {(int16_t)(maxLineLen - fontsize), (int16_t)((nofnewlines * (FONT_HEIGHT + 1) - 1) * fontsize)};
}

/*inline*/ Size getTextBounds(String text, int16_t fontsize)
{
    return getTextBounds(text.c_str(), fontsize);
}

//global::TFT
class TFT 
{
    public:
    int16_t vx;
    int16_t vy;
    int16_t vw;
    int16_t vh;
    int16_t gx;
    int16_t gy;
    int16_t cursor_x_start;
    int16_t cursor_y_start;
    int16_t cursor_x;
    int16_t cursor_y;
    int8_t  fontSize;
    uint16_t fontColor;
    Point pencil[150];
    int16_t pencilIndex;
    uint8_t override_char = 0;//are we overriding a character at the moment (used in s_prints when using backspace characters)
    uint8_t special_sequence = 0;//special character sequences, used to capture them (also index for char_sequence)
    char char_sequence[5];//array to store the special character sequence


    //TFT::setBrightness
    /**
     * @brief changes the percieved brightness of the TFT screen
     * @param percent the brightness percentage you want
     */
    void setBrightness(int percent)
    {
        #if defined(BLK_PIN)
        
            analogWrite(BLK_PIN, percent * 255 / 100);

        #else

            ::println(F("couldn't set brightness the Backlight LED Pin (BLK_PIN) wasn't defined (set to something)"));

        #endif
    }

    //TFT::getTextBounds
    Size getTextBounds(const char* text, int16_t fontSize)
    {
        return ::getTextBounds(text, fontSize);
    }

    //TFT::begin
    // begin() stays mostly the same but ensure SPE stays on
    void begin()
    {

        //set backlight pin to output (so you output a voltage)
        pinMode(BLK_PIN, OUTPUT);
        
        //set brightness by default to max (255)
        setBrightness(100);  // full brightness

        #if !WOKWI_SIM
            if(!SDRAM.begin())
            {
                ::println(F("ERROR, could not initialize the SDRAM"));
                while(true);
            }

            Serial.println("Testing SDRAM access...");
            
            screenBuffer = (uint8_t*)SDRAM.malloc(SCREEN_WIDTH * 2 * SCREEN_HEIGHT);

            if(screenBuffer == nullptr)
            {
                ::println(F("ERROR, allocation to SDRAM failed"));
                while(true);
            }else
            {
                ::println(F("SUCCESS, the SDRAM seems to work"));
                for(unsigned int i = 0; i < SCREEN_BUFFER_SIZE; i++)
                {
                    screenBuffer[i] = 0;
                }
            }   
            

            //clear the drawnPixel array (does nothing if we inverted the drawing order)
            resetDrawnPixel();
        #endif

        pinMode(DC_PIN, OUTPUT);
        pinMode(CS_PIN, OUTPUT);
        pinMode(RST_PIN, OUTPUT);
        
        digitalWrite(CS_PIN, HIGH);
        // digitalWrite(DC_PIN, HIGH);
        
        digitalWrite(RST_PIN, LOW);
        DELAY(20);
        digitalWrite(RST_PIN, HIGH);
        DELAY(150);

        // // DYNAMIC REMAPPING (Supported natively by this core)
        // SPI_BUS.setTX(3);   // Explicitly binds MOSI to GP3
        // SPI_BUS.setSCK(2);  // Explicitly binds SCK to GP2
        // SPI_BUS.setRX(0);   // Binds MISO to GP0
        // SPI_BUS.begin();
        
        #if WOKWI_SIM
            // SPI_BUS.setClockDivider(SPI_CLOCK_DIV2);
            SPI_BUS.begin();
        #else
            
            // Let Arduino library init SPI5
            Serial.println("Initializing with SPI1.begin()...");
            SPI1.begin();
            SPI1.beginTransaction(SPISettings(80000000, MSBFIRST, SPI_MODE0)); // FAST!
            
            Serial.println("SPI1.begin() done, checking SPI5 registers...");
            Serial.print("SPI5->CR1:  0x"); Serial.println(SPI5_HW->CR1, HEX);
            Serial.print("SPI5->SR:   0x"); Serial.println(SPI5_HW->SR, HEX);
            Serial.print("SPI5->CFG1: 0x"); Serial.println(SPI5_HW->CFG1, HEX);
            Serial.print("SPI5->CFG2: 0x"); Serial.println(SPI5_HW->CFG2, HEX);
            
            if (!(SPI5_HW->CR1 & SPI_CR1_SPE)) {
                Serial.println("ERROR: SPI5 not enabled!");
                while(1);
            }

            
            Serial.println("SPI5 is ON! Testing register writes...");
        #endif

        writeCommand(0xC1);  // PWCTR2
        writeData(0x10);     // SAP[2:0];BT[3:0]

        // VCOM control
        writeCommand(0xC5);  // VMCTR1
        writeData(0x3e);
        writeData(0x28);
        
        writeCommand(0xC7);  // VMCTR2
        writeData(0x86);
        
        // Memory access control (rotation)
        writeCommand(0x36);  // MADCTL

        // #if WOKWI_SIM
            writeData(0x48);     // MX, BGR (adjust for your screen orientation)
        // #else
        //     ::println("doing thei thing please work for the fucking love of god ");   
        //     writeData(0x08);
        // #endif
        // Pixel format

        
        writeCommand(0x3A);  // PIXFMT
        writeData(0x55);     // 16-bit color (RGB565)
        
        // Frame rate
        writeCommand(0xB1);  // FRMCTR1
        writeData(0x00);
        writeData(0x18);     // 79Hz
        
        // Display function control
        writeCommand(0xB6);  // DFUNCTR
        writeData(0x08);
        writeData(0x82);
        writeData(0x27);
        
        // Gamma settings (optional but recommended)
        writeCommand(0xE0);  // GMCTRP1 (Positive Gamma)
        writeData(0x0F);
        writeData(0x31);
        writeData(0x2B);
        writeData(0x0C);
        writeData(0x0E);
        writeData(0x08);
        writeData(0x4E);
        writeData(0xF1);
        writeData(0x37);
        writeData(0x07);
        writeData(0x10);
        writeData(0x03);
        writeData(0x0E);
        writeData(0x09);
        writeData(0x00);
        
        writeCommand(0xE1);  // GMCTRN1 (Negative Gamma)
        writeData(0x00);
        writeData(0x0E);
        writeData(0x14);
        writeData(0x03);
        writeData(0x11);
        writeData(0x07);
        writeData(0x31);
        writeData(0xC1);
        writeData(0x48);
        writeData(0x08);
        writeData(0x0F);
        writeData(0x0C);
        writeData(0x31);
        writeData(0x36);
        writeData(0x0F);
        
        // Exit sleep and turn on display
        writeCommand(0x11);  // SLPOUT
        DELAY(120);
        
        writeCommand(0x29);  // DISPON (Display ON)
        DELAY(20);
        
        ::println(F("Display init complete!"));
    }

    //TFT::setViewport
    void setViewport(int16_t x, int16_t y, int16_t w, int16_t h)
    {
        w = w + x - 1;
        h = h + y - 1;
    
        x = max( 0, min(240, x));
        y = max( 0, min(320, y));
        w = max(-1, min(239, w));
        h = max(-1, min(319, h));

        w = w - x + 1;
        h = h - y + 1;

        vx = x;
        vy = y;
        vw = w;
        vh = h;
    }

    //TFT::drawPixel
    void drawPixel(int16_t x, int16_t y, uint16_t color) {

        // //update position based on global
        // x += gx;
        // y += gy;

        //if the pixel is not inside of the viewport
        if (x < vx || vx + vw - 1 < x || y < vy || vy + vh - 1 < y) return;

        #if WOKWI_SIM            
            setWindow(x, y, x, y);
            writeData(color >> 8);
            writeData(color & 0xFF);
        #else
            // delay(500);

            #if NORMAL_DRAWING_ORDER
                //draw the pixel in the screen buffer
                *((uint16_t*)(screenBuffer + ((y) * SCREEN_WIDTH * 2) + ((x) * 2))) = color;
            #else
                // calculate the index in the array based on the position of the pixel (assuming that each pixel has a different index and that the array is all of the rows of the screen one after the other starting from top of the screen to the bottom)
                int truei = (x + SCREEN_WIDTH * y);
                
                //index it in the array of bytes (uint8_t) to see if we've already drawn at this place (if yes, don't waste time on drawing it)(if no, draw it and add it to the list)
                if(!(drawnPixel[truei / 8] & (0b1 << (truei % 8))))
                {
                    //draw the pixel in the screen buffer
                    *((uint16_t*)(screenBuffer + ((y) * SCREEN_WIDTH * 2) + ((x) * 2))) = color;
                    
                    //add the pixel to the list of no draws
                    drawnPixel[truei / 8] |= (0b1 << (truei % 8));
                }
            #endif

        #endif
    }

    //TFT::drawPixel
    void drawPixel(Point p, uint16_t color)
    {
        drawPixel(p.x, p.y, color);
    }

    //TFT::drawPixelNoCheck
    void drawPixelNoCheck(int16_t x, int16_t y, uint16_t color) {
        // //update position to be based on global
        // x += gx;
        // y += gy;

        #if WOKWI_SIM            
            setWindow(x, y, x, y);
            writeData(color >> 8);
            writeData(color & 0xFF);
        #else
            *((uint16_t*)(screenBuffer + (y * SCREEN_WIDTH * 2) + (x * 2))) = color;
        #endif
    }

    //TFT::fillRect
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
        
        #if WOKWI_SIM
            //update position to be based on global
            // x += gx;
            // y += gy;
        #endif

        w = w + x - 1;
        h = h + y - 1;
    
        x = max((vx), min((vx + vw), x)); // (vx), (vx + vw)
        y = max((vy), min((vy + vh), y)); // (vy), (vy + vh)
        w = max((vx - 1), min((vx + vw - 1), w)); // (vx - 1), (vx + vw - 1)
        h = max((vy - 1), min((vy + vh - 1), h)); // (vy - 1), (vy + vh - 1)

        w = w - x + 1;
        h = h - y + 1;
        
        //if on mega, then directly transfer the fillRect to the screen
        #if WOKWI_SIM   
            setWindow(x, y, x + w - 1, y + h - 1);
            
            uint32_t totalPixels = (uint32_t)w * (uint32_t)h;
            uint8_t hi = color >> 8;
            uint8_t lo = color & 0xFF;
            
            digitalWrite(CS_PIN, LOW);
            digitalWrite(DC_PIN, HIGH);

            for (uint32_t i = 0; i < totalPixels; i++) {

                SPI_BUS.transfer(hi);
                SPI_BUS.transfer(lo);
            }

            digitalWrite(CS_PIN, HIGH);

        //else, on giga, we have enough space for a screen buffer so write to the screen buffer instead
        #else

            #if NORMAL_DRAWING_ORDER

                for(int i = x; i <= (x + w - 1); i++)
                {
                    for(int j = y; j <= (y + h - 1); j++)
                    {
                        *((uint16_t*)(screenBuffer + ((j) * SCREEN_WIDTH * 2) + ((i) * 2))) = color;
                    }
                }
            #else

                // 1. Calculate how many pixels to draw to get to the first 8-bit boundary
                int startPixels = (8 - (x % 8)) % 8;
                if (startPixels > w) startPixels = w; 

                // 2. Calculate how many FULL 8-pixel blocks are in the middle
                int middlePacks = (w - startPixels) / 8;

                // 3. Calculate how many pixels are left over at the end
                int endPixels = (w - startPixels) % 8;

                for (int j = 0; j < h; j++) {
                    int current_y = y + j;
                    // int drawnIdxBase = (x + y * SCREEN_WIDTH) / 8; // Example base index

                    // --- PART 1: THE START (Slow bits) ---
                    for (int i = 0; i < startPixels; i++) {
                        drawPixel(x + i, current_y, color);
                    }

                    // --- PART 2: THE MIDDLE (The "Speed Demon" Section) ---
                    // Calculate the starting byte index for this row
                    int byteIdx = (x + startPixels + (current_y * SCREEN_WIDTH)) / 8;

                    for (int l = 0; l < middlePacks; l++) {
                        uint8_t& status = drawnPixel[byteIdx + l];

                        if (status == 0x00) { // ALL EMPTY
                            // The compiler will likely "unroll" this into a single SDRAM burst!
                            for (int i = 0; i < 8; i++) {
                                drawPixelNoCheck(x + startPixels + l * 8 + i, current_y, color);
                            }
                            status = 0xFF; // Mark all 8 as drawn
                        } 
                        else if (status != 0xFF) { // SOME EMPTY
                            for (int i = 0; i < 8; i++) {
                                drawPixel(x + startPixels + l * 8 + i, current_y, color);
                            }
                        }
                        // If status == 0xFF, we do NOTHING. We just skip 8 pixels in 1 cycle!
                    }

                    // --- PART 3: THE END (Remaining bits) ---
                    int endX = x + startPixels + (middlePacks * 8);
                    for (int i = 0; i < endPixels; i++) {
                        drawPixel(endX + i, current_y, color);
                    }
                }



                // //go through every possibilities of the rectangles
                // for(int i = 0 ; i < w; i++)
                // {
                //     for(int j = 0; j < h; j++)
                //     {
                //         //draw the pixel at the coordinates
                //         drawPixel(x + i, y + j, color);
                //     }
                // }
            #endif
        #endif
    }


    void testfillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
        
        #if WOKWI_SIM
            //update position to be based on global
            // x += gx;
            // y += gy;
        #endif

        w = w + x - 1;
        h = h + y - 1;
    
        x = max((vx), min((vx + vw), x)); // (vx), (vx + vw)
        y = max((vy), min((vy + vh), y)); // (vy), (vy + vh)
        w = max((vx - 1), min((vx + vw - 1), w)); // (vx - 1), (vx + vw - 1)
        h = max((vy - 1), min((vy + vh - 1), h)); // (vy - 1), (vy + vh - 1)

        w = w - x + 1;
        h = h - y + 1;
        
        //if on mega, then directly transfer the fillRect to the screen
        #if WOKWI_SIM   
            setWindow(x, y, x + w - 1, y + h - 1);
            
            uint32_t totalPixels = (uint32_t)w * (uint32_t)h;
            uint8_t hi = color >> 8;
            uint8_t lo = color & 0xFF;
            
            digitalWrite(CS_PIN, LOW);
            digitalWrite(DC_PIN, HIGH);

            for (uint32_t i = 0; i < totalPixels; i++) {

                SPI_BUS.transfer(hi);
                SPI_BUS.transfer(lo);
            }

            digitalWrite(CS_PIN, HIGH);

        //else, on giga, we have enough space for a screen buffer so write to the screen buffer instead
        #else

            for(int j = 0; j < h; j++)
            {
                for(int i = 0; i < w; i++)
                {
                    drawPixelNoCheck(x + i, y + j, color);
                }
            }

            // //go through every possibilities of the rectangles
            // for(int i = 0 ; i < w; i++)
            // {
            //     for(int j = 0; j < h; j++)
            //     {
            //         //draw the pixel at the coordinates
            //         drawPixel(x + i, y + j, color);
            //     }
            // }
        #endif
    }

    //TFT::fillScreen
    void fillScreen(uint16_t colour)
    {
        fillRect(vx, vy, vw, vh, colour);
    }

    //TFT::clearScreen
    void clearScreen()
    {
        fillScreen(0);
    }

    //TFT::drawRect
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t colour)
    {
        //big switch (when the b is x, big switch switches between left and right, when b is y, it switches up and down
        for(int a = 0; a <= 1; a += 1)
        {
            //x and y switch
            for(int b = 0; b <= 1; b += 1)
            {
                // setWindow(x + ((b)?(0):(((a)?(w - 1):(0)))), y + ((b)?(((a)?(h - 1):(0))):(0)), x + ((b)?(w - 1):(((a)?(w - 1):(0)))), y + ((b)?(((a)?(h - 1):(0))):(h - 1)));

                fillRect(x + ((b)?(0):(((a)?(w - 1):(0)))),
                         y + ((b)?(((a)?(h - 1):(0))):(0)),
                         x + ((b)?(w - 1):(((a)?(w - 1):(0)))) - (x + ((b)?(0):(((a)?(w - 1):(0))))) + 1,
                         y + ((b)?(((a)?(h - 1):(0))):(h - 1)) - (y + ((b)?(((a)?(h - 1):(0))):(0))) + 1,
                         colour);

                // uint8_t hi = colour >> 8;
                // uint8_t lo = colour & 0xFF;
                
                // digitalWrite(DC_PIN, HIGH);
                // digitalWrite(CS_PIN, LOW);

                // for (int i = 0; i < ((b)?(w):(h)); i++) {
                //     SPI_BUS.transfer(hi);//BE CAREFULL' WON'T WORK ON GIGA (NO TRANSACTIONS)
                //     SPI_BUS.transfer(lo);
                // }
                // digitalWrite(CS_PIN, HIGH);
            }
        }
    }

    //TFT::drawChar
    void drawChar(char c, int16_t x, int16_t y, int16_t si, uint16_t colour)
    {
        //return if the character is space (we don't need to draw space) (or carriage return, we don't allow for carriage returns, or well we could... but it would draw characters on top of characters)
        if(c == '\r')
        {
            return;
        }

        //are we overriding a character (going back, using backspace or smth)
        if(override_char > 0)
        {
            //decrease override_char to indicate we override a character (backspace for example increases override, so it only overrides previous characters)
            override_char--;

            //print a square (override) previous character
            fillRect(x, y, FONT_WIDTH * si, FONT_HEIGHT * si, 0);
        }

        if(c == ' ' || c == '\t' )
        {
            return;
        }

        if(c == '\b')
        {
            println("ERROR, ",__LINE__," in ",__FILE__,", not supposed to be drawing a \b (backspace) character (supposed to be handled by s_print)");
        }

        int charIndex = -1;
        for (int i = 0; (int unsigned)i < strlen(fontChar); i++)
        {
            if(fontChar[i] == c)
            {
                charIndex = i;
                break;
            }
        }

        //si ont a pas trouvé le charactère (c)
        if (charIndex == -1)
        {
            Serial.print("ERROR, couldn't find the character : '"); Serial.print(c); Serial.print("' -> "); Serial.println((uint8_t)c);
            // DELAY(1000);
            charIndex = 0;//put the "unknown" character

            // return;
        }

        //iChar c'est l'index de la lettre. (A,B,C, etc...)
        for (int iChar = charIndex; iChar < 1 + charIndex; iChar ++) //ont rajoute charIndex pour modifier où ont itère (trust sa marche)
        {
            //itération de la position y de la lettre
            for (int posY = 0; posY < 6 * si; posY += si) //ont ajoute la position pour déplacé la lettre
            {
            //itération de la position x de la lettre
            for (int posX = 0; posX < 5 * si; posX += si)
            {
                //ont vas déterminé l'index qu'il faut pour déterminé l'index dans la variables font
                int trueIndex = iChar * 5 * 6 + posY / si * 5 + posX / si;

                if (fontUnpacker(trueIndex))
                {
                    fillRect((uint16_t)(posX + x), (uint16_t)(posY + y), (uint16_t)(si), (uint16_t)(si), colour);
                }
            }
            }
        }
    }

    //TFT::setCursor
    void setCursor(int16_t cursor_x, int16_t cursor_y)
    {
        this->cursor_x  = cursor_x;
        this->cursor_y  = cursor_y;
    }

    //TFT::setCursor
    void setCursor(int16_t cursor_x, int16_t cursor_y, int8_t fontSize, uint16_t fontColor)
    {
        this->cursor_x  = cursor_x;
        this->cursor_y  = cursor_y;
        this->fontSize  = fontSize;
        this->fontColor = fontColor;
    }

    //TFT::setCursor
    void setCursor(int16_t cursor_x, int16_t cursor_y, int8_t fontSize, uint16_t fontColor, int16_t cursor_x_start)
    {
        this->cursor_x = cursor_x;
        this->cursor_y = cursor_y;
        this->fontSize = fontSize;
        this->fontColor = fontColor;
        this->cursor_x_start = cursor_x_start;
    }

    
    //TFT::print
    void s_print(char c)
    {
        if(special_sequence != 255)
        {
            //set current char_sequence character and increase index
            char_sequence[special_sequence] = c;
            special_sequence++;
            
            //if we see a letter, then its the end of the special sequence and we should print its output
            if(ISLETTER(c))
            {
                //set last character to \0 (emulate a normal string)
                char_sequence[special_sequence] = '\0';

                //set to 255 indicating that we are no longer inside of a special sequence
                special_sequence = 255;

                //print based on the special sequence : 
                char* cs = char_sequence;//short for char_sequence, make code more readable, same as if I was using char_sequence

                //clear screen
                if(checkstr(cs, "\033[2J", 0, nullptr))
                {
                    //clear all possible characters at the same time (with a big black square)
                    fillRect(cursor_x_start, cursor_y_start, SCREEN_WIDTH - 1, cursor_y - cursor_y_start, 0);

                //text color red
                }else if(checkstr(cs, "\033[31m", 0, nullptr))
                {
                    fontColor = TFT_RED;

                //text color yellow
                }else if(checkstr(cs, "\033[33m", 0, nullptr))
                {
                    fontColor = TFT_YELLOW;

                //text color white
                }else if(checkstr(cs, "\033[37m", 0, nullptr))
                {
                    fontColor = TFT_WHITE;

                //left arrow
                }else if(checkstr(cs, "\033[D", 0, nullptr))
                {
                    s_print('\b');//simulate backspace character (it does the same thing)

                //cursor home
                }else if(checkstr(cs, "\033[H", 0, nullptr))
                {
                    cursor_x = cursor_x_start;
                    cursor_y = cursor_y_start;
                }
            }

            //early return, we don't want to print the code
            return;
        }

        if(c == '\033')
        {
            //SPECIAL CHARACTER SEQUENCE
            special_sequence = 0;

            //set current char_sequence character and increase index
            char_sequence[special_sequence] = c;
            special_sequence++;

        }else if(c == '\n')
        {
            cursor_y += (FONT_HEIGHT + 1) * fontSize;//step the cursor_y down (since new line)
            cursor_x = cursor_x_start;//reset x
            
        }else if(c == '\b')
        {
            //if we specifically enabled the quirky backtracking feature
            #if ENABLE_TEXT_BACKTRACKING
                //only do backslash if we aren't gone past the cursor_x_start
                if(cursor_x > cursor_x_start)
                {
                    //decrease the cursor x (move cursor to the left one character)
                    cursor_x -= (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character

                    //increase override (keeps track of previous overrides)
                    override_char++;
                }
            #endif

        }else
        {
            //draw the character
            drawChar(c, cursor_x, cursor_y, fontSize, fontColor);

            cursor_x += (FONT_WIDTH + 1) * fontSize;//step cursor_x for next character
        }
    }

    //TFT::print
    void s_print(const char* s, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        if(s == nullptr)
        {
            Serial.print("ERROR line ");Serial.print(line);Serial.print(" in ");Serial.print(file);Serial.println(" in function print, the string inputed in the function did not point to a valid place in memory (it was a nullptr)");
            return;
        }

        //iterate through all of the string
        int i = 0;
        while(s[i] != '\0')
        {
            //use single character s_print for short (does the same thing)
            s_print(s[i]);

            i++;
        }
    }

    //TFT::print
    void s_print(String s, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        s_print(s.c_str(), line, file);
    }

    //TFT::print
    void s_print(long long n)
    {
        //if negative, draw "-" minus sign in front and revert to positive
        if(n < 0)
        {
            //print a minus sign
            s_print('-');

            //revert back to normal
            n = -n;
        }

        //use other print function to print the rest
       return  s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(unsigned long long n)
    {
        //special case for 0 (as it doesn't work with current logic)
        if(n == 0)
        {
            //print zero
            s_print('0');

            return;//return, handled zero
        }

        int nlength = 0;//length of the number
        {
            long long n2 = n;//copy n
            while(0 < n2)
            {
                //everytime that there is a new number we get rid of it and add to the counter of numbers we have
                n2 /= 10;
                nlength += 1;
            }
        }

        //we will go through all of the digits of the number, starting from the left (the biggest digits, to the smallest)
        while(nlength > 0)
        {
            //convert the number into a character
            char converted = '0' +  getDigits(n, nlength);

            //print number
            s_print(converted);

            //update our index, which is nlength
            nlength -= 1;
        }
    }

    //TFT::print
    void s_print(long n)
    {
        s_print((long long)(n));
    }

    //TFT::print
    void s_print(unsigned long n)
    {
        s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(int n)
    {
        s_print((long long)(n));
    }

    //TFT::print
    void s_print(unsigned int n)
    {
        s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(unsigned char n)
    {
        s_print((unsigned long long)(n));
    }

    //TFT::print
    void s_print(double d, int precision = -1)
    {
        if(precision == -1)
        {
            int last_accurate_decimal_digit = getSmallestPreciseDecimalExponent(d);
            
            precision = MAX(0, -last_accurate_decimal_digit - 1);
        }

        //convert double long long
        long long n = d * powi(10, precision);//convert double to long long

        //print the first party of the numbe (without the decimals)
        s_print((long long)(d));
        
        //get rid of negative (doesn't matter anymore since we already printed it with first s_print call)
        n = ABS(n);

        //calculate reverse length (how many decimals to print)
        //start from higher signifcant to lower significant
        int nlength = 0;
        for(int i = precision; i >= 1; i--)
        {
            //get digit at index i
            int digit = getDigits(n, i);      
            
            if(digit != 0)
            {
                nlength = precision - i + 1;
            }
        }

        //print the "." if we have length bigger then 0 (0 means there are no decimals)
        if(nlength > 0)
        {
            //print a dot '.'
            s_print('.');

            //draw decmials from left to right (most significant to less significant)
            for(int i = precision; i >= precision - nlength + 1; i--)
            {
                //get decimal digit
                int digit = getDigits(n, i);

                //convert digit into a character
                char converted = '0' + digit;

                //print the number
                s_print(converted);
            }
        }
    }

    void print(){}

    template<typename T> 
    void print(T input){s_print(input);}

    template<typename T, typename... Args>
    void print(T input, Args... other){s_print(input); print(other...);}

    void println(){s_print('\n');}

    template<typename T>
    void println(T input){s_print(input); s_print('\n');}

    template<typename T, typename... Args>
    void println(T input, Args... other){s_print(input); println(other...);}


    //TFT::drawText
    void drawText(const char* s, int16_t x, int16_t y, int16_t si, uint16_t colour, bool wrapText)
    {
        int i = 0;
        int displacement = 0;
        while((unsigned int)i < strlen(s))
        {
            char sChar = s[i];
            if(sChar == '\n')
            {
                y += si * 7;//move the text down one line
                displacement = -(i + 1);
                
            }else if(sChar != ' ')//if its not a space
            {
                drawChar(sChar, x + i * 6 * si + displacement * 6 * si, y, si, colour);
            }

            if(sChar != '\n')
            {
                if((SCREEN_WIDTH - 1 < (x + i * 6 * si + displacement * 6 * si) + (FONT_WIDTH + 1) * si) && wrapText)
                {
                    //simulate a new line
                    y += si * 7;//move the text down one line
                    displacement = -(i + 1); 
                }
            }
            
            i++;
        }
    }

    //TFT::drawText
    void drawText(const char* s, int16_t x, int16_t y, int16_t si, uint16_t colour)
    {
        drawText(s, x, y, si, colour, 0);
    }

    //TFT::drawText
    void drawText(String s, int16_t x, int16_t y, int16_t si, uint16_t colour)
    {
        drawText(s.c_str(), x, y ,si, colour, 0);
    }
    //TFT::drawText
    void drawText(String s, int16_t x, int16_t y, int16_t si, uint16_t colour, bool wrapText)
    {
        drawText(s.c_str(), x, y ,si, colour, wrapText);
    }

    //TFT::drawLine
    void drawLine(double x1, double y1, double x2, double y2, uint16_t colour)
    {
        fillTriangle(round(x1), round(y1), round(x2), round(y2), round(x2), round(y2), colour);
        return;
        ((x1)>(x2)?(x1):(x2)) += 1;
        ((y1)>(y2)?(y1):(y2)) += 1;

        //get the rule of the line (y = ax + b)
        double a = (y2 - y1) / (x2 - x1);
        double b = y1 - a * x1;

        //get the total width and height for later iteration
        int w = abs((int)(x2 - x1));
        int h = abs((int)(y2 - y1));

        //iterate either over the height (if the line is more horizontal) or wdith (if its more vertical)
        for(int i = 0; i < ((-1 <= a && a <= 1)?(h):(w)); i++)
        {
            uint16_t x3;
            uint16_t y3;
            uint16_t w3;
            uint16_t h3;

            //if line is more horizontal we get the horizontal blocks
            if(-1 <= a && a <= 1)
            {
                double y     = (min((int)y1,(int)y2) + i);
                double x     = (y2 == y1)?(x1):((y - b) / a);
                double nexty = (min((int)y1,(int)y2) + i + 1);
                double nextx = (y2 == y1)?(x1):((nexty - b) / a);

                int width  = (int)ceil(max(nextx, x)) - (int)floor(min(nextx, x));
                int xstart = floor(min(nextx, x));

                // x3 = clamp16(xstart);
                // y3 = clamp16(y);
                // x4 = clamp16(xstart + width);
                // y4 = clamp16(y);
                x3 = clamp16(xstart);
                y3 = clamp16(y);
                w3 = clamp16(width);
                h3 = clamp16(1);

                // nOfPixels = width;
            }else
            {
                double x     = (min((int)x1,(int)x2) + i);
                double y     = (x2 == x1)?(y1):(a * x + b);
                double nextx = (min((int)x1,(int)x2) + i + 1);
                double nexty = (x2 == x1)?(y1):(a * nextx + b);

                int height  = (int)ceil(max(nexty, y)) - (int)floor(min(nexty, y));
                int ystart = floor(min(nexty, y));

                // x3 = clamp16(x);
                // y3 = clamp16(ystart);
                // x4 = clamp16(x);
                // y4 = clamp16(ystart + height);
                x3 = clamp16(x);
                y3 = clamp16(ystart);
                w3 = clamp16(1);
                h3 = clamp16(height);

                // nOfPixels = height;
            }


            fillRect(x3, y3, w3, h3, colour);
            // setWindow(x3, y3, x4, y4);

            // uint8_t hi = colour >> 8;
            // uint8_t lo = colour &  0xFF;

            // digitalWrite(DC_PIN, HIGH);
            // digitalWrite(CS_PIN, LOW);

            // for(int k = 0; k < nOfPixels; k++)
            // {
            //     SPI_BUS.transfer(hi);//WON'T WORK ON GIGA, NO TRANSACTIONS
            //     SPI_BUS.transfer(lo);
            // }
            
            // digitalWrite(CS_PIN, HIGH);
        }

    }

    //TFT::drawLine
    void drawLine(Point p1, Point p2, uint16_t colour){drawLine(p1.x, p1.y, p2.x, p2.y, colour);}

    //TFT::drawOctantOfCircle
    void drawOctantOfCircle(int octant, double x, double y, double r, uint16_t colour)
    {
        if(0 <= octant && octant <= 7)
        {
            bool b  = !((bool)(octant & 0b00000010));
            int  c  = (b != ((bool)(octant & 0b00000100))) * 2 - 1;
            int  a  = ((bool)(octant & 0b00000100) != (bool)(octant & 0b00000001)) * 2 - 1;

            //a is for small switch
            //b is for switching x and y axis
            //c is for big switch

            double distance = (r / sqrt(2.0));
            double s = r - distance;

            for(int i = 0; i < (int)ceil(s) + 1; i++)
            {
                // uint16_t x1;
                // uint16_t y1;
                // uint16_t x2;
                // uint16_t y2;
                int nOfPixels;

                if(b)
                {
                    double ya     = y + c * (-r + i - 0.5);
                    double xa     = a * sqrt(pow(r, 2.0) - pow(ya - y, 2.0)) + x;
                    double nextya = y + c * (-r + i + 0.5);
                    double nextxa = a * sqrt(pow(r, 2.0) - pow(nextya - y, 2.0)) + x;

                    //check for nan 
                    if(xa != xa)
                    {
                        xa = x;
                    }

                    //check for nan
                    if(nextxa != nextxa)
                    {
                        nextxa = x;
                    }

                    println1(ya, xa, nextya, nextxa);

                    int xstart = floor(min(nextxa, xa));
                    int width  = ceil(max(nextxa, xa)) - xstart;

                    // x1 = clamp16(xstart);
                    // y1 = clamp16(ya);
                    // x2 = clamp16(xstart + width);
                    // y2 = clamp16(ya);

                    nOfPixels = width;
                }else
                {
                    double xa     = x + c * (-r + i);
                    double ya     = a * sqrt(pow(r, 2.0) - pow(xa - x, 2.0)) + y;
                    double nextxa = x + c * (-r + i + 1);
                    double nextya = a * sqrt(pow(r, 2.0) - pow(nextxa - x, 2.0)) + y;

                    //check for nan
                    if(ya != ya)
                    {
                        ya = 0.0;
                    }

                    //check for nan
                    if(nextya != nextya)
                    {
                        nextya = 0.0;
                    }

                    int ystart = floor(min(nextya, ya));
                    int height = ceil(max(nextya, ya)) - ystart;

                    // x1 = clamp16(xa);// - ((c<0)?(1):(0)));
                    // y1 = clamp16(ystart);
                    // x2 = clamp16(xa);
                    // y2 = clamp16(ystart + height);

                    nOfPixels = height;
                }

                #if !WOKWI_SIM
                    SPI_BUS.beginTransaction(SPISettings(SPI_SETTINGS, MSBFIRST, SPI_MODE0));
                #endif

                digitalWrite(CS_PIN, LOW);

                // setWindow(x1, y1, x2, y2);

                uint8_t hi = colour >> 8;
                uint8_t lo = colour &  0xFF;

                digitalWrite(DC_PIN, HIGH);

                for(int k = 0; k < nOfPixels; k++)
                {

                    SPI_BUS.transfer(hi);
                    SPI_BUS.transfer(lo);

                }
                
                digitalWrite(CS_PIN, HIGH);

                #if !WOKWI_SIM
                    SPI_BUS.endTransaction();
                #endif
            }
        }else

        {
            ::println(F("ERROR, drawOctantCircle recieved '"),octant,F("' but the range of possible octants are from 0 to 7 (this makes for 8 possiblilities because there are 8 octants in a circle)"));
        }
    }

    //TFT::drawCircle
    void drawCircle(double x, double y, double r, uint16_t colour)
    {
        ::println(F("ACCESS DENIED"));
        return;

        //normal  : (sqrt(pow(r, 2.0) - pow(x - a, 2.0)) + b );
        //inverse : sqrt(pow(r, 2.0) - pow(y - b, 2.0)) + a ;

        //draw circle in 8 parts
        for(int i = 0; i < 8; i++)
        {
            drawOctantOfCircle(i, x, y, r, colour);
        }
    }

    //TFT::fillCircle
    void fillCircle(double x, double y, double r, uint16_t colour)
    {
        int totalheight = (int)ceil(y + r) - (int)floor(y - r);
        for(int i = 0; i <= totalheight; i++)
        {
            //normal  : (sqrt(pow(r, 2.0) - pow(x - a, 2.0)) + b );
            //inverse : sqrt(pow(r, 2.0) - pow(y - b, 2.0)) + a ;

            int startY = ((int)floor(y - r) + i);
            double funcStart1 = sqrt(pow(r, 2.0) - pow(((y - r + i) - 0.5) - y, 2.0));
            double funcStart2 = sqrt(pow(r, 2.0) - pow(((y - r + i) + 0.5) - y, 2.0));

            //check if funcStart1 is Nan and set it to 0 if it is
            if(funcStart1 != funcStart1)
            {
                funcStart1 = 0.0;
            }

            //check if funcStart2 is Nan and set it to 0 if it is
            if(funcStart2 != funcStart2)
            {
                funcStart2 = 0.0;
            }
            
            int startX = floor(min(x - funcStart1, x - funcStart2));
            int width  = ceil(max(x + funcStart1, x + funcStart2)) - startX + 1;

            fillRect(clamp16(startX), clamp16(startY), clamp16(width), clamp16(startY), colour);
        }
    }

    //TFT::drawTriangle
    void drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour)
    {
        //simply draw lines between all of the points
        drawLine(x1, y1, x2, y2, colour);
        drawLine(x1, y1, x3, y3, colour);
        drawLine(x2, y2, x3, y3, colour);
    }

    //TFT::drawTriangle
    void drawTriangle(Point p1, Point p2, Point p3, uint16_t colour)
    {
        drawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, colour);
    }

    //TFT::oldfillTriangle
    void oldfillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        
        // debug triangle
        // drawTriangle(x1, y1, x2, y2, x3, y3, color(255, 0, 0));

        //classify all of the x and y coordinates highest to lowest y
        {
            int16_t y[3];
            int16_t x[3];

            y[0] = y1;
            y[1] = y2;
            y[2] = y3;
            x[0] = x1;
            x[1] = x2;
            x[2] = x3;

            //find the lowest of the numbers
            int16_t best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                println(F("ERROR line "),line,F(" in "),file,F(", could not find the lowest number"));
            }

            y1 = y[best_i];//set smallest number
            x1 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                println(F("ERROR line "),line,F(" in "),file,F(", could not find the lowest number"));
            }

            y2 = y[best_i];//set smallest number
            x2 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                println(F("ERROR line "),line,F(" in "),file,F(", could not find the lowest number"));
            }

            y3 = y[best_i];//set smallest number
            x3 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            if(x1 == INT16_MAX || x2 == INT16_MAX || x3 == INT16_MAX || y1 == INT16_MAX || y2 == INT16_MAX || y3 == INT16_MAX){println(F("ERROR line "),line,F(" in "),file,F(", was not able to sort the coordinates given in a correct order (had INT16_MIN in numbers)"));}
        }


        //1 and 2
        float a1 = (float)(y1 - y2) / (float)(x1 - x2);
        float b1 = (float)y1 - a1 * (float)x1;


        //1 and 3
        float a2 = (float)(y1 - y3) / (float)(x1 - x3);
        float b2 = (float)y1 - a2 * (float)x1;


        //2 and 3
        float a3 = (float)(y2 - y3) / (float)(x2 - x3);
        float b3 = (float)y2 - a3 * (float)x2;


        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        float xs = (x2==x3)?(x2):(y3 - b3) / a3;
        float xe = (x1==x3)?(x1):(y3 - b2) / a2;

        //get the increment for those lines
        float xis = (x2==x3)?(0):1 / a3;
        float xie = (x1==x3)?(0):1 / a2;

        //go through all of the lines one by one top to bottom until we reach the middle
        for(float i = y3; i > y2; i--)
        { 
            //if numbers are both not nan then we draw because normal numbers
            if(xs == xs && xe == xe)
            {
                //draw the line of the triangle
                fillRect(roundf(MIN(xs, xe)), i, roundf(MAX(xs, xe)) - roundf(MIN(xs, xe)) + 1, 1, colour);
            }
            
            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }


        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        xs = (x1==x3)?(x1):(y2 - b2) / a2;
        xe = (x1==x2)?(x1):(y2 - b1) / a1;

        //get the increment for those lines
        xis = (x1==x3)?(0):1 / a2;
        xie = (x1==x2)?(0):1 / a1;

        //go through all of the lines one by one middle to the bottom
        for(float i = y2; i >= y1; i--)
        {
            //if numbers are both not nan then we draw because normal numbers
            if(xs == xs && xe == xe)
            {
                //draw the line of the triangle
                fillRect(roundf(MIN(xs, xe)), i, roundf(MAX(xs, xe)) - roundf(MIN(xs, xe)) + 1, 1, colour);
            }

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }
    }

    //TFT::fillTriangle
    void fillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        //draw horizontal degenerate triangles first, (they fuck up our logic)
        if(y1 == y2 && y1 == y3 && y2 == y3)
        {
            double x_min = MIN(MIN(x1, x2), x3);
            double x_max = MAX(MAX(x1, x2), x3);

            //get lowest x possible (floored)
            int l_x = FLOOR(x_min + 0.5f);

            //get the highest x possible (ceilling)
            int h_x = CEIL(x_max - 0.5f);

            fillRect(l_x, y1, h_x - l_x + 1, 1, colour);

            return;
        }
        
        //classify all of the coordiantes by their y values
        {
            //temporary variables
            int16_t t_x1 = x1;
            int16_t t_y1 = y1;
            int16_t t_x2 = x2;
            int16_t t_y2 = y2;
            int16_t t_x3 = x3;
            int16_t t_y3 = y3;

            //if 1 is smaller than all other
            if(y1 <= y2 && y1 <= y3)
            {
                // t_x1 = x1; //no need to change 
                // t_y1 = y1; //no need to change 

                //if 2 is smaller than rest
                if(y2 <= y3)
                {
                    // t_x2 = x2; //no need to change 
                    // t_y2 = y2; //no need to change 

                    // t_x3 = x3; //no need to change 
                    // t_y3 = y3; //no need to change

                //if 3 smaller than rest
                }else
                {
                    t_x2 = x3;
                    t_y2 = y3;

                    t_x3 = x2;
                    t_y3 = y2;
                }

            //if 2 is smaller than all other
            }else if(y2 <= y1 && y2 <= y3)
            {
                t_x1 = x2;
                t_y1 = y2;

                //if 1 is smaller than rest
                if(y1 <= y3)
                {
                    t_x2 = x1;
                    t_y2 = y1;

                    // t_x3 = x3; //no need to change 
                    // t_y3 = y3; //no need to change

                //if 3 smaller than rest
                }else
                {
                    t_x2 = x3;
                    t_y2 = y3;

                    t_x3 = x1;
                    t_y3 = y1;
                }
                
            //if 3 is smaller than all other
            }else if(y3 <= y1 && y3 <= y2)
            {
                t_x1 = x3;
                t_y1 = y3;
                
                //if 1 is smaller than rest
                if(y1 <= y2)
                {
                    t_x2 = x1;
                    t_y2 = y1;

                    t_x3 = x2;
                    t_y3 = y2;

                //if 2 smaller than rest
                }else
                {
                    // t_x2 = x2; //no need to change 
                    // t_y2 = y2; //no need to change 

                    t_x3 = x1;
                    t_y3 = y1;
                }
            }
        
            //set real variables to temporary
            x1 = t_x1;
            y1 = t_y1;
            x2 = t_x2;
            y2 = t_y2;
            x3 = t_x3;
            y3 = t_y3;
        }

        //slope and initial value of line connecting 1 to 2
        double a_1_2 = (double)(x2 - x1) / (double)(y2 - y1);        //standart slope formula
        double b_1_2 = (double)(x1) - (double)(a_1_2) * (double)(y1); //find b so (y = ax + b -> b = y - ax)
        
        //slope and initial value of line connecting 1 to 3
        double a_1_3 = (double)(x3 - x1) / (double)(y3 - y1);        //standart slope formula
        double b_1_3 = (double)(x1) - (double)(a_1_3) * (double)(y1); //find b so (y = ax + b -> b = y - ax)
        
        //slope and initial value of line connecting 2 to 3
        double a_2_3 = (double)(x3 - x2) / (double)(y3 - y2);        //standart slope formula
        double b_2_3 = (double)(x2) - (double)(a_2_3) * (double)(y2); //find b so (y = ax + b -> b = y - ax)

        //fill first part of the triangle (from y1 to y2 (y2 excluded))
        for(double i = y1; i <= y2; i++)
        {  
            double x_1_2_low  = a_1_2 * (i - 0.5f) + b_1_2;
            double x_1_3_low  = a_1_3 * (i - 0.5f) + b_1_3;

            double x_1_2_high = a_1_2 * (i + 0.5f) + b_1_2;
            double x_1_3_high = a_1_3 * (i + 0.5f) + b_1_3;

            //if top of triangle then
            if(i == y1)
            {
                x_1_2_low  = x1;
                x_1_3_low  = x1;
            }

            //if bottom of triangle
            if(i == y3 && (y3 != y1 || (y3 == y1 && x3 < x1)))
            {
                x_1_2_high = x3;
                x_1_3_high = x3;
            }

            //if middle of triangle
            if(i == y2)
            {
                x_1_2_high = x2;
                // x_1_3_high = x2;
            }
            
            double x_min = MIN(MIN(x_1_2_low, x_1_3_low), MIN(x_1_2_high, x_1_3_high));
            double x_max = MAX(MAX(x_1_2_low, x_1_3_low), MAX(x_1_2_high, x_1_3_high));

            //if we have some NaNs
            if(x_min != x_min || x_max != x_max)
            {
                ::println(F("ERROR line "),line,F(" in "),file,F(", "),(x_min!=x_min)?((x_max!=x_max)?("x_min and x_max were"):("x_min was")):("x_max was"),F(" nul in the following triangle : "));
                ::println(F("{"),x1,F(", "),y1,F("}, {"),x2,F(", "),y2,F("}, {"),x3,F(", "),y3,F("}"));
            }
            
            //get lowest x possible (floored)
            int l_x = FLOOR(x_min + 0.5f);

            //get the highest x possible (ceilling)
            int h_x = CEIL(x_max - 0.5f);

            //fill that little horizontal slice of the triangle
            fillRect(l_x, i, h_x - l_x + 1, 1, colour);

        }
        

        //fill second part of the triangle (from y2 to y3)
        for(double i = y2; i <= y3; i++)
        {

            double x_2_3_low  = a_2_3 * (i - 0.5f) + b_2_3;
            double x_1_3_low  = a_1_3 * (i - 0.5f) + b_1_3;

            double x_2_3_high = a_2_3 * (i + 0.5f) + b_2_3;
            double x_1_3_high = a_1_3 * (i + 0.5f) + b_1_3;
            
            
            //if top of triangle then
            if(i == y1)
            {
                x_2_3_low  = x1;
                x_1_3_low  = x1;
            }

            //if bottom of triangle
            if(i == y3 && (y3 != y1 || (y3 == y1 && x3 < x1)))
            {
                x_2_3_high = x3;
                x_1_3_high = x3;
            }
            
            //if middle of triangle
            if(i == y2)
            {
                x_2_3_low  = x2;
                // x_1_3_low  = x2;
            }

            
            double x_min = MIN(MIN(x_2_3_low, x_1_3_low), MIN(x_2_3_high, x_1_3_high));
            double x_max = MAX(MAX(x_2_3_low, x_1_3_low), MIN(x_2_3_high, x_1_3_high));

            
            //get lowest x possible (floored)
            int l_x = FLOOR(x_min + 0.5f);

            //get the highest x possible (ceilling)
            int h_x = CEIL(x_max - 0.5f);

            //fill that little horizontal slice of the triangle
            fillRect(l_x, i, h_x - l_x + 1, 1, colour); 

        }
    
    }

    //TFT::fillTriangle
    void fillTriangle(Point p1, Point p2, Point p3, uint16_t colour)
    {
        fillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, colour);
    }

    //TFT::fillTriangle
    void fill3dTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t colour, int line = __builtin_LINE(), const char* file = __builtin_FILE())
    {
        
        // debug triangle
        // drawTriangle(x1, y1, x2, y2, x3, y3, color(255, 0, 0));

        //classify all of the x and y coordinates highest to lowest y
        {
            int16_t y[3];
            int16_t x[3];

            y[0] = y1;
            y[1] = y2;
            y[2] = y3;
            x[0] = x1;
            x[1] = x2;
            x[2] = x3;

            //find the lowest of the numbers
            int16_t best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                println(F("ERROR line "),line,F(" in "),file,F(", could not find the lowest number"));
            }

            y1 = y[best_i];//set smallest number
            x1 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                println(F("ERROR line "),line,F(" in "),file,F(", could not find the lowest number"));
            }

            y2 = y[best_i];//set smallest number
            x2 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            //find the lowest of the numbers
            best_i = -1;
            for(int i = 0; i < 3; i++)
            {
                //if we found a smaller y
                if((best_i == -1 && y[i] != INT16_MAX) || (best_i != -1 && y[i] < y[best_i]))
                {
                    best_i = i;
                }
            }

            if(best_i == -1)
            {
                println(F("ERROR line "),line,F(" in "),file,F(", could not find the lowest number"));
            }

            y3 = y[best_i];//set smallest number
            x3 = x[best_i];//set smallest number

            y[best_i] = INT16_MAX;//remove off list
            x[best_i] = INT16_MAX;//remove off list

            if(x1 == INT16_MAX || x2 == INT16_MAX || x3 == INT16_MAX || y1 == INT16_MAX || y2 == INT16_MAX || y3 == INT16_MAX){println(F("ERROR line "),line,F(" in "),file,F(", was not able to sort the coordinates given in a correct order (had INT16_MIN in numbers)"));}
        }


        //1 and 2
        float a1 = (float)(y1 - y2) / (float)(x1 - x2);
        float b1 = (float)y1 - a1 * (float)x1;


        //1 and 3
        float a2 = (float)(y1 - y3) / (float)(x1 - x3);
        float b2 = (float)y1 - a2 * (float)x1;


        //2 and 3
        float a3 = (float)(y2 - y3) / (float)(x2 - x3);
        float b3 = (float)y2 - a3 * (float)x2;



        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        float xs = (x2==x3)?(x2):(y3 - b3) / a3;
        float xe = (x1==x3)?(x1):(y3 - b2) / a2;

        //get the increment for those lines
        float xis = (x2==x3)?(0):1 / a3;
        float xie = (x1==x3)?(0):1 / a2;

        //go through all of the lines one by one top to bottom until we reach the middle
        for(float i = y3; i > y2; i--)
        { 
            //draw the line of the triangle
            fillRect(MIN(xs, xe), i, MAX(xs, xe) - MIN(xs, xe) + 1, 1, colour);

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }


        //get the starting points of each of the lines (xs -> x_start, xe -> x_end, xis -> x_increment_start, xie -> x_increment_end)
        xs = (x1==x3)?(x1):(y2 - b2) / a2;
        xe = (x1==x2)?(x1):(y2 - b1) / a1;

        //get the increment for those lines
        xis = (x1==x3)?(0):1 / a2;
        xie = (x1==x2)?(0):1 / a1;

        //go through all of the lines one by one middle to the bottom
        for(float i = y2; i >= y1; i--)
        {
            //draw the line of the triangle
            fillRect(MIN(xs, xe), i, MAX(xs, xe) - MIN(xs, xe) + 1, 1, colour);

            //get the current line start x and end x
            xs -= xis;
            xe -= xie;
        }
    }

    /**
     * @brief set down the pencil used to START drawing lines connecting dots (resets any previous drawing progress)
     * @param x the x coordinate of the starting point (starting dot of the drawing, the next dashPencil call will draw an imaginary line between this dot and the next one)
     * @param y the y coordinate of the starting point (starting dot of the drawing, the next dashPencil call will draw an imaginary line between this dot and the next one)
     */
    void setPencil(int16_t x, int16_t y)
    {
        //Reset the pencil index
        pencilIndex = 0;

        //set the first position to the position specified in the arguments
        pencil[pencilIndex] = {x, y};

        // ::println("set pencil : ");
        // for(int i = 0; i < (pencilIndex + 1); i++)
        // {
            // ::println("[",i,"] = {",pencil[i].x,", ",pencil[i].y,"}");
        // }
    }
    void setPencil(Point p){setPencil(p.x, p.y);}

    /**
     * @brief this function makes the next dashPencil call act the same as a setPencil call, which essentially resets the pencil but not the same as setPencil
     */
    void resetPencil()
    {
        //set index to -1 because "dashPencil" is going to add one at the start
        pencilIndex = -1;
    }

    /**
     * @brief create a line from the previous point to the point defined in the function (dash pencil to the next point)
     * @param x the x coordinate of the next point connecting last point (the pencil will dash from the last point to this one creating an imaginary line between both points)
     * @param y the y coordinate of the next point connecting last point (the pencil will dash from the last point to this one creating an imaginary line between both points)
     */
    void dashPencil(int16_t x, int16_t y)
    {
        //add one to the pencil index
        pencilIndex++;

        if(pencilIndex >= (int)(sizeofarray(pencil)))
        {
            pencilIndex = (int)(sizeofarray(pencil));
            ::println(F("ERROR line "),__LINE__,F(", too many pencil points to store in the pencil array (decrease the number of pencil points or increase the size of the pencil array within the tft class)"));
        }else
        {
            //set the current pencil Point specified in the arguments
            pencil[pencilIndex] = {x, y};
        }

        
        // ::println("set pencil : ");
        // for(int i = 0; i < (pencilIndex + 1); i++)
        // {
        //     ::println("[",i,"] = {",pencil[i].x,", ",pencil[i].y,"}");
        // }
    }
    void dashPencil(Point p){dashPencil(p.x, p.y);}

    /**
     * @brief this finalizes the pencil path and draws it (draws outline) (this does not reset drawing progress)
     */
    void drawPencil(uint16_t color)
    {
        //goal : go through each points in order and trace lines between them forming the outline of the shape

        //go through all of the pencil points
        for(int i = 0; i <= (pencilIndex - 1); i++)
        {
            //get current point (the Point at index "i")
            Point curr = pencil[i];

            //get the next point
            Point next = pencil[i + 1];

            //join them by a line
            drawLine(curr, next, color);
        }

        //connect the first and last points together if they aren't the same
        Point first = pencil[0];
        Point last  = pencil[pencilIndex];
        if(first != last)
        {
            drawLine(first, last, color);
        }
    }

    /**
     * @brief this finalizes the pencil path and fills it (draws outline + inside outline) (this does not reset drawing progress you can theoretically call drawPencil() to draw outline on top of that)
     * @note when the first point and last point aren't the same, code assumes you meant to connect the last point to the first point
     */
    void fillPencil(uint16_t color)
    {
        //goal : this one is going to be more clunky and longer but we want to draw the complex shape by drawing the triangles that compose said shape
        
        //make a temporary pencil copy so we can set back temp pixel as well as its previous index
        Point tempPencil[sizeofarray(pencil)];
        for(int i = 0; i < (int)sizeofarray(tempPencil); i++)
        {
            tempPencil[i] = pencil[i];
        }
        int tempPencilIndex = pencilIndex;

        //check if the last point is the same as the first point (we get rid of the last point because we already have it (its the first point) no need for it twice)
        {
            Point first = pencil[0]; 
            Point last  = pencil[pencilIndex];

            if(first.x == last.x && first.y == last.y)
            {
                pencilIndex--;
            }
        }
        
        //invert the order of the points if they are counterclockwise
        {   
            int32_t sum = 0;

            //get the rotation of the points given (counterclockwise or clockwise, if they are counterclockwise, we invert their order)
            for(int i = 0; i <= pencilIndex; i++)
            {
                sum += (int32_t)(pencil[(i + 1) % (pencilIndex + 1)].x - pencil[(i + 0) % (pencilIndex + 1)].x) * (int32_t)(pencil[(i + 1) % (pencilIndex + 1)].y + pencil[(i + 0) % (pencilIndex + 1)].y);
            }

            //if counterclockwise
            if(sum < 0)
            {

                //invert the pencil positions if counter clockwise
                for(int i = 0; i < (pencilIndex + 1) / 2; i++)
                {
                    //store pencil[i] temporarly
                    Point temp = pencil[i];
                    
                    //set pencil[i] to its opposite value (so we invert the order of the array last goes to first etc...)
                    pencil[i] = pencil[pencilIndex - i];

                    //set the last index to the first index we stored temporarly
                    pencil[pencilIndex - i] = temp;
                }
            }
        }

        int i = 0;
        //as long as the triangle converter isn't finish we loop
        while(pencilIndex > 0)
        {            
            //get the first three coordinates
            Point p1 = pencil[(i + 0) % (pencilIndex + 1)];
            Point p2 = pencil[(i + 1) % (pencilIndex + 1)];
            Point p3 = pencil[(i + 2) % (pencilIndex + 1)];

            //check if the third point is to the right of the first two points
            int32_t d = isToRight(p1, p2, p3);

            //check if p3 is to the right of the line passing through p1 and p2 (we don't need to do extra calculation if we know the later condition of if we create a triangle fails (which it does if p3 is not to the right or zero))
            bool pointInsideTriangle = false;
            if(d >= 0)
            {
                //check if any points are inside of the triangle
                for(int j = 0; j < pencilIndex + 1; j++)
                {
                    //get if the current pencil point is to the right of all of the segments
                    int32_t n1 = isToRight(p1, p2, pencil[j]);
                    int32_t n2 = isToRight(p2, p3, pencil[j]);
                    int32_t n3 = isToRight(p3, p1, pencil[j]);

                    //if they are all positive, meaning if pencil point is inside the triangle (not including the edge of it)
                    if(n1 > 0 && n2 > 0 && n3 > 0)
                    {
                        //the current point is inside of the triangle, "pointInsideTriangle" becomes true, because we found a point inside the triangle
                        pointInsideTriangle = true;
                        break;
                    }
                }
            
            }
            
            //if special conditions are true, then we can draw a triangle there
            if(d >= 0 && pointInsideTriangle == false)
            {
                //draw the triangle
                fillTriangle(p1, p2, p3, color);

                //get index of p2
                int p2index = (i + 1) % (pencilIndex + 1);

                //remove p2 (push all of the following back by one, it'll overwrite p2 in the process)
                for(int j = p2index; j <= (pencilIndex - 1); j++)
                {
                    pencil[j + 0] = pencil[j + 1];
                }

                //decrease the pencilIndex by one since we removed a point
                pencilIndex--;

                //increase the index "i" by one to move on to the next points (wrap around if it went past pencilIndex)
                i = (i + 1) % (pencilIndex + 1);
                
                //testing why it aint working
            
            //else if the three points are not valid to draw the triangle simply increase index "i" by one to move on to the next points and try again
            }else
            {
                //increase the index "i" by one to move on to the next points (wrap around if it went past pencilIndex)
                i = (i + 1) % (pencilIndex + 1);
            }
        }
    
        //restore the pencil array to what it was previously using the tempPencil array and tempPencilIndex
        for(int j = 0; j < (int)sizeofarray(pencil); j++)
        {
            pencil[j] = tempPencil[j];
        }
        pencilIndex = tempPencilIndex;
    }

    /**
     * @brief this draws all points you dashed your pencil through
     * @note when the first point and last point aren't the same, code assumes you meant to connect the last point to the first point
     */
    void drawPencilPoints(uint16_t color)
    {
        for(int i = 0; i <= pencilIndex; i++)
        {   
            drawPixel(pencil[i], convertNumberToColor(i));
        }
    }

    //TFT::TFT
    TFT()
    {
        //Variable Initializations
        this->vx = 0;
        this->vy = 0;
        this->vw = SCREEN_WIDTH;
        this->vh = SCREEN_HEIGHT;
        this->gx = 0;
        this->gy = 0;
        this->cursor_x_start = 0;
        this->cursor_x = 0;
        this->cursor_y = 0;
        this->fontSize = 1;
        this->fontColor = 0xFFFF;
        clearArray(pencil, {0, 0});
        this->pencilIndex = 0;
    }
};

/*inline*/ TFT tft;

class Rectangle 
{
    public:
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
    double r;
    int16_t roundness = 0;
    int16_t precision = 10;
    uint16_t colour;

    void pencil()
    {
        //rotated point

        //top left
        Pointd p1 ={x - (w/2            ), y - (h/2 - roundness)};
        Pointd p2 ={x - (w/2 - roundness), y - (h/2            )};
        
        //top right
        Pointd p3 ={x + (w/2 - roundness), y - (h/2            )};
        Pointd p4 ={x + (w/2            ), y - (h/2 - roundness)};
        
        //bottom left
        Pointd p5 ={x - (w/2 - roundness), y + (h/2            )};
        Pointd p6 ={x - (w/2            ), y + (h/2 - roundness)};
        
        //bottom right
        Pointd p7 ={x + (w/2            ), y + (h/2 - roundness)};
        Pointd p8 ={x + (w/2 - roundness), y + (h/2            )};

        //DO SHIT BACKWARDS
        tft.resetPencil();
        
        //bottom left corner
        // tft.dashPencil(p6);

        //make a smooth curve between both points
        for(int i = 0; i <= (precision); i++)
        {
            int truei = -i * 90 / (precision);
            int a     = 180 + truei;
            int r     = roundness;

            double cx = cos((double)(a) * PI / 180.0) * (double)(r);
            double cy = sin((double)(a) * PI / 180.0) * (double)(r);

            tft.dashPencil(pivot({p5.x + cx, p6.y + cy}, {x, y}, this->r));
        }

        // tft.dashPencil(p5);
        
        //bottom right corner
        // tft.dashPencil(p8);

        //make a smooth curve between both points
        for(int i = 0; i <= (precision); i++)
        {
            int truei = -i * 90 / (precision) + 180;
            int a     = 270 + truei;
            int r     = roundness;

            double cx = cos((double)(a) * PI / 180.0) * (double)(r);
            double cy = sin((double)(a) * PI / 180.0) * (double)(r);

            tft.dashPencil(pivot({p8.x + cx, p7.y + cy}, {x, y}, this->r));
        }

        // tft.dashPencil(p7);
        
        //top right corner
        // tft.dashPencil(p4);

        //make a smooth curve between both points
        for(int i = 0; i <= (precision); i++)
        {
            int truei = -i * 90 / (precision);
            int a     = 0 + truei;
            int r     = roundness;

            double cx = cos((double)(a) * PI / 180.0) * (double)(r);
            double cy = sin((double)(a) * PI / 180.0) * (double)(r);

            tft.dashPencil(pivot({p3.x + cx, p4.y + cy}, {x, y}, this->r));
        }

        // tft.dashPencil(p3);
        
        //top left corner
        // tft.dashPencil(p2);

        //make a smooth curve between both points
        for(int i = 0; i <= (precision); i++)
        {
            int truei = -i * 90 / (precision) + 180;
            int a     = 90 + truei;
            int r     = roundness;

            double cx = cos((double)(a) * PI / 180.0) * (double)(r);
            double cy = sin((double)(a) * PI / 180.0) * (double)(r);

            tft.dashPencil(pivot({p2.x + cx, p1.y + cy}, {x, y}, this->r));
        }

        // tft.dashPencil(p1);

        //connect last point with first point
        // tft.dashPencil(p6);
    }

    void draw()
    {
        pencil();

        tft.drawPencil(colour);
    }

    void fill()
    {
        pencil();

        tft.fillPencil(colour);
    }

    void draw(uint16_t colour)
    {
        pencil();

        tft.drawPencil(colour);
    }

    void fill(uint16_t colour)
    {
        pencil();

        tft.fillPencil(colour);
    }

    Rectangle(int x, int y, int w, int h, double r, uint16_t colour)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->r = r;
        this->colour = colour;
    }

    Rectangle()
    {
        this->x = 0;
        this->y = 0;
        this->w = 100;
        this->h = 100;
        this->r = 0;
        this->colour = rgb(255, 255, 255);
    }
};

#endif