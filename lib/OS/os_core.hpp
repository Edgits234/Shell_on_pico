//include all files in order
#include <AwesomeUI.h>
#include <BadApplePlayer.h>

#include <io.hpp>
#include <scheduler.hpp>
#include <fs.hpp>


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

        if ((i % 480) == 0) { 
            //strategic AUDIO MOFUCKER

            //play audio if says its playing
            if(Audio::playing == 1)
            {
                Audio::update();
            }
        }
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

//TFT::fillRect
void TFT::fillBinImage(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* buffer, bool is_buffer_horizontal, bool inverse_byte) {

    int16_t original_x = x;
    int16_t original_y = y;
    // int16_t original_w = w;
    int16_t original_h = h;

    //fit to the viewport

    //transform width into a secondary position to make math easier
    w = w + x - 1;
    h = h + y - 1;

    //when x goes too much to the right we want it to warp at 240 instead of 239 bcs thats going to make the result width 0 (so we display nothing)
    x = max((vx), min((vx + vw), x));
    y = max((vy), min((vy + vh), y));
    w = max((vx - 1), min((vx + vw - 1), w));
    h = max((vy - 1), min((vy + vh - 1), h));

    //transform width back into original position
    w = w - x + 1;
    h = h - y + 1;


    //if on mega, then directly transfer the fillRect to the screen
    #if WOKWI_SIM  
        setWindow(x, y, x + w - 1, y + h - 1);
        
        digitalWrite(CS_PIN, LOW);
        digitalWrite(DC_PIN, HIGH);
        
        //print the output_bin_data array
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                //figure out the true index
                int trueIndex;
                if(is_buffer_horizontal)
                {
                    trueIndex = (j + MAX(0, x - original_x)) * original_h + original_h - (i + MAX(0, y - original_y)) - 1;
                }else
                {
                    trueIndex = (i + MAX(0, y - original_y)) * original_h + (j + MAX(0, x - original_x));
                }

                uint8_t currByte = pgm_read_byte(buffer + trueIndex / 8);
                uint8_t currBit; 
                if(inverse_byte)   
                {
                    currBit = currByte & (0b10000000 >> (trueIndex % 8));
                }else
                {
                    currBit = currByte & (1 << (trueIndex % 8));
                }
                uint16_t color  = (currBit) ? (rgb(255, 255, 255)) : (rgb(0, 0, 0));

                uint8_t hi = color >> 8;
                uint8_t lo = color & 0xFF;
            
                SPI_BUS.transfer(hi);
                SPI_BUS.transfer(lo);
            }
        }

        digitalWrite(CS_PIN, HIGH);

    //else, on giga, we have enough space for a screen buffer so write to the screen buffer instead
    #else
        
        //print the output_bin_data array
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                //figure out the true index
                int trueIndex;
                if(is_buffer_horizontal)
                {
                    trueIndex = (j + MAX(0, x - original_x)) * original_h + original_h - (i + MAX(0, y - original_y)) - 1;
                }else
                {
                    trueIndex = (i + MAX(0, y - original_y)) * original_h + (j + MAX(0, x - original_x));
                }

                uint8_t currByte = pgm_read_byte(buffer + trueIndex / 8);
                uint8_t currBit  ;
                if(inverse_byte)
                {
                    currBit = currByte & (0b10000000 >> (trueIndex % 8));
                }else
                {
                    currBit = currByte & (1 << (trueIndex % 8));
                }
                uint16_t color  = (currBit) ? (rgb(255, 255, 255)) : (rgb(0, 0, 0));

                #if NORMAL_DRAWING_ORDER
                    //draw the pixel in the screen buffer
                    *((uint16_t*)(screenBuffer + ((i + y) * SCREEN_WIDTH * 2) + ((j + x) * 2))) = color;
                #else
                    // calculate the index in the array based on the position of the pixel (assuming that each pixel has a different index and that the array is all of the rows of the screen one after the other starting from top of the screen to the bottom)
                    int truei = (j + SCREEN_WIDTH * i);
                    
                    //index it in the array of bytes (uint8_t) to see if we've already drawn at this place (if yes, don't waste time on drawing it)(if no, draw it and add it to the list)
                    if(!(drawnPixel[truei / 8] & (0b1 << (truei % 8))))
                    {
                        //draw the pixel in the screen buffer
                        *((uint16_t*)(screenBuffer + ((i + y) * SCREEN_WIDTH * 2) + ((j + x) * 2))) = color;
                        
                        //add the pixel to the list of no draws
                        drawnPixel[truei / 8] |= (0b1 << (truei % 8));
                    }
                #endif
            }
        
            //every eight lines (because pretty fast to read)
            if(i % 8 == 0)
            {
                //update the audio 
                
                //play audio if says its playing
                if(Audio::playing == 1)
                {
                    Audio::update();
                }
            }
        }

    #endif
}


#include <shell.hpp>