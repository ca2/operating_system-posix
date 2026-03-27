//
// Created by camilo on 3/26/26.
//
#include "framework.h"
#include "pty_process.h"
#include "acme/operating_system/posix/_.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

#include <unistd.h>
#include <errno.h>
#include <acme/prototype/mathematics/mathematics.h>

pty_process_exception::pty_process_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage) :
::exception(estatus, scopedstrMessage)
{


}


pty_process_exception::~pty_process_exception()
{


}


namespace {
    void close_if_valid(int& fd) {
        if (fd >= 0) {
            close(fd);
            fd = -1;
        }
    }
}
FILE * current_stdin();
pty_process::pty_process()
    : child_pid_(-1),
      m_ptyMaster(-1),
      running_(false)
{

   ::string strMarker;

   strMarker = "__command_done_" + mathematics()->random_alphanumeric(32) + "__";

   m_straMarker.add(strMarker);
   m_straMarkerEcho.add("");
   m_straCommands.add("");

   m_strMarker = strMarker;

   //m_iaMarkerEcho.add(-1);

   m_flagsStdIn = -1;

}

pty_process::~pty_process() {
    __cleanup();
}

pty_process::pty_process(pty_process&& other) noexcept
    : child_pid_(other.child_pid_),
      m_ptyMaster(other.m_ptyMaster),
      running_(other.running_) {
    other.child_pid_ = -1;
    other.m_ptyMaster = -1;
    other.running_ = false;
}

pty_process& pty_process::operator=(pty_process&& other) noexcept {
    if (this != &other) {
        __cleanup();

        child_pid_ = other.child_pid_;
        m_ptyMaster = other.m_ptyMaster;
        running_ = other.running_;

        other.child_pid_ = -1;
        other.m_ptyMaster = -1;
        other.running_ = false;
    }
    return *this;
}


void pty_process::add_command_line(const ::scoped_string & scopedstrCommandLine)
{

   ::string strMarker;

   strMarker = "__command_done_" + mathematics()->random_alphanumeric(32) + "__";

   ::string strMarkerEcho;

   strMarkerEcho = "; echo \"" + strMarker + "\"";

   m_straMarker.add(strMarker);
   m_straMarkerEcho.add(strMarkerEcho);
   m_straCommands.add(scopedstrCommandLine);

}


bool pty_process::open()
{

   return open("bash -i");

}


bool pty_process::open(const ::scoped_string& scopedstrShell)
{

   ::string strShellCommand;

   strShellCommand = "echo \""+m_strMarker+"\";" + scopedstrShell;

   ::string_array_base args =
   {
      "/bin/sh", "-c", strShellCommand
   };

   return __open(args);

}

void pty_process::set_stdin_non_blocking()
{
   if (m_bSetNonBlockingIOforStdIn)
   {
      return;
   }
   m_bSetNonBlockingIOforStdIn = true;

   auto pfileStdIn = current_stdin();

   int iStdIn = fileno(pfileStdIn);

   m_flagsStdIn = fcntl(iStdIn, F_GETFL, 0);
   if (m_flagsStdIn == -1)
   {
      auto cerrornumber = c_error_number();
      auto estatus = cerrornumber.estatus();
      throw ::exception(estatus);
   }
   // Make stdin non-blocking
   if (fcntl(iStdIn, F_SETFL, m_flagsStdIn | O_NONBLOCK) == -1) {
      auto cerrornumber = c_error_number();

      auto estatus = cerrornumber.estatus();

      throw ::exception(estatus);
   }


}

void pty_process::poll_write_stdin()
{
char buf[4096];
::e_status estatus = success;

   sync_local_echo_from_child();

   auto pfileStdIn = current_stdin();
   int iStdIn = fileno(pfileStdIn);
               for (;;) {
               struct pollfd pfd = {
                  .fd = iStdIn,
                  .events = POLLIN | POLLHUP
              };

               int pr = poll(&pfd, 1, 10); // wait up to 10 ms
               if (pr == -1) {
                  throw ::exception(error_failed);
               }

               if (pr == 0) {
                  // timeout: no input yet
                  //printf("no data yet...\n");
                  //continue;
                  break;
               }

               if (pfd.revents & POLLIN) {
                  for (;;) {
                     ssize_t n = read(iStdIn, buf, sizeof(buf));

                     if (n > 0) {

                        ssize_t total;
                        // // Write to file
                        // total = 0;
                        // while (total < n) {
                        //    ssize_t w = write(outfd, buf + total, n - total);
                        //    if (w == -1) {
                        //       perror("write file");
                        //       close(outfd);
                        //       close(pipefd[1]);
                        //       waitpid(pid, NULL, 0);
                        //       return 1;
                        //    }
                        //    total += w;
                        // }

                        // Write same bytes to child stdin via pipe
                        total = 0;
                        while (total < n) {
                           ssize_t w = write_input(buf + total, n - total);
                           if (w == -1) {
                              //perror("write pipe");
                              //close(outfd);
                              //close(stdin_fds[1]);
                              //waitpid(pid, NULL, 0);
                              //return 1;
                              break;

                           }

                           total += w;

                        }
                     } else if (n == 0) {
                        // EOF
                        // printf("\nEOF\n");
                        // return 0;
                        break;
                     } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                           // no more data available right now
                           break;
                        } else if (errno == EINTR) {
                           // interrupted by signal, retry read
                           continue;
                        } else {
                           //perror("read");
                           //return 1;
                           throw ::exception(error_failed);
                        }
                     }
                  }
               }

               if (pfd.revents & POLLHUP) {
                  // input source closed
                  //printf("\nstdin closed\n");
                  //return 0;
                  break;
               }
            }

}

bool pty_process::__open(const ::string_array_base & straCommandLine)
{


    if (straCommandLine.is_empty()) {
        throw ::exception(error_bad_argument);
    }

    ::array_base < char * > cargs;
    cargs.reserve(straCommandLine.size() + 1);

    for (auto& s : straCommandLine) {
        cargs.add(const_cast<char*>(s.c_str()));
    }
    cargs.add(nullptr);

    return __spawn_internal(cargs.data());
}

bool pty_process::__spawn_internal(char* const argv[]) {
    __cleanup();

    // ------------------------------------------------------------
    // 1) Allocate PTY master
    // ------------------------------------------------------------
    int master = posix_openpt(O_RDWR | O_NOCTTY);
    if (master == -1) {
        return false;
    }

    if (grantpt(master) == -1) {
        close(master);
        return false;
    }

    if (unlockpt(master) == -1) {
        close(master);
        return false;
    }

    char* slave_name = ptsname(master);
    if (!slave_name) {
        close(master);
        return false;
    }

    // ------------------------------------------------------------
    // 2) Fork
    // ------------------------------------------------------------
    pid_t pid = fork();
    if (pid == -1) {
        close(master);
        return false;
    }

    if (pid == 0) {
        // ========================================================
        // CHILD
        // ========================================================

        close(master);

        // Become session leader
        if (setsid() == -1) {
            perror("setsid");
            _exit(127);
        }

        // Open PTY slave
        int slave = ::open(slave_name, O_RDWR);
        if (slave == -1) {
            perror("open slave pty");
            _exit(127);
        }

        // Make slave controlling terminal
        if (ioctl(slave, TIOCSCTTY, 0) == -1) {
            perror("ioctl(TIOCSCTTY)");
            close(slave);
            _exit(127);
        }

        // Optional terminal settings
        struct termios tio;
        if (tcgetattr(slave, &tio) == 0) {
            // Keep normal terminal defaults.
            // Customize here if needed.
            tcsetattr(slave, TCSANOW, &tio);
        }


        // Redirect stdin/stdout/stderr to PTY slave
        if (dup2(slave, STDIN_FILENO) == -1) {
            perror("dup2 stdin");
            close(slave);
            _exit(127);
        }
        if (dup2(slave, STDOUT_FILENO) == -1) {
            perror("dup2 stdout");
            close(slave);
            _exit(127);
        }
        if (dup2(slave, STDERR_FILENO) == -1) {
            perror("dup2 stderr");
            close(slave);
            _exit(127);
        }

        if (slave > STDERR_FILENO) {
            close(slave);
        }

        execvp(argv[0], argv);
        perror("execvp");
        _exit(127);
    }

    // ============================================================
    // PARENT
    // ============================================================
    child_pid_ = pid;
    m_ptyMaster = master;
    running_ = true;
    return true;
}

int pty_process::fd() const {
    return m_ptyMaster;
}

pid_t pty_process::pid() const {
    return child_pid_;
}

bool pty_process::is_running() {
    if (!running_ || child_pid_ <= 0) {
        return false;
    }

   m_iExitCode = wait(false);

   return running_;
}

int pty_process::wait(bool block) {
    if (child_pid_ <= 0) {
        errno = ECHILD;
        return m_iExitCode;
    }

    int status = 0;
    int options = block ? 0 : WNOHANG;
    pid_t r = waitpid(child_pid_, &status, options);

    if (r == 0) {
        return -1; // nonblocking and still running
    }
    if (r == -1) {
        return -1;
    }

   if (r == child_pid_)
   {
      running_ = false;
      child_pid_= -1;
      if (WIFEXITED(status))
      {
         m_iExitCode = WEXITSTATUS(status);
      }
      else if(WIFSIGNALED(status))
      {
         m_iExitCode = 128 + WTERMSIG(status);
      }
   }
    return m_iExitCode;
}

bool pty_process::terminate(int sig) {
    if (child_pid_ <= 0) {
        errno = ECHILD;
        return false;
    }
    return ::kill(child_pid_, sig) == 0;
}

bool pty_process::kill_force() {
    return terminate(SIGKILL);
}

memsize pty_process::write_input(const void* data, memsize size) {
    if (m_ptyMaster < 0) {
        errno = EBADF;
        return -1;
    }
    return write(m_ptyMaster, data, size);
}

memsize pty_process::write_input(const scoped_string& s) {
    return write_input(s.data(), s.size());
}

memsize pty_process::read_output(void* buf, memsize size) {
    if (m_ptyMaster < 0) {
        errno = EBADF;
        return -1;
    }
    return read(m_ptyMaster, buf, size);
}

memory pty_process::read_available() {
    memory out;
    if (m_ptyMaster < 0) {
        errno = EBADF;
        return out;
    }

    char buf[4096];

    while (true) {
        auto n = read(m_ptyMaster, buf, sizeof(buf));
        if (n > 0) {
            out.append(buf, n);
        } else if (n == 0) {
            break;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }
            if (errno == EINTR) {
                continue;
            }
            if (errno == EIO) {
                // Common PTY end-of-stream condition
                break;
            }
            break;
        }
    }

    return out;
}

void pty_process::close_fd() {
    close_if_valid(m_ptyMaster);

   if (m_bSetNonBlockingIOforStdIn)
   {
      m_bSetNonBlockingIOforStdIn = false;
      if (m_flagsStdIn >= 0)
      {
         auto pfileStdIn = current_stdin();
         int iStdIn = fileno(pfileStdIn);

         if (fcntl(iStdIn, F_SETFL, m_flagsStdIn) == -1) {
            ::information("error restoring stdin flags");
         }
      }
   }

}

bool pty_process::set_nonblocking(bool enabled) {
    if (m_ptyMaster < 0) {
        errno = EBADF;
        return false;
    }
    return __set_fd_nonblocking_impl(m_ptyMaster, enabled);
}

bool pty_process::__set_fd_nonblocking_impl(int fd, bool enabled) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return false;
    }

    if (enabled) {
        flags |= O_NONBLOCK;
    } else {
        flags &= ~O_NONBLOCK;
    }

    return fcntl(fd, F_SETFL, flags) != -1;
}


bool pty_process::stdin_echo_enabled() const {

   auto pfileStdIn = current_stdin();
   int iStdIn = fileno(pfileStdIn);

   if (!isatty(iStdIn)) {
      // If stdin isn't a terminal, treat as "not echoing"
      return false;
   }

   struct termios tio;
   if (tcgetattr(iStdIn, &tio) == -1) {
      return false;
   }

   return (tio.c_lflag & ECHO) != 0;
}


memsize pty_process::capture_stdin_once(bool forward_to_child,
                                       ::string* captured_visible,
                                       ::string* captured_hidden) {
   char buf[4096];

   auto pfileStdIn = current_stdin();
   int iStdIn = fileno(pfileStdIn);

   ssize_t n = read(iStdIn, buf, sizeof(buf));
   if (n <= 0) {
      return n; // 0 = EOF, -1 = error/EAGAIN/etc
   }

   bool echo_on = stdin_echo_enabled();

   // If echo is enabled, this is probably normal visible typing
   if (echo_on) {
      if (captured_visible) {
         captured_visible->append(buf, n);
      }
   } else {
      // Echo disabled -> likely password / sensitive input
      if (captured_hidden) {
         captured_hidden->append(buf, n);
      }
   }

   if (forward_to_child) {
      ssize_t total = 0;
      while (total < n) {
         ssize_t w = write_input(buf + total, static_cast<size_t>(n - total));
         if (w == -1) {
            if (errno == EINTR) {
               continue;
            }
            return -1;
         }
         total += w;
      }
   }

   return n;
}

::string pty_process::capture_stdin_available(bool forward_to_child,
                                                bool* echo_was_enabled) {
   ::string visible;
   ::string hidden;

   bool echo_on = stdin_echo_enabled();
   if (echo_was_enabled) {
      *echo_was_enabled = echo_on;
   }

   while (true) {
      ssize_t n = capture_stdin_once(forward_to_child, &visible, &hidden);

      if (n > 0) {
         continue;
      }

      if (n == 0) {
         // EOF
         break;
      }

      if (errno == EAGAIN || errno == EWOULDBLOCK) {
         break;
      }

      if (errno == EINTR) {
         continue;
      }

      break;
   }

   // Intentionally return only visible input.
   // Hidden/password-like input is NOT returned.
   return visible;
}

void pty_process::__cleanup() {
    close_fd();

    if (running_ && child_pid_ > 0) {
        int status = 0;
        waitpid(child_pid_, &status, WNOHANG);
    }

    child_pid_ = -1;
    running_ = false;
}



void pty_process::begin_terminal_bridge()
{

   auto pfileStdIn = current_stdin();
   int iStdIn = fileno(pfileStdIn);

   if (!isatty(iStdIn)) {
      return;
   }

   if (!m_bTerminalModeSaved) {
      if (tcgetattr(iStdIn, &m_tioOriginal) == -1) {
         throw ::exception(error_failed);
      }
      m_bTerminalModeSaved = true;
   }

   termios tio = m_tioOriginal;

   // Use raw-ish mode so local terminal stops doing its own echo/line buffering
   tio.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
   tio.c_oflag &= ~(OPOST);
   tio.c_cflag |= (CS8);
   tio.c_lflag &= ~(ICANON | IEXTEN | ISIG | ECHO);

   tio.c_cc[VMIN] = 1;
   tio.c_cc[VTIME] = 0;

   if (tcsetattr(iStdIn, TCSAFLUSH, &tio) == -1) {
      throw ::exception(error_failed);
   }

   m_bLocalRawMode = true;
}

void pty_process::end_terminal_bridge()
{
   if (m_bTerminalModeSaved) {

      auto pfileStdIn = current_stdin();
      int iStdIn = fileno(pfileStdIn);

      tcsetattr(iStdIn, TCSAFLUSH, &m_tioOriginal);
   }

   m_bLocalRawMode = false;
}

bool pty_process::sync_local_echo_from_child()
{
   auto pfileStdIn = current_stdin();
   int iStdIn = fileno(pfileStdIn);

   if (!isatty(iStdIn)) {
      return false;
   }

   if (m_ptyMaster < 0) {
      return false;
   }

   termios childTio{};
   if (tcgetattr(m_ptyMaster, &childTio) == -1) {
      return false;
   }

   termios localTio{};
   if (tcgetattr(iStdIn, &localTio) == -1) {
      return false;
   }

   bool childEcho = (childTio.c_lflag & ECHO) != 0;
   bool localEcho = (localTio.c_lflag & ECHO) != 0;

   if (childEcho != localEcho) {
      if (childEcho) {
         localTio.c_lflag |= ECHO;
      } else {
         localTio.c_lflag &= ~ECHO;
      }

      if (tcsetattr(iStdIn, TCSANOW, &localTio) == -1) {
         return false;
      }
   }

   return true;
}



void pty_process::run()
{

   set_stdin_non_blocking();

begin_terminal_bridge();

   //::memory captured;
   //bool sent_commands = false;

   while (true) {
      // struct pollfd pfd{};
      // pfd.fd = proc.fd();
      // pfd.events = POLLIN | POLLHUP;
      //
      // int pr = poll(&pfd, 1, 500);
      // if (pr == -1) {
      //    if (errno == EINTR) continue;
      //    throw ::exception(error_failed, "poll");
      //    break;
      // }
      //
      // if (pr == 0) {
      //    continue;
      // }
      //
      // if (pfd.revents & POLLIN) {
         poll_read_stdout();
         // auto chunk = proc.read_available();
         // if (chunk.has_data()) {
         //    captured += chunk;
         //    fwrite(chunk.data(), 1, chunk.size(), stdout);
         //    //std::cout << chunk << std::flush;
         // }

     //    if (!sent_commands) {

      if (m_strMarkerEcho.is_empty()
         && m_strMarker.is_empty())
      {
         if (m_iCurrentCommand < m_straCommands.size())
         {
            m_strCommand =m_straCommands[m_iCurrentCommand];
            m_strMarkerEcho = m_straMarkerEcho[m_iCurrentCommand];
            m_strMarker =m_straMarker[m_iCurrentCommand];
         //      m_iCurrentCommand++;

            auto pszCommand = m_strCommand.c_str();
            auto pszMarkerEcho = m_strMarkerEcho.c_str();
            auto pszMarker = m_strMarker.c_str();


            ::string strOutputCommand =m_strCommand + m_strMarkerEcho + "\n";

            auto pszOutputCommand = strOutputCommand.c_str();

               //str.find_replace("!", "\\!");
               write_input(strOutputCommand);

            }
       //     sent_commands = true;
         }
         poll_write_stdin();
      //}
      //
      // if (pfd.revents & POLLHUP) {
      //    break;
      // }
      //
       if (!is_running())
          {
          break;
       }
   }

   poll_read_stdout();

   end_terminal_bridge();
   // Final drain
   //captured += read_available();

   m_iExitCode = wait(true);

}

   void pty_process::on_child_raw_stdout(const void * p, memsize s)
   {

   auto psz = (const char*)p;

      m_memoryBuffer.append(p, s);

      while (m_memoryBuffer.has_data()
         && (m_strMarkerEcho.has_character() || m_strMarker.has_character()))
      {



         if (m_strMarkerEcho.has_character())
         {

            int iMarkerEchoSize = m_strMarkerEcho.size();

            auto pfind = m_memoryBuffer.find(m_strMarkerEcho);

            if (pfind)
            {

               auto iPosition = pfind - m_memoryBuffer.data();

               m_strMarkerEcho.clear();

               if (m_strMarker.is_empty())
               {

                  throw ::pty_process_exception(error_wrong_state, "m_strMarker.is_empty()");

               }

               on_child_stdout(m_memoryBuffer.data(), iPosition);

               m_memoryBuffer.delete_begin(iPosition + iMarkerEchoSize);

            }
            else
            {

               int iReserve = iMarkerEchoSize;

               int iExtra = m_memoryBuffer.size();

               int iCheck = minimum(iExtra, iReserve);

               int i = iCheck - 1;

               if (i < 0)
               {

                  i = 0;

               }

               for (; i >= 1; i--)
               {

                  ::string strTail((const char *) (m_memoryBuffer.m_end - i), i);

                  if (m_strMarkerEcho.begins(strTail))
                  {

                     break;

                  }

               }

               on_child_stdout(m_memoryBuffer.data(), m_memoryBuffer.size() - i);

               m_memoryBuffer.delete_begin(m_memoryBuffer.size() - i);

               //;//m_iLastStdOut = m_memoryOutputRaw.size() - i;

            }

         }
         else if (m_strMarker.has_character())
         {

            int iMarkerSize = m_strMarker.size();

            auto pfind = m_memoryBuffer.find(m_strMarker);

            if (pfind)
            {

               auto iPosition = pfind - m_memoryBuffer.data();

               if (m_strMarkerEcho.has_character())
               {
                  throw ::pty_process_exception(error_wrong_state, "m_strMarkerEcho.has_character()");
               }

               m_iCurrentCommand++;

               m_strMarker.clear();

               on_child_stdout(m_memoryBuffer, iPosition);

               m_memoryBuffer.delete_begin(iPosition + iMarkerSize);

            }
            else
            {

               int iReserve = iMarkerSize;

               int iExtra = m_memoryBuffer.size();

               int iCheck = minimum(iExtra, iReserve);

               int i = iCheck - 1;

               if (i < 0)
               {

                  i = 0;

               }

               for (; i >= 1; i--)
               {

                  ::string strTail((const char *) (m_memoryBuffer.m_end - i), i);

                  if (m_strMarker.begins(strTail))
                  {

                     break;

                  }

               }

               on_child_stdout(m_memoryBuffer.data(), m_memoryBuffer.size() - i);

               m_memoryBuffer.delete_begin(m_memoryBuffer.size() - i);


            }

         }

      }

   if (m_memoryBuffer.has_data() && m_strMarkerEcho.is_empty() && m_strMarker.is_empty())
   {

      on_child_stdout(m_memoryBuffer.data(), m_memoryBuffer.size());

      m_memoryBuffer.clear();

   }


   }


   void pty_process::on_child_stdout(const void * p, memsize s)
   {
      auto buf = (char *)p;
      auto n = s;
      // show child terminal output live
      ssize_t total = 0;
      while (total < n)
      {

         ssize_t w = write(STDOUT_FILENO, buf + total, n - total);
         if (w == -1)
         {
            if (errno == EINTR)
               continue;
            break;
         }
         total += w;
      }

   }

void pty_process::poll_read_stdout()
{
   char buf[4096];

   for (;;)
   {
      struct pollfd pfd{};
      pfd.fd = m_ptyMaster;
      pfd.events = POLLIN | POLLHUP;

      int pr = poll(&pfd, 1, 0);
      if (pr == -1)
      {
         if (errno == EINTR)
            continue;

         throw ::exception(error_failed);
      }

      if (pr == 0)
      {
         break;
      }

      if (pfd.revents & POLLIN)
      {
         for (;;)
         {
            ssize_t n = read(m_ptyMaster, buf, sizeof(buf));

            if (n > 0)
            {
               on_child_raw_stdout(buf, n);
            }
            else if (n == 0)
            {
               return;
            }
            else
            {
               if (errno == EAGAIN || errno == EWOULDBLOCK)
                  break;
               if (errno == EINTR)
                  continue;
               if (errno == EIO) // common PTY end
                  return;

               throw ::exception(error_failed);
            }
         }
      }

      if (pfd.revents & POLLHUP)
      {
         return;
      }
   }
}