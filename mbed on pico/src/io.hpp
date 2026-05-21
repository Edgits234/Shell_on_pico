#pragma once
// ============================================================
// io.hpp  —  swappable I/O layer
// To redirect: define your own io_read / io_write before
// including this header, or override the function pointers
// at runtime via IO::set_backend().
// Default backend: Arduino/mbed Serial (USB CDC).
// ============================================================

#include <mbed.h>
#include <cstdarg>
#include <cstdio>

namespace IO {

// ---- backend function pointers --------------------------------
// Replace these at runtime to redirect all shell I/O.
inline int  (*read_char)()          = []() -> int  { return Serial.read(); };
inline void (*write_char)(char c)   = [](char c)   { Serial.write(c); };
inline int  (*available)()          = []() -> int  { return Serial.available(); };

inline void set_backend(
    int  (*r)(),
    void (*w)(char),
    int  (*a)()
) { read_char = r; write_char = w; available = a; }

// ---- convenience helpers --------------------------------------
inline void print(const char* s) {
    while (*s) write_char(*s++);
}

inline void println(const char* s) {
    print(s);
    write_char('\r');
    write_char('\n');
}

// Minimal printf-style print (no heap alloc, 128-byte stack buf)
inline void printf(const char* fmt, ...) {
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    print(buf);
}

// Read one line into buf (max len-1 chars), echo chars back.
// Returns number of chars read (without newline).
inline int readline(char* buf, int len) {
    int i = 0;
    while (i < len - 1) {
        while (!available()) { /* spin */ }
        int c = read_char();
        if (c == '\r' || c == '\n') break;
        if (c == 0x7F || c == '\b') {   // backspace
            if (i > 0) { i--; write_char('\b'); write_char(' '); write_char('\b'); }
            continue;
        }
        buf[i++] = (char)c;
        write_char((char)c);             // echo
    }
    buf[i] = '\0';
    write_char('\r'); write_char('\n');
    return i;
}

} // namespace IO