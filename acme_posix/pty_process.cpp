//
// Created by camilo on 3/26/26.
//
#include "platform.h"
#include "pty_process.h"
#include "acme/operating_system/posix/_.h"
#include "acme/prototype/mathematics/mathematics.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <string_view>

#include <unistd.h>
#include <errno.h>


pty_process_exception::pty_process_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage) :
::exception(estatus, scopedstrMessage)
{


}


pty_process_exception::~pty_process_exception()
{


}


namespace
{

   void close_if_valid(int& fd)
   {

      if (fd >= 0)
      {

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
   m_straCommands.add("");

   m_strMarker = strMarker;

   m_flagsStdIn = -1;

}


pty_process::~pty_process()
{

   __cleanup();

}


pty_process::pty_process(pty_process&& other) noexcept
    : child_pid_(other.child_pid_),
      m_ptyMaster(other.m_ptyMaster),
      running_(other.running_)
{

   other.child_pid_ = -1;
   other.m_ptyMaster = -1;
   other.running_ = false;

}


pty_process& pty_process::operator=(pty_process&& other) noexcept
{

   if (this != &other)
   {

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

   auto strToken = mathematics()->random_alphanumeric(32);
   ::string strCommand(scopedstrCommandLine);
   strCommand.replace_with("'\\''", "'");
   // Send one input line even when the script contains literal newlines.
   strCommand.replace_with("'$'\\n''", "\n");

   // The full marker exists only in the output of printf, even with terminal echo on.
   m_straMarker.add("__command_done_" + strToken + "__");
   m_straCommands.add("eval '" + strCommand +
      "'; __exit_status=$?; printf '%s%s__' '__command_done_' '" +
      strToken + "'; (exit \"$__exit_status\")");
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

      auto cerrno = c_errno();

      auto estatus = cerrno.estatus();

      throw ::exception(estatus);

   }

   // Make stdin non-blocking
   if (fcntl(iStdIn, F_SETFL, m_flagsStdIn | O_NONBLOCK) == -1)
   {

      auto cerrno = c_errno();

      auto estatus = cerrno.estatus();

      throw ::exception(estatus);

   }

}


void pty_process::poll_write_stdin()
{

   char buf[4096];

   sync_local_echo_from_child();

   auto pfileStdIn = current_stdin();

   int iStdIn = fileno(pfileStdIn);

   for (;;)
   {

      struct pollfd pfd =
      {
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

   if (straCommandLine.is_empty())
   {

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

   ::string strPendingInput;
   memsize iWritten = 0;
   bool bExitQueued = false;

   while (is_running())
   {
      poll_read_stdout();

      if (strPendingInput.is_empty() && m_strMarker.is_empty() && !bExitQueued)
      {
         if (m_iCurrentCommand < m_straCommands.size())
         {
            m_strMarker = m_straMarker[m_iCurrentCommand];
            strPendingInput = m_straCommands[m_iCurrentCommand] + "\n";
         }
         else if (m_straCommands.size() > 1)
         {
            strPendingInput = "exit $?\n";
            bExitQueued = true;
         }
      }

      if (strPendingInput.has_character())
      {
         auto n = write_input(strPendingInput.data() + iWritten, strPendingInput.size() - iWritten);

         if (n > 0)
         {
            iWritten += n;
            if (iWritten == strPendingInput.size())
            {
               strPendingInput.clear();
               iWritten = 0;
            }
         }
         else if (n < 0 && errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK)
         {
            if (errno == EIO && !is_running())
            {
               break;
            }

            end_terminal_bridge();
            throw ::exception(error_failed, "Could not send command to the inner shell");
         }
      }

      if (strPendingInput.is_empty() && !bExitQueued)
      {
         poll_write_stdin();
      }
      else
      {
         // Avoid spinning while a nonblocking write or shell exit is pending.
         pollfd pfd{m_ptyMaster, POLLIN, 0};
         if (strPendingInput.has_character())
         {
            pfd.events |= POLLOUT;
         }
         poll(&pfd, 1, 10);
      }
   }

   poll_read_stdout();
   if (m_strPendingCommandEcho.has_character() && !m_bDiscardingCommandEcho)
   {
      process_child_stdout(m_strPendingCommandEcho.data(), m_strPendingCommandEcho.size());
   }
   m_strPendingCommandEcho.clear();
   m_bDiscardingCommandEcho = false;
   m_bOutputOnCurrentLine = false;

   if (m_memoryBuffer.has_data())
   {
      on_child_stdout(m_memoryBuffer.data(), m_memoryBuffer.size());
      m_memoryBuffer.clear();
   }

   end_terminal_bridge();
   m_iExitCode = wait(true);

}


void pty_process::on_child_raw_stdout(const void * p, memsize s)
{
   m_strPendingCommandEcho.append(static_cast<const char *>(p), s);
   std::string_view output(m_strPendingCommandEcho.data(), m_strPendingCommandEcho.size());

   auto show = [this](std::string_view visible)
   {
      if (!visible.empty())
      {
         process_child_stdout(visible.data(), visible.size());
         m_bOutputOnCurrentLine = visible.back() != '\n';
      }
   };

   while (!output.empty())
   {
      if (m_bDiscardingCommandEcho)
      {
         const auto newline = output.find('\n');
         if (newline == std::string_view::npos)
         {
            // Keep a trailing CR in case the next read starts with LF.
            output.remove_prefix(output.size() - (output.back() == '\r' ? 1 : 0));
            break;
         }

         if (m_bOutputOnCurrentLine)
         {
            const auto ending = newline > 0 && output[newline - 1] == '\r' ? newline - 1 : newline;
            show(output.substr(ending, newline - ending + 1));
         }
         output.remove_prefix(newline + 1);
         m_bDiscardingCommandEcho = false;
         continue;
      }

      // A shell prompt can precede the echo. Match the queued text before
      // parsing completion markers, which can also occur within the echo.
      auto match = output.size();
      bool complete = false;
      for (const auto & command : m_straCommands)
      {
         if (command.is_empty())
         {
            continue;
         }

         const std::string_view echo(command.data(), command.size());
         for (auto pos = output.find(echo.front()); pos < match; pos = output.find(echo.front(), pos + 1))
         {
            const auto suffix = output.substr(pos);
            if (suffix.starts_with(echo) || echo.starts_with(suffix))
            {
               match = pos;
               complete = suffix.size() >= echo.size();
               break;
            }
         }
      }

      show(output.substr(0, match));
      output.remove_prefix(match);
      if (!complete)
      {
         break;
      }
      m_bDiscardingCommandEcho = true;
   }

   if (output.empty())
   {
      m_strPendingCommandEcho.clear();
   }
   else
   {
      m_strPendingCommandEcho = ::string(output.data(), output.size());
   }
}


void pty_process::process_child_stdout(const void * p, memsize s)
{

   m_memoryBuffer.append(p, s);

   if (m_strMarker.has_character())
   {
      auto pfind = m_memoryBuffer.find(m_strMarker);

      if (!pfind)
      {
         // Retain only a possible marker prefix across PTY reads.
         auto iKeep = minimum(m_memoryBuffer.size(), m_strMarker.size() - 1);
         while (iKeep > 0 && !m_strMarker.begins(
            ::string((const char *) (m_memoryBuffer.m_end - iKeep), iKeep)))
         {
            --iKeep;
         }

         auto iOutput = m_memoryBuffer.size() - iKeep;
         on_child_stdout(m_memoryBuffer.data(), iOutput);
         m_memoryBuffer.delete_begin(iOutput);
         return;
      }

      auto iPosition = pfind - m_memoryBuffer.data();
      on_child_stdout(m_memoryBuffer.data(), iPosition);
      m_memoryBuffer.delete_begin(iPosition + m_strMarker.size());
      m_strMarker.clear();
      ++m_iCurrentCommand;
   }

   if (m_memoryBuffer.has_data())
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
