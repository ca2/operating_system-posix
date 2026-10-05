#include "accessibility_gtk3/automation.h"
#include "app-core/ambient/mate_terminal_automation.h"
#include <stdio.h>
#include "acme/parallelization/_.h"
#include "acme/platform/system.h"

#include <unistd.h>
#include <fcntl.h>
#include <gio/gio.h>

namespace
{
   using namespace accessibility::automation;
   void dump(const element_pointer &item, int depth, int &budget)
   {
      if (!item || depth > 16 || --budget < 0) return;
      ::string indentation;
      for (int i = 0; i < depth; ++i) indentation += "  ";
      printf("%s%d %s\n", indentation.c_str(), static_cast<int>(item->type()), item->name().c_str());
      if (item->type() != role::terminal)
         for (auto &child : item->children()) dump(child, depth + 1, budget);
   }
}
int main(int argc, char **argv, char **envp)
{
   setvbuf(stdout, nullptr, _IOLBF, 0);
   fprintf(stderr, "MATE Terminal accessibility helper started\n");
   // Follow ca2's console entry-point bootstrap before any ca2 strings,
   // particles or referencing-debugging allocations. The system lives until
   // process exit, as in acme/inline/console/main_executable.inl.
   fprintf(stderr, "MATE Terminal accessibility: initializing Acme runtime\n");
   auto psystem = new ::platform::system();
   psystem->initialize_system(argc, argv, envp);
   psystem->m_bConsole = true;
   fprintf(stderr, "MATE Terminal accessibility: Acme runtime ready\n");
   if ((argc != 2 && argc != 3) || !argv[1][0]
       || (argc == 3 && ::string(argv[1]) != "--profile-id"))
   {
      fprintf(stderr, "Usage: accessibility_atspi_mate_terminal PROFILE-NAME | --profile-id ID | --dump\n");
      return 2;
   }
   try
   {
      ::string profile_name = argv[1];
      if (argc == 3)
      {
         ::string id = argv[2];
         if (id.is_empty() || id.contains("/") || id.contains(".."))
            throw ::exception(error_failed, "Invalid MATE Terminal profile ID");
         auto path = "/org/mate/terminal/profiles/" + id + "/";
         auto settings = g_settings_new_with_path("org.mate.terminal.profile", path.c_str());
         char *name = g_settings_get_string(settings, "visible-name");
         profile_name = name ? name : "";
         g_free(name); g_object_unref(settings);
         if (profile_name.is_empty()) throw ::exception(error_failed, "Terminal profile has no visible name");
      }
      // Serialize automation from multiple Ambient instances. Closing this
      // descriptor releases the lock even if this helper fails.
      const char *home = getenv("HOME");
      if (!home) throw ::exception(error_failed, "HOME is not set");
      auto lock_path = ::string(home) + "/.ambient-mate-terminal-accessibility.lock";
      int lock = open(lock_path.c_str(), O_CREAT | O_RDWR, 0600);
      struct flock request = {};
      request.l_type = F_WRLCK; request.l_whence = SEEK_SET;
      if (lock < 0 || fcntl(lock, F_SETLK, &request) < 0)
         throw ::exception(error_failed, "Terminal accessibility automation is already running or cannot lock");
      fprintf(stderr, "MATE Terminal accessibility: connecting to AT-SPI\n");
      ::pointer<session> automation = allocateø session(accessibility_gtk3::desktop());
      int windows = 0, tabs = 0, failures = 0, applications = 0;
      auto timeStart = ::time::now();
      auto settle = [&]
      {
         if (timeStart.elapsed() > 30_s)
            throw ::exception(error_failed, "Terminal automation timed out");
         ::preempt(100_ms);
      };
      auto terminal_applications = automation->applications(
         [](element &app) { return app.executable_name() == "mate-terminal"; });
      fprintf(stderr, "MATE Terminal accessibility: found %lld terminal applications\n",
         static_cast<long long>(terminal_applications.get_count()));
      for (auto &app : terminal_applications)
      {
         if (timeStart.elapsed() > 30_s)
            throw ::exception(error_failed, "Terminal automation timed out");
         try
         {
            ++applications;
            if (::string(argv[1]) == "--dump") { int budget = 4096; dump(app, 0, budget); continue; }
            for (auto &window : automation->windows(app))
            {
               if (timeStart.elapsed() > 30_s)
                  throw ::exception(error_failed, "Terminal automation timed out");
               if (find_all(window, [](element &e) { return e.type() == role::terminal; }).is_empty()) continue;
               try
               {
                  tabs += app_core_ambient::mate_terminal_automation::apply_window(window, profile_name, settle);
                  ++windows;
               }
               catch (const ::exception &e) { ++failures; fprintf(stderr, "Window: %s\n", e.get_message().c_str()); }
            }
         }
         catch (const ::exception &e) { ++failures; fprintf(stderr, "Application: %s\n", e.get_message().c_str()); }
      }
      close(lock);
      if (!applications)
      {
         fprintf(stderr, "No MATE Terminal registered with AT-SPI; enable org.mate.interface accessibility, then reopen MATE Terminal\n");
         return 1;
      }
      printf("MATE Terminal accessibility: %d windows, %d tabs, %d failures\n", windows, tabs, failures);
      return failures ? 1 : 0;
   }
   catch (const ::exception &e) { fprintf(stderr, "%s\n", e.get_message().c_str()); return 1; }
}
