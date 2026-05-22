#pragma once
// ============================================================
// shell.hpp  —  command-line shell
//
// Built-in commands:
//   help            list commands
//   ps              list processes
//   kill <pid>      kill process by pid
//   ls [dir]        list SD directory
//   cat <file>      print file
//   rm  <file>      delete file
//   mkdir <dir>     make directory
//   write <f> <str> overwrite file with string
//   append <f> <str>append string to file
//   echo <str>      print string
//   ticks           print scheduler tick counter
//   run  <name>     spawn a demo background task
//   clear           clear terminal screen
//
// Adding a command: add a row to _commands[] and a handler.
// ============================================================

#include "io.hpp"
#include "process.hpp"
#include "scheduler.hpp"
#include "fs.hpp"
#include <cstring>
#include <cstdlib>

namespace Shell {

// ---- token helpers -----------------------------------------
static constexpr int MAX_ARGS = 8;
static constexpr int LINE_BUF = 128;

static int tokenize(char* line, char* argv[], int max_args) {
    int argc = 0;
    char* p = line;
    while (*p && argc < max_args) {
        while (*p == ' ') p++;
        if (!*p) break;
        argv[argc++] = p;
        while (*p && *p != ' ') p++;
        if (*p) *p++ = '\0';
    }
    return argc;
}

// ---- demo background task (spawned by 'run') ----------------
static void _demo_task() {
    int cnt = 0;
    while (true) {
        // A real task would do work here.
        // It yields voluntarily; mbed preemption handles the rest.
        Scheduler::sleep_ms(2000);
        // Note: IO from background threads is fine over USB Serial,
        // but add a Mutex if you need strict output ordering.
        IO::printf("[bg] tick %lu cnt=%d\r\n", Scheduler::g_tick, ++cnt);
    }
}

// ---- command handlers ---------------------------------------
static void cmd_help(int, char**) {
    IO::println(
        "  help                show this message\r\n"
        "  ps                  list processes\r\n"
        "  kill <pid>          kill process\r\n"
        "  ls [dir]            list directory (default /)\r\n"
        "  cat <file>          print file\r\n"
        "  rm  <file>          remove file\r\n"
        "  mkdir <dir>         make directory\r\n"
        "  write <file> <str>  overwrite file with string\r\n"
        "  append <file> <str> append string to file\r\n"
        "  echo <str...>       echo arguments\r\n"
        "  ticks               print scheduler tick counter\r\n"
        "  run <name>          spawn demo background task\r\n"
        "  clear               clear screen"
    );
}

static void cmd_ps(int, char**) {
    IO::println("PID  STATE    STACK   NAME");
    IO::println("---  -------  ------  ----------------");
    g_proctable.for_each([](const Process& p) {
        const char* st = "?      ";
        switch (p.state) {
            case ProcState::RUNNING: st = "RUNNING"; break;
            case ProcState::BLOCKED: st = "BLOCKED"; break;
            case ProcState::ZOMBIE:  st = "ZOMBIE "; break;
            default: break;
        }
        IO::printf("%-3d  %s  %-6lu  %s\r\n",
                   p.pid, st, (unsigned long)p.stack_size, p.name);
    });
}

static void cmd_kill(int argc, char** argv) {
    if (argc < 2) { IO::println("usage: kill <pid>"); return; }
    int pid = atoi(argv[1]);
    if (Scheduler::kill(pid))
        IO::printf("killed %d\r\n", pid);
    else
        IO::printf("kill: no such process %d\r\n", pid);
}

static void cmd_ls(int argc, char** argv) {
    FS::ls(argc >= 2 ? argv[1] : "/");
}

static void cmd_cat(int argc, char** argv) {
    if (argc < 2) { IO::println("usage: cat <file>"); return; }
    if (!FS::cat(argv[1]))
        IO::printf("cat: %s: not found\r\n", argv[1]);
}

static void cmd_rm(int argc, char** argv) {
    if (argc < 2) { IO::println("usage: rm <file>"); return; }
    if (!FS::remove(argv[1]))
        IO::printf("rm: %s: failed\r\n", argv[1]);
}

static void cmd_mkdir(int argc, char** argv) {
    if (argc < 2) { IO::println("usage: mkdir <dir>"); return; }
    if (!FS::mkdir(argv[1]))
        IO::printf("mkdir: %s: failed\r\n", argv[1]);
}

static void cmd_write(int argc, char** argv) {
    if (argc < 3) { IO::println("usage: write <file> <string>"); return; }
    if (!FS::write(argv[1], argv[2]))
        IO::printf("write: %s: failed\r\n", argv[1]);
}

static void cmd_append(int argc, char** argv) {
    if (argc < 3) { IO::println("usage: append <file> <string>"); return; }
    if (!FS::append(argv[1], argv[2]))
        IO::printf("append: %s: failed\r\n", argv[1]);
}

static void cmd_echo(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (i > 1) IO::write_char(' ');
        IO::print(argv[i]);
    }
    IO::print("\r\n");
}

static void cmd_ticks(int, char**) {
    IO::printf("ticks: %lu\r\n", (unsigned long)Scheduler::g_tick);
}

static void cmd_run(int argc, char** argv) {
    const char* name = (argc >= 2) ? argv[1] : "demo";
    int pid = Scheduler::spawn(_demo_task, name, 512);
    if (pid >= 0)
        IO::printf("spawned '%s' as pid %d\r\n", name, pid);
    else
        IO::println("run: process table full");
}

static void cmd_clear(int, char**) {
    IO::print("\033[2J\033[H");   // ANSI clear screen + home cursor
}

// ---- command dispatch table ---------------------------------
struct Cmd { const char* name; void (*fn)(int, char**); };

static const Cmd _commands[] = {
    { "help",   cmd_help   },
    { "ps",     cmd_ps     },
    { "kill",   cmd_kill   },
    { "ls",     cmd_ls     },
    { "cat",    cmd_cat    },
    { "rm",     cmd_rm     },
    { "mkdir",  cmd_mkdir  },
    { "write",  cmd_write  },
    { "append", cmd_append },
    { "echo",   cmd_echo   },
    { "ticks",  cmd_ticks  },
    { "run",    cmd_run    },
    { "clear",  cmd_clear  },
};
static constexpr int CMD_COUNT = sizeof(_commands) / sizeof(_commands[0]);

// ---- public API ---------------------------------------------

// Print the prompt string.
inline void prompt(const char* cwd = "/") {
    IO::printf("picoOS:%s> ", cwd);
}

// Execute one text line.  Mutates the string (tokenization).
inline void exec(char* line) {
    char* argv[MAX_ARGS];
    int   argc = tokenize(line, argv, MAX_ARGS);
    if (argc == 0) return;

    for (int i = 0; i < CMD_COUNT; i++) {
        if (strcmp(argv[0], _commands[i].name) == 0) {
            _commands[i].fn(argc, argv);
            return;
        }
    }
    IO::printf("unknown command: %s  (try 'help')\r\n", argv[0]);
}

// Run the shell loop forever (call from main thread).
inline void run() {
    char line[LINE_BUF];
    IO::println("\r\npicoOS  —  type 'help' for commands");
    while (true) {
        prompt();
        IO::readline(line, sizeof(line));
        exec(line);
    }
}

} // namespace Shell