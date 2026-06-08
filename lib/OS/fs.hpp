#pragma once
// ============================================================
// fs.hpp  —  SD card file management
//
// Wraps the Arduino SD library (works with mbed + Pico via
// the arduino-pico core or the mbed SD driver).
// All paths are absolute from the SD root, e.g. "/notes.txt".
//
// To adapt to a different storage backend, swap the SD.*
// calls in each function body — the public API stays the same.
//
// SPI pins: adjust FS_SD_CS, FS_SD_MOSI, etc. in your
// platform header or pass them to FS::init().
// ============================================================

#include <SD.h>           // Arduino SD library
#include "io.hpp"
#include <cstring>

#if WOKWI_SIM
    // ---- Pin config — change here or via build flags -----------
    #ifndef FS_SD_CS
    #  define FS_SD_CS   17   // GP17 on Pico (adjust to wiring)
    #endif
#else
    #ifndef FS_SD_CS
    #  define FS_SD_CS   7   // pin 7 on Giga (adjust to wiring)
    #endif
#endif

namespace FS {

// ---- Lifecycle ----------------------------------------------

inline bool init(int cs_pin = FS_SD_CS) {
    return SD.begin(cs_pin);
}

// ---- File operations ----------------------------------------

// Read file to IO output.  Returns false if not found.
inline bool cat(const char* path) {
    File f = SD.open(path, FILE_READ);
    if (!f) return false;
    while (f.available()) {
        char c = f.read();
        IO::write_char(c);
    }
    f.close();
    IO::print("\r\n");
    return true;
}

// Write (overwrite) a string to a file.
inline bool write(const char* path, const char* data) {
    SD.remove(path);
    File f = SD.open(path, FILE_WRITE);
    if (!f) return false;
    f.print(data);
    f.close();
    return true;
}

// Append a string to a file (creates if not present).
inline bool append(const char* path, const char* data) {
    File f = SD.open(path, FILE_WRITE);   // SD lib always appends
    if (!f) return false;
    f.print(data);
    f.close();
    return true;
}

inline bool remove(const char* path) {
    return SD.remove(path);
}

inline bool mkdir(const char* path) {
    return SD.mkdir(path);
}

inline bool rmdir(const char* path) {
    return SD.rmdir(path);
}

inline bool exists(const char* path) {
    return SD.exists(path);
}

// ---- Directory listing --------------------------------------
// Lists entries in 'dir' to IO output.
inline void ls(const char* dir = "/") {
    File root = SD.open(dir);
    if (!root || !root.isDirectory()) {
        IO::println("ls: cannot open directory");
        return;
    }
    File entry;
    while ((entry = root.openNextFile())) {
        if (entry.isDirectory())
            IO::printf("  [DIR]  %s\r\n", entry.name());
        else
            IO::printf("  %8lu  %s\r\n", (unsigned long)entry.size(), entry.name());
        entry.close();
    }
    root.close();
}

} // namespace FS