#include <SD.h>
#include <Arduino_AdvancedAnalog.h>

// --- Configuration ---
const int chipSelect = 7;           // Updated to pin 7 for your SD module
const uint32_t sampleRate = 22050*2;  // Updated to match your 22050 Hz file (double because stereo)
const uint32_t samplesPerBuffer = 512; // Size of individual audio blocks
const uint32_t queueDepth = 4;      // Pre-allocated buffers to prevent stuttering

// Create the DAC object on the audio jack pin
AdvancedDAC myDac(A12); 

File audioFile;

namespace Audio
{
    bool playing = false;

    void begin()
    {
        Serial.println("Initializing Audio Output...");
        
        // Initialize AdvancedDAC with 12-bit resolution and the 22050 Hz sample rate
        if (!myDac.begin(AN_RESOLUTION_12, sampleRate, samplesPerBuffer, queueDepth)) {
            Serial.println("Failed to initialize AdvancedDAC!");
            while (1);
        }
        Serial.println("Audio system ready.");

        // Open the file
        audioFile = SD.open("badapple.wav", FILE_READ);
        if (!audioFile) {
            Serial.println("Error: Could not open badapple.wav!");
            while (1);
        }

        // Skip the standard 44-byte WAV header to hit raw PCM data
        if (audioFile.available()) {
            audioFile.seek(44);
            Serial.println("Playing badapple.wav...");
        }
    }

    void update()
    {
        // Check if the DAC hardware is ready for a new block of data
        if (myDac.available()) {
            
            // Dequeue a free SampleBuffer from the library's pool
            SampleBuffer buf = myDac.dequeue();
            
            // Create a temporary staging buffer for the raw 16-bit SD card data
            int16_t rawSDBuffer[buf.size()];
            
            // Calculate how many raw bytes we need to fetch (2 bytes per 16-bit sample)
            size_t bytesToRead = buf.size() * sizeof(int16_t);
            
            // Read directly into our temporary staging buffer
            int bytesRead = audioFile.read((uint8_t*)rawSDBuffer, bytesToRead);
            
            // Handle end-of-file condition
            if (bytesRead <= 0) {
            Serial.println("Finished playing badapple.wav.");
            audioFile.close();
            while (1); 
            }
            
            // Calculate exactly how many full samples we managed to read
            size_t samplesRead = bytesRead / sizeof(int16_t);
            
            // Process the data and transfer it safely to the DAC buffer
            for (size_t i = 0; i < buf.size(); i++) {
            if (i < samplesRead) {
                // Grab the uncorrupted sample from our temporary staging buffer
                int16_t sample16 = rawSDBuffer[i];
                
                // Convert signed 16-bit (-32768 to 32767) to unsigned 12-bit (0 to 4095)
                uint16_t sample12 = ((sample16 + 32768) >> 4) & 0xFFF;
                buf.data()[i] = sample12;
            } else {
                // Pad the remainder of the buffer with silence if we hit the end of the file
                buf.data()[i] = 2048; 
            }
            }
            
            // Hand the completely ready buffer back to the hardware queue
            myDac.write(buf);
        }
    
    }
};