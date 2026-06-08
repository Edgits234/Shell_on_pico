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
        "  clear               clear screen\r\n"
        "  bad_apple           plays bad apple"
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

static void cmd_bad_apple(int, char**)
{
    //if we are on wokwi, do a couple of stuff for performence
    #if WOKWI_SIM
        //delete terminal for performence
        ui.remove("Shell");

        //don't draw useless stuff (the bad apple player is going to override everything since its in a full screen window)
        tft.disable_fillRect = 1;

    #else

        IO::println("Processing bad apple video...");
        IO::println("this may take ~10 sec");

        ui.update();
    #endif

    //create a window
    Window& bad_apple_win = ui.addWindow("bad_apple_win");
    bad_apple_win.x = 0;
    bad_apple_win.y = -10;
    bad_apple_win.w = SCREEN_WIDTH;
    bad_apple_win.h = SCREEN_HEIGHT + 10;

    //add bad apple in the window
    bad_apple_win.add<BadApplePlayer>("bad_apple");

    bad_apple_win.userTick = [](UIelement* self) -> void
    {
        //convert UIelement pointer to specific window
        Window& win = *(Window*)(self);

        //if the window has a different width height x or y then previously assigned (no longer fullscreen), disable the optimization for fillrect
        if(win.x != 0 || win.y != -10 || win.w != SCREEN_WIDTH || win.h != SCREEN_HEIGHT + 10)
        {
            //re enable drawing of the rectangles
            tft.disable_fillRect = 0;
        }
    };
}

// ---- command dispatch table ---------------------------------
struct Cmd { const char* name; void (*fn)(int, char**); };

static const Cmd _commands[] = {
    { "help",      cmd_help      },
    { "ps",        cmd_ps        },
    { "kill",      cmd_kill      },
    { "ls",        cmd_ls        },
    { "cat",       cmd_cat       },
    { "rm",        cmd_rm        },
    { "mkdir",     cmd_mkdir     },
    { "write",     cmd_write     },
    { "append",    cmd_append    },
    { "echo",      cmd_echo      },
    { "ticks",     cmd_ticks     },
    { "run",       cmd_run       },
    { "clear",     cmd_clear     },
    { "bad_apple", cmd_bad_apple }
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
            ::DEBUG_BANNER("Running cmd : \"",_commands[i].name,"\"");
            _commands[i].fn(argc, argv);
            return;
        }
    }
    IO::printf("unknown command: %s  (try 'help')\r\n", argv[0]);
}

// set a custom write to be the terminal
void terminal_write_char(char c)
{
    if(ui.exists("Shell"))
    {
        Terminal& terminal = ui.getTerminal("Shell");

        //write a character to the terminal
        terminal.write(c);
    }
}

// Run the shell loop forever (call from main thread).
inline void run() {
    char line[LINE_BUF];

    //create a terminal ui for the shell
    ui.addTerminal("Shell");
    
    //set custom write
    IO::write_char = terminal_write_char;
    
    IO::println("\r\npicoOS  -  type 'help' for commands");

    while (true) {
        //Performence, delete shell
        if(ui.exists("Shell")) {
            Terminal& terminal = ui.getTerminal("Shell");

            prompt();

            
            //wait until a terminal command is available
            while(!terminal.available())
            {
                //call update to update elements while waiting
                ui.update();
            }

            IO::readline(line, sizeof(line), terminal);//use terminal version instead

            exec(line);
        }else {
            //update elemtns, make them show up on the screen
            ui.update();
        }
    }
}

} // namespace Shell