//
// Created by camilo on 3/26/26.
//
#pragma once

#include <sys/types.h>
#include <signal.h>
#include <termios.h>


class pty_process :
virtual public ::particle
{
public:
   //private:
   pid_t child_pid_;
   int m_ptyMaster;
   bool running_;

::memory m_memoryOutput;
   ::string_array m_straCommands;
   int m_iCurrentCommand = 0;
   int m_flagsStdIn;
   int m_iExitCode = 0;
   bool m_bSetNonBlockingIOforStdIn = false;
   termios m_tioOriginal{};
   bool m_bTerminalModeSaved = false;
   bool m_bLocalRawMode = false;
   pty_process();
   ~pty_process();

   pty_process(const pty_process&) = delete;
   pty_process& operator=(const pty_process&) = delete;

   pty_process(pty_process&& other) noexcept;
   pty_process& operator=(pty_process&& other) noexcept;

   // Spawn using /bin/sh -c <command>
   bool spawn(const ::scoped_string& command);

   // Spawn using execvp(argv[0], argv)
   bool spawn(const string_array_base & args);

   // Single PTY FD (read + write)
   int fd() const;

   pid_t pid() const;

   bool is_running();
   int wait(bool block = true); // exit code or -1
   bool terminate(int sig = SIGTERM);
   bool kill_force(); // SIGKILL

   memsize write_input(const void* data, memsize size);
   memsize write_input(const ::scoped_string& s);

   memsize read_output(void* buf, memsize size);
   ::memory read_available();

   void close_fd();
   bool set_nonblocking(bool enabled = true);
void set_stdin_non_blocking();
   bool sync_local_echo_from_child();



   // NEW: terminal stdin helpers
   bool stdin_echo_enabled() const;
   memsize capture_stdin_once(bool forward_to_child = true,
                              ::string* captured_visible = nullptr,
                              ::string* captured_hidden = nullptr);

   ::string capture_stdin_available(bool forward_to_child = true,
                                       bool* echo_was_enabled = nullptr);
   void poll_write_stdin();
   void poll_read_stdout();

//private:
   bool __spawn_internal(char* const argv[]);
   void __cleanup();
   static bool __set_fd_nonblocking_impl(int fd, bool enabled);



   void begin_terminal_bridge();
   void end_terminal_bridge();

   void run() override;

};