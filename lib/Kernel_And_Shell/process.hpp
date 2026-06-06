#pragma once
// ============================================================
// process.hpp  —  lightweight process registry
// A "process" here is a named, cooperating task slot.
// Actual preemption is handled by mbed threads (scheduler.hpp).
// Max processes: PROC_MAX (tune to taste).
// ============================================================

#include <mbed.h>
#include <cstring>

static constexpr int PROC_MAX       = 8;   // tweak for RAM budget
static constexpr int PROC_NAME_LEN  = 16;

enum class ProcState : uint8_t {
    EMPTY = 0,
    RUNNING,
    BLOCKED,
    ZOMBIE,
};

struct Process {
    char        name[PROC_NAME_LEN];
    ProcState   state;
    uint8_t     pid;
    rtos::Thread*     thread;          // nullptr = shell / main thread
    uint32_t    stack_size;
    uint32_t    wake_tick;       // used by sleep()
};

// ---- ProcessTable -------------------------------------------
class ProcessTable {
public:
    ProcessTable() { memset(_procs, 0, sizeof(_procs)); }

    // Register a new process slot (does NOT start the thread).
    // Returns pid on success, -1 if table is full.
    int alloc(const char* name, uint32_t stack = 512) {
        for (int i = 0; i < PROC_MAX; i++) {
            if (_procs[i].state == ProcState::EMPTY) {
                strncpy(_procs[i].name, name, PROC_NAME_LEN - 1);
                _procs[i].name[PROC_NAME_LEN - 1] = '\0';
                _procs[i].state      = ProcState::RUNNING;
                _procs[i].pid        = (uint8_t)i;
                _procs[i].thread     = nullptr;
                _procs[i].stack_size = stack;
                _procs[i].wake_tick  = 0;
                return i;
            }
        }
        return -1;
    }

    // Attach an mbed Thread* to a pid slot.
    void attach_thread(int pid, rtos::Thread* t) {
        if (valid(pid)) _procs[pid].thread = t;
    }

    // Kill: terminate thread and mark slot EMPTY.
    bool kill(int pid) {
        if (!valid(pid)) return false;
        if (_procs[pid].thread) {
            _procs[pid].thread->terminate();
            delete _procs[pid].thread;
            _procs[pid].thread = nullptr;
        }
        _procs[pid].state = ProcState::EMPTY;
        return true;
    }

    Process* get(int pid) {
        return valid(pid) ? &_procs[pid] : nullptr;
    }

    // Iterate over all non-empty slots
    template<typename Fn>
    void for_each(Fn fn) {
        for (int i = 0; i < PROC_MAX; i++)
            if (_procs[i].state != ProcState::EMPTY)
                fn(_procs[i]);
    }

    int count() const {
        int n = 0;
        for (int i = 0; i < PROC_MAX; i++)
            if (_procs[i].state != ProcState::EMPTY) n++;
        return n;
    }

private:
    Process _procs[PROC_MAX];

    bool valid(int pid) const {
        return pid >= 0 && pid < PROC_MAX &&
               _procs[pid].state != ProcState::EMPTY;
    }
};

// Global singleton
inline ProcessTable g_proctable;