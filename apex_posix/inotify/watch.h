#pragma once


#include "acme/filesystem/watcher/watch.h"
#if defined(FREEBSD)
#include <sys/time.h>
#endif

namespace inotify
{


   class watcher;


   class watch :
      virtual public ::file::watch
   {
   public:

      i32                        m_iFd;
      struct timeval             m_timevalTimeOut;
      fd_set                     m_fdset;
      int                        m_watchdescriptor;
      //bool                 m_bOwn;


      watch();
      ~watch() override;


      void on_initialize_particle() override;


      bool open(const ::file::path & pathFolder, bool bRecursive) override;


      bool file_watch_step() override;


   };


} // namespace inotify



