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
protected:

   ::string_array m_straCommands;
   ::string_array m_straMarkerEcho;
   ::string_array m_straMarker;
   //iptr_array m_iaMarkerEcho;
   //iptr_array m_iaMarker;
   int m_iCurrentCommand = 0;
   bool m_bWaitingMarker = false;
   //memsize m_iSearchMarkerFrom= 0;
   //memsize  m_iLastStdOut = 0;
   ::string m_strCommand;
   ::string m_strMarkerEcho;
   ::string m_strMarker;

public:
   //private:
   pid_t child_pid_;
   int m_ptyMaster;
   bool running_;

   ::memory m_memoryBuffer;
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


   void add_command_line(const ::scoped_string & scopedstrCommand);

   // Spawn using /bin/sh -c <command>
   bool open();
   bool open(const ::scoped_string& scopedstrShell);
   void on_child_raw_stdout(const void *p, memsize s);
   void on_child_stdout(const void *p, memsize s);
   // Spawn using execvp(argv[0], argv)
   bool __open(const string_array_base & args);
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



class pty_process_exception :
virtual public ::exception
{
public:

   pty_process_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage);
   ~pty_process_exception() override;



};