



// ============================================================
// main.cpp  —  picoOS entry point
//
// Build with the arduino-pico core (mbed flavour) or the
// official Raspberry Pi Pico Arduino board package that
// exposes the mbed RTOS.  Requires the Arduino SD library.
//
// Pinout for Raspberry pi pico :
//   SD CS   → GP17
//   SD MOSI → GP19  (SPI0 MOSI)
//   SD MISO → GP16  (SPI0 MISO)
//   SD SCK  → GP18  (SPI0 SCK)
//
// Pinout for ARDUINO GIGA R1 WIFI : 
//   SD CS   → D7
//   SD MOSI → SPI1_COPI
//   SD MISO → SPI1_CIPO
//   SD SCK  → SPI1_SCK
//   see : https://docs.arduino.cc/resources/pinouts/ABX00063-full-pinout.pdf
//
// Serial baud: 115200 (USB CDC — baud is irrelevant but set
// it in your monitor to 115200 for consistency).
// ============================================================

#include <Arduino.h>      // Arduino-pico / mbed glue
#include <os_core.hpp>

// ---- Optional: swap I/O backend here -----------------------
// Example — redirect to a hardware UART instead of USB serial:
//
//   static SerialUART uart1(8, 9);   // TX=GP8, RX=GP9
//   void setup_io() {
//       uart1.begin(115200);
//       IO::set_backend(
//           []() -> int  { return uart1.read(); },
//           [](char c)   { uart1.write(c); },
//           []() -> int  { return uart1.available(); }
//       );
//   }
//
// For now we use the default USB CDC backend defined in io.hpp.
// ------------------------------------------------------------

void updateUI()
{
    while(true)
    {
        ::println("updating");
        ui.update();
    }
}

void setup() {
    Serial.begin(115200);

    // Wait up to 2 s for a serial monitor (helpful during dev;
    // remove for headless / always-on deployment).
    for (int i = 0; i < 200 && !Serial; i++)
        delay(10);

    //start the ui manager (AwesomeUI)
    ui.basecolor = rgb(50, 50, 50);
    ui.begin();

    //initialize SD
    if(!SD.begin(SD_CS_PIN))
    {
        ::println("failed to initialize SD");
    }

    //begin audio set up audio
    Audio::begin();

    // Start the 1 ms tick thread.
    Scheduler::init();

    // Mount SD card (non-fatal — fs commands report errors if absent).
    if (!FS::init()) {
        IO::println("[warn] SD card not found - filesystem commands unavailable");
    }

    Shell::run();//main thread
}

void loop() {
    // loop() is never reached; Shell::run() owns the main thread.
    // mbed RTOS preempts background threads spawned via Scheduler::spawn().
}



