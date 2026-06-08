#pragma once
// ============================================================
// scheduler.hpp  —  preemptive multitasker wrapper
//
// mbed-os already provides preemptive scheduling via its RTOS
// (based on RTX). This layer is a thin, ergonomic wrapper that:
//   1. Spawns named mbed Threads and registers them in the
//      ProcessTable.
//   2. Provides a blocking sleep / yield primitive.
//   3. Keeps a tick counter for basic timing.
//
// Stack sizes are configurable per task; keep them tight on
// the Pico (264 KB total SRAM).  Minimum safe: ~512 bytes.
// ============================================================

#include "process.hpp"
#include <mbed.h>

namespace Scheduler {

// Tick counter incremented by a background thread every 1 ms.
inline volatile uint32_t g_tick = 0;

// Internal ticker thread (1 ms resolution).
inline rtos::Thread* _ticker_thread = nullptr;

inline void _ticker_fn() {
    while (true) {
        rtos::ThisThread::sleep_for(std::chrono::milliseconds(1));
        g_tick++;
    }
}

inline void init() {
    _ticker_thread = new rtos::Thread(osPriorityNormal, 1024, nullptr, "ticker");
    _ticker_thread->start(_ticker_fn);
}

// Spawn a new preemptive task.
// fn     : task entry point (void(*)() or lambda with no capture)
// name   : display name (max PROC_NAME_LEN-1 chars)
// stack  : stack in bytes (default 1 KB; tune down if needed)
// prio   : mbed osPriority (default Normal)
// Returns pid on success, -1 on failure.
inline int spawn(
    mbed::Callback<void()> fn,
    const char*   name,
    uint32_t      stack = 1024,
    osPriority_t  prio  = osPriorityNormal
) {
    int pid = g_proctable.alloc(name, stack);
    if (pid < 0) return -1;

    rtos::Thread* t = new rtos::Thread(prio, stack, nullptr, name);
    if (t->start(fn) != osOK) {
        delete t;
        g_proctable.kill(pid);
        return -1;
    }
    g_proctable.attach_thread(pid, t);
    return pid;
}

// Kill a running process by pid.
inline bool kill(int pid) {
    return g_proctable.kill(pid);
}

// Yield remaining timeslice to scheduler.
inline void yield() {
    rtos::ThisThread::yield();
}

// Sleep for ms milliseconds (uses mbed RTOS sleep, not spin).
inline void sleep_ms(uint32_t ms) {
    rtos::ThisThread::sleep_for(rtos::Kernel::Clock::duration_u32(ms));
}

} // namespace Scheduler